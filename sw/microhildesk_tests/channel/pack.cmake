#
# @brief   microhildesk_tests list of all sources and unit tests for config
# @version v1.0.3
# @date    Tue Sep 19 08:55:54 PM CEST 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

set(
    MICROHIL_PARAMS_HEADERS
    ${PROJECT_SOURCE_DIR}/../microhildesk/
)

set(
    MICROHIL_PARAMS_TESTS
    ${PROJECT_SOURCE_DIR}/channel/test_params_channel.cc
    ${PROJECT_SOURCE_DIR}/channel/test_log_params.cc
    ${PROJECT_SOURCE_DIR}/channel/test_serial_params.cc
)
