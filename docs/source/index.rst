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

|microhil_base tests| |microhil_base_ble tests| |microhil_base_wifi tests| |microhil_nuttx tests| |microhil_upy tests| |microhildesk tests|

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

.. |microhildesk tests| image:: https://github.com/electux/microhil/actions/workflows/microhildesk_tests.yml/badge.svg
   :target: https://github.com/electux/microhil/actions/workflows/microhildesk_tests.yml

Installation
------------

Navigate to release `page`_ download and extract release archive.

.. _page: https://github.com/electux/microhil/releases

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

**microhildesk** requires next modules and libraries:

* **Runtime:**
  * ``libgtkmm-4.0-1`` | ``libgtkmm-4.0-1t64``
  * ``socat`` (for virtual serial ports)
* **Development / Build:**
  * ``pkg-config``
  * ``libgtkmm-4.0-dev``
  * C++17 compliant compiler (``g++``)

Project structure
------------------

The repository is organized as follows:

.. code-block:: text

   microhil/
   ├── docs/                   # Documentation files
   ├── hw/                     # Hardware design files (schematics, PCB layouts)
   └── sw/                     # Software and firmware source directories
       ├── microhil_base/            # C-based firmware for Pico (direct HWIL interface)
       ├── microhil_base_tests/      # Unit tests for microhil_base firmware
       ├── microhil_base_ble/        # C-based BLE firmware for Pico W (wireless HWIL interface)
       ├── microhil_base_ble_tests/  # Unit tests for microhil_base_ble firmware
       ├── microhil_base_wifi/       # C-based Wi-Fi firmware for Pico W (TCP socket HWIL interface)
       ├── microhil_base_wifi_tests/ # Unit tests for microhil_base_wifi firmware
       ├── microhil_nuttx/           # NuttX-based RTOS firmware for Pico
       ├── microhil_upy/             # MicroPython-based firmware for Pico
       ├── microhildesk/             # Desktop GUI application (gtkmm/C++)
       └── microhildesk_tests/       # Test suites for the desktop application

Copyright and licence
----------------------

microHIL Licenses
^^^^^^^^^^^^^^^^^^
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

