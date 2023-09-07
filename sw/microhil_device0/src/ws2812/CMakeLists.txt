#
# @brief   microhil-device0 ws2812 pio
# @version v1.0.3
# @date    2023-09-05
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

aux_source_directory(. DIR_WS2812_SRCS)

include_directories(../io_config)

add_library(ws2812 ${DIR_WS2812_SRCS})

target_link_libraries(ws2812 PUBLIC io_config)
