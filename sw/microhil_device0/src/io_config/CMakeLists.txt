#
# @brief   microhil-device0 IO lib support
# @version v1.0.3
# @date    2023-09-05
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

# Add sources
aux_source_directory(. DIR_CONFIG_SRCS)

# Add io_config target library
add_library(io_config ${DIR_CONFIG_SRCS})

# Link dependecy libraries
target_link_libraries(io_config PUBLIC pico_stdlib hardware_pwm)
