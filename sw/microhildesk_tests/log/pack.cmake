#
# @brief   microhildesk_tests list of all sources and unit tests for log
# @version v1.0.3
# @date    Tue Sep 19 08:55:54 PM CEST 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

set(
    MICROHIL_LOG_HEADERS
    ${PROJECT_SOURCE_DIR}/../microhildesk/log/
)

set(
    MICROHIL_LOG_SOURCES
    ${PROJECT_SOURCE_DIR}/../microhildesk/log/microhil_log.cc
    ${PROJECT_SOURCE_DIR}/../microhildesk/log/microhil_log_<TODO>.cc
)

set(
    MICROHIL_LOG_TESTS
    ${PROJECT_SOURCE_DIR}/controller/test_mhlog_file_path.cc
    ${PROJECT_SOURCE_DIR}/controller/test_mhlog_log_level.cc
    ${PROJECT_SOURCE_DIR}/controller/test_mhlog_open.cc
    ${PROJECT_SOURCE_DIR}/controller/test_mhlog_write.cc
    ${PROJECT_SOURCE_DIR}/controller/test_mhlog_close.cc
)
