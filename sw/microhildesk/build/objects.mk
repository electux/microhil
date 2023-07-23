#
# @brief   microhildesk
# @version 1.0.0
# @date    Fri 26 Nov 2021 11:10:21 PM CET
# @company None, free software to use 2021
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

GENERATED_SRC = resources.c
OBJECTS = $(GENERATED_SRC:.c=.o) $(SOURCES:.cc=.o)
