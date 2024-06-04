#
# @brief  microhildesk
# @version 1.0.0
# @date    Sat Aug 19 11:15:56 AM CEST 2023
# @company None, free software to use 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

ifeq ($(CC),gcc)
CFLAGS = \
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
	-Wshadow \
	-Wstrict-overflow=5 \
	-Wundef \
	-Wno-overlength-strings \
	-Wno-unused
else ifeq ($(CC),clang)
CFLAGS = \
	-c \
	-g \
	-pedantic \
	-Wall \
	-Wextra \
	-Wcast-align \
	-Wcast-qual \
	-Wformat=2 \
	-Winit-self \
	-Wmissing-declarations \
	-Wmissing-include-dirs \
	-Wshadow \
	-Wstrict-overflow=5 \
	-Wundef \
	-Wno-overlength-strings \
	-Wunused \
	-v
else
  $(error Unsupported compiler: $(CC))
endif
