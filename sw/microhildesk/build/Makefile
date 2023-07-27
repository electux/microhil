#
# @brief   microhildesk
# @version 1.0.0
# @date    Fri 26 Nov 2021 11:10:21 PM CET
# @company None, free software to use 2021
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

EXECUTABLE=microhildesk

GLIB_COMPILE_RESOURCES = $(shell pkg-config --variable=glib_compile_resources gio-2.0)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@ `pkg-config gtkmm-3.0 --libs`

resources.c: ../resource/microhildesk.gresource.xml ../resource/home.ui
	$(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=../resource --generate-source $<

.cc.o:
	$(CXX) $(CCFLAGS) $< -o $@ `pkg-config gtkmm-3.0 --cflags`

.c.o:
	$(CC) $(CFLAGS) $< -o $@ `pkg-config gio-2.0 --cflags`

clean:
	$(RM) -rf ../*/*.o ../*.o *.o resources.c $(EXECUTABLE)
