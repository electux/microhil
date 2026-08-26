/****************************************************************************
 * apps/microhil/command/microhil_cmd.c
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
#include "microhil_cmd.h"
#include <stdio.h>
#include <string.h>

static const char *const CMD_STR_SYS_ID = "mh#sys#id#end";
static const char *const CMD_STR_SYS_VERSION = "mh#sys#version#end";
static const char *const CMD_STR_SYS_RESET = "mh#sys#reset#end";

static const char *const CMD_STR_ALL_ON = "mh#all#on#end";
static const char *const CMD_STR_ALL_OFF = "mh#all#off#end";
static const char *const CMD_STR_ALL_STAT = "mh#all#stat#end";
static const char *const CMD_STR_ALL_MASK_PREFIX = "mh#all#mask#";

static const char *const CMD_STR_CH_PREFIX = "mh#ch#";

static const char *const CMD_STR_CH_ON = "#on#end";
static const char *const CMD_STR_CH_OFF = "#off#end";
static const char *const CMD_STR_CH_STAT = "#stat#end";
static const char *const CMD_STR_CH_TMR_PREFIX = "#tmr#";
static const char *const CMD_STR_CH_PULSE_PREFIX = "#pulse#";
static const char *const CMD_STR_CH_BLINK_PREFIX = "#blink#";

static const char *const CMD_STR_END_SUFFIX = "#end";

static const size_t ALL_MASK_PREFIX_LEN = 12;
static const size_t ALL_MASK_SUFFIX_OFFSET = 12 + RELAY_NUM_CHANNELS;

static const size_t CH_PREFIX_LEN = 6;
static const size_t CH_NUM_OFFSET = 6;
static const size_t CH_SUFFIX_OFFSET = 7;

static const size_t CH_TMR_PREFIX_LEN = 5;
static const size_t CH_PULSE_PREFIX_LEN = 7;
static const size_t CH_BLINK_PREFIX_LEN = 7;

static bool parse_sys_cmd(const char *cmd_str, microhil_cmd_t *cmd) {
  if (strcmp(cmd_str, CMD_STR_SYS_ID) == 0) {
    cmd->type = CMD_TYPE_SYS_ID;
    return true;
  }
  if (strcmp(cmd_str, CMD_STR_SYS_VERSION) == 0) {
    cmd->type = CMD_TYPE_SYS_VERSION;
    return true;
  }
  if (strcmp(cmd_str, CMD_STR_SYS_RESET) == 0) {
    cmd->type = CMD_TYPE_SYS_RESET;
    return true;
  }
  return false;
}

static bool parse_all_cmd(const char *cmd_str, microhil_cmd_t *cmd) {
  if (strcmp(cmd_str, CMD_STR_ALL_ON) == 0) {
    cmd->type = CMD_TYPE_ALL_ON;
    return true;
  }
  if (strcmp(cmd_str, CMD_STR_ALL_OFF) == 0) {
    cmd->type = CMD_TYPE_ALL_OFF;
    return true;
  }
  if (strcmp(cmd_str, CMD_STR_ALL_STAT) == 0) {
    cmd->type = CMD_TYPE_ALL_STAT;
    return true;
  }
  if (strncmp(cmd_str, CMD_STR_ALL_MASK_PREFIX, ALL_MASK_PREFIX_LEN) == 0 &&
      strcmp(cmd_str + ALL_MASK_SUFFIX_OFFSET, CMD_STR_END_SUFFIX) == 0) {
    cmd->type = CMD_TYPE_ALL_MASK;
    for (size_t i = 0; i < RELAY_NUM_CHANNELS; i++) {
      cmd->data.mask[i] = cmd_str[ALL_MASK_PREFIX_LEN + i];
    }
    cmd->data.mask[RELAY_NUM_CHANNELS] = '\0';
    return true;
  }
  return false;
}

static bool parse_ch_cmd(const char *cmd_str, microhil_cmd_t *cmd) {
  if (strncmp(cmd_str, CMD_STR_CH_PREFIX, CH_PREFIX_LEN) != 0) {
    return false;
  }

  uint32_t ch = cmd_str[CH_NUM_OFFSET] - '1';
  if (ch >= RELAY_NUM_CHANNELS) {
    return false;
  }

  const char *suffix = cmd_str + CH_SUFFIX_OFFSET;

  if (strcmp(suffix, CMD_STR_CH_ON) == 0) {
    cmd->type = CMD_TYPE_CH_ON;
    cmd->data.ch.ch_idx = ch;
    return true;
  }
  if (strcmp(suffix, CMD_STR_CH_OFF) == 0) {
    cmd->type = CMD_TYPE_CH_OFF;
    cmd->data.ch.ch_idx = ch;
    return true;
  }
  if (strcmp(suffix, CMD_STR_CH_STAT) == 0) {
    cmd->type = CMD_TYPE_CH_STAT;
    cmd->data.ch.ch_idx = ch;
    return true;
  }
  if (strncmp(suffix, CMD_STR_CH_TMR_PREFIX, CH_TMR_PREFIX_LEN) == 0) {
    unsigned int sec = 0;
    if (sscanf(suffix + CH_TMR_PREFIX_LEN, "%u#end", &sec) == 1) {
      cmd->type = CMD_TYPE_CH_TMR;
      cmd->data.ch.ch_idx = ch;
      cmd->data.ch.args.timer_sec = (uint32_t)sec;
      return true;
    }
  }
  if (strncmp(suffix, CMD_STR_CH_PULSE_PREFIX, CH_PULSE_PREFIX_LEN) == 0) {
    unsigned int ms = 0;
    if (sscanf(suffix + CH_PULSE_PREFIX_LEN, "%u#end", &ms) == 1) {
      cmd->type = CMD_TYPE_CH_PULSE;
      cmd->data.ch.ch_idx = ch;
      cmd->data.ch.args.pulse_ms = (uint32_t)ms;
      return true;
    }
  }
  if (strncmp(suffix, CMD_STR_CH_BLINK_PREFIX, CH_BLINK_PREFIX_LEN) == 0) {
    unsigned int on = 0, off = 0, count = 0;
    if (sscanf(suffix + CH_BLINK_PREFIX_LEN, "%u#%u#%u#end", &on, &off,
               &count) == 3) {
      cmd->type = CMD_TYPE_CH_BLINK;
      cmd->data.ch.ch_idx = ch;
      cmd->data.ch.args.blink.on_ms = (uint32_t)on;
      cmd->data.ch.args.blink.off_ms = (uint32_t)off;
      cmd->data.ch.args.blink.count = (uint32_t)count;
      return true;
    }
  }
  return false;
}

bool microhil_cmd_parse(const char *cmd_str, microhil_cmd_t *cmd) {
  if (cmd_str == NULL || cmd == NULL) {
    return false;
  }

  memset(cmd, 0, sizeof(microhil_cmd_t));

  if (parse_sys_cmd(cmd_str, cmd)) {
    return true;
  }
  if (parse_all_cmd(cmd_str, cmd)) {
    return true;
  }
  if (parse_ch_cmd(cmd_str, cmd)) {
    return true;
  }

  cmd->type = CMD_TYPE_INVALID;
  return false;
}
