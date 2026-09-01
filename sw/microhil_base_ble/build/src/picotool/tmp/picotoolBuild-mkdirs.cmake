# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/_deps/picotool-src"
  "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/_deps/picotool-build"
  "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/_deps"
  "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/src/picotool/tmp"
  "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/src/picotool/src/picotoolBuild-stamp"
  "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/src/picotool/src"
  "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/src/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/src/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/data/dev/raspberry/microhil/github/microhil/sw/microhil_base_ble/build/src/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
