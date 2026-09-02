#!/bin/bash
#
# microhil-ble Connect/Disconnect Stress & Verification Test
# Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
#
# microhil-base-ble is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#

set -e

# Color definitions
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

TARGET_MAC="$1"
ITERATIONS="${2:-5}"
DELAY_SEC="${3:-2}"

echo -e "${BLUE}======================================================${NC}"
echo -e "${BLUE}     microhil-ble Reconnect Test (${ITERATIONS} Cycles)       ${NC}"
echo -e "${BLUE}======================================================${NC}"

# If MAC is not provided as argument, resolve it from BlueZ
if [ -z "$TARGET_MAC" ]; then
    echo -e "${CYAN}[*] Searching for 'microhil-ble' in BlueZ cache...${NC}"
    PICO_DEV=$(bluetoothctl devices | grep -i "microhil" | head -n 1 || true)
    if [ -n "$PICO_DEV" ]; then
        TARGET_MAC=$(echo "$PICO_DEV" | awk '{print $2}')
        echo -e "    ${GREEN}Found microhil-ble MAC: ${TARGET_MAC}${NC}"
    else
        echo -e "    ${YELLOW}Device not found in cache. Scanning for 5 seconds...${NC}"
        bluetoothctl --timeout 5 scan le >/dev/null 2>&1 || true
        PICO_DEV=$(bluetoothctl devices | grep -i "microhil" | head -n 1 || true)
        if [ -n "$PICO_DEV" ]; then
            TARGET_MAC=$(echo "$PICO_DEV" | awk '{print $2}')
            echo -e "    ${GREEN}Discovered microhil-ble MAC: ${TARGET_MAC}${NC}"
        else
            echo -e "${RED}[!] Error: 'microhil-ble' device not found. Make sure Pico W is powered on.${NC}"
            exit 1
        fi
    fi
fi

# Ensure device is disconnected before starting
cleanup() {
    echo -e "\n${YELLOW}[*] Cleaning up connection to ${TARGET_MAC}...${NC}"
    bluetoothctl disconnect "$TARGET_MAC" >/dev/null 2>&1 || true
}
trap cleanup EXIT INT TERM

SUCCESS_COUNT=0
FAIL_COUNT=0

for i in $(seq 1 "$ITERATIONS"); do
    echo -e "\n${CYAN}--- Cycle ${i} / ${ITERATIONS} ---${NC}"

    # Connect
    echo -e "  [*] Connecting to ${TARGET_MAC}..."
    CONNECT_OUT=$(bluetoothctl connect "$TARGET_MAC" 2>&1 || true)
    
    if echo "$CONNECT_OUT" | grep -iq "Connection successful"; then
        echo -e "  [+] ${GREEN}Connected successfully.${NC}"
    else
        # Verify via info
        IS_CONN=$(bluetoothctl info "$TARGET_MAC" | grep -i "Connected: yes" || true)
        if [ -n "$IS_CONN" ]; then
            echo -e "  [+] ${GREEN}Connected successfully (verified).${NC}"
        else
            echo -e "  [-] ${RED}Connect FAILED:${NC} ${CONNECT_OUT}"
            FAIL_COUNT=$((FAIL_COUNT + 1))
            sleep "$DELAY_SEC"
            continue
        fi
    fi

    # Hold connection briefly
    sleep "$DELAY_SEC"

    # Disconnect
    echo -e "  [*] Disconnecting from ${TARGET_MAC}..."
    DISCONN_OUT=$(bluetoothctl disconnect "$TARGET_MAC" 2>&1 || true)
    
    if echo "$DISCONN_OUT" | grep -iq "Successful disconnected"; then
        echo -e "  [+] ${GREEN}Disconnected successfully.${NC}"
        SUCCESS_COUNT=$((SUCCESS_COUNT + 1))
    else
        IS_DISCONN=$(bluetoothctl info "$TARGET_MAC" | grep -i "Connected: no" || true)
        if [ -n "$IS_DISCONN" ]; then
            echo -e "  [+] ${GREEN}Disconnected successfully (verified).${NC}"
            SUCCESS_COUNT=$((SUCCESS_COUNT + 1))
        else
            echo -e "  [-] ${RED}Disconnect FAILED:${NC} ${DISCONN_OUT}"
            FAIL_COUNT=$((FAIL_COUNT + 1))
        fi
    fi

    # Delay between cycles for advertising re-engagement
    sleep "$DELAY_SEC"
done

echo -e "\n${BLUE}======================================================${NC}"
echo -e "${BLUE}                   Test Summary                       ${NC}"
echo -e "${BLUE}======================================================${NC}"
echo -e "  Total Cycles : ${ITERATIONS}"
echo -e "  ${GREEN}Passed       : ${SUCCESS_COUNT}${NC}"
if [ "$FAIL_COUNT" -gt 0 ]; then
    echo -e "  ${RED}Failed       : ${FAIL_COUNT}${NC}"
else
    echo -e "  ${GREEN}Failed       : 0 (100% OK)${NC}"
fi
echo -e "${BLUE}======================================================${NC}"
