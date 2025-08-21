#
# @brief   microhildesk
# @version 1.1.6
# @date    2024-07-21 16:05:11.326670
# @company None, free software to use 2024
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

include toolchain.mk
include cxxflags.mk
include odflags.mk
include csflags.mk
include sources.mk
include objects.mk

EXECUTABLE = microhildesk

LSS = \
	$(EXECUTABLE).lss

SIZEDUMMY = \
	sizedummy

CLEAN_LIST = \
	$(OBJECTS) \
	$(EXECUTABLE) \
	$(LSS) \
	$(SIZEDUMMY)

all: $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE).lss sizedummy

.cc.o:
	@echo 'Invoking: compile unit $<'
	$(CXX) $(CXXFLAGS) -o $@ $< `pkg-config --cflags gtkmm-4.0 libserial`
	@echo 'Finished compile unit $<'
	@echo ' '

$(EXECUTABLE):
	@echo 'Invoking: link executable $@'
	$(CXX) $(OBJECTS) -o $@ `pkg-config --libs gtkmm-4.0 libserial`
	@echo 'Finished link process: $@'
	@echo ' '

$(EXECUTABLE).lss:
	@echo 'Invoking: Display information from object $@'
	$(OD) $(ODFLAGS) $(EXECUTABLE)  > "$(EXECUTABLE).lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy:
	@echo 'Invoking: Displays the sizes of sections inside $@'
	$(CS) $(CSFLAGS) $(EXECUTABLE)
	@echo 'Finished building: $@'
	@echo ' '

clean:
	@echo 'Invoking: clean up project structure'
	@for item in $(CLEAN_LIST); do \
	if [ -e "$$item" ]; then \
		echo "$(RM) $$item"; \
		$(RM) $$item; \
	fi; \
	done
	@echo 'Finished clean up'
	@echo ' '

