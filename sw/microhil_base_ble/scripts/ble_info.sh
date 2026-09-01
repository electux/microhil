#!/bin/bash
#
# BLE Diagnostic & Info script for Ubuntu 24.04
#
set -e

# Color definitions
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

echo -e "${BLUE}======================================================${NC}"
echo -e "${BLUE}       microhil-ble Diagnostics (Ubuntu 24.04)        ${NC}"
echo -e "${BLUE}======================================================${NC}"

# Check system bluetooth service
echo -e "${CYAN}[1] Bluetooth Service Status:${NC}"
systemctl is-active bluetooth >/dev/null && echo -e "  ${GREEN}Service: active (running)${NC}" || echo -e "  ${YELLOW}Service: inactive${NC}"

# Check local controller
echo -e "\n${CYAN}[2] Local Bluetooth Controller:${NC}"
bluetoothctl show | grep -E "Controller|Name|Powered|Discovering" | sed 's/^/  /'

# Check for microhil-ble device
echo -e "\n${CYAN}[3] Checking for microhil-ble in BlueZ cache:${NC}"
pico_dev=$(bluetoothctl devices | grep -i "microhil" || true)
if [ -n "$pico_dev" ]; then
    echo -e "  ${GREEN}Found: ${pico_dev}${NC}"
    mac=$(echo "$pico_dev" | awk '{print $2}')
    echo -e "\n${CYAN}[4] Device Details for ${mac}:${NC}"
    bluetoothctl info "$mac" | grep -E "Device|Name|Alias|Connected|Paired|RSSI|UUID" | sed 's/^/  /'
else
    echo -e "  ${YELLOW}Device 'microhil-ble' not yet cached in BlueZ.${NC}"
    echo -e "  Run: ${GREEN}./scripts/ble_scan.sh${NC} to discover it."
fi

echo -e "\n${BLUE}======================================================${NC}"
echo -e "${BLUE} Recommended settings for microhildesk:${NC}"
echo -e "  Device Name / MAC : microhil-ble (or MAC from scan)"
echo -e "  Service UUID      : 6e400001-b5a3-f393-e0a9-e50e24dcca9e"
echo -e "  RX UUID           : 6e400003-b5a3-f393-e0a9-e50e24dcca9e"
echo -e "  TX UUID           : 6e400002-b5a3-f393-e0a9-e50e24dcca9e"
echo -e "${BLUE}======================================================${NC}"
