/****************************************************************************
 * apps/microhil/command/microhil_parser.c
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
#include "microhil_parser.h"
#include <string.h>

static const char START_DELIMITER = '<';
static const char END_DELIMITER = '>';
static const char NULL_CHAR = '\0';
static const char CHAR_CR = '\r';
static const char CHAR_LF = '\n';

void microhil_parser_init(microhil_parser_t *parser)
{
  if (parser != NULL)
    {
      parser->state = PARSER_STATE_IDLE;
      parser->buf_idx = 0;
      memset(parser->buf, 0, sizeof(parser->buf));
    }
}

bool microhil_parser_feed(microhil_parser_t *parser, char c, char *cmd_out, size_t max_len)
{
  if (parser == NULL || cmd_out == NULL || max_len == 0)
    {
      return false;
    }

  if (c == CHAR_CR || c == CHAR_LF)
    {
      return false;
    }

  if (c == START_DELIMITER)
    {
      parser->state = PARSER_STATE_RECEIVING;
      parser->buf_idx = 0;
      return false;
    }

  if (parser->state == PARSER_STATE_RECEIVING)
    {
      if (c == END_DELIMITER)
        {
          parser->buf[parser->buf_idx] = NULL_CHAR;
          strncpy(cmd_out, parser->buf, max_len - 1);
          cmd_out[max_len - 1] = NULL_CHAR;

          parser->state = PARSER_STATE_IDLE;
          parser->buf_idx = 0;
          return true;
        }

      if (parser->buf_idx < (MICROHIL_REQ_MAX_LEN - 1))
        {
          parser->buf[parser->buf_idx++] = c;
        }
      else
        {
          parser->state = PARSER_STATE_IDLE;
          parser->buf_idx = 0;
        }
    }

  return false;
}
