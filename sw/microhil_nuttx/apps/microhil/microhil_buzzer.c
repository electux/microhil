/****************************************************************************
# apps/microhil/microhil_buzzer.c
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

#include "microhil_buzzer.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <nuttx/timers/pwm.h>
#include <stdio.h>
#include <time.h>

static int pwm_fd = -1;
static uint64_t buzzer_off_time_ms = 0;

static uint64_t get_time_ms(void)
{
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

bool buzzer_init(void)
{
  pwm_fd = open("/dev/pwm3", O_RDWR);
  if (pwm_fd < 0)
    {
      return false;
    }
  buzzer_write(0);
  return true;
}

void buzzer_write(uint16_t duty_percent)
{
  if (pwm_fd >= 0)
    {
      struct pwm_info_s info;
      memset(&info, 0, sizeof(info));
      info.frequency = 1000;
#ifdef CONFIG_PWM_MULTICHAN
      info.channels[0].duty = (uint32_t)duty_percent * 65535 / 100;
      info.channels[0].channel = 1;
#else
      info.duty = (uint32_t)duty_percent * 65535 / 100;
#endif
      info.arg = NULL;
      ioctl(pwm_fd, PWMIOC_SETCHARACTERISTICS,
            (unsigned long)((uintptr_t)&info));
      if (duty_percent > 0)
        {
          ioctl(pwm_fd, PWMIOC_START, 0);
        }
      else
        {
          ioctl(pwm_fd, PWMIOC_STOP, 0);
        }
    }
}

void buzzer_beep_start(void)
{
  buzzer_write(80);
  usleep(100000);
  buzzer_write(0);
}

void buzzer_beep_changed(void)
{
  buzzer_write(80);
  buzzer_off_time_ms = get_time_ms() + 50;
}

void buzzer_beep_stop(void)
{
  buzzer_write(100);
  usleep(300000);
  buzzer_write(0);
}

void buzzer_tick(void)
{
  if (buzzer_off_time_ms > 0)
    {
      if (get_time_ms() >= buzzer_off_time_ms)
        {
          buzzer_write(0);
          buzzer_off_time_ms = 0;
        }
    }
}

void buzzer_close(void)
{
  if (pwm_fd >= 0)
    {
      ioctl(pwm_fd, PWMIOC_STOP, 0);
      close(pwm_fd);
      pwm_fd = -1;
    }
}
