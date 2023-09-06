#
# @brief   microhil-device0 channel support
# @version v1.0.3
# @date    2023-09-05
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

aux_source_directory(. DIR_CHANNEL_SRCS)

include_directories(../ws2812)
include_directories(../io_config)

add_library(channel ${DIR_CHANNEL_SRCS})

target_link_libraries(channel PUBLIC pico_stdlib pico_stdio_usb hardware_pio hardware_spi hardware_i2c hardware_pwm hardware_adc)
