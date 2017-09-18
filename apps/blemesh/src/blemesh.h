/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef BLEMESH_H
#define BLEMESH_H

#include <stdbool.h>

int blemesh_cfg_relay_set(bool enable);
int blemesh_send_msg(uint8_t ttl, uint16_t appkey_index, uint16_t src_addr,
                     uint16_t dst_addr, uint8_t *buf, uint16_t len);
void blemesh_iv_update(bool enable, uint32_t iv_index, bool iv_update);

void cmd_init(void);

#endif
