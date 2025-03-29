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
	@$(PLATFORMIO) run -e $(ENVIRONMENT) --target clean

monitor:
	@echo "Monitoring for environment: $(ENVIRONMENT)"
	@$(PLATFORMIO) device monitor

build-all:
	@$(PLATFORMIO) run

upload-all:
	@$(PLATFORMIO) run --target upload

clean-all:
	@$(PLATFORMIO) run --target clean

test:
	@echo "Running tests for environment: $(ENVIRONMENT)"
	@$(PLATFORMIO) test -e $(ENVIRONMENT) --without-uploading

help:
	@$(PLATFORMIO) run --help

.PHONY: build upload clean monitor build-all upload-all clean-all help test
