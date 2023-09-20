#
# @brief   microhildesk_tests list of all sources and unit tests for config
# @version v1.0.3
# @date    Tue Sep 19 08:55:54 PM CEST 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

set(
    MICROHIL_COM_HEADERS
    ${PROJECT_SOURCE_DIR}/../microhildesk/com/
)

set(
    MICROHIL_COM_SOURCES
    ${PROJECT_SOURCE_DIR}/../microhildesk/com/microhil_serial_com.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/com/microhil_serial_com_utils.cc
)

set(
    MICROHIL_COM_TESTS
    ${PROJECT_SOURCE_DIR}/config/test_mhserial_baude_rate.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhserial_data_bits.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhserial_parity.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhserial_stop_bits.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhserial_setup.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhserial_open.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhserial_close.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhserial_read.cc
    ${PROJECT_SOURCE_DIR}/config/test_mhserial_write.cc
)
