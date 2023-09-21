#
# @brief   microhildesk_tests main entry point for build tests
# @version v1.0.3
# @date    Tue Sep 19 08:55:54 PM CEST 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

cmake_minimum_required(VERSION 3.12)
project(microhil_tests CXX)
set(GOOGLETEST_VERSION 1.14.0)

enable_testing()

# Add gtkmm and glibmm packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(gtkmm REQUIRED IMPORTED_TARGET gtkmm-3.0 glibmm-2.4)

# Add sources and includes for googletest
add_subdirectory(googletest)
include_directories(googletest/include)

# Add sources and includes for microhil_config and microhil_config_tests
include(${PROJECT_SOURCE_DIR}/com/pack.cmake)
include(${PROJECT_SOURCE_DIR}/config/pack.cmake)
include(${PROJECT_SOURCE_DIR}/log/pack.cmake)
include_directories(com)
include_directories(config)
include_directories(log)
include_directories(${MICROHIL_COM_HEADERS})
include_directories(${MICROHIL_CONFIG_HEADERS})
include_directories(${MICROHIL_LOG_HEADERS})

add_executable(
    microhil_tests
    main.cc
    ${MICROHIL_COM_TESTS}
    ${MICROHIL_CONFIG_TESTS}
    ${MICROHIL_LOG_TESTS}
    ${MICROHIL_COM_SOURCES}
    ${MICROHIL_CONFIG_SOURCES}
    ${MICROHIL_LOG_SOURCES}
)

# Link libraries
target_link_libraries(microhil_tests PUBLIC gtest gtest_main PkgConfig::gtkmm)
include(GoogleTest)
gtest_discover_tests(microhil_tests)
