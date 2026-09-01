#
# @brief   ble library setup
# @version v1.0.0
# @date    2026-08-21
#

add_library(ble
    ble_ring_buffer.c
    ble_gap.c
    ble_gatt_spp.c
    ble_transport.c
)

# Generate GATT database header from microhil_ble.gatt
pico_btstack_make_gatt_header(ble PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../microhil_ble.gatt")

target_include_directories(ble PUBLIC . ..)
target_link_libraries(ble
    pico_stdlib
    pico_cyw43_arch_none_headers
    pico_cyw43_arch_none
    pico_btstack_cyw43
    pico_btstack_ble
)
