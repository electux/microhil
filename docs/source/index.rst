microhil
---------

**microhil** is development device which can be used for HWIL.

The README is used to introduce the tool and provide instructions on
how to install the tool, any machine dependencies it may have and any
other information that should be provided before the tool is installed.

.. toctree::
   :hidden:

   self

|GitHub issues| |Documentation Status| |GitHub contributors|

|microhil_base C checker| |microhil_base_ble C checker| |microhil_base_wifi C checker| |microhil_nuttx C checker| |microhil_upy Python checker|

|microhil_base tests| |microhil_base_ble tests| |microhil_base_wifi tests| |microhil_nuttx tests| |microhil_upy tests|

|microhildesk build checker| |microhil-desktop build checker|

|microhildesk tests|

.. |GitHub issues| image:: https://img.shields.io/github/issues/electux/microhil.svg
   :target: https://github.com/electux/microhil/issues

.. |GitHub contributors| image:: https://img.shields.io/github/contributors/electux/microhil.svg
   :target: https://github.com/electux/microhil/graphs/contributors

.. |Documentation Status| image:: https://readthedocs.org/projects/microhil/badge/?version=latest
   :target: https://microhil.readthedocs.io/projects/microhil/en/latest/?badge=latest

.. |microhil_base C checker| image:: https://github.com/electux/microhil/actions/workflows/microhil_base_c_checker.yml/badge.svg
   :target: https://github.com/electux/microhil/actions/workflows/microhil_base_c_checker.yml

.. |microhil_base_ble C checker| image:: https://github.com/electux/microhil/actions/workflows/microhil_base_ble_c_checker.yml/badge.svg
   :target: https://github.com/electux/microhil/actions/workflows/microhil_base_ble_c_checker.yml

.. |microhil_base_wifi C checker| image:: https://github.com/electux/microhil/actions/workflows/microhil_base_wifi_c_checker.yml/badge.svg
   :target: https://github.com/electux/microhil/actions/workflows/microhil_base_wifi_c_checker.yml

.. |microhil_nuttx C checker| image:: https://github.com/electux/microhil/actions/workflows/microhil_nuttx_c_checker.yml/badge.svg
   :target: https://github.com/electux/microhil/actions/workflows/microhil_nuttx_c_checker.yml

.. |microhil_upy Python checker| image:: https://github.com/electux/microhil/actions/workflows/microhil_upy_c_checker.yml/badge.svg
   :target: https://github.com/electux/microhil/actions/workflows/microhil_upy_c_checker.yml

.. |microhil_base tests| image:: https://github.com/electux/microhil/actions/workflows/microhil_base_tests.yml/badge.svg
   :target: https://github.com/electux/microhil/actions/workflows/microhil_base_tests.yml

.. |microhil_base_ble tests| image:: https://github.com/electux/microhil/actions/workflows/microhil_base_ble_tests.yml/badge.svg
   :target: https://github.com/electux/microhil/actions/workflows/microhil_base_ble_tests.yml

.. |microhil_base_wifi tests| image:: https://github.com/electux/microhil/actions/workflows/microhil_base_wifi_tests.yml/badge.svg
   :target: https://github.com/electux/microhil/actions/workflows/microhil_base_wifi_tests.yml

.. |microhil_nuttx tests| image:: https://github.com/electux/microhil/actions/workflows/microhil_nuttx_tests.yml/badge.svg
   :target: https://github.com/electux/microhil/actions/workflows/microhil_nuttx_tests.yml

.. |microhil_upy tests| image:: https://github.com/electux/microhil/actions/workflows/microhil_upy_tests.yml/badge.svg
   :target: https://github.com/electux/microhil/actions/workflows/microhil_upy_tests.yml

.. |microhildesk build checker| image:: https://github.com/electux/microhil/actions/workflows/microhil_desktop_cc_checker_build.yml/badge.svg
   :target: https://github.com/electux/microhil/actions/workflows/microhil_desktop_cc_checker_build.yml

.. |microhil-desktop build checker| image:: https://github.com/electux/microhil/actions/workflows/microhil_desktop_cc_checker.yml/badge.svg
   :target: https://github.com/electux/microhil/actions/workflows/microhil_desktop_cc_checker.yml

.. |microhildesk tests| image:: https://github.com/electux/microhil/actions/workflows/microhildesk_tests.yml/badge.svg
   :target: https://github.com/electux/microhil/actions/workflows/microhildesk_tests.yml

Development
-----------

SW Firmware Application
^^^^^^^^^^^^^^^^^^^^^^^

**microhil-base**

A C-based firmware designed for the microHIL hardware controller (Raspberry Pi Pico). It acts as the direct hardware interface layer, managing physical relays, status LEDs, and buzzer alerts by parsing and executing command protocols received over standard serial interfaces.

* **Supported Operations:**
  * **Channel Toggle:** Control individual relays (channels 1-8) by turning them ON or OFF.
  * **Timer Mode:** Keep a channel active for a specified duration in seconds.
  * **Pulse Mode:** Trigger a brief pulse on a channel for a duration specified in milliseconds.
  * **Blink Mode:** Configure blinking loops with custom ON/OFF durations and a loop count.
  * **Channel Masking:** Apply an 8-bit binary mask (e.g., ``10101010``) to update all 8 channel states at once.
  * **Status Monitoring:** Query the current state of a single channel or all channels.
  * **System Reset:** Trigger a watchdog-based hardware reboot.
  * **Diagnostics:** Query system board identity and firmware version info.

**microhil-base-ble**

A C-based firmware designed for the microHIL hardware controller (Raspberry Pi Pico W). It integrates the CYW43439 wireless chipset with the BTstack Bluetooth stack, exposing a Nordic BLE UART (SPP) GATT service for wireless HWIL control, physical relay management, status LEDs, and buzzer alerts.

* **Supported Operations:**
  * **Wireless BLE Transport:** Nordic UART Service (NUS) GATT implementation over Bluetooth Low Energy.
  * **Channel Toggle:** Control individual relays (channels 1-8) by turning them ON or OFF.
  * **Timer & Pulse Mode:** Activate channels with second-level precision or trigger millisecond-level pulses.
  * **Blink Mode:** Trigger repeating blinking loops with configurable duty cycles and loop counts.
  * **Channel Masking:** Apply an 8-bit binary mask (e.g., ``10101010``) to update all 8 channels at once.
  * **System Status & Reset:** Monitor channel status and reboot the board via hardware watchdog.
  * **Diagnostics:** Query device identification (``microhil-ble``) and firmware version details.

**microhil-base-wifi**

A C-based firmware designed for the microHIL hardware controller (Raspberry Pi Pico W). It utilizes the CYW43439 Wi-Fi chipset, lwIP raw TCP socket server, and on-board Flash NVM storage, allowing full remote HWIL control over Wi-Fi TCP/IP (Access Point or Station mode) with live USB-Serial network provisioning.

* **Supported Operations:**
  * **Wi-Fi & TCP Server:** Dual-mode Wi-Fi (AP hotspot on ``192.168.4.1`` or Station mode) hosting raw TCP server on port ``5000``.
  * **Persistent NVM Configuration:** Live parameter provisioning and Flash persistence (``<mh#net#...#end>``).
  * **Channel Toggle:** Control individual relays (channels 1-8) by turning them ON or OFF.
  * **Timer & Pulse Mode:** Activate channels with second-level precision or trigger millisecond-level pulses.
  * **Blink Mode:** Trigger repeating blinking loops with configurable duty cycles and loop counts.
  * **Channel Masking:** Apply an 8-bit binary mask (e.g., ``10101010``) to update all 8 channels at once.
  * **System Status & Reset:** Monitor channel status and reboot the board remotely.
  * **Diagnostics:** Query device identification (``microhil-wifi``) and network settings.

**microhil-nuttx**

An RTOS-based firmware built on Apache NuttX (v12.0.0+) for the microHIL hardware controller (Raspberry Pi Pico). It runs a low-latency, non-blocking background daemon (``microhil_daemon``) for controlling hardware channels and features a combined boot mode that exposes a NuttX Shell (NSH) console on the physical UART0 interface.

* **Supported Operations:**
  * **Background Daemon Execution:** Automatically initializes hardware channels, buzzer and WS2812 status LED upon boot.
  * **Channel Control:** Turn individual relays (channels 1-8) ON or OFF.
  * **Timer & Pulse Mode:** Activate channels with second-level precision or trigger millisecond-level pulses.
  * **Blink Mode:** Trigger repeating blinking loops with configurable duty cycles and loop counts.
  * **Combined Console Support:** Exposes standard NSH console on UART0 (GP0/GP1) for device diagnostics and ``microhil`` control daemon on the virtual USB CDC ACM serial interface (``/dev/ttyACM0``).
  * **System Status & Reset:** Monitor real-time channel status and reboot the board remotely.

**microhil-upy**

A MicroPython-based firmware designed for the microHIL hardware controller (Raspberry Pi Pico). It implements a non-blocking execution loop that manages channel states, timer-based activities, status LEDs, and buzzer beeps by processing command strings in a structured ``<mh#...#end>`` format received over serial connections.

* **Supported Operations:**
  * **Channel Control:** Toggle channel state ON/OFF or apply an 8-bit channel mask.
  * **Timer & Pulse Mode:** Activate a channel for a duration in seconds or trigger a millisecond-precision pulse.
  * **Blink Mode:** Trigger repeating ON/OFF blinking cycles with a specific loop count.
  * **System Status & Reset:** Monitor channel statuses and trigger remote system watchdog resets.
  * **Diagnostics:** Query device version and identification details.

SW Desktop Application
^^^^^^^^^^^^^^^^^^^^^^

**microhildesk**

A desktop GUI application built in C++ using ``gtkmm``. It acts as the primary orchestration and control panel, allowing users to interact with and manage microHIL hardware controllers visually.

* **Supported Operations:**
  * **Multi-Interface Connectivity:** Switch and communicate seamlessly over Serial, TCP (Socket), and BLE (Bluetooth Low Energy) interfaces.
  * **Visual Control Dashboard:** Visually toggle channel states, apply 8-bit channel masks, and monitor live statuses.
  * **Advanced Control Configuration:** Configure and execute timer, pulse, and blinking tasks on hardware channels through the GUI.
  * **Diagnostics & System Control:** Read connected board IDs/versions and trigger remote watchdog system resets.

Installation
------------

Navigate to release `page`_ download and extract release archive.

.. _page: https://github.com/electux/microhil/releases

SW Firmware Application installation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To install **microhil-base** type the following:

.. code-block:: bash

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

To install **microhil-base-ble** type the following:

.. code-block:: bash

   # Clone the repository
   git clone https://github.com/electux/microhil.git
   cd microhil/sw/microhil_base_ble

   # Create build directory
   mkdir build && cd build

   # Configure build (ensure PICO_SDK_PATH is set)
   cmake -DPICO_SDK_PATH=/path/to/pico-sdk ..

   # Build
   make

   # Deploy by copying the generated microhil-base-ble.uf2 file to the Pico W mounted storage
   cp src/microhil-base-ble.uf2 /media/$USER/RPI-RP2/

To install **microhil-base-wifi** type the following:

.. code-block:: bash

   # Clone the repository
   git clone https://github.com/electux/microhil.git
   cd microhil/sw/microhil_base_wifi

   # Create build directory
   mkdir build && cd build

   # Configure build (ensure PICO_SDK_PATH is set)
   cmake -DPICO_SDK_PATH=/path/to/pico-sdk ..

   # Build
   make

   # Deploy by copying the generated microhil-base-wifi.uf2 file to the Pico W mounted storage
   cp src/microhil-base-wifi.uf2 /media/$USER/RPI-RP2/

To install **microhil-nuttx** type the following:

.. code-block:: bash

   # Clone the repository recursively (to pull the NuttX submodule)
   git clone --recursive https://github.com/electux/microhil.git
   cd microhil/sw/microhil_nuttx

   # Build the firmware (automatically configures if .config is missing)
   make

   # Deploy by copying the generated microhil-nuttx.uf2 file to the Pico mounted storage
   # Note: Ensure the Pico is in BOOTSEL mode before running
   make flash

To install **microhil-upy** type the following:

.. code-block:: bash

   # Clone the repository recursively (to pull the MicroPython submodule)
   git clone --recursive https://github.com/electux/microhil.git
   cd microhil/sw/microhil_upy

   # Setup virtual environment and generate typings for development
   make env

   # Compile the MicroPython OS firmware image (.uf2) from source
   make firmware

   # Flash the compiled OS firmware to Raspberry Pi Pico (in BOOTSEL mode)
   make flash

   # Compile Python application scripts to .mpy bytecodes and stage deployment package
   make

   # Deploy the compiled scripts to Raspberry Pi Pico (using mpremote)
   make deploy

SW Desktop Application installation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To install **microhildesk** type the following:

**From Source:**

.. code-block:: bash

   # Clone the repository
   git clone https://github.com/electux/microhil.git
   cd microhil/sw/microhildesk/build

   # Build the release version
   make release

   # Run the application
   ./microhildesk

**As a Debian Package (.deb):**

.. code-block:: bash

   # Generate the .deb package
   python3 sw/microhildesk/scripts/deb/create_deb.py

   # Install the package
   sudo dpkg -i sw/microhildesk/build/deb_dist/microhildesk_*.deb

Dependencies
------------

SW Firmware Application dependencies
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**microhil-base** requires next modules and libraries:

* **Runtime:**
  * Raspberry Pi Pico (RP2040) hardware
* **Development / Build:**
  * Raspberry Pi Pico SDK (``pico-sdk``)
  * GNU Arm Embedded Toolchain (``gcc-arm-none-eabi``)
  * ``CMake`` (v3.12+)

**microhil-base-ble** requires next modules and libraries:

* **Runtime:**
  * Raspberry Pi Pico W (RP2040 + CYW43439) hardware
* **Development / Build:**
  * Raspberry Pi Pico SDK (``pico-sdk``) with BTstack & CYW43 driver support
  * GNU Arm Embedded Toolchain (``gcc-arm-none-eabi``)
  * ``CMake`` (v3.13+)

**microhil-base-wifi** requires next modules and libraries:

* **Runtime:**
  * Raspberry Pi Pico W (RP2040 + CYW43439) hardware
* **Development / Build:**
  * Raspberry Pi Pico SDK (``pico-sdk``) with lwIP & CYW43 driver support
  * GNU Arm Embedded Toolchain (``gcc-arm-none-eabi``)
  * ``CMake`` (v3.13+)

**microhil-nuttx** requires next modules and libraries:

* **Runtime:**
  * Raspberry Pi Pico (RP2040) hardware
* **Development / Build:**
  * GNU Arm Embedded Toolchain (``gcc-arm-none-eabi``)
  * ``kconfig-frontends`` (for NuttX configuration)
  * ``make`` and standard Linux build tools

**microhil-upy** requires next modules and libraries:

* **Runtime:**
  * MicroPython firmware (v1.20+) on Raspberry Pi Pico (RP2/RP2040)
* **Development / Environment Setup:**
  * ``micropython-rp2-stubs`` (for static analysis/autocomplete typings)
  * ``micropython-stdlib-stubs`` (for standard library autocomplete typings)

SW Desktop Application dependencies
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**microhildesk** requires next modules and libraries:

* **Runtime:**
  * ``libgtkmm-4.0-1`` | ``libgtkmm-4.0-1t64``
  * ``socat`` (for virtual serial ports)
* **Development / Build:**
  * ``pkg-config``
  * ``libgtkmm-4.0-dev``
  * C++23 compliant compiler (``g++``)

Docs
----

|Documentation Status|

More documentation and info at
* `https://microhil.readthedocs.io/en/latest/ <https://microhil.readthedocs.io/en/latest/>`_
* `https://www.gnome.org <https://www.gnome.org/>`_

Copyright and licence
---------------------

microHIL Licenses
^^^^^^^^^^^^^^^^^
|License: GPL v3| |License: Apache 2.0|

**microhil** is free software and is dual-licensed under the **GPLv3** and **Apache 2.0** licenses. Copyright (C) 2020 - 2026 by `electux.github.io/microhil <https://electux.github.io/microhil>`_.

Third-Party Component Licenses
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
This project utilizes several open-source technologies, each under their respective licenses:

* **Apache NuttX RTOS:** Licensed under the |License: Apache 2.0| license.
* **MicroPython (uPy):** Licensed under the |License: MIT| license.
* **GNOME / gtkmm:** Licensed under the |License: LGPL v2.1| license.
* **Raspberry Pi Pico SDK:** Licensed under the |License: BSD 3-Clause| license.

Lets help and support Raspberry PI, Nuttx, MicroPython and GNOME.

.. |License: GPL v3| image:: https://img.shields.io/badge/License-GPLv3-blue.svg
   :target: https://www.gnu.org/licenses/gpl-3.0

.. |License: Apache 2.0| image:: https://img.shields.io/badge/License-Apache%202.0-blue.svg
   :target: https://opensource.org/licenses/Apache-2.0

.. |License: MIT| image:: https://img.shields.io/badge/License-MIT-yellow.svg
   :target: https://opensource.org/licenses/MIT

.. |License: LGPL v2.1| image:: https://img.shields.io/badge/License-LGPL%20v2.1-blue.svg
   :target: https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html

.. |License: BSD 3-Clause| image:: https://img.shields.io/badge/License-BSD_3--Clause-blue.svg
   :target: https://opensource.org/licenses/BSD-3-Clause
