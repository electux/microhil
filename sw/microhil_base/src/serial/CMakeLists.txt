#
# @brief   serial library setup
# @version v1.0.0
# @date    2026-09-01
#

add_library(serial serial_transport.c)
target_include_directories(serial PUBLIC . ..)
target_link_libraries(serial
    pico_stdlib
    pico_stdio_usb
)
