# This Makefile section automates the process of compiling and uploading an 
# Arduino sketch, as well as cleaning up the build directory. The 'all' target 
# ensures that the clean, verify, upload, and clean steps are executed in order. 
# The 'verify' target compiles the sketch for the specified board, the 'upload' 
# target uploads the compiled sketch to the board connected to the specified port, 
# and the 'clean' target removes any temporary build files.

all: clean verify upload clean

verify:
	@printf "\033[1;32m >> \033[1;34m Compiling $(SKETCH) for $(BOARD_NAME) \033[0m \n"
	arduino-cli compile --fqbn $(BOARD_FQBN) ./

upload:
	@printf "\033[1;32m >> \033[1;34m Uploading $(SKETCH) to $(PORT) \033[0m \n"
	arduino-cli upload -p $(PORT) --fqbn $(BOARD_FQBN) ./

clean:
	@printf "\033[1;32m >> \033[1;34m Cleaning build directory \033[0m \n"

.PHONY: all verify upload clean

