# microhildesk

Desktop GUI orchestration and control panel for the microHIL hardware controller.

`microhildesk` is a modern C++ desktop application built with `gtkmm-4.0` (GTK4), providing a visual dashboard for configuring, monitoring, and controlling 8-channel microHIL devices over multiple communication protocols.

## Features

- **Multi-Transport Communication:**
  - **Serial (USB CDC / UART):** Connects to microHIL over standard serial ports with configurable baud rates and timeout controls.
  - **TCP/IP Socket:** Communicates with `microhil-base-wifi` over raw TCP/IP sockets (default port `5000`).
  - **Bluetooth Low Energy (BLE):** Discovers, connects, and streams data wirelessly to `microhil-base-ble` via Linux BlueZ D-Bus Nordic UART Service (NUS).
- **Interactive Control Dashboard:**
  - 8 independent channel widgets supporting **Toggle**, **Timer**, **Pulse**, and **Blink** modes.
  - Global channel controls: Turn all ON, turn all OFF, apply 8-bit binary masks.
  - Real-time channel state feedback and synchronization.
- **Console & Logging:** Monospaced live terminal log display for tracking sent commands and device responses.
- **Device Diagnostics:** Automated initial handshaking, board identification querying, firmware version detection, and remote system reset.

## Architecture

```
sw/microhildesk/
├── application.cc/.h           # Gtk::Application lifecycle management
├── app_controller.cc/.h        # Main application controller & coordinator
├── com/                        # Transport communication layer
│   ├── icom.h                  # Abstract communication interface
│   ├── switchable_com.cc/.h    # Multi-transport router (Serial, TCP, BLE)
│   ├── serial/                 # POSIX serial port implementation
│   ├── tcp/                    # BSD socket TCP/IP implementation
│   └── ble/                    # BlueZ D-Bus BLE client & GATT resolvers
├── model/                      # Application state & settings data models
├── view/                       # GTK4 UI views & widgets
│   ├── home.cc/.h              # Main window & terminal console
│   ├── channel/                # Channel frame widgets and mode sub-pages
│   └── settings/               # Settings dialogs (General, Serial, TCP, BLE, Log)
├── worker/                     # Asynchronous non-blocking background I/O worker
└── command/                    # Command formatters and response processors
```

## Dependencies

- **Compiler:** C++23 standard compliant compiler (`g++` >= 13)
- **GUI Framework:** `gtkmm-4.0` / `gtk4`
- **D-Bus & Utilities:** `giomm-2.68`, `glibmm-2.68`, `sigc++-3.0`
- **Build System:** `make`

On Ubuntu 24.04 / Debian, install required packages:
```bash
sudo apt-get install -y libgtkmm-4.0-dev libsigc++-3.0-dev g++ make
```

## Building and Running

```bash
# Navigate to build directory
cd sw/microhildesk/build

# Build application
make -j$(nproc)

# Run application
./microhildesk
```
