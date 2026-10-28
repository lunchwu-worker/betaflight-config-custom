/*
 * A7456HD power-integrity diagnostic build for the MATEKH743.
 *
 * Keep only USB/VCP and the SPI2 OSD path at runtime.  This deliberately
 * omits sensors, SD card, ADC, UART pins, motors, servos, LEDs, beeper,
 * receiver and LED-strip hardware from the board configuration.
 */

#pragma once

// Use the feature-gated build path instead of Betaflight's classic build,
// which enables most drivers and protocols by default.
#define CLOUD_BUILD

#define FC_TARGET_MCU     STM32H743

#define BOARD_NAME        MATEKH743_OSD_ONLY
#define MANUFACTURER_ID   MTKS

#define USE_MAX7456
#define USE_OSD
#define USE_OSD_SD

// Only the OSD SPI bus is assigned board pins.
#define SPI2_SCK_PIN          PB13
#define SPI2_SDI_PIN          PB14
#define SPI2_SDO_PIN          PB15
#define MAX7456_SPI_CS_PIN    PB12
#define MAX7456_SPI_INSTANCE  SPI2

// Reproduce Betaflight's official MAX7456 initialization transaction order,
// timings and SPI rates, then select the verified 27MHz CVBS clock path.
#define MAX7456_OFFICIAL_INIT_LOGIC
#define A7456HD_27MHZ_CLOCK_INIT

#define DEFAULT_OSD_DISPLAYPORT_DEVICE OSD_DISPLAYPORT_DEVICE_MAX7456
#define DEFAULT_FEATURES FEATURE_OSD
