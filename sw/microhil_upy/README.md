# microhil-upy

MicroPython-based firmware for the microHIL hardware controller (Raspberry Pi Pico).

This component manages physical relays, status LEDs, and buzzer alerts on the Raspberry Pi Pico by implementing a non-blocking event-driven loop that parses and executes serial commands.

## Features

- **8-Channel Relay Control:** Independent toggling, pulse duration, timing, and blinking cycles on 8 physical channels.
- **NEOPIXEL Status LED:** Visual status indication utilizing NeoPixel LEDs.
- **Buzzer Notification:** Sound alerts for start-up and channel toggles.
- **Watchdog System Reset:** Remote soft system restart via hardware watchdog.
- **Environment and Compile Tools:** Out-of-the-box local development stub setup and compilation tools to compile `.py` scripts to `.mpy` bytecodes.

## Project Structure

```
sw/microhil_upy/
├── Makefile                    # Automation tool for compiler & environment setup
├── requirements.txt            # Python development stub requirements
├── microhil_upy.code-workspace # VS Code workspace configuration
├── upy/                        # MicroPython submodule (source compiler)
├── apps/
│   └── microhil/               # Core firmware source code
│       ├── engine.py           # Main MicroHil class and execution loop
│       ├── drivers/            # Hardware drivers wrapper
│       │   ├── relay.py        # Pin controller for relays
│       │   ├── channel.py      # Behavioral coordinator for channels
│       │   ├── led.py          # NeoPixel status LED controller
│       │   ├── buzzer.py       # Passive/active buzzer controller
│       │   └── behaviors/      # Channel behavioral strategies
│       │       ├── base.py
│       │       ├── toggle.py   # Standard ON/OFF state
│       │       ├── timer.py    # Auto-off timer in seconds
│       │       ├── pulse.py    # Auto-off pulse in milliseconds
│       │       └── blink.py    # Periodic blinking cycles
│       └── commands/           # Command parsing and execution
│           ├── base.py         # Abstract command handler
│           ├── parser.py       # Serial character parser
│           └── ...             # Individual command implementations
└── build/                      # Build output folder for compiled MPY binaries
```

## Command Protocol

Communication occurs over the standard serial (USB CDC/UART) interface using characters processed non-blockingly via standard input (`sys.stdin`).

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
| `mh#all#stat#end` | Get state of all relay channels | `<mh#sys#channels: off off ... off#end>` |
| `mh#ch#<ch>#on#end` | Turn channel `<ch>` ON (1-indexed) | `<mh#sys#channel 1 on#end>` |
| `mh#ch#<ch>#off#end` | Turn channel `<ch>` OFF (1-indexed) | `<mh#sys#channel 1 off#end>` |
| `mh#ch#<ch>#tmr#<s>#end` | Turn channel `<ch>` ON for `<s>` seconds | `<mh#sys#channel 1 timer started: 10 seconds#end>` |
| `mh#ch#<ch>#pulse#<ms>#end` | Pulse channel `<ch>` for `<ms>` milliseconds | `<mh#sys#channel 1 pulse started: 500 ms#end>` |
| `mh#ch#<ch>#blink#<on_ms>#<off_ms>#<n>#end` | Blink channel `<ch>` `<n>` times | `<mh#sys#channel 1 blink started: on=200 ms, off=200 ms, count=5#end>` |
| `mh#ch#<ch>#stat#end` | Get detailed status of channel `<ch>` | `<mh#sys#Channel 1: OFF (Toggle)#end>` |
| `mh#all#mask#<mask>#end` | Apply 8-bit binary mask (e.g. `10101010`) | `<mh#sys#channels mask applied: 10101010#end>` |

*Note: `<ch>` ranges from `1` to `8`. Channel status response adapts dynamically to the current behavior (e.g., `<mh#sys#Channel 1: ON (Timer, rem: 8s)#end>`, `<mh#sys#Channel 1: ON (Pulse, rem: 420ms)#end>`, or `<mh#sys#Channel 1: ON (Blink, count: 3, phase: ON)#end>`).*

## Development Environment Setup

To set up a local workspace with full Python IDE typing stubs, auto-completion, and static analysis:

1. Create Python virtual environment and install stubs:
   ```bash
   make env
   ```
2. Open the directory in VS Code using the provided workspace configuration:
   ```bash
   code microhil_upy.code-workspace
   ```

## Compilation

To compile Python source files into compact `.mpy` binary bytecodes (which optimizes memory usage and performance on the Pico):

```bash
# Build the mpy-cross compiler (first run) and compile all source scripts
make
```

Compiled `.mpy` files will be outputted to `build/deploy/apps/microhil/`.

## Deployment

Deploy the firmware to your board (e.g., Raspberry Pi Pico) using `mpremote`, `ampy`, or `rshell`.

Using `mpremote` (recommended):

```bash
# Copy compiled mpy files to the root directory on the Pico
mpremote fs cp -r build/deploy/apps/microhil :

# OR deploy python source code directly (if debugging)
mpremote fs cp -r apps/microhil :
```

You can then run it interactively or configure `main.py` on the device to invoke `microhil.engine`:

```python
# main.py on the board
from microhil.engine import MicroHil

board = MicroHil()
while True:
    board.tick()
```
