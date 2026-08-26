# microhil-nuttx

Apache NuttX RTOS-based C firmware for the microHIL hardware controller (Raspberry Pi Pico).

This component manages physical relays, status LEDs, and buzzer alerts on the Raspberry Pi Pico by running a background daemon task on the Apache NuttX RTOS. It connects to the host PC via USB CDCACM serial emulation, parsing and executing command packets.

## Features

- **8-Channel Relay Control:** Independent toggling, pulse duration, timing, and blinking cycles on 8 physical channels (GP21 to GP14).
- **NeoPixel Status LED:** RGB status indication utilizing the NuttX WS2812 driver on pin GP13.
- **Buzzer Notification:** Sound alerts for startup (1 beep) and USB host serial connection (2 beeps) utilizing the NuttX PWM driver (Slice 3, Pin GP6).
- **Watchdog System Reset:** Soft system restart triggered via NuttX boardctl system reset.
- **Boot Autostart Loop:** Automatic connection of the USB controller and redirection of standard input/output streams to `/dev/ttyACM0` asynchronously at boot.

## Project Structure

```
sw/microhil_nuttx/
├── Makefile                    # Automation tool for NuttX config, build, and deploy
├── nuttx/                      # Apache NuttX kernel submodule (RTOS kernel)
├── apps/                       # Apache NuttX apps repository
│   └── microhil/               # Core firmware source code
│       ├── CMakeLists.txt      # CMake build script
│       ├── Kconfig             # Menuconfig properties (priority, stack)
│       ├── Make.defs           # Classic Make build definitions
│       ├── Makefile            # App Make recipe
│       ├── microhil_main.c     # Main daemon loop & hardware setup
│       ├── command/            # Command parsing and dispatching module
│       │   ├── microhil_parser.h
│       │   ├── microhil_parser.c
│       │   ├── microhil_cmd.h
│       │   ├── microhil_cmd.c
│       │   ├── microhil_dispatcher.h
│       │   └── microhil_dispatcher.c
│       └── controllers/        # Hardware driver controller wrappers
│           ├── microhil_led.h
│           ├── microhil_led.c
│           ├── microhil_buzzer.h
│           ├── microhil_buzzer.c
│           ├── microhil_relay.h
│           └── microhil_relay.c
└── build/                      # Build output directory
    └── deploy/                 # Deployment target outputs
        ├── apps/               # Source copy of the microhil app
        └── nuttx/              # NuttX OS compiled binary (microhil-nuttx.uf2)
```

## Command Protocol

Communication occurs over the USB CDC/ACM serial interface (`/dev/ttyACM0` on the Pico, mapped to stdin/stdout inside the daemon) using characters processed non-blockingly.

- **Input Frame Format:** `<command_string>`
- **Output Frame Format:** `<response_string>`

All packets are enclosed within `<` and `>`. Inside the packet, elements are separated by `#`.

### Command Reference

| Command | Action | Example Output / Response |
|---------|--------|----------------------------|
| `mh#sys#id#end` | Query hardware board identification | `<mh#sys#mh:333:2023:0#end>` |
| `mh#sys#version#end` | Query firmware version | `<mh#sys#microHIL v1.0.0#end>` |
| `mh#sys#reset#end` | Trigger hardware watchdog reset | `<mh#sys#system resetting...#end>` |
| `mh#all#on#end` | Turn all relay channels ON | `<mh#sys#all channels on#end>` |
| `mh#all#off#end` | Turn all relay channels OFF | `<mh#sys#all channels off#end>` |
| `mh#all#stat#end` | Get state of all relay channels | `<mh#sys#channels: 1:OFF 2:OFF ... 8:OFF#end>` |
| `mh#ch#<ch>#on#end` | Turn channel `<ch>` ON (1-indexed) | `<mh#sys#channel 1 on#end>` |
| `mh#ch#<ch>#off#end` | Turn channel `<ch>` OFF (1-indexed) | `<mh#sys#channel 1 off#end>` |
| `mh#ch#<ch>#tmr#<s>#end` | Turn channel `<ch>` ON for `<s>` seconds | `<mh#sys#channel 1 timer started: 10 seconds#end>` |
| `mh#ch#<ch>#pulse#<ms>#end` | Pulse channel `<ch>` for `<ms>` milliseconds | `<mh#sys#channel 1 pulse started: 500 ms#end>` |
| `mh#ch#<ch>#blink#<on_ms>#<off_ms>#<n>#end` | Blink channel `<ch>` `<n>` times | `<mh#sys#channel 1 blink started: on=200 ms, off=200 ms, count=5#end>` |
| `mh#ch#<ch>#stat#end` | Get detailed status of channel `<ch>` | `<mh#sys#ch:1:OFF:TOGGLE#end>` |
| `mh#all#mask#<mask>#end` | Apply 8-bit binary mask (e.g. `10101010`) | `<mh#sys#channels mask applied: 10101010#end>` |

*Note: `<ch>` ranges from `1` to `8`.*

## Compilation & Deployment

The build system automatically bootstraps, configures, compiles, and packages the binary into the deployment layout:

### 1. Build and Deploy
To configure (if `.config` is missing) and compile the firmware binary:
```bash
make
```
This produces `build/deploy/nuttx/microhil-nuttx.uf2`.

### 2. Flash to Hardware
1. Connect the Raspberry Pi Pico to your PC while holding the physical **BOOTSEL** button.
2. Run:
   ```bash
   make flash
   ```
   This will automatically locate the Pico's mass storage mount path and copy the `.uf2` binary onto it.
