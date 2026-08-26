/****************************************************************************
 * apps/microhil/controllers/microhil_led.c
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
#include "microhil_led.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static const char *const LED_DEV_PATH = "/dev/leds0";
static const uint8_t RED_SHIFT = 16;
static const uint8_t GREEN_SHIFT = 8;
static const uint8_t LED_COLOR_OFF = 0;

static int led_fd = -1;

bool microhil_led_init(void) {
  led_fd = open(LED_DEV_PATH, O_WRONLY);
  if (led_fd < 0) {
    return false;
  }
  microhil_led_write(LED_COLOR_OFF, LED_COLOR_OFF, LED_COLOR_OFF);
  return true;
}

void microhil_led_write(uint8_t red, uint8_t green, uint8_t blue) {
  if (led_fd >= 0) {
    uint32_t pixel =
        ((uint32_t)red << RED_SHIFT) | ((uint32_t)green << GREEN_SHIFT) | blue;
    lseek(led_fd, 0, SEEK_SET);
    write(led_fd, &pixel, sizeof(pixel));
  }
}

void microhil_led_close(void) {
  if (led_fd >= 0) {
    close(led_fd);
    led_fd = -1;
  }
}
