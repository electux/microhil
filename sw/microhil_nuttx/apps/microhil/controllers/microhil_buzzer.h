/****************************************************************************
 * apps/microhil/controllers/microhil_buzzer.h
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
#pragma once

#include <stdbool.h>
#include <stdint.h>

bool microhil_buzzer_init(void);
void microhil_buzzer_beep_start(void);
void microhil_buzzer_beep_changed(void);
void microhil_buzzer_beep_stop(void);
void microhil_buzzer_play_usb_fail(void);
void microhil_buzzer_play_usb_success(void);
void microhil_buzzer_tick(void);
void microhil_buzzer_close(void);
