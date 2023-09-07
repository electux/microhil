#
# @brief   microhil-device0 setup output files
# @version v1.0.3
# @date    2021-12-15
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

# Prepare PIO target for ws2812 
pico_simple_hardware_target(pio)

add_subdirectory(io_config)
add_subdirectory(ws2812)
add_subdirectory(channel)

include_directories(channel)
include_directories(ws2812)
include_directories(io_config)

# Create executable
add_executable("${CMAKE_PROJECT_NAME}" main.c)

# Enable usb output, enable uart output
pico_enable_stdio_usb("${CMAKE_PROJECT_NAME}" 1)
pico_enable_stdio_uart("${CMAKE_PROJECT_NAME}" 1)

# Link all libraries
target_link_libraries("${CMAKE_PROJECT_NAME}" channel ws2812 io_config)

# Create extra output files map/bin/hex
pico_add_extra_outputs("${CMAKE_PROJECT_NAME}")

# Add url via pico_set_program_url
pro_auto_set_url("${CMAKE_PROJECT_NAME}")
