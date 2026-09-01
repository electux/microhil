////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// switchable_com_configurator.cc
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
#include <com/com_types.h>
#include <com/switchable_com.h>
#include <com/switchable_com_configurator.h>
#include <model/imodel.h>
#include <string>

namespace Electux::App::Com {
    SwitchableComConfigurator::SwitchableComConfigurator(
        std::unique_ptr<IComConfigurator> serialConfigurator,
        std::unique_ptr<IComConfigurator> tcpConfigurator,
        std::unique_ptr<IComConfigurator> bleConfigurator
    )
        : m_serialConfigurator(std::move(serialConfigurator)),
          m_tcpConfigurator(std::move(tcpConfigurator)),
          m_bleConfigurator(std::move(bleConfigurator)) {}

    bool SwitchableComConfigurator::configure(
        const Model::IModel &model, ICom &comChannel
    ) {
        auto *switchable = dynamic_cast<SwitchableCom *>(&comChannel);
        if (switchable == nullptr) {
            return false;
        }

        auto comTypeKey = model.toString(Model::ModelGeneralKey::ComType);
        std::string comType = model.getEntity(comTypeKey);

        switchable->setComType(comType);

        if (comType == toConfigString(ComType::Tcp)) {
            auto *tcpCom = switchable->getTcpCom();
            return (tcpCom != nullptr && m_tcpConfigurator)
                ? m_tcpConfigurator->configure(model, *tcpCom)
                : false;
        } else if (comType == toConfigString(ComType::Ble)) {
            auto *bleCom = switchable->getBleCom();
            return (bleCom != nullptr && m_bleConfigurator)
                ? m_bleConfigurator->configure(model, *bleCom)
                : false;
        } else {
            auto *serialCom = switchable->getSerialCom();
            return (serialCom != nullptr && m_serialConfigurator)
                ? m_serialConfigurator->configure(model, *serialCom)
                : false;
        }
    }
} // namespace Electux::App::Com
