# microhil-base-ble

Bluetooth Low Energy (BLE) C firmware for the microHIL hardware controller (Raspberry Pi Pico W).

This component runs on the Raspberry Pi Pico W using the Raspberry Pi Pico SDK, CYW43439 wireless driver, BTstack, and non-volatile Flash memory (NVM). It provides a wireless BLE UART (Nordic SPP) GATT service for remote HWIL control, relay management, status LEDs, buzzer alerts, and persistent BLE parameter provisioning over USB-Serial or BLE.

## Features

- **8-Channel Relay Control:** Independent toggling, pulse duration, timing, and blinking cycles on 8 physical channels.
- **Wireless BLE SPP Transport:** Nordic UART Service (NUS) GATT implementation over Bluetooth Low Energy using BTstack.
- **Dual-Stream Command Tokenizer:** Seamlessly receives and processes commands from both the wireless BLE stream and the USB CDC serial console.
- **Persistent NVM Configuration:** Store custom advertising device name, advertising interval, and passkey in RP2040 Flash memory.
- **NeoPixel Status LED:** RGB status indication utilizing WS2812 PIO on GP13.
- **Buzzer Notification:** Sound alerts for startup and connection events using PWM on GP6.
- **Watchdog System Reset:** Soft system restart triggered via RP2040 hardware watchdog.

## Project Structure

```
sw/microhil_base_ble/
├── CMakeLists.txt              # Top-level CMake configuration
├── src/                        # Core firmware source code
│   ├── CMakeLists.txt          # Target configuration and BTstack linking
│   ├── main.c                  # Main execution loop & system init
│   ├── btstack_config.h        # BTstack profile and memory configuration
│   ├── config/                 # NVM Flash storage & default settings
│   │   ├── nvm_config.h/.c     # Flash read/write/checksum
│   │   └── ble_default_config.h
│   ├── ble/                    # BLE transport, GAP, GATT SPP, and ring buffer
│   ├── command/                # Command parsing, BLE commands, and dispatching
│   ├── device/                 # Hardware controllers (relays, LED, buzzer)
│   ├── io/                     # Low-level I/O abstractions
│   └── ws2812/                 # WS2812 PIO driver
└── build/                      # Build output directory (generates microhil-base-ble.uf2)
```

## Command Protocol

Communication occurs wirelessly over the BLE Nordic UART Service or over the USB CDC/ACM serial console using structured command packets:
- **Input Frame Format:** `<command_string>`
- **Output Frame Format:** `<response_string>`

All packets are enclosed within `<` and `>`. Inside the packet, elements are separated by `#`.

### Command Reference

| Command | Action | Example Output / Response |
|---|---|---|
| `mh#sys#id#end` | Query system board identity | `<mh#sys#mh:333:2023:0:ble#end>` |
| `mh#sys#version#end` | Query firmware version | `<mh#sys#microHIL-BLE v1.0.0#end>` |
| `mh#sys#reset#end` | Trigger hardware watchdog reset | `<mh#sys#system resetting...#end>` |
| `mh#ble#get#end` | Query active BLE configuration | `<mh#ble#cfg#microhil-ble#50#0#end>` |
| `mh#ble#set#<NAME>#<INT_MS>#<PIN>#end` | Set BLE name, interval & PIN, save to Flash & reboot | `<mh#ble#ok#restarting#end>` |
| `mh#ble#reset#end` | Restore default BLE settings in Flash & reboot | `<mh#ble#ok#default_restored#end>` |
| `mh#all#on#end` | Turn all channels ON | `<mh#sys#all channels on#end>` |
| `mh#all#off#end` | Turn all channels OFF | `<mh#sys#all channels off#end>` |
| `mh#all#stat#end` | Query all channels status | `<mh#sys#channels: 1:OFF 2:OFF ... 8:OFF#end>` |
| `mh#ch#<N>#on#end` | Turn channel N ON (1-8) | `<mh#sys#channel <N> on#end>` |
| `mh#ch#<N>#off#end` | Turn channel N OFF (1-8) | `<mh#sys#channel <N> off#end>` |
| `mh#ch#<N>#stat#end` | Query status of channel N (1-8) | `<mh#sys#channel <N>: OFF#end>` |
| `mh#ch#<N>#tmr#<SEC>#end` | Timer mode for channel N | `<mh#sys#channel <N> timer started: <SEC> seconds#end>` |
| `mh#ch#<N>#pulse#<MS>#end` | Pulse mode for channel N | `<mh#sys#channel <N> pulse started: <MS> ms#end>` |
| `mh#ch#<N>#blink#<ON>#<OFF>#<CNT>#end` | Blink mode for channel N | `<mh#sys#channel <N> blink started: on=<ON> ms, off=<OFF> ms, count=<CNT>#end>` |
| `mh#all#mask#<MASK>#end` | Apply 8-bit binary mask (e.g. `10101010`) | `<mh#sys#channels mask applied: 10101010#end>` |

## Building and Flashing

```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)

# Flash to Raspberry Pi Pico W in BOOTSEL mode
cp src/microhil-base-ble.uf2 /media/$USER/RPI-RP2/
```
