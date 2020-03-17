#ifndef TARGET_DEFINITIONS_H
#define TARGET_DEFINITIONS_H

#ifdef REVB
static const char *TEMP_SENSOR_DEV_PATH = "/dev/i2c-6";
static const char *EEPROM_DEV_PATH = "/sys/bus/i2c/devices/6-0056/eeprom";
#else
static const char *TEMP_SENSOR_DEV_PATH = "/dev/i2c-6";
static const char *EEPROM_DEV_PATH = "/sys/bus/i2c/devices/6-0056/eeprom";
#endif // REVB

static const char *CAPTURE_DEVICE_NAME = "vi-output, addi9036 6-0064";

#endif // TARGET_DEFINITIONS_H
