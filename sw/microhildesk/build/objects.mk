#
# @brief   microhildesk
# @version 1.0.0
# @date    Sat Aug 19 11:15:56 AM CEST 2023
# @company None, free software to use 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

GENERATED_SRC = resources.c
OBJECTS = $(GENERATED_SRC:.c=.o) $(SOURCES:.cc=.o)
