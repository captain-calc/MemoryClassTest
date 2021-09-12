#!/bin/bash

ti84pce_rom_path="/run/media/jackb/PineTree/ti84pce-rom-5.3.0/ROMImage.rom"
program_src_path="/run/media/jackb/PineTree/programs/MemoryClassTest/program/src/"

# Arguments
#   $1 = relative path to directory containing tests
#
# Example:
#   bash runtests.sh tests/
#
source .runtests/runtests-backend.sh
