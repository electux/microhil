# microHIL

<img align="right" src="https://raw.githubusercontent.com/electux/microhil/master/docs/microhil_logo.png" width="25%">

**microhil** is development device which can be used for **[HWIL](https://en.wikipedia.org/wiki/Hardware-in-the-loop_simulation)**.

The README is used to introduce the tool and provide instructions on
how to install the tool, any machine dependencies it may have and any
other information that should be provided before the tool is installed.

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [Statistics](#statistics)
  - [Contributing activities](#contributing-activities)
  - [SW Firmware checks](#sw-firmware-checks)
  - [SW Desktop checks](#sw-desktop-checks)
- [Development](#development)
  - [SW Firmware Application](#sw-firmware-application)
  - [SW Desktop Application](#sw-desktop-application)
- [Installation](#installation)
  - [SW Firmware Application installation](#sw-firmware-application-installation)
  - [SW Desktop Application installation](#sw-desktop-application-installation)
- [Dependencies](#dependencies)
  - [SW Firmware Application dependencies](#sw-firmware-application-dependencies)
  - [SW Desktop Application dependencies](#sw-desktop-application-dependencies)
- [Docs](#docs)
- [Copyright and licence](#copyright-and-licence)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

### Statistics

#### Contributing activities

[![GitHub issues open](https://img.shields.io/github/issues/electux/microhil.svg)](https://github.com/electux/microhil/issues) [![GitHub contributors](https://img.shields.io/github/contributors/electux/microhil.svg)](https://github.com/electux/microhil/graphs/contributors)

#### SW Firmware checks

[![microhil_base C checker](https://github.com/electux/microhil/actions/workflows/microhil_base_c_checker.yml/badge.svg)](https://github.com/electux/microhil/actions/workflows/microhil_base_c_checker.yml) [![microhil_nuttx C checker](https://github.com/electux/microhil/actions/workflows/microhil_nuttx_c_checker.yml/badge.svg)](https://github.com/electux/microhil/actions/workflows/microhil_nuttx_c_checker.yml) [![microhil_upy Python checker](https://github.com/electux/microhil/actions/workflows/microhil_upy_c_checker.yml/badge.svg)](https://github.com/electux/microhil/actions/workflows/microhil_upy_c_checker.yml)

#### SW Desktop checks

[![microhildesk build checker](https://github.com/electux/microhil/actions/workflows/microhil_desktop_cc_checker_build.yml/badge.svg)](https://github.com/electux/microhil/actions/workflows/microhil_desktop_cc_checker_build.yml) [![microhil-desktop build checker](https://github.com/electux/microhil/actions/workflows/microhil_desktop_cc_checker.yml/badge.svg)](https://github.com/electux/microhil/actions/workflows/microhil_desktop_cc_checker.yml)

### Development

#### SW Firmware Application

**microhil-base**

A C-based firmware designed for the microHIL hardware controller (Raspberry Pi Pico). It acts as the direct hardware interface layer, managing physical relays, status LEDs, and buzzer alerts by parsing and executing command protocols received over standard serial interfaces.

*   **Supported Operations:**
    *   **Channel Toggle:** Control individual relays (channels 1-8) by turning them ON or OFF.
    *   **Timer Mode:** Keep a channel active for a specified duration in seconds.
    *   **Pulse Mode:** Trigger a brief pulse on a channel for a duration specified in milliseconds.
    *   **Blink Mode:** Configure blinking loops with custom ON/OFF durations and a loop count.
    *   **Channel Masking:** Apply an 8-bit binary mask (e.g., `10101010`) to update all 8 channel states at once.
    *   **Status Monitoring:** Query the current state of a single channel or all channels.
    *   **System Reset:** Trigger a watchdog-based hardware reboot.
    *   **Diagnostics:** Query system board identity and firmware version info.

**microhil-nuttx**

An RTOS-based firmware built on Apache NuttX (v12.0.0+) for the microHIL hardware controller (Raspberry Pi Pico). It runs a low-latency, non-blocking background daemon (`microhil_daemon`) for controlling hardware channels and features a combined boot mode that exposes a NuttX Shell (NSH) console on the physical UART0 interface.

*   **Supported Operations:**
    *   **Background Daemon Execution:** Automatically initializes hardware channels, zujalica (buzzer) and WS2812 status LED upon boot.
    *   **Channel Control:** Turn individual relays (channels 1-8) ON or OFF.
    *   **Timer & Pulse Mode:** Activate channels with second-level precision or trigger millisecond-level pulses.
    *   **Blink Mode:** Trigger repeating blinking loops with configurable duty cycles and loop counts.
    *   **Combined Console Support:** Exposes standard NSH console on UART0 (GP0/GP1) for device diagnostics and `microhil` control daemon on the virtual USB CDC ACM serial interface (`/dev/ttyACM0`).
    *   **System Status & Reset:** Monitor real-time channel status and reboot the board remotely.

**microhil-upy**

A MicroPython-based firmware designed for the microHIL hardware controller (Raspberry Pi Pico). It implements a non-blocking execution loop that manages channel states, timer-based activities, status LEDs, and buzzer beeps by processing command strings in a structured `<mh#...#end>` format received over serial connections.

*   **Supported Operations:**
    *   **Channel Control:** Toggle channel state ON/OFF or apply an 8-bit channel mask.
    *   **Timer & Pulse Mode:** Activate a channel for a duration in seconds or trigger a millisecond-precision pulse.
    *   **Blink Mode:** Trigger repeating ON/OFF blinking cycles with a specific loop count.
    *   **System Status & Reset:** Monitor channel statuses and trigger remote system watchdog resets.
    *   **Diagnostics:** Query device version and identification details.

#### SW Desktop Application

**microhildesk**

A desktop GUI application built in C++ using `gtkmm`. It acts as the primary orchestration and control panel, allowing users to interact with and manage microHIL hardware controllers visually.

*   **Supported Operations:**
    *   **Multi-Interface Connectivity:** Switch and communicate seamlessly over Serial, TCP (Socket), and BLE (Bluetooth Low Energy) interfaces.
    *   **Visual Control Dashboard:** Visually toggle channel states, apply 8-bit channel masks, and monitor live statuses.
    *   **Advanced Control Configuration:** Configure and execute timer, pulse, and blinking tasks on hardware channels through the GUI.
    *   **Diagnostics & System Control:** Read connected board IDs/versions and trigger remote watchdog system resets.

### Installation

![Debian Linux OS](https://raw.githubusercontent.com/electux/microhil/master/docs/debtux.png)

Navigate to release **[page](https://github.com/electux/microhil/releases)** download and extract release archive.

#### SW Firmware Application installation

To install **microhil-base** type the following

```bash
# Clone the repository
git clone https://github.com/electux/microhil.git
cd microhil/sw/microhil_base

# Create build directory
mkdir build && cd build

# Configure build (ensure PICO_SDK_PATH is set)
cmake -DPICO_SDK_PATH=/path/to/pico-sdk ..

# Build
make

# Deploy by copying the generated microhil-base.uf2 file to the Pico mounted storage
cp src/microhil-base.uf2 /media/$USER/RPI-RP2/
```

To install **microhil-nuttx** type the following

```bash
# Clone the repository
git clone --recursive https://github.com/electux/microhil.git
cd microhil/sw/microhil_nuttx

# Configure the NuttX build system
cd nuttx
./tools/configure.sh raspberrypi-pico:usbnsh
cd ..

# Build the firmware
make

# Deploy by copying the generated microhil-nuttx.uf2 file to the Pico mounted storage
# Note: Ensure the Pico is in BOOTSEL mode before mounting
make flash
```

To install **microhil-upy** type the following

```bash
# Clone the repository
git clone https://github.com/electux/microhil.git
cd microhil/sw/microhil_upy

# Setup virtual environment and generate typings for development
make env

# Compile python source files to .mpy binaries
make

# Deploy to Raspberry Pi Pico (using mpremote or standard tool)
mpremote fs cp -r apps/microhil :
```

#### SW Desktop Application installation

To install **microhildesk** type the following

**From Source:**
```bash
# Clone the repository
git clone https://github.com/electux/microhil.git
cd microhil/sw/microhildesk/build

# Build the release version
make release

# Run the application
./microhildesk
```

**As a Debian Package (.deb):**
```bash
# Generate the .deb package
python3 sw/microhildesk/scripts/deb/create_deb.py

# Install the package
sudo dpkg -i sw/microhildesk/build/deb_dist/microhildesk_*.deb
```

### Dependencies

#### SW Firmware Application dependencies

**microhil-base** requires next modules and libraries

*   **Runtime:**
    *   Raspberry Pi Pico (RP2040) hardware
*   **Development / Build:**
    *   Raspberry Pi Pico SDK (`pico-sdk`)
    *   GNU Arm Embedded Toolchain (`gcc-arm-none-eabi`)
    *   `CMake` (v3.12+)

**microhil-nuttx** requires next modules and libraries

*   **Runtime:**
    *   Raspberry Pi Pico (RP2040) hardware
*   **Development / Build:**
    *   GNU Arm Embedded Toolchain (`gcc-arm-none-eabi`)
    *   `kconfig-frontends` (for NuttX configuration)
    *   `make` and standard Linux build tools

**microhil-upy** requires next modules and libraries

*   **Runtime:**
    *   MicroPython firmware (v1.20+) on Raspberry Pi Pico (RP2/RP2040)
*   **Development / Environment Setup:**
    *   `micropython-rp2-stubs` (for static analysis/autocomplete typings)
    *   `micropython-stdlib-stubs` (for standard library autocomplete typings)

#### SW Desktop Application dependencies

**microhildesk** requires next modules and libraries

*   **Runtime:**
    *   `libgtkmm-4.0-1` | `libgtkmm-4.0-1t64`
    *   `socat` (for virtual serial ports)
*   **Development / Build:**
    *   `pkg-config`
    *   `libgtkmm-4.0-dev`
    *   C++17 compliant compiler (`g++`)

### Docs

[![Documentation Status](https://readthedocs.org/projects/microhil/badge/?version=latest)](https://microhil.readthedocs.io/projects/microhil/en/latest/?badge=latest)

More documentation and info at
* [https://microhil.readthedocs.io/en/latest/](https://microhil.readthedocs.io/en/latest/)
* [https://www.gnome.org](https://www.gnome.org/)

### Copyright and licence

#### microHIL Licenses
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

**microhil** is free software and is dual-licensed under the **GPLv3** and **Apache 2.0** licenses. Copyright (C) 2020 - 2026 by [electux.github.io/microhil](https://electux.github.io/microhil).

#### Third-Party Component Licenses
This project utilizes several open-source technologies, each under their respective licenses:
*   **Apache NuttX RTOS:** Licensed under the [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0) license.
*   **MicroPython (uPy):** Licensed under the [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) license.
*   **GNOME / gtkmm:** Licensed under the [![License: LGPL v2.1](https://img.shields.io/badge/License-LGPL%20v2.1-blue.svg)](https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html) license.
*   **Raspberry Pi Pico SDK:** Licensed under the [![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause) license.

Lets help and support Raspberry PI, Nuttx, MicroPython and GNOME.

<p align="center">
  <a href="https://www.raspberrypi.org/donate/">
    <img src="https://raw.githubusercontent.com/electux/microhil/master/docs/fondations.png" alt="GNOME&&RPi">
  </a>
</p>
