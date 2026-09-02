////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_com_configurator.cc
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
#include <com/icom.h>
#include <com/serial/configurator/serial_com_configurator.h>
#include <com/serial/iserial.h>
#include <com/serial/serial_utils.h>
#include <model/imodel.h>
#include <string>

namespace Electux::App::Com {
    bool SerialComConfigurator::configure(
        const Model::IModel &model, ICom &comChannel
    ) {
        auto *serial = dynamic_cast<ISerial *>(&comChannel);
        if (serial == nullptr) {
            return false;
        }

        Com::SerialParams params;
        params.device =
            model.getEntity(model.toString(Model::ModelSerialKey::Device));

        uint32_t baudIdx = static_cast<uint32_t>(std::stoul(
            model.getEntity(model.toString(Model::ModelSerialKey::Baud))
        ));
        params.baud = Com::SerialUtils::uintToBaud(baudIdx);

        uint32_t dataIdx = static_cast<uint32_t>(std::stoul(
            model.getEntity(model.toString(Model::ModelSerialKey::Data))
        ));
        params.data = Com::SerialUtils::uintToDataBits(dataIdx);

        uint32_t parityIdx = static_cast<uint32_t>(std::stoul(
            model.getEntity(model.toString(Model::ModelSerialKey::Parity))
        ));
        params.parity = Com::SerialUtils::uintToParity(parityIdx);

        uint32_t stopIdx = static_cast<uint32_t>(std::stoul(
            model.getEntity(model.toString(Model::ModelSerialKey::Stop))
        ));
        params.stop = Com::SerialUtils::uintToStopBits(stopIdx);

        uint32_t flowIdx = static_cast<uint32_t>(std::stoul(
            model.getEntity(model.toString(Model::ModelSerialKey::Flow))
        ));
        params.flow = Com::SerialUtils::uintToFlowControl(flowIdx);

        serial->setDevice(params.device);

        return serial->setup(params);
    }
} // namespace Electux::App::Com
