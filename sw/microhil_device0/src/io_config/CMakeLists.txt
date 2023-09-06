#
# @brief   microhil-device0 IO lib support
# @version v1.0.3
# @date    2023-09-05
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

aux_source_directory(. DIR_CONFIG_SRCS)

add_library(io_config ${DIR_CONFIG_SRCS})

target_link_libraries(io_config PUBLIC pico_stdlib hardware_spi hardware_i2c hardware_pwm hardware_adc)
