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
#include "hardware/watchdog.h"
#include "pico/stdlib.h"
#include "response.h"
#include <stdio.h>
#include <string.h>

static const char *const MICROHIL_VERSION = "microHIL v1.0.0";
static const char *const MICROHIL_BOARD_ID = "mh:333:2023:0";

static const uint8_t STATUS_LED_DEFAULT_VAL = 255;

static const char CMD_CHANNEL_MIN_CHAR = '1';
static const char CMD_CHANNEL_MAX_CHAR = '8';
static const size_t CMD_CHANNEL_CHAR_INDEX = 6;

static const size_t CMD_TIMER_ARGS_OFFSET = 12;
static const size_t CMD_PULSE_ARGS_OFFSET = 14;
static const size_t CMD_BLINK_ARGS_OFFSET = 14;
static const size_t CMD_MASK_ARGS_OFFSET = 12;

static const size_t CMD_MASK_SUFFIX_OFFSET = 20;

static const size_t CMD_PREFIX_CH_LEN = 6;
static const char *const CMD_PREFIX_CH = "mh#ch#";

static const size_t CMD_TMR_LEN = 5;
static const char *const CMD_TMR = "#tmr#";

static const size_t CMD_PULSE_LEN = 7;
static const char *const CMD_PULSE = "#pulse#";

static const size_t CMD_BLINK_LEN = 7;
static const char *const CMD_BLINK = "#blink#";

static const char *const CMD_STAT_SUFFIX = "#stat#end";

static const size_t CMD_PREFIX_MASK_LEN = 12;
static const char *const CMD_PREFIX_MASK = "mh#all#mask#";

static const char *const CMD_SUFFIX_END = "#end";

typedef void (*cmd_handler_t)(const char *cmd_str);

typedef struct {
  const char *pattern;
  cmd_handler_t handler;
} command_entry_t;

static void cmd_handle_board_id(const char *cmd_str) {
  (void)cmd_str;
  response_send_formatted("<mh#sys#%s#end>", MICROHIL_BOARD_ID);
}

static void cmd_handle_version(const char *cmd_str) {
  (void)cmd_str;
  response_send_formatted("<mh#sys#%s#end>", MICROHIL_VERSION);
}

static void cmd_handle_all_channels(const char *cmd_str) {
  bool on = (strstr(cmd_str, "#on#") != NULL);

  relay_set_all(on);
  if (on) {
    status_led_write(
        STATUS_LED_DEFAULT_VAL, STATUS_LED_DEFAULT_VAL, STATUS_LED_DEFAULT_VAL
    );
  } else {
    status_led_write(0, 0, 0);
  }
  response_send_formatted("<mh#sys#all channels %s#end>", on ? "on" : "off");
}

static void cmd_handle_channel(const char *cmd_str) {
  char ch_char = cmd_str[CMD_CHANNEL_CHAR_INDEX];
  uint32_t channel = ch_char - CMD_CHANNEL_MIN_CHAR;
  bool on = (strstr(cmd_str, "#on#") != NULL);

  if (channel < RELAY_NUM_CHANNELS) {
    relay_set(channel, on);
    response_send_formatted("<mh#sys#channel %c %s#end>", ch_char, on ? "on" : "off");
  }
}

static void cmd_handle_timer(const char *cmd_str) {
  char ch_char = cmd_str[CMD_CHANNEL_CHAR_INDEX];
  uint32_t channel = ch_char - CMD_CHANNEL_MIN_CHAR;
  uint32_t seconds = 0;

  if (sscanf(cmd_str + CMD_TIMER_ARGS_OFFSET, "%u#end", &seconds) == 1) {
    if (channel < RELAY_NUM_CHANNELS) {
      relay_start_timer(channel, seconds);
      response_send_formatted(
          "<mh#sys#channel %c timer started: %u seconds#end>", ch_char, seconds
      );
    }
  }
}

static void cmd_handle_pulse(const char *cmd_str) {
  char ch_char = cmd_str[CMD_CHANNEL_CHAR_INDEX];
  uint32_t channel = ch_char - CMD_CHANNEL_MIN_CHAR;
  uint32_t duration_ms = 0;

  if (sscanf(cmd_str + CMD_PULSE_ARGS_OFFSET, "%u#end", &duration_ms) == 1) {
    if (channel < RELAY_NUM_CHANNELS) {
      relay_start_pulse(channel, duration_ms);
      response_send_formatted(
          "<mh#sys#channel %c pulse started: %u ms#end>", ch_char, duration_ms
      );
    }
  }
}

static void cmd_handle_blink(const char *cmd_str) {
  char ch_char = cmd_str[CMD_CHANNEL_CHAR_INDEX];
  uint32_t channel = ch_char - CMD_CHANNEL_MIN_CHAR;
  uint32_t on_time = 0;
  uint32_t off_time = 0;
  uint32_t count = 0;

  if (sscanf(
          cmd_str + CMD_BLINK_ARGS_OFFSET, "%u#%u#%u#end", &on_time, &off_time,
          &count
      ) == 3) {
    if (channel < RELAY_NUM_CHANNELS) {
      relay_start_blink(channel, on_time, off_time, count);
      response_send_formatted(
          "<mh#sys#channel %c blink started: on=%u ms, off=%u ms, "
          "count=%u#end>",
          ch_char, on_time, off_time, count
      );
    }
  }
}

static void cmd_handle_mask(const char *cmd_str) {
  for (uint32_t i = 0; i < RELAY_NUM_CHANNELS; i++) {
    char bit = cmd_str[CMD_MASK_ARGS_OFFSET + i];
    bool on = (bit == '1');
    relay_set(i, on);
  }
  response_send_formatted(
      "<mh#sys#channels mask applied: %.8s#end>", cmd_str + CMD_MASK_ARGS_OFFSET
  );
}

static void cmd_handle_reset(const char *cmd_str) {
  (void)cmd_str;
  response_send_formatted("<mh#sys#system resetting...#end>");
  buzzer_beep_stop();
  watchdog_reboot(0, 0, 0);
}

static void cmd_handle_channel_status(const char *cmd_str) {
  char ch_char = cmd_str[CMD_CHANNEL_CHAR_INDEX];
  uint32_t channel = ch_char - CMD_CHANNEL_MIN_CHAR;
  if (channel < RELAY_NUM_CHANNELS) {
    char status_buf[64];
    relay_get_status(channel, status_buf, sizeof(status_buf));
    response_send_formatted("<mh#sys#%s#end>", status_buf);
  }
}

static void cmd_handle_all_status(const char *cmd_str) {
  (void)cmd_str;
  char all_status_buf[256] = "channels: ";
  uint32_t offset = 10;
  for (uint32_t i = 0; i < RELAY_NUM_CHANNELS; i++) {
    char status_buf[48];
    relay_get_status(i, status_buf, sizeof(status_buf));
    const char *state_str = strstr(status_buf, "ON") ? "ON" : "OFF";
    int written = snprintf(
        all_status_buf + offset, sizeof(all_status_buf) - offset, "%u:%s ",
        i + 1, state_str
    );
    if (written > 0) {
      offset += (uint32_t)written;
    }
  }
  response_send_formatted("<mh#sys#%s#end>", all_status_buf);
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
    {"mh#all#on#end", cmd_handle_all_channels},
    {"mh#all#off#end", cmd_handle_all_channels},
    {"mh#all#stat#end", cmd_handle_all_status},
    {"mh#sys#reset#end", cmd_handle_reset},
    {"mh#sys#id#end", cmd_handle_board_id},
    {"mh#sys#version#end", cmd_handle_version},
};

static const size_t command_tbl_size =
    sizeof(command_tbl) / sizeof(command_tbl[0]);

void command_dispatch(const char *cmd_str) {
  // Check for timer commands: "mh#ch#X#tmr#Y#end"
  if (strncmp(cmd_str, CMD_PREFIX_CH, CMD_PREFIX_CH_LEN) == 0 &&
      cmd_str[CMD_CHANNEL_CHAR_INDEX] >= CMD_CHANNEL_MIN_CHAR &&
      cmd_str[CMD_CHANNEL_CHAR_INDEX] <= CMD_CHANNEL_MAX_CHAR &&
      strncmp(cmd_str + CMD_CHANNEL_CHAR_INDEX + 1, CMD_TMR, CMD_TMR_LEN) ==
          0) {
    cmd_handle_timer(cmd_str);
    return;
  }

  // Check for pulse commands: "mh#ch#X#pulse#Y#end"
  if (strncmp(cmd_str, CMD_PREFIX_CH, CMD_PREFIX_CH_LEN) == 0 &&
      cmd_str[CMD_CHANNEL_CHAR_INDEX] >= CMD_CHANNEL_MIN_CHAR &&
      cmd_str[CMD_CHANNEL_CHAR_INDEX] <= CMD_CHANNEL_MAX_CHAR &&
      strncmp(cmd_str + CMD_CHANNEL_CHAR_INDEX + 1, CMD_PULSE, CMD_PULSE_LEN) ==
          0) {
    cmd_handle_pulse(cmd_str);
    return;
  }

  // Check for blink commands: "mh#ch#X#blink#Y#Z#W#end"
  if (strncmp(cmd_str, CMD_PREFIX_CH, CMD_PREFIX_CH_LEN) == 0 &&
      cmd_str[CMD_CHANNEL_CHAR_INDEX] >= CMD_CHANNEL_MIN_CHAR &&
      cmd_str[CMD_CHANNEL_CHAR_INDEX] <= CMD_CHANNEL_MAX_CHAR &&
      strncmp(cmd_str + CMD_CHANNEL_CHAR_INDEX + 1, CMD_BLINK, CMD_BLINK_LEN) ==
          0) {
    cmd_handle_blink(cmd_str);
    return;
  }

  // Check for channel status commands: "mh#ch#X#stat#end"
  if (strncmp(cmd_str, CMD_PREFIX_CH, CMD_PREFIX_CH_LEN) == 0 &&
      cmd_str[CMD_CHANNEL_CHAR_INDEX] >= CMD_CHANNEL_MIN_CHAR &&
      cmd_str[CMD_CHANNEL_CHAR_INDEX] <= CMD_CHANNEL_MAX_CHAR &&
      strcmp(cmd_str + CMD_CHANNEL_CHAR_INDEX + 1, CMD_STAT_SUFFIX) == 0) {
    cmd_handle_channel_status(cmd_str);
    return;
  }

  // Check for mask commands: "mh#all#mask#10101010#end"
  if (strncmp(cmd_str, CMD_PREFIX_MASK, CMD_PREFIX_MASK_LEN) == 0 &&
      strcmp(cmd_str + CMD_MASK_SUFFIX_OFFSET, CMD_SUFFIX_END) == 0) {
    cmd_handle_mask(cmd_str);
    return;
  }

  for (size_t i = 0; i < command_tbl_size; i++) {
    if (strcmp(cmd_str, command_tbl[i].pattern) == 0) {
      command_tbl[i].handler(cmd_str);
      return;
    }
  }
}

static void on_relay_state_changed(uint32_t channel, bool state) {
  if (!state) {
    response_send_formatted("<mh#sys#channel %u off#end>", channel + 1);
  }
}

void command_init(void) {
  relay_set_state_callback(on_relay_state_changed);
}
