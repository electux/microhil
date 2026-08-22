/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * command_tbl.c
 * Copyright (C) 2025 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhil-base is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhil-base is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name. If not, see <http://www.gnu.org/licenses/>.
 */
#include "device/buzzer.h"
#include "device/relay.h"
#include "device/status_led.h"
#include "dispatcher.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

static const char *const MICROHIL_VERSION = "microHIL v1.0.0";
static const char *const MICROHIL_BOARD_ID = "mh:333:2023:0";
static const char *const MICROHIL_VERBOSE = "microHIL log:";

typedef void (*cmd_handler_t)(const char *cmd_str);

typedef struct {
  const char *pattern;
  cmd_handler_t handler;
} command_entry_t;

static void cmd_handle_board_id(const char *cmd_str) {
  (void)cmd_str;
  printf("%s", MICROHIL_BOARD_ID);
}

static void cmd_handle_version(const char *cmd_str) {
  (void)cmd_str;
  printf("%s", MICROHIL_VERSION);
}

static void cmd_handle_all_channels(const char *cmd_str) {
  // Pattern: "mh#ch#all#on#end" or "mh#ch#all#off#end"
  bool on = (strstr(cmd_str, "#on#") != NULL);

  relay_set_all(on);
  status_led_write(255, 255, 255);
  buzzer_beep_start();

#ifdef VERBOSE
  printf("%s all channels %s\n", MICROHIL_VERBOSE, on ? "on" : "off");
#endif
}

static void cmd_handle_channel(const char *cmd_str) {
  // Pattern: "mh#ch#X#on#end" or "mh#ch#X#off#end"
  char ch_char = cmd_str[6];
  uint32_t channel = ch_char - '1';
  bool on = (strstr(cmd_str, "#on#") != NULL);

  if (channel < RELAY_NUM_CHANNELS) {
    relay_set(channel, on);
#ifdef VERBOSE
    printf("%s channel %c %s\n", MICROHIL_VERBOSE, ch_char, on ? "on" : "off");
#endif
  }
}

static void cmd_handle_timer(const char *cmd_str) {
  // Pattern: "mh#ch#X#tmr#Y#end"
  char ch_char = cmd_str[6];
  uint32_t channel = ch_char - '1';
  uint32_t seconds = 0;

  if (sscanf(cmd_str + 12, "%u#end", &seconds) == 1) {
    if (channel < RELAY_NUM_CHANNELS) {
#ifdef VERBOSE
      printf("%s channel %c timer %u seconds\n", MICROHIL_VERBOSE, ch_char, seconds);
#endif
    }
  }
}

static const command_entry_t command_tbl[] = {
    {"mh#ch#1#on#end", cmd_handle_channel},
    {"mh#ch#1#off#end", cmd_handle_channel},
    {"mh#ch#2#on#end", cmd_handle_channel},
    {"mh#ch#2#off#end", cmd_handle_channel},
    {"mh#ch#3#on#end", cmd_handle_channel},
    {"mh#ch#3#off#end", cmd_handle_channel},
    {"mh#ch#4#on#end", cmd_handle_channel},
    {"mh#ch#4#off#end", cmd_handle_channel},
    {"mh#ch#5#on#end", cmd_handle_channel},
    {"mh#ch#5#off#end", cmd_handle_channel},
    {"mh#ch#6#on#end", cmd_handle_channel},
    {"mh#ch#6#off#end", cmd_handle_channel},
    {"mh#ch#7#on#end", cmd_handle_channel},
    {"mh#ch#7#off#end", cmd_handle_channel},
    {"mh#ch#8#on#end", cmd_handle_channel},
    {"mh#ch#8#off#end", cmd_handle_channel},
    {"mh#ch#all#on#end", cmd_handle_all_channels},
    {"mh#ch#all#off#end", cmd_handle_all_channels},
    {"mh#ch#board#id#end", cmd_handle_board_id},
    {"mh#ch#version#end", cmd_handle_version},
};

static const size_t command_tbl_size =
    sizeof(command_tbl) / sizeof(command_tbl[0]);

void command_dispatch(const char *cmd_str) {
  // Check for timer commands: "mh#ch#X#tmr#Y#end"
  // Where X is '1'-'8', followed by "#tmr#"
  if (strncmp(cmd_str, "mh#ch#", 6) == 0 &&
      cmd_str[6] >= '1' && cmd_str[6] <= '8' &&
      strncmp(cmd_str + 7, "#tmr#", 5) == 0) {
    cmd_handle_timer(cmd_str);
    return;
  }

  for (size_t i = 0; i < command_tbl_size; i++) {
    if (strcmp(cmd_str, command_tbl[i].pattern) == 0) {
      command_tbl[i].handler(cmd_str);
      return;
    }
  }
#ifdef VERBOSE
  printf("%s invalid command: %s\n", MICROHIL_VERBOSE, cmd_str);
#endif
}
