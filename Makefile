# Compiler
CC = riscv64-linux-gnu-gcc


# Debug args only
INC_PATH = include

C_SETS = -march=rv32imf -mabi=ilp32f -static -fno-pic -nostdlib -Wno-builtin-declaration-mismatch


# Source
CSRC_DIR = src

CSRCS    = $(shell find $(CSRC_DIR) -name "*.c")
SSRCS    = $(shell find $(CSRC_DIR) -name "*.s")


# Rules
include script/build.mk


# Phony rules
object: $(OBJS)
PHONY += object

asm: $(ASMS)
PHONY += asm

clean:
	@echo '- CLEAN $(CLEAN)'
	@rm -rf $(CLEAN)
PHONY += clean

help:
	@  echo ': commands' \
	&& echo '  $(PHONY)'
PHONY += help


# Settings
.PHONY: $(PHONY)

## do not remove secondary file
.SECONDARY:

## Default target
.DEFAULT_GOAL = object

