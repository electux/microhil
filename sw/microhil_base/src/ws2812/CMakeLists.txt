#
# @brief   microhil-base ws2812 pio
# @version v1.0.3
# @date    2023-09-05
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

# Add sources
aux_source_directory(. DIR_WS2812_SRCS)

# Add dependecy includes
include_directories(../io_config)

# Add WS2812 target library
add_library(ws2812 ${DIR_WS2812_SRCS})

# Link dependecy library
target_link_libraries(ws2812 PUBLIC io_config)
