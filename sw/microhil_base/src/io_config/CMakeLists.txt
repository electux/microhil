#
# @brief   microhil-base IO lib support
# @version v1.0.3
# @date    2023-09-05
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

# Adds sources
aux_source_directory(. DIR_CONFIG_SRCS)

# Adds io_config target library
add_library(io_config ${DIR_CONFIG_SRCS})

# Links dependecy libraries
target_link_libraries(io_config PUBLIC pico_stdlib hardware_pwm)
