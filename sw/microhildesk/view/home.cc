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

#include <model/model.h>
#include <view/home.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/stylecontext.h>

namespace {
    constexpr std::string_view cHomeTitle{"microhildesk"};
    constexpr int cHomeWidth{600};
    constexpr int cHomeHeight{520};
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
    m_textView.set_wrap_mode(Gtk::WrapMode::CHAR);
    m_textView.set_monospace(true);
    m_textView.set_left_margin(10);
    m_textView.set_right_margin(10);
    m_textView.set_top_margin(10);
    m_textView.set_bottom_margin(10);

    auto css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data("textview text { background-color: black; color: white; }");
    m_textView.get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    m_scrolled_window.set_child(m_textView);
    m_scrolled_window.set_vexpand(true);
    m_scrolled_window.set_hexpand(true);
    m_scrolled_window.set_size_request(-1, 250);
    m_scrolled_window.set_margin_start(10);
    m_scrolled_window.set_margin_end(10);
    m_scrolled_window.set_margin_bottom(10);

    m_dispatcher.connect(
        sigc::mem_fun(*this, &AppHome::onDataReceivedDispatcher)
    );

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
}

SigSettings AppHome::controlChanged() { return m_controlSignal; }

void AppHome::setControlSetup(const SettingsSetup &setup) { m_setup = setup; }

void AppHome::updateUiData() {
    const auto &config = *m_setup.m_config;

    for (ssize_t i = 0; i < cNumOfChannels; i++) {
        m_channelWidgets[static_cast<size_t>(i)]->updateState(
            config.getChannelState(static_cast<size_t>(i))
        );
    }
}

void AppHome::getUiData() {
    auto &config = *m_setup.m_config;

    for (ssize_t i = 0; i < cNumOfChannels; i++) {
        config.setChannelState(
            static_cast<size_t>(i),
            m_channelWidgets[static_cast<size_t>(i)]->getState()
        );
    }

    m_controlSignal.emit(m_setup);
}

void AppHome::onChannelChanged(size_t index) {
    auto &config = *m_setup.m_config;
    config.setChannelState(index, m_channelWidgets[index]->getState());
    m_controlSignal.emit(m_setup);
}

void AppHome::show() { set_visible(true); }

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

void AppHome::onDataReceivedDispatcher() {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto buffer = m_textView.get_buffer();

    while (!m_incomingDataQueue.empty()) {
        std::string data = m_incomingDataQueue.front();
        buffer->insert(buffer->end(), data);
        buffer->insert(buffer->end(), "\n");

        m_incomingDataQueue.pop();
    }
}
