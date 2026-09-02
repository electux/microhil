#
# @brief   command library setup
# @version v1.0.0
# @date    2026-08-21
#

add_library(command
    ble_command.c
    command_tbl.c
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
    ble
    pico_stdlib
    hardware_watchdog
)
