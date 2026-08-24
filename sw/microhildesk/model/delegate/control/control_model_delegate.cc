////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// control_model_delegate.cc
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

#include <model/delegate/control/control_model_delegate.h>
#include <model/channel_types.h>
#include <algorithm>
#include <initializer_list>
#include <sstream>
#include <vector>

namespace Electux::App::Model {
    namespace {
        constexpr std::string_view cEnable{"enable"};
        constexpr std::string_view cMode{"mode"};
        constexpr std::string_view cToggle{"toggle"};
        constexpr std::string_view cTimer{"timer"};
        constexpr std::string_view cTimerEnable{"timerEnable"};
        constexpr std::string_view cPulseTime{"pulseTime"};
        constexpr std::string_view cPulseTriggered{"pulseTriggered"};
        constexpr std::string_view cBlinkOn{"blinkOn"};
        constexpr std::string_view cBlinkOff{"blinkOff"};
        constexpr std::string_view cBlinkCount{"blinkCount"};
        constexpr std::string_view cBlinkEnabled{"blinkEnabled"};
        constexpr std::string_view cUnknown{"unknown"};

        std::vector<std::string> split_to_vector(const std::string_view &input) {
            std::vector<std::string> elements;
            std::stringstream ss{std::string(input)};
            std::string item;
            while (ss >> item) {
                elements.push_back(item);
            }
            return elements;
        }

        std::string extract_param_value_by_index(
            const std::string_view &input, size_t index
        ) {
            auto elements = split_to_vector(input);
            if (index < elements.size()) {
                return elements[index];
            }
            return "";
        }

        std::string update_param_value_by_index(
            const std::string_view &input, size_t index,
            const std::string_view &newValue
        ) {
            auto elements = split_to_vector(input);
            if (elements.size() < static_cast<size_t>(Electux::App::Model::Channel::cNumOfChannels)) {
                std::string defaultValue =
                    elements.empty() ? std::string(newValue) : elements.back();
                elements.resize(
                    static_cast<size_t>(Electux::App::Model::Channel::cNumOfChannels),
                    defaultValue
                );
            }
            if (index < elements.size()) {
                elements[index] = std::string(newValue);
            }
            std::string result;
            for (size_t i = 0; i < elements.size(); ++i) {
                result += elements[i] + (i < elements.size() - 1 ? " " : "");
            }
            return result;
        }
    } // namespace

    std::string_view ControlModelDelegate::toString(ModelControlKey key) const {
        switch (key) {
        case ModelControlKey::Enable:
            return cEnable;
        case ModelControlKey::Mode:
            return cMode;
        case ModelControlKey::Toggle:
            return cToggle;
        case ModelControlKey::Timer:
            return cTimer;
        case ModelControlKey::TimerEnable:
            return cTimerEnable;
        case ModelControlKey::PulseTime:
            return cPulseTime;
        case ModelControlKey::PulseTriggered:
            return cPulseTriggered;
        case ModelControlKey::BlinkOn:
            return cBlinkOn;
        case ModelControlKey::BlinkOff:
            return cBlinkOff;
        case ModelControlKey::BlinkCount:
            return cBlinkCount;
        case ModelControlKey::BlinkEnabled:
            return cBlinkEnabled;
        default:
            return cUnknown;
        }
    }

    bool ControlModelDelegate::validateKey(const std::string_view &key) const {
        static const std::initializer_list<std::string_view> validKeys = {
            cEnable, cMode, cToggle, cTimer, cTimerEnable,
            cPulseTime, cPulseTriggered, cBlinkOn, cBlinkOff, cBlinkCount, cBlinkEnabled
        };
        return std::any_of(validKeys.begin(), validKeys.end(), [&](auto k) {
            return k == key;
        });
    }

    ChannelState ControlModelDelegate::getChannelState(const Entities &entities, size_t index) const {
        using Electux::App::Model::Channel::ChannelMode;

        auto getEntityStr = [&](ModelControlKey key) -> std::string {
            auto keyStr = std::string(toString(key));
            auto it = entities.find(keyStr);
            if (it != entities.end()) {
                return it->second;
            }
            return "";
        };

        ChannelState state;

        state.enabled = (extract_param_value_by_index(getEntityStr(ModelControlKey::Enable), index) == "true");

        auto modeStr = extract_param_value_by_index(getEntityStr(ModelControlKey::Mode), index);
        if (modeStr.empty()) {
            state.mode = ChannelMode::Unknown;
        } else if (modeStr == "0" || modeStr == "toggle") {
            state.mode = ChannelMode::Toggle;
        } else if (modeStr == "1" || modeStr == "timer") {
            state.mode = ChannelMode::Timer;
        } else if (modeStr == "2" || modeStr == "pulse") {
            state.mode = ChannelMode::Pulse;
        } else if (modeStr == "3" || modeStr == "blink") {
            state.mode = ChannelMode::Blink;
        } else {
            state.mode = ChannelMode::Unknown;
        }

        state.toggle = (extract_param_value_by_index(getEntityStr(ModelControlKey::Toggle), index) == "true");

        auto timerStr = extract_param_value_by_index(getEntityStr(ModelControlKey::Timer), index);
        state.timer = timerStr.empty() ? 0 : std::stoi(timerStr);

        state.timerEnabled = (extract_param_value_by_index(getEntityStr(ModelControlKey::TimerEnable), index) == "true");

        auto pulseTimeStr = extract_param_value_by_index(getEntityStr(ModelControlKey::PulseTime), index);
        state.pulseTime = pulseTimeStr.empty() ? 0 : std::stoi(pulseTimeStr);

        state.pulseTriggered = (extract_param_value_by_index(getEntityStr(ModelControlKey::PulseTriggered), index) == "true");

        auto blinkOnStr = extract_param_value_by_index(getEntityStr(ModelControlKey::BlinkOn), index);
        state.blinkOnTime = blinkOnStr.empty() ? 0 : std::stoi(blinkOnStr);

        auto blinkOffStr = extract_param_value_by_index(getEntityStr(ModelControlKey::BlinkOff), index);
        state.blinkOffTime = blinkOffStr.empty() ? 0 : std::stoi(blinkOffStr);

        auto blinkCountStr = extract_param_value_by_index(getEntityStr(ModelControlKey::BlinkCount), index);
        state.blinkCount = blinkCountStr.empty() ? 0 : std::stoi(blinkCountStr);

        state.blinkEnabled = (extract_param_value_by_index(getEntityStr(ModelControlKey::BlinkEnabled), index) == "true");

        return state;
    }

    void ControlModelDelegate::setChannelState(
        Entities &entities, size_t index, const ChannelState &state
    ) const {
        using Electux::App::Model::Channel::toConfigString;

        auto updateEntity = [&](ModelControlKey key, const std::string &newValue) {
            auto keyStr = std::string(toString(key));
            auto it = entities.find(keyStr);
            if (it != entities.end()) {
                it->second = update_param_value_by_index(it->second, index, newValue);
            }
        };

        updateEntity(ModelControlKey::Enable, state.enabled ? "true" : "false");
        updateEntity(ModelControlKey::Mode, std::string(toConfigString(state.mode)));
        updateEntity(ModelControlKey::Toggle, state.toggle ? "true" : "false");
        updateEntity(ModelControlKey::Timer, std::to_string(state.timer));
        updateEntity(ModelControlKey::TimerEnable, state.timerEnabled ? "true" : "false");
        updateEntity(ModelControlKey::PulseTime, std::to_string(state.pulseTime));
        updateEntity(ModelControlKey::PulseTriggered, state.pulseTriggered ? "true" : "false");
        updateEntity(ModelControlKey::BlinkOn, std::to_string(state.blinkOnTime));
        updateEntity(ModelControlKey::BlinkOff, std::to_string(state.blinkOffTime));
        updateEntity(ModelControlKey::BlinkCount, std::to_string(state.blinkCount));
        updateEntity(ModelControlKey::BlinkEnabled, state.blinkEnabled ? "true" : "false");
    }

    std::unique_ptr<IControlModelDelegate> ControlModelDelegate::clone() const {
        return std::make_unique<ControlModelDelegate>(*this);
    }
} // namespace Electux::App::Model
