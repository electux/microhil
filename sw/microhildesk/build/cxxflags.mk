#
# @brief   microhildesk
# @version 1.1.6
# @date    2024-07-21 16:05:11.297462
# @company None, free software to use 2024
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

ifeq ($(CXX), g++)
CXXFLAGS = \
	-std=c++20 \
	-c \
	-g \
	-pedantic \
	-Wall \
	-Wextra \
	-Wconversion \
	-Wnull-dereference \
	-Wnon-virtual-dtor \
	-Wsuggest-override \
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
else ifeq ($(CXX), clang++)
CXXFLAGS = \
    -std=c++20 \
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
