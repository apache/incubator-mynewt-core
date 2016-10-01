/**
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

#ifndef SPLIT_PRIV_H
#define SPLIT_PRIV_H

#ifdef __cplusplus
extern "C" {
#endif

int split_conf_init(void);
int split_nmgr_register(void);
int split_read_split(split_mode_t *split);
int split_write_split(split_mode_t mode);
split_status_t split_check_status(void);

#ifdef __cplusplus
}
#endif

#endif /* SPLIT_PRIV_H */

