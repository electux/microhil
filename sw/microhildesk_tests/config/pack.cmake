#
# @brief   microhildesk_tests list of all sources and unit tests for config
# @version v1.0.3
# @date    Tue Sep 19 08:55:54 PM CEST 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

set(
    MICROHIL_CONFIG_HEADERS
    ${PROJECT_SOURCE_DIR}/../microhildesk/config/
)

set(
    MICROHIL_CONFIG_SOURCES
    ${PROJECT_SOURCE_DIR}/../microhildesk/config/microhil_config.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/config/microhil_config_log.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/config/microhil_config_log_utils.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/config/microhil_config_serial.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/config/microhil_config_serial_utils.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/config/microhil_config_signals.cc
)

set(
    MICROHIL_CONFIG_TESTS
    ${PROJECT_SOURCE_DIR}/config/test_mhconfig_baud_rate.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhconfig_data_bits.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhconfig_device.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhconfig_file.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhconfig_level.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhconfig_load.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhconfig_parity.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhconfig_pre_valid.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhconfig_stop_bits.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhconfig_store.cc
)
