/****************************************************************************
# apps/microhil/microhil_relay.c
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

#include "microhil_relay.h"
#include "microhil_buzzer.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <nuttx/ioexpander/gpio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct
{
  relay_mode_t mode;
  bool active;
  uint64_t start_time;
  uint64_t duration_ms;
  uint32_t blink_on_ms;
  uint32_t blink_off_ms;
  uint32_t blink_count;
  bool blink_phase;
} relay_state_internal_t;

static const char *const relay_devs[RELAY_NUM_CHANNELS] =
{
  "/dev/gpio21", "/dev/gpio20", "/dev/gpio19", "/dev/gpio18",
  "/dev/gpio17", "/dev/gpio16", "/dev/gpio15", "/dev/gpio14",
};

static int relay_fds[RELAY_NUM_CHANNELS] = {-1, -1, -1, -1, -1, -1, -1, -1};
static relay_state_internal_t relay_states[RELAY_NUM_CHANNELS];
static bool current_phys_state[RELAY_NUM_CHANNELS] = {false};

static uint64_t get_time_ms(void)
{
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

static void relay_set_phys(uint32_t channel, bool state)
{
  if (channel < RELAY_NUM_CHANNELS && relay_fds[channel] >= 0)
    {
      if (current_phys_state[channel] != state)
        {
          current_phys_state[channel] = state;
          ioctl(relay_fds[channel], GPIOC_WRITE,
                (unsigned long)(state ? 0 : 1));
          buzzer_beep_changed();
        }
    }
}

bool relay_init(void)
{
  for (int i = 0; i < RELAY_NUM_CHANNELS; i++)
    {
      relay_fds[i] = open(relay_devs[i], O_RDWR);
      if (relay_fds[i] < 0)
        {
          return false;
        }

      ioctl(relay_fds[i], GPIOC_WRITE, (unsigned long)1);
      current_phys_state[i] = false;

      relay_states[i].mode = RELAY_MODE_TOGGLE;
      relay_states[i].active = false;
      relay_states[i].start_time = 0;
      relay_states[i].duration_ms = 0;
      relay_states[i].blink_on_ms = 0;
      relay_states[i].blink_off_ms = 0;
      relay_states[i].blink_count = 0;
      relay_states[i].blink_phase = false;
    }
  return true;
}

void relay_set(uint32_t channel, bool state)
{
  if (channel < RELAY_NUM_CHANNELS)
    {
      relay_states[channel].active = false;
      relay_states[channel].mode = RELAY_MODE_TOGGLE;
      relay_set_phys(channel, state);
    }
}

void relay_set_all(bool state)
{
  for (int i = 0; i < RELAY_NUM_CHANNELS; i++)
    {
      relay_set(i, state);
    }
}

void relay_start_timer(uint32_t channel, uint32_t seconds)
{
  if (channel < RELAY_NUM_CHANNELS)
    {
      relay_states[channel].mode = RELAY_MODE_TIMER;
      relay_states[channel].active = true;
      relay_states[channel].start_time = get_time_ms();
      relay_states[channel].duration_ms = (uint64_t)seconds * 1000;
      relay_set_phys(channel, true);
    }
}

void relay_start_pulse(uint32_t channel, uint32_t duration_ms)
{
  if (channel < RELAY_NUM_CHANNELS)
    {
      relay_states[channel].mode = RELAY_MODE_PULSE;
      relay_states[channel].active = true;
      relay_states[channel].start_time = get_time_ms();
      relay_states[channel].duration_ms = duration_ms;
      relay_set_phys(channel, true);
    }
}

void relay_start_blink(uint32_t channel, uint32_t on_ms,
                       uint32_t off_ms, uint32_t count)
{
  if (channel < RELAY_NUM_CHANNELS)
    {
      relay_states[channel].mode = RELAY_MODE_BLINK;
      relay_states[channel].active = true;
      relay_states[channel].start_time = get_time_ms();
      relay_states[channel].blink_on_ms = on_ms;
      relay_states[channel].blink_off_ms = off_ms;
      relay_states[channel].blink_count = count;
      relay_states[channel].blink_phase = true;
      relay_set_phys(channel, true);
    }
}

void relay_get_status(uint32_t channel, char *buf, size_t buf_len)
{
  if (channel < RELAY_NUM_CHANNELS)
    {
      const char *mode_str = "TOGGLE";
      if (relay_states[channel].active)
        {
          if (relay_states[channel].mode == RELAY_MODE_TIMER)
            {
              mode_str = "TIMER";
            }
          else if (relay_states[channel].mode == RELAY_MODE_PULSE)
            {
              mode_str = "PULSE";
            }
          else if (relay_states[channel].mode == RELAY_MODE_BLINK)
            {
              mode_str = "BLINK";
            }
        }
      snprintf(buf, buf_len, "ch:%u:%s:%s", channel + 1,
               current_phys_state[channel] ? "ON" : "OFF", mode_str);
    }
}

void relay_tick(void)
{
  uint64_t now = get_time_ms();
  for (int i = 0; i < RELAY_NUM_CHANNELS; i++)
    {
      if (!relay_states[i].active)
        {
          continue;
        }

      uint64_t elapsed = now - relay_states[i].start_time;

      if (relay_states[i].mode == RELAY_MODE_TIMER ||
          relay_states[i].mode == RELAY_MODE_PULSE)
        {
          if (elapsed >= relay_states[i].duration_ms)
            {
              relay_states[i].active = false;
              relay_set_phys(i, false);
            }
        }
      else if (relay_states[i].mode == RELAY_MODE_BLINK)
        {
          uint32_t phase_time = relay_states[i].blink_phase ?
              relay_states[i].blink_on_ms : relay_states[i].blink_off_ms;

          if (elapsed >= phase_time)
            {
              relay_states[i].start_time = now;
              if (relay_states[i].blink_phase)
                {
                  relay_states[i].blink_phase = false;
                  relay_set_phys(i, false);
                }
              else
                {
                  if (relay_states[i].blink_count > 0)
                    {
                      relay_states[i].blink_count--;
                    }
                  if (relay_states[i].blink_count == 0)
                    {
                      relay_states[i].active = false;
                    }
                  else
                    {
                      relay_states[i].blink_phase = true;
                      relay_set_phys(i, true);
                    }
                }
            }
        }
    }
}

void relay_close(void)
{
  for (int i = 0; i < RELAY_NUM_CHANNELS; i++)
    {
      if (relay_fds[i] >= 0)
        {
          close(relay_fds[i]);
          relay_fds[i] = -1;
        }
    }
}
