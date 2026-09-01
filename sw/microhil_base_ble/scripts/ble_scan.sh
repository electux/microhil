#!/bin/bash
#
# BLE Scanner helper script for finding microhil-ble on Ubuntu 24.04
#
set -e

# Color definitions
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

echo -e "${BLUE}======================================================${NC}"
echo -e "${BLUE}       microhil-ble Scanner (Ubuntu 24.04)           ${NC}"
echo -e "${BLUE}======================================================${NC}"

# Check Bluetooth power state
if ! bluetoothctl show | grep -q "Powered: yes"; then
    echo -e "${YELLOW}[*] Bluetooth controller is OFF. Powering ON...${NC}"
    bluetoothctl power on
fi

echo -e "${CYAN}[*] Starting BLE device discovery (press Ctrl+C to stop)...${NC}"
echo -e "${CYAN}[*] Looking for device: 'microhil-ble'${NC}"
echo ""

# Run bluetoothctl with timeout or interactive monitoring
# We use bluetoothctl to scan for LE devices and highlight microhil-ble
bluetoothctl --timeout "${1:-15}" scan le 2>/dev/null | while read -r line; do
    if [[ "$line" =~ "microhil-ble" ]] || [[ "$line" =~ "Device " ]]; then
        if [[ "$line" =~ "microhil-ble" ]]; then
            echo -e "${GREEN}>>> FOUND MICROHIL-BLE: ${line}${NC}"
            
            # Extract MAC address if present
            mac=$(echo "$line" | grep -o -E '([[:xdigit:]]{1,2}:){5}[[:xdigit:]]{1,2}')
            if [ -n "$mac" ]; then
                echo -e "${GREEN}------------------------------------------------------${NC}"
                echo -e "${GREEN}MAC Address: ${mac}${NC}"
                echo -e "${GREEN}Use in microhildesk:${NC}"
                echo -e "  BLE Device Address / Name : ${mac}  (or 'microhil-ble')"
                echo -e "  Service UUID             : 6e400001-b5a3-f393-e0a9-e50e24dcca9e"
                echo -e "  RX Characteristic UUID   : 6e400003-b5a3-f393-e0a9-e50e24dcca9e"
                echo -e "  TX Characteristic UUID   : 6e400002-b5a3-f393-e0a9-e50e24dcca9e"
                echo -e "${GREEN}------------------------------------------------------${NC}"
            fi
        else
            echo "$line"
        fi
    fi
done

echo ""
echo -e "${BLUE}[*] Known / Discovered devices in BlueZ cache:${NC}"
bluetoothctl devices | grep -i "microhil" || bluetoothctl devices
