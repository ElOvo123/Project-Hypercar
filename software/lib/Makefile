# Project paths
PROJECT_DIR := .
SRC_DIR := $(PROJECT_DIR)/src
BUILD_DIR := $(PROJECT_DIR)/.pio/build
PLATFORMIO := pio

# Default environment (board) if none is specified
DEFAULT_ENVIRONMENT := uno

# If the ENVIRONMENT variable is not set when calling make, use the default
ENVIRONMENT ?= $(DEFAULT_ENVIRONMENT)

# Target: Build the project for the specified environment
build:
	@echo "Building for environment: $(ENVIRONMENT)"
	@$(PLATFORMIO) run -e $(ENVIRONMENT)

# Upload the firmware to the board
upload:
	@echo "Uploading for environment: $(ENVIRONMENT)"
	@$(PLATFORMIO) run -e $(ENVIRONMENT) --target upload

# Clean the build directory for the specified environment
clean:
	@echo "Cleaning for environment: $(ENVIRONMENT)"
	@$(PLATFORMIO) run -e $(ENVIRONMENT) --target clean

# Monitor serial output for the specified environment
monitor:
	@echo "Monitoring for environment: $(ENVIRONMENT)"
	@$(PLATFORMIO) device monitor

# Build for all environments
build-all:
	@$(PLATFORMIO) run

# Upload for all environments
upload-all:
	@$(PLATFORMIO) run --target upload

# Clean for all environments
clean-all:
	@$(PLATFORMIO) run --target clean

# Show help
help:
	@$(PLATFORMIO) run --help

# Phony targets
.PHONY: build upload clean monitor build-all upload-all clean-all help
