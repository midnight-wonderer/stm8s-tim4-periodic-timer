SHELL := /usr/bin/env bash
ROOT_PATH := $(strip $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))
CC = sdcc
AR = sdar
CDEFS = -DSTM8S103

include $(ROOT_PATH)/utilities/builder/Makefile

.PHONY: build clean

build: $(BIN_DIR)/app.lib

clean:
	rm -rf $(BIN_DIR) || true
