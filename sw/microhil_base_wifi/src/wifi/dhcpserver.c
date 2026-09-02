/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * dhcpserver.c
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
#include "dhcpserver.h"
#include "cyw43_config.h"
#include "lwip/udp.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define DHCPDISCOVER (1)
#define DHCPOFFER (2)
#define DHCPREQUEST (3)
#define DHCPDECLINE (4)
#define DHCPACK (5)
#define DHCPNACK (6)

#define DHCP_OPT_PAD (0)
#define DHCP_OPT_SUBNET_MASK (1)
#define DHCP_OPT_ROUTER (3)
#define DHCP_OPT_DNS (6)
#define DHCP_OPT_HOST_NAME (12)
#define DHCP_OPT_REQUESTED_IP (50)
#define DHCP_OPT_IP_LEASE_TIME (51)
#define DHCP_OPT_MSG_TYPE (53)
#define DHCP_OPT_SERVER_ID (54)
#define DHCP_OPT_END (255)

#define PORT_DHCP_SERVER (67)
#define PORT_DHCP_CLIENT (68)
#define DEFAULT_LEASE_TIME_S (24 * 60 * 60)
#define MAC_LEN (6)
#define DHCP_MIN_SIZE (240 + 3)

typedef struct {
	uint8_t op;
	uint8_t htype;
	uint8_t hlen;
	uint8_t hops;
	uint32_t xid;
	uint16_t secs;
	uint16_t flags;
	uint8_t ciaddr[4];
	uint8_t yiaddr[4];
	uint8_t siaddr[4];
	uint8_t giaddr[4];
	uint8_t chaddr[16];
	uint8_t sname[64];
	uint8_t file[128];
	uint8_t options[312];
} dhcp_msg_t;

static uint8_t *opt_find(uint8_t *opt, uint8_t cmd) {
	for (int i = 0; i < 308 && opt[i] != DHCP_OPT_END;) {
		if (opt[i] == cmd) {
			return &opt[i];
		}
		i += 2 + opt[i + 1];
	}
	return NULL;
}

static void opt_write_n(uint8_t **opt, uint8_t cmd, size_t n, const void *data) {
	uint8_t *o = *opt;
	*o++ = cmd;
	*o++ = (uint8_t)n;
	memcpy(o, data, n);
	*opt = o + n;
}

static void opt_write_u8(uint8_t **opt, uint8_t cmd, uint8_t val) {
	uint8_t *o = *opt;
	*o++ = cmd;
	*o++ = 1;
	*o++ = val;
	*opt = o;
}

static void opt_write_u32(uint8_t **opt, uint8_t cmd, uint32_t val) {
	uint8_t *o = *opt;
	*o++ = cmd;
	*o++ = 4;
	*o++ = (uint8_t)(val >> 24);
	*o++ = (uint8_t)(val >> 16);
	*o++ = (uint8_t)(val >> 8);
	*o++ = (uint8_t)val;
	*opt = o;
}

static int dhcp_send_packet(struct udp_pcb **udp, struct netif *nif, const void *buf, size_t len, uint32_t ip, uint16_t port) {
	if (len > 0xffff) {
		len = 0xffff;
	}
	struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, (uint16_t)len, PBUF_RAM);
	if (p == NULL) {
		return -ENOMEM;
	}
	memcpy(p->payload, buf, len);
	ip_addr_t dest;
	IP4_ADDR(ip_2_ip4(&dest), (ip >> 24) & 0xff, (ip >> 16) & 0xff, (ip >> 8) & 0xff, ip & 0xff);
	err_t err = (nif != NULL) ? udp_sendto_if(*udp, p, &dest, port, nif) : udp_sendto(*udp, p, &dest, port);
	pbuf_free(p);
	return (err == ERR_OK) ? (int)len : (int)err;
}

static int dhcp_find_or_alloc_lease(dhcp_server_t *d, const uint8_t *mac) {
	int yi = DHCPS_MAX_IP;
	for (int i = 0; i < DHCPS_MAX_IP; ++i) {
		if (memcmp(d->lease[i].mac, mac, MAC_LEN) == 0) {
			return i;
		}
		if (yi == DHCPS_MAX_IP) {
			if (memcmp(d->lease[i].mac, "\0\0\0\0\0\0", MAC_LEN) == 0) {
				yi = i;
			}
			uint32_t expiry = (uint32_t)(d->lease[i].expiry << 16 | 0xffff);
			if ((int32_t)(expiry - cyw43_hal_ticks_ms()) < 0) {
				memset(d->lease[i].mac, 0, MAC_LEN);
				yi = i;
			}
		}
	}
	return yi;
}

static void dhcp_server_process(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *src_addr, u16_t src_port) {
	dhcp_server_t *d = (dhcp_server_t *)arg;
	(void)upcb; (void)src_addr; (void)src_port;
	dhcp_msg_t dhcp_msg;

	if (p->tot_len < DHCP_MIN_SIZE) {
		pbuf_free(p);
		return;
	}
	size_t len = pbuf_copy_partial(p, &dhcp_msg, sizeof(dhcp_msg), 0);
	if (len < DHCP_MIN_SIZE) {
		pbuf_free(p);
		return;
	}

	dhcp_msg.op = DHCPOFFER;
	memcpy(&dhcp_msg.yiaddr, &ip4_addr_get_u32(ip_2_ip4(&d->ip)), 4);
	uint8_t *opt = (uint8_t *)&dhcp_msg.options + 4;
	uint8_t *msgtype = opt_find(opt, DHCP_OPT_MSG_TYPE);
	if (msgtype == NULL) {
		pbuf_free(p);
		return;
	}

	if (msgtype[2] == DHCPDISCOVER) {
		int yi = dhcp_find_or_alloc_lease(d, dhcp_msg.chaddr);
		if (yi == DHCPS_MAX_IP) {
			pbuf_free(p);
			return;
		}
		dhcp_msg.yiaddr[3] = (uint8_t)(DHCPS_BASE_IP + yi);
		opt_write_u8(&opt, DHCP_OPT_MSG_TYPE, DHCPOFFER);
	} else if (msgtype[2] == DHCPREQUEST) {
		uint8_t *o = opt_find(opt, DHCP_OPT_REQUESTED_IP);
		if (o == NULL || memcmp(o + 2, &ip4_addr_get_u32(ip_2_ip4(&d->ip)), 3) != 0) {
			pbuf_free(p);
			return;
		}
		uint8_t yi = o[5] - DHCPS_BASE_IP;
		if (yi >= DHCPS_MAX_IP) {
			pbuf_free(p);
			return;
		}
		if (memcmp(d->lease[yi].mac, dhcp_msg.chaddr, MAC_LEN) != 0 &&
		    memcmp(d->lease[yi].mac, "\0\0\0\0\0\0", MAC_LEN) != 0) {
			pbuf_free(p);
			return;
		}
		memcpy(d->lease[yi].mac, dhcp_msg.chaddr, MAC_LEN);
		d->lease[yi].expiry = (uint16_t)((cyw43_hal_ticks_ms() + DEFAULT_LEASE_TIME_S * 1000) >> 16);
		dhcp_msg.yiaddr[3] = (uint8_t)(DHCPS_BASE_IP + yi);
		opt_write_u8(&opt, DHCP_OPT_MSG_TYPE, DHCPACK);
	} else {
		pbuf_free(p);
		return;
	}

	opt_write_n(&opt, DHCP_OPT_SERVER_ID, 4, &ip4_addr_get_u32(ip_2_ip4(&d->ip)));
	opt_write_n(&opt, DHCP_OPT_SUBNET_MASK, 4, &ip4_addr_get_u32(ip_2_ip4(&d->nm)));
	opt_write_n(&opt, DHCP_OPT_ROUTER, 4, &ip4_addr_get_u32(ip_2_ip4(&d->ip)));
	opt_write_n(&opt, DHCP_OPT_DNS, 4, &ip4_addr_get_u32(ip_2_ip4(&d->ip)));
	opt_write_u32(&opt, DHCP_OPT_IP_LEASE_TIME, DEFAULT_LEASE_TIME_S);
	*opt++ = DHCP_OPT_END;

	struct netif *nif = ip_current_input_netif();
	dhcp_send_packet(&d->udp, nif, &dhcp_msg, (size_t)(opt - (uint8_t *)&dhcp_msg), 0xffffffff, PORT_DHCP_CLIENT);
	pbuf_free(p);
}

void dhcp_server_init(dhcp_server_t *d, struct netif *nif, ip_addr_t *ip, ip_addr_t *nm) {
	if (d == NULL || ip == NULL || nm == NULL) {
		return;
	}
	ip_addr_copy(d->ip, *ip);
	ip_addr_copy(d->nm, *nm);
	memset(d->lease, 0, sizeof(d->lease));
	d->udp = udp_new();
	if (d->udp == NULL) {
		return;
	}
	udp_recv(d->udp, dhcp_server_process, (void *)d);
	udp_bind(d->udp, IP_ANY_TYPE, PORT_DHCP_SERVER);
	if (nif != NULL) {
		udp_bind_netif(d->udp, nif);
	}
}

void dhcp_server_deinit(dhcp_server_t *d) {
	if (d != NULL && d->udp != NULL) {
		udp_remove(d->udp);
		d->udp = NULL;
	}
}
