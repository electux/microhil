/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * tcp_server.c
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
#include "tcp_server.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>

static struct tcp_pcb *s_server_pcb = 0;
static struct tcp_pcb *s_client_pcb = 0;
static wifi_ring_buffer_t *s_rx_ring_buffer = 0;

static void tcp_server_client_cleanup(struct tcp_pcb *tpcb) {
  if (tpcb == 0) {
    return;
  }

  tcp_arg(tpcb, 0);
  tcp_recv(tpcb, 0);
  tcp_err(tpcb, 0);
  tcp_poll(tpcb, 0, 0);
  tcp_close(tpcb);

  if (s_client_pcb == tpcb) {
    s_client_pcb = 0;
  }

  printf("[Info] TCP client disconnected\n");
}

static void tcp_server_err_callback(void *arg, err_t err) {
  (void)arg;
  (void)err;
  printf("[Warning] TCP error on connection, closing socket\n");
  s_client_pcb = 0;
}

static err_t tcp_server_recv_callback(
    void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err
) {
  (void)arg;

  if (p == 0) {
    tcp_server_client_cleanup(tpcb);
    return ERR_OK;
  }

  if (err != ERR_OK) {
    pbuf_free(p);
    return err;
  }

  if (s_rx_ring_buffer != 0) {
    for (struct pbuf *q = p; q != 0; q = q->next) {
      const uint8_t *data = (const uint8_t *)q->payload;
      for (u16_t i = 0; i < q->len; i++) {
        wifi_ring_buffer_put(s_rx_ring_buffer, data[i]);
      }
    }
  }

  tcp_recved(tpcb, p->tot_len);
  pbuf_free(p);

  return ERR_OK;
}

static err_t tcp_server_accept_callback(
    void *arg, struct tcp_pcb *client_pcb, err_t err
) {
  (void)arg;

  if (err != ERR_OK || client_pcb == 0) {
    return ERR_VAL;
  }

  if (s_client_pcb != 0) {
    printf("[Info] Replacing previous TCP client connection\n");
    tcp_server_client_cleanup(s_client_pcb);
  }

  s_client_pcb = client_pcb;
  tcp_arg(client_pcb, 0);
  tcp_recv(client_pcb, tcp_server_recv_callback);
  tcp_err(client_pcb, tcp_server_err_callback);

  printf("[Info] New TCP client connected\n");

  return ERR_OK;
}

bool tcp_server_init(uint16_t port, wifi_ring_buffer_t *rx_rb) {
  s_rx_ring_buffer = rx_rb;

  cyw43_arch_lwip_begin();

  struct tcp_pcb *pcb = tcp_new_ip_type(IPADDR_TYPE_ANY);
  if (pcb == 0) {
    cyw43_arch_lwip_end();
    printf("[Error] Failed to create TCP PCB\n");
    return false;
  }

  err_t err = tcp_bind(pcb, IP_ANY_TYPE, port);
  if (err != ERR_OK) {
    tcp_close(pcb);
    cyw43_arch_lwip_end();
    printf("[Error] Failed to bind TCP server on port %u\n", port);
    return false;
  }

  s_server_pcb = tcp_listen_with_backlog(pcb, 1);
  if (s_server_pcb == 0) {
    tcp_close(pcb);
    cyw43_arch_lwip_end();
    printf("[Error] Failed to start TCP listening\n");
    return false;
  }

  tcp_accept(s_server_pcb, tcp_server_accept_callback);
  cyw43_arch_lwip_end();

  printf("[Info] TCP server listening on port %u\n", port);

  return true;
}

bool tcp_server_send(const uint8_t *data, uint16_t length) {
  if (s_client_pcb == 0 || data == 0 || length == 0) {
    return false;
  }

  cyw43_arch_lwip_begin();

  err_t err = tcp_write(s_client_pcb, data, length, TCP_WRITE_FLAG_COPY);
  if (err == ERR_OK) {
    tcp_output(s_client_pcb);
  }

  cyw43_arch_lwip_end();

  return (err == ERR_OK);
}

bool tcp_server_is_connected(void) {
  return (s_client_pcb != 0);
}

void tcp_server_close_client(void) {
  if (s_client_pcb != 0) {
    cyw43_arch_lwip_begin();
    tcp_server_client_cleanup(s_client_pcb);
    cyw43_arch_lwip_end();
  }
}
