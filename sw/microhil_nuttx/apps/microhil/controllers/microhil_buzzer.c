/****************************************************************************
 * apps/microhil/controllers/microhil_buzzer.c
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
#include "microhil_buzzer.h"
#include <fcntl.h>
#include <nuttx/timers/pwm.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

static const char *const PWM_DEV_PATH = "/dev/pwm3";
static const uint32_t PWM_FREQUENCY = 1000;
static const uint32_t PWM_MAX_DUTY = 65535;
static const uint32_t DUTY_SCALE = 100;
static const uint8_t PWM_CHANNEL = 1;

static const uint16_t BEEP_DUTY_NORMAL = 80;
static const uint16_t BEEP_DUTY_MAX = 100;
static const uint16_t BEEP_DUTY_SILENT = 0;

static const uint64_t MS_PER_SEC = 1000;
static const uint64_t NS_PER_MS = 1000000;

static const useconds_t BOOT_BEEP_DELAY_US = 100000;
static const uint64_t CHANGED_BEEP_DURATION_MS = 50;
static const useconds_t STOP_BEEP_DELAY_US = 300000;

static const int USB_FAIL_BEEP_COUNT = 5;
static const useconds_t USB_FAIL_BEEP_ON_US = 50000;
static const useconds_t USB_FAIL_BEEP_OFF_US = 50000;

static const int USB_SUCCESS_BEEP_COUNT = 2;
static const useconds_t USB_SUCCESS_BEEP_ON_US = 100000;
static const useconds_t USB_SUCCESS_BEEP_OFF_US = 100000;

static int pwm_fd = -1;
static uint64_t buzzer_off_time_ms = 0;

static uint64_t get_time_ms(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)ts.tv_sec * MS_PER_SEC + ts.tv_nsec / NS_PER_MS;
}

static void buzzer_write(uint16_t duty_percent) {
  if (pwm_fd >= 0) {
    struct pwm_info_s info;
    memset(&info, 0, sizeof(info));
    info.frequency = PWM_FREQUENCY;
    info.channels[0].duty = (uint32_t)duty_percent * PWM_MAX_DUTY / DUTY_SCALE;
    info.channels[0].channel = PWM_CHANNEL;
    info.arg = NULL;
    ioctl(pwm_fd, PWMIOC_SETCHARACTERISTICS, (unsigned long)((uintptr_t)&info));
    if (duty_percent > BEEP_DUTY_SILENT) {
      ioctl(pwm_fd, PWMIOC_START, 0);
    } else {
      ioctl(pwm_fd, PWMIOC_STOP, 0);
    }
  }
}

bool microhil_buzzer_init(void) {
  pwm_fd = open(PWM_DEV_PATH, O_RDWR);
  if (pwm_fd < 0) {
    return false;
  }
  buzzer_write(BEEP_DUTY_SILENT);
  return true;
}

void microhil_buzzer_beep_start(void) {
  buzzer_write(BEEP_DUTY_NORMAL);
  usleep(BOOT_BEEP_DELAY_US);
  buzzer_write(BEEP_DUTY_SILENT);
}

void microhil_buzzer_beep_changed(void) {
  buzzer_write(BEEP_DUTY_NORMAL);
  buzzer_off_time_ms = get_time_ms() + CHANGED_BEEP_DURATION_MS;
}

void microhil_buzzer_beep_stop(void) {
  buzzer_write(BEEP_DUTY_MAX);
  usleep(STOP_BEEP_DELAY_US);
  buzzer_write(BEEP_DUTY_SILENT);
}

void microhil_buzzer_play_usb_fail(void) {
  for (int i = 0; i < USB_FAIL_BEEP_COUNT; i++) {
    buzzer_write(BEEP_DUTY_NORMAL);
    usleep(USB_FAIL_BEEP_ON_US);
    buzzer_write(BEEP_DUTY_SILENT);
    usleep(USB_FAIL_BEEP_OFF_US);
  }
}

void microhil_buzzer_play_usb_success(void) {
  for (int i = 0; i < USB_SUCCESS_BEEP_COUNT; i++) {
    buzzer_write(BEEP_DUTY_NORMAL);
    usleep(USB_SUCCESS_BEEP_ON_US);
    buzzer_write(BEEP_DUTY_SILENT);
    usleep(USB_SUCCESS_BEEP_OFF_US);
  }
}

void microhil_buzzer_tick(void) {
  if (buzzer_off_time_ms > 0) {
    if (get_time_ms() >= buzzer_off_time_ms) {
      buzzer_write(BEEP_DUTY_SILENT);
      buzzer_off_time_ms = 0;
    }
  }
}

void microhil_buzzer_close(void) {
  if (pwm_fd >= 0) {
    ioctl(pwm_fd, PWMIOC_STOP, 0);
    close(pwm_fd);
    pwm_fd = -1;
  }
}
