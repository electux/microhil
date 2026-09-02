#
# @brief   microhil-base-wifi command library
# @version v1.0.0
# @date    2025-09-02
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

add_library(command STATIC
    command_tbl.c
    net_command.c
    parser.c
    response.c
)

target_include_directories(command PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(command PUBLIC
    config
    device
    wifi
    pico_stdlib
    hardware_watchdog
)
