cmake_minimum_required(VERSION 3.12)
project(microhil_base_wifi_tests C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
enable_testing()

# 1. Include Mocks first so that standard Pico and device includes are intercepted
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/mocks
    ${CMAKE_CURRENT_SOURCE_DIR}/../microhil_base_wifi/src
)

# 2. Add Googletest subdirectory from microhildesk_tests (offline/local reuse)
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../microhildesk_tests/googletest
    ${CMAKE_CURRENT_BINARY_DIR}/googletest_build
)

# Include Googletest headers
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../microhildesk_tests/googletest/googletest/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../microhildesk_tests/googletest/googlemock/include
)

# 3. Create test executable compiling Wi-Fi C modules with host mock structures
add_executable(
    microhil_base_wifi_tests
    main.cc
    mocks/mocks.cc
    ../microhil_base_wifi/src/config/nvm_config.c
    ../microhil_base_wifi/src/wifi/wifi_ring_buffer.c
    ../microhil_base_wifi/src/command/net_command.c
    ../microhil_base_wifi/src/command/command_tbl.c
    ../microhil_base_wifi/src/command/parser.c
    ../microhil_base_wifi/src/command/response.c
    tests/test_ring_buffer.cc
    tests/test_nvm_config.cc
    tests/test_parser.cc
    tests/test_command.cc
)

# 4. Link GoogleTest libraries
target_link_libraries(
    microhil_base_wifi_tests
    PUBLIC
    gtest
    gtest_main
    gmock
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(microhil_base_wifi_tests)
