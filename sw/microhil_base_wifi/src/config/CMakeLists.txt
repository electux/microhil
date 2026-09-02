#
# @brief   microhil-base-wifi config library
# @version v1.0.0
# @date    2025-09-02
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

add_library(config STATIC
    nvm_config.c
)

target_include_directories(config PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(config PUBLIC
    pico_stdlib
    hardware_flash
    hardware_sync
)
