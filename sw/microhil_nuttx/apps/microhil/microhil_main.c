/****************************************************************************
 * apps/microhil/microhil_main.c
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
#include "command/microhil_cmd.h"
#include "command/microhil_dispatcher.h"
#include "command/microhil_parser.h"
#include "controllers/microhil_buzzer.h"
#include "controllers/microhil_led.h"
#include "controllers/microhil_relay.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/boardctl.h>
#include <unistd.h>

static const char *const DAEMON_NAME = "microhil_daemon";
static const int DAEMON_PRIORITY = 100;
static const int DAEMON_STACKSIZE = 2048;

static const char *const SERIAL_DEV_PATH = "/dev/ttyACM0";
static const useconds_t SERIAL_OPEN_RETRY_US = 200000;
static const useconds_t BOOT_DELAY_US = 500000;
static const useconds_t MAIN_LOOP_YIELD_US = 1000;

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  /* Initialize hardware first so we can use diagnostic beeps */
  if (!microhil_led_init() || !microhil_buzzer_init() ||
      !microhil_relay_init()) {
    return 1;
  }

  /* Boot beep: 1 beep */
  microhil_buzzer_beep_start();
  usleep(BOOT_DELAY_US);

  /* Connect USB CDCACM */
  struct boardioc_usbdev_ctrl_s ctrl;
  ctrl.usbdev = BOARDIOC_USBDEV_CDCACM;
  ctrl.action = BOARDIOC_USBDEV_CONNECT;
  ctrl.instance = 0;
  ctrl.handle = NULL;
  int ret = boardctl(BOARDIOC_USBDEV_CONTROL, (uintptr_t)&ctrl);

  if (ret < 0) {
    /* USB controller connection failed: beep 5 times rapidly */
    microhil_buzzer_play_usb_fail();
  }

  /* Wait indefinitely for SERIAL_DEV_PATH to open successfully */
  int fd = -1;

  while (fd < 0) {
    fd = open(SERIAL_DEV_PATH, O_RDWR | O_NONBLOCK);

    if (fd >= 0) {
      break;
    }

    usleep(SERIAL_OPEN_RETRY_US);
  }

  /* Redirect standard streams to USB serial */
  dup2(fd, 0);
  dup2(fd, 1);
  dup2(fd, 2);
  close(fd);

  /* Connection success beep: 2 beeps */
  microhil_buzzer_play_usb_success();

  int flags = fcntl(0, F_GETFL, 0);
  fcntl(0, F_SETFL, flags | O_NONBLOCK);

  microhil_parser_t parser;
  microhil_parser_init(&parser);

  char request[MICROHIL_REQ_MAX_LEN] = {0};
  char c;

  while (true) {
    microhil_relay_tick();
    microhil_buzzer_tick();

    while (read(0, &c, 1) > 0) {
      if (microhil_parser_feed(&parser, c, request, MICROHIL_REQ_MAX_LEN)) {
        microhil_cmd_t cmd;

        if (microhil_cmd_parse(request, &cmd)) {
          microhil_dispatcher_execute(&cmd);
        }

        memset(request, 0, sizeof(request));
      }
    }
    usleep(MAIN_LOOP_YIELD_US);
  }

  microhil_led_close();
  microhil_buzzer_close();
  microhil_relay_close();
  return 0;
}

int microhil_init(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  int ret =
      task_create(DAEMON_NAME, DAEMON_PRIORITY, DAEMON_STACKSIZE, main, NULL);

  if (ret < 0) {
    fprintf(stderr, "Failed to start microhil daemon!\n");
  }

  extern int nsh_main(int argc, char *argv[]);

  return nsh_main(argc, argv);
}
