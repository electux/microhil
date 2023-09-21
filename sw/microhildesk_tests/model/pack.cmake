#
# @brief   microhildesk_tests list of all sources and unit tests for model
# @version v1.0.3
# @date    Tue Sep 19 08:55:54 PM CEST 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

set(
    MICROHIL_MODEL_HEADERS
    ${PROJECT_SOURCE_DIR}/../microhildesk/model/
)

set(
    MICROHIL_MODEL_SOURCES
    ${PROJECT_SOURCE_DIR}/../microhildesk/model/microhil_model.cc
)

set(
    MICROHIL_MODEL_TESTS
    ${PROJECT_SOURCE_DIR}/model/test_mhmodel_channel.cc
)
