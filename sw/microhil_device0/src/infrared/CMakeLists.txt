#
# @brief   microhil-device0 infrared lib support
# @version v1.0.3
# @date    2023-09-05
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

aux_source_directory(. DIR_INFRARED_SRCS)

include_directories(../io_config)

add_library(infrared ${DIR_INFRARED_SRCS})

target_link_libraries(infrared PUBLIC io_config)
