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
	../com/serial_com_baud_rate.cc \
	../com/serial_com_data_bits.cc \
	../com/serial_com_parity.cc \
	../com/serial_com_stop_bits.cc \
	../com/serial_com_flow_control.cc \
	../com/serial_com_setup.cc \
	../com/serial_lib_wrapper.cc \
	../com/serial_com.cc \
	../model/model.cc \
	../view/home_map.cc \
	../view/home_slots.cc \
	../view/home_ui_utils.cc \
	../view/home.cc \
	../view/about/about.cc \
	../view/help/help.cc \
	../view/settings/settings_map.cc \
	../view/settings/settings_slots.cc \
	../view/settings/settings_ui_utils.cc \
	../view/settings/settings.cc \
	../application_map.cc \
	../application_slots.cc \
	../application.cc \
	../main.cc
