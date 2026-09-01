# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/wlama/pico/pico-sdk/tools/pioasm"
  "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/pioasm"
  "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/pioasm-install"
  "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
  "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
