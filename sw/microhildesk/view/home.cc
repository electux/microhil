////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// home.cc
/// Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
///
/// microhildesk is free software: you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by the
/// Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// microhildesk is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
/// See the GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program. If not, see <http://www.gnu.org/licenses/>.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <gtkmm/cssprovider.h>
#include <gtkmm/stylecontext.h>
#include <model/model.h>
#include <view/home.h>

namespace {
    constexpr std::string_view cHomeTitle{"microhildesk"};
    constexpr int cHomeWidth{600};
    constexpr int cHomeHeight{520};
    constexpr std::string_view cTextViewCss{
        "textview text { background-color: black; color: white; }"
    };
    constexpr int cWidgetMargin{10};
    constexpr int cScrolledWindowHeight{250};
    constexpr std::string_view cNewline{"\n"};
} // namespace

using namespace Electux::App::View;
using namespace Electux::App::Model;
using namespace Electux::App::Model::Channel;

AppHome::AppHome() {
    set_title(cHomeTitle.data());
    set_default_size(cHomeWidth, cHomeHeight);
    set_resizable(false);
    set_show_menubar(true);
    m_boxRoot.set_orientation(Gtk::Orientation::VERTICAL);
    m_boxChannels.set_orientation(Gtk::Orientation::HORIZONTAL);
    m_textView.set_editable(false);
    m_textView.set_cursor_visible(false);
    m_textView.set_wrap_mode(Gtk::WrapMode::WORD_CHAR);
    m_textView.set_monospace(true);
    m_textView.set_left_margin(cWidgetMargin);
    m_textView.set_right_margin(cWidgetMargin);
    m_textView.set_top_margin(cWidgetMargin);
    m_textView.set_bottom_margin(cWidgetMargin);

    auto css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data(cTextViewCss.data());
    m_textView.get_style_context()->add_provider(
        css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    m_scrolled_window.set_child(m_textView);
    m_scrolled_window.set_policy(
        Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC
    );
    m_scrolled_window.set_vexpand(true);
    m_scrolled_window.set_hexpand(true);
    m_scrolled_window.set_size_request(-1, cScrolledWindowHeight);
    m_scrolled_window.set_margin_start(cWidgetMargin);
    m_scrolled_window.set_margin_end(cWidgetMargin);
    m_scrolled_window.set_margin_bottom(cWidgetMargin);

    m_dispatcher.connect(
        sigc::mem_fun(*this, &AppHome::onDataReceivedDispatcher)
    );
    m_connectionDispatcher.connect([this]() {
        m_boxChannels.set_sensitive(
            m_latestConnectionState.load() == Worker::ConnectionState::Ready
        );
    });

    m_boxRoot.append(m_boxChannels);
    m_boxRoot.append(m_scrolled_window);
    set_child(m_boxRoot);

    for (ssize_t i = 0; i < cNumOfChannels; i++) {
        auto widget = std::make_unique<ChannelWidget>(static_cast<size_t>(i));

        widget->signal_changed().connect(
            sigc::bind(
                sigc::mem_fun(*this, &AppHome::onChannelChanged),
                static_cast<size_t>(i)
            )
        );

        m_boxChannels.append(*widget);
        m_channelWidgets.push_back(std::move(widget));
    }
    m_boxChannels.set_sensitive(false);
}

SigSettings AppHome::controlChanged() { return m_controlSignal; }

SigChannelChanged AppHome::channelChanged() { return m_channelSignal; }

void AppHome::setControlSetup(const SettingsSetup &setup) {
    m_setup = setup;
    updateUiData();
}

void AppHome::getUiData() {
    if (!m_setup.m_config) {
        return;
    }
    auto &config = *m_setup.m_config;
    for (size_t i = 0; i < cNumOfChannels; i++) {
        config.setChannelState(i, m_channelWidgets[i]->getState());
    }
    m_controlSignal.emit(m_setup);
}

void AppHome::updateUiData() {
    if (!m_setup.m_config) {
        return;
    }

    const auto &config = *m_setup.m_config;
    for (size_t i = 0; i < cNumOfChannels; i++) {
        m_channelWidgets[i]->updateState(config.getChannelState(i));
    }
}

void AppHome::onChannelChanged(size_t index) {
    if (index < m_channelWidgets.size()) {
        auto state = m_channelWidgets[index]->getState();
        if (m_setup.m_config) {
            m_setup.m_config->setChannelState(index, state);
        }
        m_channelSignal.emit(index, state);
    }
}

void AppHome::show() { present(); }

void AppHome::hide() { set_visible(false); }

void AppHome::connect_close_request(const sigc::slot<bool()> &slot) {
    signal_close_request().connect(slot, false);
}

Gtk::Window &AppHome::getGtkWindow() { return *this; }

void AppHome::postData(const std::string &data) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_incomingDataQueue.push(data);
    m_dispatcher.emit();
}

void AppHome::setConnectionState(Worker::ConnectionState state) {
    m_latestConnectionState = state;
    m_connectionDispatcher.emit();
}

void AppHome::onDataReceivedDispatcher() {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto buffer = m_textView.get_buffer();

    while (!m_incomingDataQueue.empty()) {
        std::string data = m_incomingDataQueue.front();
        buffer->insert(buffer->end(), data);
        buffer->insert(buffer->end(), cNewline.data());
        m_incomingDataQueue.pop();
    }

    auto vadj = m_scrolled_window.get_vadjustment();
    if (vadj) {
        double max_val =
            std::max(0.0, vadj->get_upper() - vadj->get_page_size());
        vadj->set_value(max_val);
    }
}

void AppHome::clearConsole() {
    auto buffer = m_textView.get_buffer();

    if (buffer) {
        buffer->set_text("");
    }
}
