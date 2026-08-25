#
# @brief   microhildesk_tests list of all sources and unit tests for model
# @version v1.0.3
# @date    Tue Sep 19 08:55:54 PM CEST 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

set(
    MICROHIL_MODEL_HEADERS
    ${PROJECT_SOURCE_DIR}/../microhildesk/
)

set(
    MICROHIL_MODEL_SOURCES
    ${PROJECT_SOURCE_DIR}/../microhildesk/model/model.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/model/model_factory.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/model/delegate/control/control_model_delegate.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/model/delegate/serial/serial_model_delegate.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/model/delegate/general/general_model_delegate.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/model/delegate/ble/ble_model_delegate.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/model/delegate/log/log_model_delegate.cc
)

set(
    MICROHIL_MODEL_TESTS
    ${PROJECT_SOURCE_DIR}/model/test_model.cc
)
