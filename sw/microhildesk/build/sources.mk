#
# @brief   microhildesk
# @version 1.1.6
# @date    2024-07-21 16:05:11.341582
# @company None, free software to use 2024
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

SOURCES = \
	../log/log.cc \
	../config/config_manager_utils.cc \
	../config/config_manager.cc \
	../com/serial/serial_lib_wrapper.cc \
	../com/serial/serial_utils.cc \
	../com/serial/serial_com.cc \
	../com/serial/serial_com_configurator.cc \
	../com/tcp/tcp_com.cc \
	../com/tcp/tcp_com_configurator.cc \
	../com/ble/ble_com.cc \
	../com/ble/ble_com_configurator.cc \
	../com/ble/bluez_ble_client.cc \
	../com/ble/bluez_device_resolver.cc \
	../com/switchable_com.cc \
	../com/switchable_com_configurator.cc \
	../model/model.cc \
	../view/settings_setup.cc \
	../view/channel_widget.cc \
	../view/home.cc \
	../view/about/about.cc \
	../view/help/help.cc \
	../view/settings/general_settings_tab.cc \
	../view/settings/serial_settings_tab.cc \
	../view/settings/tcp_settings_tab.cc \
	../view/settings/ble_settings_tab.cc \
	../view/settings/log_settings_tab.cc \
	../view/settings/settings.cc \
	../application.cc \
	../app_controller.cc \
	../command/command_formatter.cc \
	../command/response_processor.cc \
	../main.cc
