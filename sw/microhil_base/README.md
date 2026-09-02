# microhil-base

C-based firmware for the microHIL hardware controller (Raspberry Pi Pico).

This component serves as the direct hardware interface layer for the Raspberry Pi Pico (RP2040). It manages physical relays, status LEDs, and buzzer alerts by parsing and executing command packets received over the standard USB CDC/ACM serial interface.

## Features

- **8-Channel Relay Control:** Independent toggling, pulse duration, timing, and blinking cycles on 8 physical channels (GP21 to GP14).
- **USB CDC/ACM Serial Transport:** Non-blocking buffered serial communication over USB.
- **NeoPixel Status LED:** RGB status indication utilizing WS2812 PIO on GP13.
- **Buzzer Notification:** Sound alerts for startup (1 beep) and USB host serial connection (2 beeps) using PWM on GP6.
- **Watchdog System Reset:** Soft system restart triggered via RP2040 hardware watchdog.

## Project Structure

```
sw/microhil_base/
├── CMakeLists.txt              # Top-level CMake configuration
├── src/                        # Core firmware source code
│   ├── CMakeLists.txt          # Target configuration and Pico SDK linking
│   ├── main.c                  # Main execution loop & system init
│   ├── command/                # Command parsing and dispatching
│   ├── device/                 # Hardware controllers (relays, LED, buzzer)
│   ├── io/                     # Low-level I/O abstractions
│   ├── serial/                 # USB serial transport & ring buffer
│   └── ws2812/                 # WS2812 PIO driver
└── build/                      # Build output directory (generates microhil-base.uf2)
```

## Command Protocol

Communication occurs over the USB CDC/ACM serial interface using structured command packets:
- **Input Frame Format:** `<command_string>`
- **Output Frame Format:** `<response_string>`

All packets are enclosed within `<` and `>`. Inside the packet, elements are separated by `#`.

### Command Reference

| Command | Action | Example Output / Response |
|---|---|---|
| `mh#sys#id#end` | Query system board identity | `<mh#sys#mh:333:2023:0:base#end>` |
| `mh#sys#version#end` | Query firmware version | `<mh#sys#microHIL-BASE v1.0.0#end>` |
| `mh#sys#reset#end` | Trigger hardware watchdog reset | `<mh#sys#system resetting...#end>` |
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

# Flash to Raspberry Pi Pico in BOOTSEL mode
cp src/microhil-base.uf2 /media/$USER/RPI-RP2/
```
