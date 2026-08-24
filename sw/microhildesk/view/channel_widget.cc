////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// channel_widget.cc
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
#include <format>
#include <view/channel_widget.h>

namespace {
    constexpr std::string_view cChannelEnableLabel{"Enable Channel #"};
} // namespace

using namespace Electux::App::View;

ChannelWidget::ChannelWidget(size_t index)
    : Gtk::Frame(), m_index(index),
      m_mainBox(Gtk::Orientation::VERTICAL, 5),
      m_enableBtn(std::format("{} {}", cChannelEnableLabel.data(), index)),
      m_pageToggle(index),
      m_pageTimer(index),
      m_pagePulse(index),
      m_pageBlink(index) {
    set_margin(10);
    m_mainBox.set_margin(10);
    m_mainBox.set_vexpand(true);

    m_mainBox.append(m_enableBtn);
    m_enableBtn.signal_toggled().connect(
        sigc::mem_fun(*this, &ChannelWidget::onEnableToggled)
    );

    // Dynamically populate mode combo box from descriptors
    for (const auto &desc : Model::Channel::cChannelModeDescriptors) {
        m_modeCombo.append(desc.displayName.data());
    }
    m_modeCombo.set_active(0);
    m_mainBox.append(m_modeCombo);
    m_modeCombo.signal_changed().connect(
        sigc::mem_fun(*this, &ChannelWidget::onModeChanged)
    );

    // Configure stack properties
    m_stack.set_transition_type(Gtk::StackTransitionType::CROSSFADE);
    m_stack.set_transition_duration(100);
    m_stack.set_hhomogeneous(true);
    m_stack.set_vhomogeneous(true);
    m_stack.set_vexpand(true);

    // Add concrete mode pages to stack using overloaded add(widget, name)
    m_stack.add(m_pageToggle, std::string(Model::Channel::toConfigString(Model::Channel::ChannelMode::Toggle)));
    m_stack.add(m_pageTimer, std::string(Model::Channel::toConfigString(Model::Channel::ChannelMode::Timer)));
    m_stack.add(m_pagePulse, std::string(Model::Channel::toConfigString(Model::Channel::ChannelMode::Pulse)));
    m_stack.add(m_pageBlink, std::string(Model::Channel::toConfigString(Model::Channel::ChannelMode::Blink)));

    m_mainBox.append(m_stack);
    set_child(m_mainBox);

    // Connect state change signals from child pages
    m_pageToggle.signal_changed().connect(
        sigc::mem_fun(*this, &ChannelWidget::onChildPageChanged)
    );
    m_pageTimer.signal_changed().connect(
        sigc::mem_fun(*this, &ChannelWidget::onChildPageChanged)
    );
    m_pagePulse.signal_changed().connect(
        sigc::mem_fun(*this, &ChannelWidget::onChildPageChanged)
    );
    m_pageBlink.signal_changed().connect(
        sigc::mem_fun(*this, &ChannelWidget::onChildPageChanged)
    );

    updateSensitivity();
}

void ChannelWidget::updateSensitivity() {
    bool isEnabled = m_enableBtn.get_active();
    m_modeCombo.set_sensitive(isEnabled);
    m_stack.set_sensitive(isEnabled);
}

void ChannelWidget::updateState(const ChannelState &state) {
    m_blockSignals = true;
    m_enableBtn.set_active(state.enabled);

    int activeRow = -1;
    for (size_t i = 0; i < Model::Channel::cChannelModeDescriptors.size(); ++i) {
        if (Model::Channel::cChannelModeDescriptors[i].mode == state.mode) {
            activeRow = static_cast<int>(i);
            break;
        }
    }
    m_modeCombo.set_active(activeRow >= 0 ? activeRow : 0);

    auto visibleChildName = Model::Channel::toConfigString(state.mode);
    if (state.mode != Model::Channel::ChannelMode::Unknown) {
        m_stack.set_visible_child(std::string(visibleChildName));
    } else {
        m_stack.set_visible_child(std::string(Model::Channel::toConfigString(Model::Channel::ChannelMode::Toggle)));
    }

    m_pageToggle.updateState(state);
    m_pageTimer.updateState(state);
    m_pagePulse.updateState(state);
    m_pageBlink.updateState(state);

    m_blockSignals = false;
    updateSensitivity();
}

ChannelState ChannelWidget::getState() const {
    ChannelState state;
    state.enabled = m_enableBtn.get_active();

    int activeRow = m_modeCombo.get_active_row_number();
    if (activeRow >= 0 && activeRow < static_cast<int>(Model::Channel::cChannelModeDescriptors.size())) {
        state.mode = Model::Channel::cChannelModeDescriptors[static_cast<size_t>(activeRow)].mode;
    } else {
        state.mode = Model::Channel::ChannelMode::Unknown;
    }

    m_pageToggle.getState(state);
    m_pageTimer.getState(state);
    m_pagePulse.getState(state);
    m_pageBlink.getState(state);

    return state;
}

void ChannelWidget::onEnableToggled() {
    updateSensitivity();
    if (!m_blockSignals) {
        m_signalChanged.emit();
    }
}

void ChannelWidget::onModeChanged() {
    int activeRow = m_modeCombo.get_active_row_number();
    if (activeRow >= 0 && activeRow < static_cast<int>(Model::Channel::cChannelModeDescriptors.size())) {
        auto mode = Model::Channel::cChannelModeDescriptors[static_cast<size_t>(activeRow)].mode;
        auto visibleChildName = Model::Channel::toConfigString(mode);
        m_stack.set_visible_child(std::string(visibleChildName));
    }
    updateSensitivity();

    if (!m_blockSignals) {
        m_signalChanged.emit();
    }
}

void ChannelWidget::onChildPageChanged() {
    if (!m_blockSignals) {
        m_signalChanged.emit();
    }
}
