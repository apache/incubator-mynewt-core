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
#include "boot_test.h"

TEST_CASE(boot_test_vm_ns_11_b)
{
    int rc;

    struct image_header hdr0 = {
        .ih_magic = IMAGE_MAGIC,
        .ih_tlv_size = 4 + 32,
        .ih_hdr_size = BOOT_TEST_HEADER_SIZE,
        .ih_img_size = 5 * 1024,
        .ih_flags = IMAGE_F_SHA256,
        .ih_ver = { 0, 5, 21, 432 },
    };

    struct image_header hdr1 = {
        .ih_magic = IMAGE_MAGIC,
        .ih_tlv_size = 4 + 32,
        .ih_hdr_size = BOOT_TEST_HEADER_SIZE,
        .ih_img_size = 32 * 1024,
        .ih_flags = IMAGE_F_SHA256,
        .ih_ver = { 1, 2, 3, 432 },
    };

    struct boot_req req = {
        .br_area_descs = boot_test_area_descs,
        .br_slot_areas = boot_test_slot_areas,
        .br_num_image_areas = BOOT_TEST_AREA_IDX_SCRATCH + 1,
        .br_scratch_area_idx = BOOT_TEST_AREA_IDX_SCRATCH,
        .br_img_sz = (384 * 1024),
    };

    boot_test_util_init_flash();
    boot_test_util_write_image(&hdr0, 0);
    boot_test_util_write_hash(&hdr0, 0);
    boot_test_util_write_image(&hdr1, 1);
    boot_test_util_write_hash(&hdr1, 1);

    rc = boot_set_pending();
    TEST_ASSERT(rc == 0);

    boot_test_util_verify_all(&req, BOOT_SWAP_TYPE_TEST, &hdr0, &hdr1);
}
