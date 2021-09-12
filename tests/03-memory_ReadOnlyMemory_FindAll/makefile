# ----------------------------
# Makefile Options
# ----------------------------

NAME       = TEST
COMPRESSED = NO
ARCHIVED   = NO

CFLAGS            = -Wall -Wextra -Oz
CXXFLAGS          = -Wall -Wextra -Oz
EXTRA_CPPSOURCES = $(filter-out ../../program/src/main.cpp, $(wildcard ../../program/src/*.cpp))
EXTRA_ASMSOURCES = $(wildcard ../../program/src/*.asm)

# ----------------------------

include $(shell cedev-config --makefile)
