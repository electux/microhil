# microhil-base-ble

Bluetooth Low Energy (BLE) C firmware for the microHIL hardware controller (Raspberry Pi Pico W).

This component runs on the Raspberry Pi Pico W using the Raspberry Pi Pico SDK, CYW43439 wireless driver, and BTstack. It provides a wireless BLE UART (Nordic SPP) GATT service for remote HWIL control, relay management, status LEDs, and buzzer alerts.

## Features

- **8-Channel Relay Control:** Independent toggling, pulse duration, timing, and blinking cycles on 8 physical channels.
- **Wireless BLE SPP Transport:** Nordic UART Service (NUS) GATT implementation over Bluetooth Low Energy using BTstack.
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
│   ├── ble/                    # BLE transport, GAP, GATT SPP, and ring buffer
│   ├── command/                # Command parsing and dispatching
│   ├── device/                 # Hardware controllers (relays, LED, buzzer)
│   └── io/                     # Low-level I/O abstractions
└── build/                      # Build output directory (generates microhil-base-ble.uf2)
```

## Command Protocol

Communication occurs wirelessly over the BLE Nordic UART Service using structured command packets:
- **Input Frame Format:** `<command_string>`
- **Output Frame Format:** `<response_string>`

All packets are enclosed within `<` and `>`. Inside the packet, elements are separated by `#`.

### Command Reference

| Command | Action | Example Output / Response |
|---|---|---|
| `mh#sys#id#end` | Query system board identity | `<mh#sys#microhil-ble#end>` |
| `mh#sys#ver#end` | Query firmware version | `<mh#sys#microHIL v1.0.0#end>` |
| `mh#sys#status#end` | Query all channels status | `<mh#sys#00000000#end>` |
| `mh#sys#rst#end` | Trigger hardware watchdog reset | `<mh#sys#resetting#end>` |
| `mh#ch#<N>#on#end` | Turn channel N ON (1-8) | `<mh#ch#<N>#on#end>` |
| `mh#ch#<N>#off#end` | Turn channel N OFF (1-8) | `<mh#ch#<N>#off#end>` |
| `mh#ch#mask#<MASK>#end` | Apply 8-bit binary mask (e.g. `10101010`) | `<mh#ch#mask#<MASK>#end>` |
| `mh#ch#<N>#time#<SEC>#end` | Timer mode for channel N | `<mh#ch#<N>#time#<SEC>#end>` |
| `mh#ch#<N>#pulse#<MS>#end` | Pulse mode for channel N | `<mh#ch#<N>#pulse#<MS>#end>` |
| `mh#ch#<N>#blink#<ON>#<OFF>#<CNT>#end` | Blink mode for channel N | `<mh#ch#<N>#blink#...#end>` |

## Building and Flashing

```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)

# Flash to Raspberry Pi Pico W in BOOTSEL mode
cp src/microhil-base-ble.uf2 /media/$USER/RPI-RP2/
```
