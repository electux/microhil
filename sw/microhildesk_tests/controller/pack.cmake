#
# @brief   microhildesk_tests list of all sources and unit tests for controller
# @version v1.0.3
# @date    Tue Sep 19 08:55:54 PM CEST 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

set(
    MICROHIL_CONTROLLER_HEADERS
    ${PROJECT_SOURCE_DIR}/../microhildesk/controller/
)

set(
    MICROHIL_CONTROLLER_SOURCES
    ${PROJECT_SOURCE_DIR}/../microhildesk/controller/microhil_controller.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/controller/microhil_controller_<TODO>.cc
)

set(
    MICROHIL_CONTROLLER_TESTS
    ${PROJECT_SOURCE_DIR}/controller/test_mhcontroller_<TODO>.cc
)
