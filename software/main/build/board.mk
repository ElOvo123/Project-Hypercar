# This Makefile sets the Fully Qualified Board Name (FQBN) for various Arduino 
# boards based on the BOARD_NAME variable. This is essential for ensuring the 
# correct compilation and upload of sketches to the respective Arduino hardware. 
# The FQBN is a unique identifier used by the Arduino development environment 
# to recognize the board type and apply the appropriate settings and parameters. 
# The conditional statements below match the BOARD_NAME to the corresponding FQBN.


BOARD_MAP = \
    Arduino_Uno:arduino:avr:uno \
    Arduino_Nano:arduino:avr:nano \
    Arduino_Mega:arduino:avr:mega \
    Arduino_Leonardo:arduino:avr:leonardo \
    Arduino_Micro:arduino:avr:micro \
    Arduino_Esplora:arduino:avr:esplora \
    Arduino_Yún:arduino:avr:yun \
    Adafruit_Circuit_Playground:arduino:avr:circuitplay32u4cat \
    Linino_One:arduino:avr:one \
    LilyPad_Arduino_USB:arduino:avr:LilyPadUSB \
    LilyPad_Arduino:arduino:avr:lilypad \
    Arduino_Yún_Mini:arduino:avr:yunmini \
    Arduino_Uno_WiFi:arduino:avr:unowifi \
    Arduino_Uno_Mini:arduino:avr:unomini \
    Arduino_Robot_Motor:arduino:avr:robotMotor \
    Arduino_BT:arduino:avr:bt \
    Arduino_Duemilanove_or_Diecimila:arduino:avr:diecimila \
    Arduino_Ethernet:arduino:avr:ethernet \
    Arduino_Fio:arduino:avr:fio \
    Arduino_Gemma:arduino:avr:gemma \
    Arduino_Industrial_101:arduino:avr:chiwawa \
    Arduino_Leonardo_ETH:arduino:avr:leonardoeth \
    Arduino_Mega_ADK:arduino:avr:megaADK \
    Arduino_Mini:arduino:avr:mini \
    Arduino_NG_or_older:arduino:avr:atmegang \
    Arduino_Pro_or_Pro_Mini:arduino:avr:pro \
    Arduino_Robot_Control:arduino:avr:robotControl


# Function to get FQBN from BOARD_MAP
define get-fqbn
$(foreach pair,$(BOARD_MAP),$(if $(findstring $(1):,$(pair)),$(subst $(1):,,$(pair))))
endef


# Set BOARD_FQBN based on BOARD_NAME
BOARD_FQBN = $(call get-fqbn,$(BOARD_NAME))


# Debug print BOARD_FQBN
$(info  Board chossen -> $(BOARD_NAME))
$(info  Corresponding Fully Qualified Board Name(FQBN) -> $(BOARD_FQBN))