/****************************************************************************
 * apps/microhil/command/microhil_parser.h
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
#include <stddef.h>
#include <stdint.h>

#define MICROHIL_REQ_MAX_LEN 32

typedef enum { PARSER_STATE_IDLE, PARSER_STATE_RECEIVING } parser_state_t;

typedef struct {
  parser_state_t state;
  uint32_t buf_idx;
  char buf[MICROHIL_REQ_MAX_LEN];
} microhil_parser_t;

void microhil_parser_init(microhil_parser_t *parser);
bool microhil_parser_feed(microhil_parser_t *parser, char c, char *cmd_out,
                          size_t max_len);
