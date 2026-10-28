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
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

// Airbot_G4_AIO_HP_2026-V3  (STM32G474CEU6 / UFQFPN48)
// Derived from PR_AIRBOT_G4AIO, updated to match the HP-2026-V3 schematic:
//   - single IMU: U2 ICM-42688-P on SPI1 (CS=PB0, INT=PC4),
//     VTX power switch on PC13 (PINIO1), motor order M1=PA0..M4=PA3, UART3 TX on PB9.
//   - FLASH: U45 PY25Q128HA on SPI2 (CS=PC6); driver enabled by common_pre default.
// Serial defaults per request:
//   - UART1  (USART1) : OSD DisplayPort + MSP + VTX(MSP)
//   - "UART5" (LPUART1, board silk T5/R5) : Bluetooth + MSP

#pragma once

#define FC_TARGET_MCU     STM32G47X

#define BOARD_NAME        PR_Airbot_G4_AIO
#define MANUFACTURER_ID   AIRB

#define USE_ACC
#define USE_BARO
#define USE_MAG
#define USE_GYRO
#define USE_FLASH
#define USE_LED_STRIP
#define USE_TRANSPONDER
// No analog OSD chip on this board (MAX7456/AT7456 absent).
// OSD is provided over MSP DisplayPort by an external CH32V203 (see UART1 below).
// USE_MAX7456 is intentionally NOT defined so USE_OSD_HD is auto-enabled
// (common_pre.h) and the OSD defaults to MSP DisplayPort with HD selectable.

#define USE_ACC_SPI_ICM42688P
#define USE_GYRO_SPI_ICM42688P
#define USE_ACCGYRO_ICM40608
#define USE_ACCGYRO_LSM6DSV16X
#define USE_FLASH_W25Q128FV

#define USE_BARO_DPS310
#define USE_BARO_BMP280
#define USE_BARO_BMP085
#define USE_BARO_MS5611
#define USE_BARO_QMP6988
#define USE_BARO_LPS

#define GYRO_1_CS_PIN        PB0
#define GYRO_1_EXTI_PIN      PC4

#define BEEPER_PIN           PB7

#define MOTOR1_PIN           PA0
#define MOTOR2_PIN           PA1
#define MOTOR3_PIN           PA2
#define MOTOR4_PIN           PA3

#define LED_STRIP_PIN        PB6

#define UART1_TX_PIN         PA9
#define UART2_TX_PIN         PB3
#define UART3_TX_PIN         PB9
#define UART4_TX_PIN         PC10
#define LPUART1_TX_PIN       PB11

#define UART1_RX_PIN         PA10
#define UART2_RX_PIN         PB4
#define UART4_RX_PIN         PC11
#define LPUART1_RX_PIN       PB10

#define I2C1_SCL_PIN         PA13
#define I2C1_SDA_PIN         PA14

#define LED0_PIN             PA15
#define LED1_PIN             PC15

#define SPI1_SCK_PIN         PA5
#define SPI2_SCK_PIN         PB13

#define SPI1_SDI_PIN         PA6
#define SPI2_SDI_PIN         PB14

#define SPI1_SDO_PIN         PA7
#define SPI2_SDO_PIN         PB15

#define ADC_VBAT_PIN         PB2
#define ADC_CURR_PIN         PB1

#define FLASH_CS_PIN         PC6

#define CAMERA_CONTROL_PIN   PB5

// VTX power switch (net VTX_POWER_SWITCH -> PC13), user-toggleable via mode (USER1)
#define PINIO1_PIN           PC13
#define PINIO1_CONFIG        129
#define PINIO1_BOX           40

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, LED_STRIP_PIN , 3,  12) \
    TIMER_PIN_MAP( 1, MOTOR1_PIN , 1,  1) \
    TIMER_PIN_MAP( 2, MOTOR2_PIN , 1,  2) \
    TIMER_PIN_MAP( 3, MOTOR3_PIN , 1,  3) \
    TIMER_PIN_MAP( 4, MOTOR4_PIN , 1,  4)

#define ADC1_DMA_OPT                 10
#define ADC2_DMA_OPT                 11

#define SPI1_RX_DMA_OPT              6
#define SPI1_TX_DMA_OPT              7
#define SPI2_RX_DMA_OPT              8
#define SPI2_TX_DMA_OPT              9

#define ADC_INSTANCE                 ADC2
#define DEFAULT_BLACKBOX_DEVICE      BLACKBOX_DEVICE_FLASH
#define DEFAULT_DSHOT_BURST          DSHOT_DMAR_ON
#define DEFAULT_CURRENT_METER_SOURCE CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SCALE  179
#define DEFAULT_VOLTAGE_METER_SCALE  110
#define BEEPER_INVERTED
#define SYSTEM_HSE_MHZ               8

#define BARO_I2C_INSTANCE            I2CDEV_1
#define MAG_I2C_INSTANCE             I2CDEV_1
#define FLASH_SPI_INSTANCE           SPI2
#define GYRO_1_SPI_INSTANCE          SPI1
#define GYRO_1_ALIGN                 CW0_DEG_FLIP
#define DEFAULT_ALIGN_BOARD_YAW      -45

// ===== Serial port function defaults =====
// UART1 (USART1, PA9/PA10): digital OSD DisplayPort + MSP + VTX(MSP)
#define MSP_DISPLAYPORT_UART         SERIAL_PORT_USART1
// LPUART1 (board silk "UART5", PB11/PB10): Bluetooth module + MSP
#define USE_MSP_UART                 SERIAL_PORT_LPUART1
