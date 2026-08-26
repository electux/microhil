/****************************************************************************
 * apps/microhil/controllers/microhil_relay.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define RELAY_NUM_CHANNELS 8

typedef enum {
  RELAY_MODE_TOGGLE = 0,
  RELAY_MODE_TIMER,
  RELAY_MODE_PULSE,
  RELAY_MODE_BLINK
} relay_mode_t;

bool microhil_relay_init(void);
void microhil_relay_set(uint32_t channel, bool state);
void microhil_relay_set_all(bool state);
void microhil_relay_start_timer(uint32_t channel, uint32_t seconds);
void microhil_relay_start_pulse(uint32_t channel, uint32_t duration_ms);
void microhil_relay_start_blink(uint32_t channel, uint32_t on_ms,
                                uint32_t off_ms, uint32_t count);
void microhil_relay_get_status(uint32_t channel, char *buf, size_t buf_len);
void microhil_relay_tick(void);
void microhil_relay_close(void);
