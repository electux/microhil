#
# @brief   microhildesk
# @version 1.0.0
# @date    Sat Aug 19 11:15:56 AM CEST 2023
# @company None, free software to use 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

CC  = gcc
CXX = g++
RM  = rm

include ccflags.mk
include cflags.mk
include ldflags.mk
include sources.mk
include objects.mk
include resources.mk

EXECUTABLE=microhildesk

GLIB_COMPILE_RESOURCES = $(shell pkg-config --variable=glib_compile_resources gio-2.0)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@ `pkg-config --libs gtkmm-3.0` `pkg-config --libs libserial`

resources.c: ../resource/microhildesk.gresource.xml $(RESOURCES)
	$(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=../resource --generate-source $<

.cc.o:
	$(CXX) $(CCFLAGS) $< -o $@ `pkg-config gtkmm-3.0 --cflags`

.c.o:
	$(CC) $(CFLAGS) $< -o $@ `pkg-config gio-2.0 --cflags`

clean:
	$(RM) -rf ../*/*/*/*.o ../*/*/*.o ../*/*.o ../*.o *.o resources.c $(EXECUTABLE)
