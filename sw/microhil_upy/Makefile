MPY_CROSS = upy/mpy-cross/build/mpy-cross
BUILD_DIR = build/deploy
BOARD ?= RPI_PICO
PORT ?= /dev/ttyACM0

MOUNT_PATH ?= $(shell if [ -d "/media/$$USER/RPI-RP2" ]; then echo "/media/$$USER/RPI-RP2"; elif [ -d "/run/media/$$USER/RPI-RP2" ]; then echo "/run/media/$$USER/RPI-RP2"; fi)
UPY_FIRMWARE = $(BUILD_DIR)/upy/firmware.uf2

SRCS = $(shell find apps -name "*.py")
OBJS = $(patsubst %.py,$(BUILD_DIR)/%.mpy,$(SRCS))

.PHONY: all clean clean-compiler mpy-cross-compiler build firmware clean-firmware deploy reset repl ls flash

all: build

mpy-cross-compiler:
	@if [ ! -f $(MPY_CROSS) ]; then \
		echo "Building mpy-cross compiler..."; \
		$(MAKE) -C upy/mpy-cross COPT="-Wno-error"; \
	fi

$(BUILD_DIR)/%.mpy: %.py mpy-cross-compiler
	@mkdir -p $(dir $@)
	@echo "Compiling $< -> $@"
	@$(MPY_CROSS) -o $@ $<

build: $(OBJS)
	@echo "Build complete. Compiled files are ready in $(BUILD_DIR)/"

firmware:
	$(MAKE) -C upy/ports/rp2 BOARD=$(BOARD)
	@mkdir -p $(BUILD_DIR)/upy
	@cp upy/ports/rp2/build-$(BOARD)/firmware.uf2 $(UPY_FIRMWARE)
	@echo "Firmware copied to $(UPY_FIRMWARE)"

clean-firmware:
	$(MAKE) -C upy/ports/rp2 BOARD=$(BOARD) clean

flash:
	@if [ -z "$(MOUNT_PATH)" ]; then \
		echo "ERROR: Pico mount path RPI-RP2 not found under /media/$$USER/ or /run/media/$$USER/. Please connect Pico in BOOTSEL mode."; \
		exit 1; \
	fi
	@if [ ! -f "$(UPY_FIRMWARE)" ]; then \
		echo "ERROR: Local firmware.uf2 not found at $(UPY_FIRMWARE). Please run 'make firmware' first to compile it."; \
		exit 1; \
	fi
	echo "Flashing compiled firmware: $(UPY_FIRMWARE)..."
	cp $(UPY_FIRMWARE) $(MOUNT_PATH)/
	sync
	@echo "Successfully flashed! Pico should reboot now."

deploy: build
	.venv/bin/mpremote connect $(PORT) fs cp -r $(BUILD_DIR)/apps/microhil :
	.venv/bin/mpremote connect $(PORT) fs cp apps/main.py :

reset:
	.venv/bin/mpremote connect $(PORT) soft-reset

repl:
	.venv/bin/mpremote connect $(PORT) repl

ls:
	.venv/bin/mpremote connect $(PORT) fs ls

clean:
	@rm -rf $(BUILD_DIR)
	@echo "Cleaned build directory."

clean-compiler:
	$(MAKE) -C upy/mpy-cross clean

env:
	@echo "Setting up virtual environment..."
	python3 -m venv .venv
	.venv/bin/pip install -r requirements.txt
	@echo "Preparing typings..."
	mkdir -p typings
	cp -r .venv/lib/python3.*/site-packages/*.pyi typings/ 2>/dev/null || true
	cp -r .venv/lib/python3.*/site-packages/rp2 typings/ 2>/dev/null || true
	@echo "Creating symlinks for apps/microhil..."
	ln -sf ../../typings/machine.pyi apps/microhil/machine.pyi
	ln -sf ../../typings/rp2 apps/microhil/rp2
	ln -sf ../../typings/time.pyi apps/microhil/time.pyi
	ln -sf ../../typings/micropython.pyi apps/microhil/micropython.pyi
	ln -sf ../../typings/neopixel.pyi apps/microhil/neopixel.pyi
	ln -sf ../../typings/uselect.pyi apps/microhil/uselect.pyi
	ln -sf ../../typings/select.pyi apps/microhil/select.pyi
	@echo "Environment setup complete!"
