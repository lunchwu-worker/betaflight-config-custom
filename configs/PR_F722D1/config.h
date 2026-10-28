/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software. You can redistribute this software
 * and/or modify this software under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later
 * version.
 *
 * Betaflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 */

#pragma once

// PR_F722D1 — STM32F722RET6 (LQFP64).
// Pin assignments are taken from the JLCEDA project time_over/MAMBA_F722_2022B
// and interpreted using the STM32F722 LQFP64 pin table (not the F405 aliases
// also printed on the shared GenericF405/F435/F722 schematic symbol).

#define FC_TARGET_MCU     STM32F7X2

#define BOARD_NAME        PR_F722D1
#define MANUFACTURER_ID   DIAT

// Sensors: U1 ICM-42688-P on SPI1; U12 SPA06-003 on I2C1.
// External magnetometer is supported on the I2C1 pads (no onboard MAG).
#define USE_ACC
#define USE_GYRO
#define USE_ACC_SPI_ICM42688P
#define USE_GYRO_SPI_ICM42688P
#define USE_BARO
#define USE_BARO_DPS310
#define USE_MAG
#define USE_GPS
#define USE_I2C_PULLUP

// U2 PY25Q128HA (128 Mbit) on SPI3.
#define USE_FLASH
#define USE_FLASH_PY25Q128HA

// U25 CH32V203 exposes the board's MAX7456-compatible soft-OSD protocol on SPI2.
// This is an analog SD OSD; explicitly select it instead of the global HD/MSP default.
#define USE_OSD_SD
#define USE_MAX7456
#define DEFAULT_OSD_DISPLAYPORT_DEVICE OSD_DISPLAYPORT_DEVICE_MAX7456

#define USE_LED_STRIP
#define USE_PINIO

#define BEEPER_PIN           PB2

#define MOTOR1_PIN           PC8
#define MOTOR2_PIN           PC9
#define MOTOR3_PIN           PA8
#define MOTOR4_PIN           PA9
#define MOTOR5_PIN           PB0
#define MOTOR6_PIN           PB1
#define MOTOR7_PIN           PA10
#define MOTOR8_PIN           PB4

#define LED_STRIP_PIN        PB3

#define UART1_TX_PIN         PB6
#define UART1_RX_PIN         PB7
#define UART2_TX_PIN         PA2
#define UART2_RX_PIN         PA3
#define UART3_TX_PIN         PB10
#define UART3_RX_PIN         PB11
#define UART4_TX_PIN         PA0
#define UART4_RX_PIN         PA1
#define UART5_TX_PIN         PC12
#define UART5_RX_PIN         PD2
#define UART6_TX_PIN         PC6
#define UART6_RX_PIN         PC7

#define I2C1_SCL_PIN         PB8
#define I2C1_SDA_PIN         PB9

// Schematic nets: LED0 -> PC14, LED_GYRO -> PC15 (both active-low).
// LED0 = MCU/status indicator after board init.
// GYRO_LED blinks at 1 Hz once the gyro is calibrated/stable.
#define LED0_PIN             PC14
#define GYRO_LED_PIN         PC15
#define GYRO_LED_BLINK

#define SPI1_SCK_PIN         PA5
#define SPI1_SDI_PIN         PA6
#define SPI1_SDO_PIN         PA7
#define SPI2_SCK_PIN         PB13
#define SPI2_SDI_PIN         PB14
#define SPI2_SDO_PIN         PB15
#define SPI3_SCK_PIN         PC10
#define SPI3_SDI_PIN         PC11
#define SPI3_SDO_PIN         PB5

#define ADC_VBAT_PIN         PC1
#define ADC_CURR_PIN         PC3

// Keep the schematic pin assignment unchanged:
// PINIO1/PC2 = CAM_SWITCH; PINIO2/PC0 = active-high 12V_EN.
// Hold 12V_EN low during USB-only power, and enable it only when
// VBAT > 6.00V and USER1 is not active.
#define PINIO1_PIN           PC2
#define PINIO2_PIN           PC0
#define PINIO2_VBAT_ENABLE_THRESHOLD 600

#define FLASH_CS_PIN         PA15
#define MAX7456_SPI_CS_PIN   PB12
#define GYRO_1_CS_PIN        PA4
#define GYRO_1_EXTI_PIN      PC4

// U1 INT2/CLKIN is wired to PC13. PC13 has no timer alternate function on the
// STM32F722 LQFP64, so USE_GYRO_CLKIN must remain disabled with the current
// Betaflight timer-based CLKIN driver.
#define GYRO_1_CLKIN_PIN     PC13

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, PB9 , 2, -1) \
    TIMER_PIN_MAP( 1, PC8 , 2,  0) \
    TIMER_PIN_MAP( 2, PC9 , 2,  0) \
    TIMER_PIN_MAP( 3, PA8 , 1,  0) \
    TIMER_PIN_MAP( 4, PA9 , 1,  0) \
    TIMER_PIN_MAP( 5, PB8 , 1,  0) \
    TIMER_PIN_MAP( 6, PB3 , 1,  0) \
    TIMER_PIN_MAP( 7, PB0 , 2,  0) \
    TIMER_PIN_MAP( 8, PB1 , 2,  0) \
    TIMER_PIN_MAP( 9, PA10, 1,  0) \
    TIMER_PIN_MAP(10, PB4 , 1,  0)

#define ADC3_DMA_OPT         0
#define ADC_INSTANCE         ADC3

#define MAG_I2C_INSTANCE     I2CDEV_1
#define BARO_I2C_INSTANCE    I2CDEV_1
#define MAX7456_SPI_INSTANCE SPI2
#define FLASH_SPI_INSTANCE   SPI3
#define GYRO_1_SPI_INSTANCE  SPI1

// Mechanical alignment cannot be inferred from the netlist; retain the
// established 2022B board orientation.
#define GYRO_1_ALIGN         CW180_DEG

#define DEFAULT_BLACKBOX_DEVICE       BLACKBOX_DEVICE_FLASH
#define DEFAULT_DSHOT_BURST           DSHOT_DMAR_ON
#define DEFAULT_CURRENT_METER_SOURCE  CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE  VOLTAGE_METER_ADC
// R39=10k / R40=1k divider (1:10) -> scale 110.
#define DEFAULT_VOLTAGE_METER_SCALE   110
// Current sense is supplied by the ESC connector; its transfer ratio is not
// present in the FC schematic, so retain the established 2022B value.
#define DEFAULT_CURRENT_METER_SCALE   115

#define BEEPER_INVERTED
#define SYSTEM_HSE_MHZ                8

// CH443L: SEL low selects CH0/CAM1; USER2 high selects CH1/CAM2.
#define PINIO1_CONFIG 1
#define PINIO2_CONFIG 129
#define PINIO1_BOX    41
#define PINIO2_BOX    40
