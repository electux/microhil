#
# @brief   microhil-base-wifi source directory
# @version v1.0.0
# @date    2025-09-02
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

# Prepares PIO target for WS2812 (headers and implementation)
pico_simple_hardware_target(pio)

# Enable verbose logging globally
add_compile_definitions(VERBOSE)

# Adds sub-structure includes
include_directories(.)
include_directories(config)
include_directories(io)
include_directories(ws2812)
include_directories(device)
include_directories(wifi)
include_directories(command)

# Adds subdirectories
add_subdirectory(config)
add_subdirectory(io)
add_subdirectory(ws2812)
add_subdirectory(device)
add_subdirectory(wifi)
add_subdirectory(command)

# Adds executable
add_executable("${CMAKE_PROJECT_NAME}" main.c)

# Enables USB output for debug & CLI
pico_enable_stdio_usb("${CMAKE_PROJECT_NAME}" 1)

# Disables UART output
pico_enable_stdio_uart("${CMAKE_PROJECT_NAME}" 0)

target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Links all libraries
target_link_libraries("${CMAKE_PROJECT_NAME}"
    config
    command
    device
    io
    wifi
    ws2812
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
)

# Creates extra output files map/bin/hex/uf2
pico_add_extra_outputs("${CMAKE_PROJECT_NAME}")

# Adds URL via pico_set_program_url
pro_auto_set_url("${CMAKE_PROJECT_NAME}")
