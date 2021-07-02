# Medion HM-SEC-SC

This is a firmware for Medion MAX! door/window contacts as sold by Aldi/Hofer.
These window contacts contain an STM8L and an Si4430 radio module instead of 
the Samsung processor used in the original MAX! door/window contact series.

The firmware is heavily based on work by Timo Schlüßler who did all the hard
work in getting AskSin on the STM8L/Si4430 combination. His work can be found
at https://github.com/timo-schluessler/custom-hm-cc-rt-dn

## Compilation

You need a Linux machine with sdcc, stm8flash, stm8-binutils-gdb and srecord as
well as CMake for configuring the build system.

The desired Serial and ID are configured in the EEPROM of the device. The EEPROM
can be written separately, see flash.sh/flash.sh.in for instructions.

When flashing, stm8flash has a bug that prevents it from writing to the STM8L052C6
device. See Issue 139 at https://github.com/vdudouyt/stm8flash/issues/139 for
details and resolution.

## Status

Currently, the basics are working. A short button press initializes pairing
or, if already paired, enables config mode. Reading the magnet and sending
the status is working. There is no feedback on the device, see TODO.

## TODO

  - Power Management
  - Battery reporting
  - LED feedback on activities
  - AES
  - Configuration settings
  - Periodic battery reporting

## Caveats

This has only been tested with Homegear, not with FHEM or a CCU! AES is not 
supported, configuration settings is not supported.
