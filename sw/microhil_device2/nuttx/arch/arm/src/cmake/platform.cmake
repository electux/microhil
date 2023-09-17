# ##############################################################################
# ./arch/arm/src/cmake/platform.cmake
#
# Licensed to the Apache Software Foundation (ASF) under one or more contributor
# license agreements.  See the NOTICE file distributed with this work for
# additional information regarding copyright ownership.  The ASF licenses this
# file to you under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License.  You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations under
# the License.
#
# ##############################################################################

# configure target processor

if(CONFIG_ARCH_CORTEXM0)
  set(CMAKE_SYSTEM_PROCESSOR cortex-m0)
else()
  message(FATAL_ERROR "CMAKE_SYSTEM_PROCESSOR not set")
endif()

get_directory_property(NUTTX_EXTRA_FLAGS DIRECTORY ${CMAKE_SOURCE_DIR}
                                                   COMPILE_OPTIONS)

execute_process(
  COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} ${NUTTX_EXTRA_FLAGS}
          --print-libgcc-file-name
  OUTPUT_STRIP_TRAILING_WHITESPACE
  OUTPUT_VARIABLE extra_library)
if(NOT EXISTS ${extra_library} AND CONFIG_ARCH_TOOLCHAIN_CLANG)
  get_filename_component(COMPILER_RT_LIB ${extra_library} NAME)
  execute_process(
    COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} ${NUTTX_EXTRA_FLAGS}
            --print-file-name ${COMPILER_RT_LIB}
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE extra_library)
endif()

list(APPEND EXTRA_LIB ${extra_library})

if(NOT CONFIG_LIBM)
  execute_process(
    COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} ${NUTTX_EXTRA_FLAGS}
            --print-file-name=libm.a
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE extra_library)
  list(APPEND EXTRA_LIB ${extra_library})
endif()

if(CONFIG_LIBSUPCXX)
  execute_process(
    COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} ${NUTTX_EXTRA_FLAGS}
            --print-file-name=libsupc++.a
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE extra_library)
  list(APPEND EXTRA_LIB ${extra_library})
endif()

if(CONFIG_ARCH_COVERAGE)
  execute_process(
    COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} ${NUTTX_EXTRA_FLAGS}
            --print-file-name=libgcov.a
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE extra_library)
  list(APPEND EXTRA_LIB ${extra_library})
endif()

set_property(GLOBAL APPEND PROPERTY NUTTX_EXTRA_LIBRARIES ${EXTRA_LIB})

separate_arguments(CMAKE_C_FLAG_ARGS NATIVE_COMMAND ${CMAKE_C_FLAGS})
set(PREPROCES ${CMAKE_C_COMPILER} ${CMAKE_C_FLAG_ARGS} -E -P -x c)
