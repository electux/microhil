#
# @brief   microhil-base-wifi wifi transport library
# @version v1.0.0
# @date    2025-09-02
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

add_library(wifi STATIC
    wifi_ring_buffer.c
    wifi_manager.c
    tcp_server.c
    wifi_transport.c
)

target_include_directories(wifi PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(wifi PUBLIC
    config
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    hardware_sync
)
