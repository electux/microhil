#
# @brief   microhil-base channel support
# @version v1.0.3
# @date    2023-09-05
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

# Adds sources
aux_source_directory(. DIR_CHANNEL_SRCS)

# Adds dependecy includes
include_directories(../ws2812)
include_directories(../io_config)

# Adds channel target library
add_library(channel ${DIR_CHANNEL_SRCS})

# Links dependecy libraries
target_link_libraries(
    channel PUBLIC pico_stdlib pico_stdio_usb hardware_pio hardware_pwm
)
