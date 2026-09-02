/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * dhcpserver.h
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
#pragma once

#include "lwip/ip_addr.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DHCPS_BASE_IP (16)
#define DHCPS_MAX_IP (8)

typedef struct _dhcp_server_lease_t {
	uint8_t mac[6];
	uint16_t expiry;
} dhcp_server_lease_t;

typedef struct _dhcp_server_t {
	ip_addr_t ip;
	ip_addr_t nm;
	dhcp_server_lease_t lease[DHCPS_MAX_IP];
	struct udp_pcb *udp;
} dhcp_server_t;

void dhcp_server_init(dhcp_server_t *d, struct netif *nif, ip_addr_t *ip, ip_addr_t *nm);
void dhcp_server_deinit(dhcp_server_t *d);

#ifdef __cplusplus
}
#endif
