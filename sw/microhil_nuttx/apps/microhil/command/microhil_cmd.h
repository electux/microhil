/****************************************************************************
 * apps/microhil/command/microhil_cmd.h
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

#include "../controllers/microhil_relay.h"
#include <stdbool.h>
#include <stdint.h>

typedef enum {
  CMD_TYPE_INVALID = 0,
  CMD_TYPE_SYS_ID,
  CMD_TYPE_SYS_VERSION,
  CMD_TYPE_SYS_RESET,
  CMD_TYPE_ALL_ON,
  CMD_TYPE_ALL_OFF,
  CMD_TYPE_ALL_STAT,
  CMD_TYPE_ALL_MASK,
  CMD_TYPE_CH_ON,
  CMD_TYPE_CH_OFF,
  CMD_TYPE_CH_STAT,
  CMD_TYPE_CH_TMR,
  CMD_TYPE_CH_PULSE,
  CMD_TYPE_CH_BLINK
} microhil_cmd_type_t;

typedef struct {
  uint32_t on_ms;
  uint32_t off_ms;
  uint32_t count;
} microhil_cmd_blink_args_t;

typedef union {
  char mask[RELAY_NUM_CHANNELS + 1];
  struct {
    uint32_t ch_idx;
    union {
      uint32_t timer_sec;
      uint32_t pulse_ms;
      microhil_cmd_blink_args_t blink;
    } args;
  } ch;
} microhil_cmd_data_t;

typedef struct {
  microhil_cmd_type_t type;
  microhil_cmd_data_t data;
} microhil_cmd_t;

bool microhil_cmd_parse(const char *cmd_str, microhil_cmd_t *cmd);
