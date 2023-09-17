#
# @brief   microhil-base main entry point for build process
# @version v1.0.3
# @date    2021-12-15
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

# Setup CMake version and RPI Pico SDK import
cmake_minimum_required(VERSION 3.12)

# Pico SDK import setup
include(pico_sdk_import.cmake)

# Setup project info
project(microhil-base C CXX ASM)
set(CMAKE_PROJECT_VERSION 1.0.0)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PRO_PATH ${PROJECT_SOURCE_DIR})
set(PICO_BOARD "pico")

# Initialize the SDK
pico_sdk_init()

# Setup project url
include(pro_auto_set_url.cmake)

# Add source directory
add_subdirectory(src)
