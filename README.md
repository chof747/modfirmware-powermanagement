# Modfirmware Power Management Library

This library allows the power management of battery powered microcontroller boards that are
enabling the tracking of the status of the charging circuit as well as the power state of the battery and the current consumption of the board.

For this the library requires the following hardware components:

- 1 GPIO pin connected to the READY bin of the respective charging IC
- 1 GPIO pin connected to the CHARGING bin of the same IC
- An INA219 IC connected via I2C to the microcontroller measuring the battery voltage and the current consumption

Example boards can be found here:

- [MCU Bat Power Board](https://github.com/chof747/mcu-bat-power)
- [Kitchen Clock](https://github.com/chof747/kitchen-clock)