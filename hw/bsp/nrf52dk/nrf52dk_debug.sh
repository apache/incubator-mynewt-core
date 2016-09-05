#!/bin/sh
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
# 
#   http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#
# Called: $0 <bsp_directory_path> <binary> [features...]
#  - bsp_directory_path is absolute path to hw/bsp/bsp_name
#  - binary is the path to prefix to target binary, .elf.bin appended to this
#    name is the raw binary format of the binary.
#  - features are the target features. So you can have e.g. different
#    flash offset for bootloader 'feature'
# 
#
if [ $# -lt 1 ]; then
    echo "Need binary to download"
    exit 1
fi

FILE_NAME=$2.elf

SPLIT_ELF_PRESENT=0
if [ $# -gt 2 ]; then
    SPLIT_ELF_PRESENT=1
    SPLIT_ELF_NAME=$3.elf
fi

GDB_CMD_FILE=.gdb_cmds

echo "Debugging" $FILE_NAME

# Monitor mode. Background process gets it's own process group.
set -m
JLinkGDBServer -device nRF52 -speed 4000 -if SWD -port 3333 -singlerun > /dev/null &
set +m



echo "target remote localhost:3333" > $GDB_CMD_FILE
if [ $SPLIT_ELF_PRESENT -eq 1 ]; then
    # TODO -- this magic number 0x42000 is the location of the second image slot.
    # we should either get this from a flash map file or somehow learn this from the image itself
    echo "add-symbol-file $SPLIT_ELF_NAME 0x8000 -readnow" >> $GDB_CMD_FILE
fi

arm-none-eabi-gdb -x $GDB_CMD_FILE $FILE_NAME

rm $GDB_CMD_FILE

