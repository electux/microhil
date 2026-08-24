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

[![microhil_base C checker](https://github.com/electux/microhil/actions/workflows/microhil_base_c_checker.yml/badge.svg)](https://github.com/electux/microhil/actions/workflows/microhil_base_c_checker.yml) [![microhil_nuttx C checker](https://github.com/electux/microhil/actions/workflows/microhil_nuttx_c_checker.yml/badge.svg)](https://github.com/electux/microhil/actions/workflows/microhil_nuttx_c_checker.yml) [![microhil_upy C checker](https://github.com/electux/microhil/actions/workflows/microhil_upy_c_checker.yml/badge.svg)](https://github.com/electux/microhil/actions/workflows/microhil_upy_c_checker.yml)

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
```
TODO
```

**microhil-upy**
```
TODO
```

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
```
TODO
```

To install **microhil-nuttx** type the following
```
TODO
```

To install **microhil-upy** type the following
```
TODO
```

#### SW Desktop Application installation

To install **microhildesk** type the following
```
TODO
```

### Dependencies

#### SW Firmware Application dependencies

**microhil-base** requires next modules and libraries
```
TODO
```

**microhil-nuttx** requires next modules and libraries
```
TODO
```

**microhil-upy** requires next modules and libraries
```
TODO
```

#### SW Desktop Application dependencies

**microhildesk** requires next modules and libraries
```
TODO
```

### Docs

[![Documentation Status](https://readthedocs.org/projects/microhil/badge/?version=latest)](https://microhil.readthedocs.io/projects/microhil/en/latest/?badge=latest)

More documentation and info at
* [https://microhil.readthedocs.io/en/latest/](https://microhil.readthedocs.io/en/latest/)
* [https://www.gnome.org](https://www.gnome.org/)

### Copyright and licence

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

Copyright (C) 2020 by [electux.github.io/microhil](https://electux.github.io/microhil)

**microhil** is free software; you can redistribute it and/or modify it.

Lets help and support Raspberry PI && GNOME.

<p align="center">
  <a href="https://www.raspberrypi.org/donate/">
    <img src="https://raw.githubusercontent.com/electux/microhil/master/docs/fondations.png" alt="GNOME&&RPi">
  </a>
</p>
