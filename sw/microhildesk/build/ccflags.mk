#
# @brief   microhildesk
# @version 1.0.0
# @date    Sat Aug 19 11:15:56 AM CEST 2023
# @company None, free software to use 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

ifeq ($(CXX),g++)
CCFLAGS = \
	-std=c++17 \
	-c \
	-g \
	-pedantic \
	-Wall \
	-Wextra \
	-Wcast-align \
	-Wcast-qual \
	-Wdisabled-optimization \
	-Wformat=2 \
	-Winit-self \
	-Wlogical-op \
	-Wmissing-declarations \
	-Wmissing-include-dirs \
	-Wnoexcept \
	-Woverloaded-virtual \
	-Wshadow \
	-Wsign-promo \
	-Wstrict-null-sentinel \
	-Wstrict-overflow=5 \
	-Wundef \
	-Werror \
	-Wno-unused
else ifeq ($(CXX),clang++)
CXXFLAGS = \
    -std=c++17 \
    -c \
    -g \
    -pedantic \
    -Wall \
    -Wextra \
    -Wcast-align \
    -Wcast-qual \
    -Wdisable-optimizations \
    -Wformat=2 \
    -Winit-self \
    -Wlogical-op \
    -Wmissing-declarations \
    -Wmissing-include-dirs \
    -Wno-except \
    -Woverloaded-virtual \
    -Wshadow \
    -Wsign-conversion \
    -Wstrict-null-sentinel \
    -Wstrict-overflow=5 \
    -Wundef \
    -Werror \
    -Wunused \
    -v
else
  $(error Unsupported compiler: $(CXX))
endif
