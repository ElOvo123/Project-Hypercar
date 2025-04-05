PROJECT_DIR := .
SRC_DIR := $(PROJECT_DIR)/src
BUILD_DIR := $(PROJECT_DIR)/.pio/build
PLATFORMIO := pio

DEFAULT_ENVIRONMENT := uno

ENVIRONMENT ?= $(DEFAULT_ENVIRONMENT)

build:
	@echo "Building for environment: $(ENVIRONMENT)"
	@$(PLATFORMIO) run -e $(ENVIRONMENT)

upload:
	@echo "Uploading for environment: $(ENVIRONMENT)"
	@$(PLATFORMIO) run -e $(ENVIRONMENT) --target upload

clean:
	@echo "Cleaning for environment: $(ENVIRONMENT)"
	@rm -rf logs/scheduler_log.csv
	@$(PLATFORMIO) run -e $(ENVIRONMENT) --target clean

monitor:
	@echo "Monitoring for environment: $(ENVIRONMENT)"
	@$(PLATFORMIO) device monitor

build-all:
	@$(PLATFORMIO) run

upload-all:
	@$(PLATFORMIO) run --target upload

clean-all:
	@rm -rf logs/scheduler_log.csv
	@$(PLATFORMIO) run --target clean

test_native:
	@echo "Running tests for environment: native"
	@rm -rf logs/scheduler_log.csv
	@$(PLATFORMIO) test -e native --without-uploading

cppcheck:
	@echo "Running cppcheck..."
	@make clean
	@cppcheck --enable=all --inconclusive --std=c++17 --language=c++ --force \
		--suppress=missingIncludeSystem \
		-I include -I src -I lib \
		src lib

clang-tidy:
	@echo "Running clang-tidy..."
	@make clean
	@find $(SRC_DIR) -name '*.cpp' | xargs -I{} clang-tidy {} -- \
	    -Iinclude \
	    -Isrc \
	    -Ilib \
	    -Ilib/scheduler/src \
	    -std=c++17

help:
	@$(PLATFORMIO) run --help

.PHONY: build upload clean monitor build-all upload-all clean-all help test_native cppcheck clang-tidy
