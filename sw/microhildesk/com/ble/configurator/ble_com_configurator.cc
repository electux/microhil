////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// ble_com_configurator.cc
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
#include <com/ble/configurator/ble_com_configurator.h>
#include <com/ble/ible.h>
#include <com/icom.h>
#include <model/imodel.h>
#include <string>

namespace Electux::App::Com {
    bool BleComConfigurator::configure(
        const Model::IModel &model, ICom &comChannel
    ) {
        auto *ble = dynamic_cast<IBle *>(&comChannel);
        if (ble == nullptr) {
            return false;
        }

        auto addrKey = model.toString(Model::ModelBleKey::Address);
        auto serviceKey = model.toString(Model::ModelBleKey::ServiceUuid);
        auto rxKey = model.toString(Model::ModelBleKey::RxUuid);
        auto txKey = model.toString(Model::ModelBleKey::TxUuid);

        std::string addr = model.getEntity(addrKey);
        std::string service = model.getEntity(serviceKey);
        std::string rx = model.getEntity(rxKey);
        std::string tx = model.getEntity(txKey);

        ble->setBleAddress(addr);
        ble->setServiceUuid(service);
        ble->setRxUuid(rx);
        ble->setTxUuid(tx);

        return comChannel.open();
    }
} // namespace Electux::App::Com
