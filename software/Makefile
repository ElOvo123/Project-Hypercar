BOARD = arduino:avr:uno
PORT = /dev/ttyACM0  # Change this to your actual port
SKETCH = main

all: compile

compile:
	arduino-cli compile --fqbn $(BOARD) $(SKETCH)

upload:
	arduino-cli upload -p $(PORT) --fqbn $(BOARD) $(SKETCH)

clean:
	rm -rf build

.PHONY: all compile upload clean
