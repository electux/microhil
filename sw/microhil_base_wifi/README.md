# microhil-base-wifi

Wi-Fi & TCP/IP Socket Server C firmware for the microHIL hardware controller (Raspberry Pi Pico W).

This component runs on the Raspberry Pi Pico W using the Raspberry Pi Pico SDK, CYW43439 wireless driver, lwIP TCP/IP stack, and non-volatile Flash memory (NVM). It provides a high-speed TCP socket server on port `5000` for remote HWIL relay control, status LED, buzzer notifications, and persistent runtime Wi-Fi provisioning over USB-Serial or TCP socket.

## Features

- **8-Channel Relay Control:** Independent toggling, pulse duration, timing, and blinking cycles on 8 physical channels.
- **Dual Wi-Fi Operation Modes:**
  - **Access Point (AP) Mode (Default):** Pico W broadcasts its own Wi-Fi hotspot (`SSID: microhil-wifi`, `IP: 192.168.4.1`, `Port: 5000`).
  - **Station (STA) Mode:** Connects to an existing Wi-Fi network with DHCP.
- **Dual-Stream Command Tokenizer:** Seamlessly receives and processes commands from both the Wi-Fi TCP socket and the USB CDC serial console.
- **Persistent NVM Configuration:** Store Wi-Fi credentials, mode, and port in RP2040 Flash memory.
- **Raw lwIP TCP Server:** High-throughput, non-blocking TCP socket server on port `5000`.
- **NeoPixel Status LED:** RGB status indication utilizing WS2812 PIO on GP13.
- **Buzzer Notification:** Sound alerts for startup and connection events using PWM on GP6.
- **Watchdog System Reset:** Soft system restart triggered via RP2040 hardware watchdog.

## Project Structure

```
sw/microhil_base_wifi/
├── CMakeLists.txt              # Top-level CMake configuration
├── src/                        # Core firmware source code
│   ├── CMakeLists.txt          # Target configuration and lwIP linking
│   ├── lwipopts.h              # lwIP stack configuration
│   ├── main.c                  # Main execution loop & system init
│   ├── config/                 # NVM Flash storage & default settings
│   │   ├── nvm_config.h/.c     # Flash read/write/checksum
│   │   └── wifi_default_config.h
│   ├── wifi/                   # Wi-Fi manager, TCP server & ring buffer
│   │   ├── wifi_manager.h/.c   # AP/STA mode management
│   │   ├── tcp_server.h/.c     # lwIP raw TCP socket server
│   │   ├── wifi_ring_buffer.h/.c
│   │   └── wifi_transport.h/.c # Unified transport facade
│   ├── command/                # Command parsing, network commands, and dispatching
│   │   ├── ble_command.h/.c    # Net command handlers
│   │   ├── command_tbl.c       # Command dispatch table
│   │   ├── parser.h/.c         # Dual-stream tokenizer
│   │   └── response.h/.c       # Formatted response emitter
│   ├── device/                 # Hardware controllers (relays, LED, buzzer)
│   ├── io/                     # Low-level I/O abstractions
│   └── ws2812/                 # WS2812 PIO driver
└── build/                      # Build output directory (generates microhil-base-wifi.uf2)
```

## Command Protocol

Communication occurs over the TCP socket connection (port 5000) or the USB CDC/ACM serial console using structured command packets:
- **Input Frame Format:** `<command_string>`
- **Output Frame Format:** `<response_string>`

All packets are enclosed within `<` and `>`. Inside the packet, elements are separated by `#`.

### Command Reference

| Command | Action | Example Output / Response |
|---|---|---|
| `mh#sys#id#end` | Query system board identity | `<mh#sys#mh:333:2023:0:wifi#end>` |
| `mh#sys#version#end` | Query firmware version | `<mh#sys#microHIL-WIFI v1.0.0#end>` |
| `mh#sys#reset#end` | Trigger hardware watchdog reset | `<mh#sys#system resetting...#end>` |
| `mh#net#get#end` | Query active network configuration | `<mh#net#cfg#AP#microhil-wifi#192.168.4.1#5000#end>` |
| `mh#net#set#ap#<SSID>#<PASS>#<IP>#<PORT>#end` | Configure AP mode, save to Flash & reboot | `<mh#net#ok#restarting#end>` |
| `mh#net#set#sta#<SSID>#<PASS>#<PORT>#end` | Configure STA mode, save to Flash & reboot | `<mh#net#ok#restarting#end>` |
| `mh#net#reset#end` | Restore default Wi-Fi settings in Flash & reboot | `<mh#net#ok#default_restored#end>` |
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
cp src/microhil-base-wifi.uf2 /media/$USER/RPI-RP2/
```
