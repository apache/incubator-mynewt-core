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

#include "os/os.h"

#include "os/queue.h"
#include "os/os_time.h"

#include "console/console.h"
#include "shell/shell.h"
#include "shell_priv.h"

#include <assert.h>
#include <string.h>
#include <util/datetime.h>

int 
shell_os_tasks_display_cmd(int argc, char **argv)
{
    struct os_task *prev_task;
    struct os_task_info oti;
    char *name;
    int found;

    name = NULL;
    found = 0;

    if (argc > 1 && strcmp(argv[1], "")) {
        name = argv[1];
    }

    console_printf("Tasks: \n");
    prev_task = NULL;
    while (1) {
        prev_task = os_task_info_get_next(prev_task, &oti);
        if (prev_task == NULL) {
            break;
        }

        if (name) {
            if (strcmp(name, oti.oti_name)) {
                continue;
            } else {
                found = 1;
            }
        }

        console_printf("  %s (prio: %u, tid: %u, lcheck: %lu, ncheck: %lu, "
                "flags: 0x%x, ssize: %u, susage: %u, cswcnt: %lu, "
                "tot_run_time: %lums)\n",
                oti.oti_name, oti.oti_prio, oti.oti_taskid, 
                (unsigned long)oti.oti_last_checkin,
                (unsigned long)oti.oti_next_checkin, oti.oti_flags,
                oti.oti_stksize, oti.oti_stkusage, (unsigned long)oti.oti_cswcnt,
                (unsigned long)oti.oti_runtime);

    }

    if (name && !found) {
        console_printf("Couldn't find task with name %s\n", name);
    }

    return (0);
}

int 
shell_os_mpool_display_cmd(int argc, char **argv)
{
    struct os_mempool *mp;
    struct os_mempool_info omi;
    char *name;
    int found;

    name = NULL;
    found = 0;

    if (argc > 1 && strcmp(argv[1], "")) {
        name = argv[1];
    }

    console_printf("Mempools: \n");
    mp = NULL;
    while (1) {
        mp = os_mempool_info_get_next(mp, &omi);
        if (mp == NULL) {
            break;
        }

        if (name) {
            if (strcmp(name, omi.omi_name)) {
                continue;
            } else {
                found = 1;
            }
        }

        console_printf("  %s (blksize: %d, nblocks: %d, nfree: %d)\n",
                omi.omi_name, omi.omi_block_size, omi.omi_num_blocks,
                omi.omi_num_free);
    }

    if (name && !found) {
        console_printf("Couldn't find a memory pool with name %s\n", 
                name);
    }

    return (0);
}

int
shell_os_date_cmd(int argc, char **argv)
{
    struct os_timeval tv;
    struct os_timezone tz;
    char buf[DATETIME_BUFSIZE];
    int rc;

    argc--; argv++;     /* skip command name */

    if (argc == 0) {
        /* Display the current datetime */
        rc = os_gettimeofday(&tv, &tz);
        assert(rc == 0);
        rc = format_datetime(&tv, &tz, buf, sizeof(buf));
        assert(rc == 0);
        console_printf("%s\n", buf);
    } else if (argc == 1) {
        /* Set the current datetime */
        rc = parse_datetime(*argv, &tv, &tz);
        if (rc == 0) {
            rc = os_settimeofday(&tv, &tz);
        } else {
            console_printf("Invalid datetime\n");
        }
    } else {
        rc = -1;
    }

    return (rc);
}
