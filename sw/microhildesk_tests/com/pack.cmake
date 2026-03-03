#
# @brief   microhildesk_tests list of all sources and unit tests for config
# @version v1.0.3
# @date    Tue Sep 19 08:55:54 PM CEST 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

set(
    MICROHIL_COM_HEADERS
    ${PROJECT_SOURCE_DIR}/../microhildesk/
)

set(
    MICROHIL_COM_SOURCES
    ${PROJECT_SOURCE_DIR}/../microhildesk/com/serial_com.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/com/serial_lib_wrapper.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/com/serial_com_baud_rate.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/com/serial_com_data_bits.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/com/serial_com_parity.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/com/serial_com_stop_bits.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/com/serial_com_flow_control.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/com/serial_com_setup.cc
)

set(
    MICROHIL_COM_TESTS
    ${PROJECT_SOURCE_DIR}/com/test_serial_baude_rate.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_data_bits.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_parity.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_stop_bits.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_flow_control.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_setup.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_open.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_close.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_read.cc
    #${PROJECT_SOURCE_DIR}/com/test_serial_write.cc
)
