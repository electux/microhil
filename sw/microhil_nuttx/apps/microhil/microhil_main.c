/****************************************************************************
# apps/microhil/microhil_main.c
#
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.  The
# ASF licenses this file to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance with the
# License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations
# under the License.
#
****************************************************************************/

#include "microhil_led.h"
#include "microhil_buzzer.h"
#include "microhil_relay.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <nuttx/arch.h>
#include <sys/boardctl.h>

#define REQ_LEN 32

static const char *const VERSION = "microHIL v1.0.0";
static const char *const BOARD_ID = "mh:333:2023:0";

typedef enum
{
  STATE_IDLE,
  STATE_RECEIVING
} parser_state_t;

static parser_state_t state = STATE_IDLE;
static uint32_t buf_idx = 0;

static void dispatch(const char *cmd)
{
  if (strcmp(cmd, "mh#sys#id#end") == 0)
    {
      printf("<mh#sys#%s#end>\n", BOARD_ID);
      fflush(stdout);
    }
  else if (strcmp(cmd, "mh#sys#version#end") == 0)
    {
      printf("<mh#sys#%s#end>\n", VERSION);
      fflush(stdout);
    }
  else if (strcmp(cmd, "mh#sys#reset#end") == 0)
    {
      printf("<mh#sys#system resetting...#end>\n");
      fflush(stdout);
      buzzer_beep_stop();
      status_led_close();
      buzzer_close();
      relay_close();
      up_systemreset();
    }
  else if (strcmp(cmd, "mh#all#on#end") == 0)
    {
      relay_set_all(true);
      status_led_write(255, 255, 255);
      printf("<mh#sys#all channels on#end>\n");
      fflush(stdout);
    }
  else if (strcmp(cmd, "mh#all#off#end") == 0)
    {
      relay_set_all(false);
      status_led_write(0, 0, 0);
      printf("<mh#sys#all channels off#end>\n");
      fflush(stdout);
    }
  else if (strcmp(cmd, "mh#all#stat#end") == 0)
    {
      char all_status[256] = "channels: ";
      uint32_t offset = 10;
      for (unsigned int i = 0; i < RELAY_NUM_CHANNELS; i++)
        {
          char st[48];
          relay_get_status(i, st, sizeof(st));
          const char *state_str = strstr(st, "ON") ? "ON" : "OFF";
          offset += snprintf(all_status + offset, sizeof(all_status) - offset,
                             "%u:%s ", i + 1, state_str);
        }
      printf("<mh#sys#%s#end>\n", all_status);
      fflush(stdout);
    }
  else if (strncmp(cmd, "mh#all#mask#", 12) == 0 &&
           strcmp(cmd + 20, "#end") == 0)
    {
      for (uint32_t i = 0; i < RELAY_NUM_CHANNELS; i++)
        {
          relay_set(i, cmd[12 + i] == '1');
        }
      printf("<mh#sys#channels mask applied: %.8s#end>\n", cmd + 12);
      fflush(stdout);
    }
  else if (strncmp(cmd, "mh#ch#", 6) == 0)
    {
      uint32_t ch = cmd[6] - '1';
      if (ch < RELAY_NUM_CHANNELS)
        {
          if (strcmp(cmd + 7, "#on#end") == 0)
            {
              relay_set(ch, true);
              printf("<mh#sys#channel %c on#end>\n", cmd[6]);
            }
          else if (strcmp(cmd + 7, "#off#end") == 0)
            {
              relay_set(ch, false);
              printf("<mh#sys#channel %c off#end>\n", cmd[6]);
            }
          else if (strcmp(cmd + 7, "#stat#end") == 0)
            {
              char st[64];
              relay_get_status(ch, st, sizeof(st));
              printf("<mh#sys#%s#end>\n", st);
            }
          else if (strncmp(cmd + 7, "#tmr#", 5) == 0)
            {
              unsigned int sec = 0;
              if (sscanf(cmd + 12, "%u#end", &sec) == 1)
                {
                  relay_start_timer(ch, (uint32_t)sec);
                  printf("<mh#sys#channel %c timer started: %u seconds#end>\n",
                         cmd[6], sec);
                }
            }
          else if (strncmp(cmd + 7, "#pulse#", 7) == 0)
            {
              unsigned int ms = 0;
              if (sscanf(cmd + 14, "%u#end", &ms) == 1)
                {
                  relay_start_pulse(ch, (uint32_t)ms);
                  printf("<mh#sys#channel %c pulse started: %u ms#end>\n",
                         cmd[6], ms);
                }
            }
          else if (strncmp(cmd + 7, "#blink#", 7) == 0)
            {
              unsigned int on = 0, off = 0, count = 0;
              if (sscanf(cmd + 14, "%u#%u#%u#end", &on, &off, &count) == 3)
                {
                  relay_start_blink(ch, (uint32_t)on, (uint32_t)off, (uint32_t)count);
                  printf("<mh#sys#channel %c blink started: "
                         "on=%u ms, off=%u ms, count=%u#end>\n",
                         cmd[6], on, off, count);
                }
            }
          fflush(stdout);
        }
    }
}

static bool parse_char(char c, char *buf, uint32_t max_len)
{
  if (c == '\r' || c == '\n')
    {
      return false;
    }
  if (c == '<')
    {
      state = STATE_RECEIVING;
      buf_idx = 0;
      return false;
    }
  if (state == STATE_RECEIVING)
    {
      if (c == '>')
        {
          buf[buf_idx] = '\0';
          state = STATE_IDLE;
          buf_idx = 0;
          return true;
        }
      if (buf_idx < (max_len - 1))
        {
          buf[buf_idx++] = c;
        }
      else
        {
          state = STATE_IDLE;
          buf_idx = 0;
        }
    }
  return false;
}

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  struct boardioc_usbdev_ctrl_s ctrl;
  ctrl.usbdev = BOARDIOC_USBDEV_CDCACM;
  ctrl.action = BOARDIOC_USBDEV_CONNECT;
  ctrl.instance = 0;
  ctrl.handle = NULL;
  boardctl(BOARDIOC_USBDEV_CONTROL, (uintptr_t)&ctrl);

  int fd = -1;
  for (int i = 0; i < 50; i++)
    {
      fd = open("/dev/ttyACM0", O_RDWR | O_NONBLOCK);
      if (fd >= 0)
        {
          break;
        }
      usleep(100000);
    }

  if (fd >= 0)
    {
      dup2(fd, 0);
      dup2(fd, 1);
      dup2(fd, 2);
      close(fd);
    }

  if (!status_led_init() || !buzzer_init() || !relay_init())
    {
      fprintf(stderr, "Device initialization failed!\n");
      return 1;
    }

  buzzer_beep_start();

  int flags = fcntl(0, F_GETFL, 0);
  fcntl(0, F_SETFL, flags | O_NONBLOCK);

  char request[REQ_LEN] = {0};
  char c;

  while (true)
    {
      relay_tick();
      buzzer_tick();

      while (read(0, &c, 1) > 0)
        {
          if (parse_char(c, request, REQ_LEN))
            {
              dispatch(request);
              memset(request, 0, sizeof(request));
            }
        }
      usleep(1000);
    }

  status_led_close();
  buzzer_close();
  relay_close();
  return 0;
}

int microhil_init(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  int ret = task_create("microhil_daemon", 100, 2048, main, NULL);
  if (ret < 0)
    {
      fprintf(stderr, "Failed to start microhil daemon!\n");
    }

  extern int nsh_main(int argc, char *argv[]);
  return nsh_main(argc, argv);
}
