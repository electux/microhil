/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * wifi_manager.c
 * Copyright (C) 2025 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhil-base-wifi is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhil-base-wifi is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name. If not, see <http://www.gnu.org/licenses/>.
 */
#include "wifi_manager.h"
#include "dhcpserver.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>
#include <string.h>

static char s_current_ip[NVM_IP_MAX_LEN] = "0.0.0.0";
static bool s_is_ap_mode = true;
static dhcp_server_t s_dhcp_server;

bool wifi_manager_init(const nvm_wifi_config_t *config) {
	if (config == 0) {
		return false;
	}

	if (cyw43_arch_init_with_country(CYW43_COUNTRY_WORLDWIDE)) {
		printf("[Error] Failed to initialize CYW43 Wi-Fi hardware\n");
		return false;
	}

	if (config->mode == (uint8_t)WIFI_MODE_AP) {
		s_is_ap_mode = true;
		uint32_t auth = (strlen(config->password) >= 8) ? CYW43_AUTH_WPA2_MIXED_PSK : CYW43_AUTH_OPEN;
		cyw43_arch_enable_ap_mode(config->ssid, config->password, auth);

		ip4_addr_t gw;
		ip4_addr_t mask;
		if (!ip4addr_aton(config->ip, &gw)) {
			IP4_ADDR(&gw, 192, 168, 4, 1);
		}
		IP4_ADDR(&mask, 255, 255, 255, 0);

		netif_set_addr(&cyw43_state.netif[CYW43_ITF_AP], &gw, &mask, &gw);
		netif_set_up(&cyw43_state.netif[CYW43_ITF_AP]);
		netif_set_link_up(&cyw43_state.netif[CYW43_ITF_AP]);

		dhcp_server_init(&s_dhcp_server, &cyw43_state.netif[CYW43_ITF_AP], &gw, &mask);

		strncpy(s_current_ip, config->ip, NVM_IP_MAX_LEN - 1);
		printf("[Info] Wi-Fi AP '%s' started on IP %s with DHCP server\n", config->ssid, s_current_ip);
		return true;
	}

	s_is_ap_mode = false;
	cyw43_arch_enable_sta_mode();
	printf("[Info] Connecting to Wi-Fi '%s'...\n", config->ssid);

	uint32_t auth = (strlen(config->password) > 0) ? CYW43_AUTH_WPA2_MIXED_PSK : CYW43_AUTH_OPEN;

	if (cyw43_arch_wifi_connect_async(config->ssid, config->password, auth) != 0) {
		printf("[Warning] Failed to start Wi-Fi station connection\n");
	}

	return true;
}

bool wifi_manager_is_connected(void) {
	if (s_is_ap_mode) {
		return true;
	}

	int status = cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA);
	return (status == CYW43_LINK_UP);
}

const char *wifi_manager_get_ip(void) {
	if (!s_is_ap_mode && wifi_manager_is_connected()) {
		const ip4_addr_t *ip = netif_ip4_addr(netif_default ? netif_default : &cyw43_state.netif[CYW43_ITF_STA]);
		if (ip != 0) {
			snprintf(s_current_ip, sizeof(s_current_ip), "%s", ip4addr_ntoa(ip));
		}
	}

	return s_current_ip;
}
