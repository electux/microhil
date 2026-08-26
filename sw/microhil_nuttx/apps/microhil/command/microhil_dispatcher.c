/****************************************************************************
 * apps/microhil/command/microhil_dispatcher.c
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
#include "microhil_dispatcher.h"
#include "../controllers/microhil_buzzer.h"
#include "../controllers/microhil_led.h"
#include "../controllers/microhil_relay.h"
#include <nuttx/arch.h>
#include <stdio.h>
#include <string.h>

static const char *const VERSION = "microHIL v1.0.0";
static const char *const BOARD_ID = "mh:333:2023:0";

static const char *const RESP_FMT = "<mh#sys#%s#end>\n";
static const char *const RESP_RESETTING = "<mh#sys#system resetting...#end>\n";
static const char *const RESP_ALL_ON = "<mh#sys#all channels on#end>\n";
static const char *const RESP_ALL_OFF = "<mh#sys#all channels off#end>\n";

static const char *const STAT_PREFIX = "channels: ";
static const char *const STATE_ON = "ON";
static const char *const STATE_OFF = "OFF";
static const char *const ALL_STAT_FMT = "%u:%s ";

static const char *const RESP_MASK_FMT =
    "<mh#sys#channels mask applied: %.8s#end>\n";

static const char *const RESP_CH_ON_FMT = "<mh#sys#channel %c on#end>\n";
static const char *const RESP_CH_OFF_FMT = "<mh#sys#channel %c off#end>\n";
static const char *const RESP_CH_TMR_FMT =
    "<mh#sys#channel %c timer started: %u seconds#end>\n";
static const char *const RESP_CH_PULSE_FMT =
    "<mh#sys#channel %c pulse started: %u ms#end>\n";
static const char *const RESP_CH_BLINK_FMT =
    "<mh#sys#channel %c blink started: on=%u ms, off=%u ms, count=%u#end>\n";

static const uint8_t LED_COLOR_ON = 255;
static const uint8_t LED_COLOR_OFF = 0;

static void handle_sys_cmd(const microhil_cmd_t *cmd) {
  switch (cmd->type) {
  case CMD_TYPE_SYS_ID: {
    printf(RESP_FMT, BOARD_ID);
    fflush(stdout);
    break;
  }
  case CMD_TYPE_SYS_VERSION: {
    printf(RESP_FMT, VERSION);
    fflush(stdout);
    break;
  }
  case CMD_TYPE_SYS_RESET: {
    printf("%s", RESP_RESETTING);
    fflush(stdout);
    microhil_buzzer_beep_stop();
    microhil_led_close();
    microhil_buzzer_close();
    microhil_relay_close();
    up_systemreset();
    break;
  }
  default:
    break;
  }
}

static void handle_all_cmd(const microhil_cmd_t *cmd) {
  switch (cmd->type) {
  case CMD_TYPE_ALL_ON: {
    microhil_relay_set_all(true);
    microhil_led_write(LED_COLOR_ON, LED_COLOR_ON, LED_COLOR_ON);
    printf("%s", RESP_ALL_ON);
    fflush(stdout);
    break;
  }
  case CMD_TYPE_ALL_OFF: {
    microhil_relay_set_all(false);
    microhil_led_write(LED_COLOR_OFF, LED_COLOR_OFF, LED_COLOR_OFF);
    printf("%s", RESP_ALL_OFF);
    fflush(stdout);
    break;
  }
  case CMD_TYPE_ALL_STAT: {
    char all_status[256];
    uint32_t offset = 0;
    strncpy(all_status, STAT_PREFIX, sizeof(all_status) - 1);
    all_status[sizeof(all_status) - 1] = '\0';
    offset = strlen(STAT_PREFIX);

    for (uint32_t i = 0; i < RELAY_NUM_CHANNELS; i++) {
      char st[48];
      microhil_relay_get_status(i, st, sizeof(st));
      const char *state_str = strstr(st, STATE_ON) ? STATE_ON : STATE_OFF;
      offset += snprintf(all_status + offset, sizeof(all_status) - offset,
                         ALL_STAT_FMT, (unsigned int)(i + 1), state_str);
    }
    printf(RESP_FMT, all_status);
    fflush(stdout);
    break;
  }
  case CMD_TYPE_ALL_MASK: {
    for (uint32_t i = 0; i < RELAY_NUM_CHANNELS; i++) {
      microhil_relay_set(i, cmd->data.mask[i] == '1');
    }
    printf(RESP_MASK_FMT, cmd->data.mask);
    fflush(stdout);
    break;
  }
  default:
    break;
  }
}

static void handle_ch_cmd(const microhil_cmd_t *cmd) {
  uint32_t ch = cmd->data.ch.ch_idx;
  char ch_char = (char)('1' + ch);

  switch (cmd->type) {
  case CMD_TYPE_CH_ON: {
    microhil_relay_set(ch, true);
    printf(RESP_CH_ON_FMT, ch_char);
    break;
  }
  case CMD_TYPE_CH_OFF: {
    microhil_relay_set(ch, false);
    printf(RESP_CH_OFF_FMT, ch_char);
    break;
  }
  case CMD_TYPE_CH_STAT: {
    char st[64];
    microhil_relay_get_status(ch, st, sizeof(st));
    printf(RESP_FMT, st);
    break;
  }
  case CMD_TYPE_CH_TMR: {
    uint32_t sec = cmd->data.ch.args.timer_sec;
    microhil_relay_start_timer(ch, sec);
    printf(RESP_CH_TMR_FMT, ch_char, (unsigned int)sec);
    break;
  }
  case CMD_TYPE_CH_PULSE: {
    uint32_t ms = cmd->data.ch.args.pulse_ms;
    microhil_relay_start_pulse(ch, ms);
    printf(RESP_CH_PULSE_FMT, ch_char, (unsigned int)ms);
    break;
  }
  case CMD_TYPE_CH_BLINK: {
    uint32_t on = cmd->data.ch.args.blink.on_ms;
    uint32_t off = cmd->data.ch.args.blink.off_ms;
    uint32_t count = cmd->data.ch.args.blink.count;
    microhil_relay_start_blink(ch, on, off, count);
    printf(RESP_CH_BLINK_FMT, ch_char, (unsigned int)on, (unsigned int)off,
           (unsigned int)count);
    break;
  }
  default:
    break;
  }
  fflush(stdout);
}

void microhil_dispatcher_execute(const microhil_cmd_t *cmd) {
  if (cmd == NULL) {
    return;
  }

  switch (cmd->type) {
  case CMD_TYPE_SYS_ID:
  case CMD_TYPE_SYS_VERSION:
  case CMD_TYPE_SYS_RESET: {
    handle_sys_cmd(cmd);
    break;
  }
  case CMD_TYPE_ALL_ON:
  case CMD_TYPE_ALL_OFF:
  case CMD_TYPE_ALL_STAT:
  case CMD_TYPE_ALL_MASK: {
    handle_all_cmd(cmd);
    break;
  }
  case CMD_TYPE_CH_ON:
  case CMD_TYPE_CH_OFF:
  case CMD_TYPE_CH_STAT:
  case CMD_TYPE_CH_TMR:
  case CMD_TYPE_CH_PULSE:
  case CMD_TYPE_CH_BLINK: {
    handle_ch_cmd(cmd);
    break;
  }
  default:
    break;
  }
}
