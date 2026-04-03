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

#pragma once

#define FC_TARGET_MCU     STM32F405

#define BOARD_NAME        PR_FRBALLF405
#define MANUFACTURER_ID   AIRB

// ============================================================================
// IMU
// ============================================================================
#define USE_ACC
#define USE_GYRO

// ICM42688P
#define USE_ACC_SPI_ICM42688P
#define USE_GYRO_SPI_ICM42688P

// IIM42652
#define USE_ACCGYRO_IIM42652

// ICM40608
#define USE_ACCGYRO_ICM40608

// LSM6DSV16X / LSM6DSK320X
#define USE_ACCGYRO_LSM6DSV16X
#define USE_ACCGYRO_LSM6DSK320X

// ============================================================================
// Barometer (I2C1)
// ============================================================================
#define USE_BARO
#define USE_BARO_BMP280
#define USE_BARO_DPS310

// ============================================================================
// Magnetometer (I2C1)
// ============================================================================
#define USE_MAG
#define USE_MAG_HMC5883
#define USE_MAG_QMC5883
#define USE_MAG_LIS3MDL
#define USE_MAG_AK8963
#define USE_MAG_IST8310

// ============================================================================
// Storage & OSD
// ============================================================================
#define USE_FLASH
#define USE_FLASH_PY25Q128HA
#define USE_GPS
#define USE_LED_STRIP

// ============================================================================
// Gyro external clock
// ============================================================================
#define USE_GYRO_CLKIN

// ============================================================================
// Beeper
// ============================================================================
#define BEEPER_PIN         PB1
#define BEEPER_INVERTED

// ============================================================================
// Motors (6路) - TIM8(PC8,PC9) + TIM1(PA9,PA10) + TIM3(PA6,PA7)
// ============================================================================
#define MOTOR1_PIN         PC8
#define MOTOR2_PIN         PC9
#define MOTOR3_PIN         PA9
#define MOTOR4_PIN         PA10
#define MOTOR5_PIN         PA6
#define MOTOR6_PIN         PA7

// ============================================================================
// PPM
// ============================================================================
#define RX_PPM_PIN         PA3

// ============================================================================
// LED strip
// ============================================================================
#define LED_STRIP_PIN      PB0

// ============================================================================
// UART - 6 channels
// ============================================================================
#define UART1_TX_PIN       PB6
#define UART1_RX_PIN       PB7
#define UART2_TX_PIN       PA2
#define UART2_RX_PIN       PA3
#define UART3_TX_PIN       PC10
#define UART3_RX_PIN       PC11
#define UART4_TX_PIN       PA0
#define UART4_RX_PIN       PA1
#define UART5_TX_PIN       PC12
#define UART5_RX_PIN       PD2
#define UART6_TX_PIN       PC6
#define UART6_RX_PIN       PC7

// ============================================================================
// I2C
// ============================================================================
#define I2C1_SCL_PIN       PB8
#define I2C1_SDA_PIN       PB9

// ============================================================================
// Status LED
// ============================================================================
#define LED0_PIN           PC5

// ============================================================================
// SPI
// ============================================================================
// SPI2 - Gyro
#define SPI2_SCK_PIN       PB13
#define SPI2_SDI_PIN       PB14
#define SPI2_SDO_PIN       PB15

// SPI3 - Flash
#define SPI3_SCK_PIN       PB3
#define SPI3_SDI_PIN       PB4
#define SPI3_SDO_PIN       PB5

// ============================================================================
// ADC
// ============================================================================
#define ADC_VBAT_PIN       PC1
#define ADC_CURR_PIN       PC2

// ============================================================================
// Gyro - SPI2
// ============================================================================
#define FLASH_CS_PIN       PA15
#define GYRO_1_EXTI_PIN    PB12
#define GYRO_1_CS_PIN      PA8
#define GYRO_1_CLKIN_PIN   PB10

#define ESCSERIAL_PIN      PC11
#define INVERTER_PIN_UART2 PA4

// ============================================================================
// Timer pin mapping
//  0: PA3  RX_PPM  - TIM5_CH4, DMA
//  1: PC9  MOTOR2  - TIM8_CH4, DMA
//  2: PC8  MOTOR1  - TIM8_CH3, DMA
//  3: PA9  MOTOR3  - TIM1_CH2, DMA
//  4: PA10 MOTOR4  - TIM1_CH3, DMA
//  5: PB0  LED     - TIM3_CH3, DMA
//  6: PB10 CLKIN   - TIM2_CH3, no DMA
//  7: PA6  MOTOR5  - TIM3_CH1, DMA
//  8: PA7  MOTOR6  - TIM3_CH2, DMA
// ============================================================================
#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, PA3,  2, 0) \
    TIMER_PIN_MAP( 1, PC9,  2, 0) \
    TIMER_PIN_MAP( 2, PC8,  2, 1) \
    TIMER_PIN_MAP( 3, PA9,  1, 1) \
    TIMER_PIN_MAP( 4, PA10, 1, 1) \
    TIMER_PIN_MAP( 5, PB0,  2, 0) \
    TIMER_PIN_MAP( 6, PB10, 1, -1) \
    TIMER_PIN_MAP( 7, PA6,  1, 0) \
    TIMER_PIN_MAP( 8, PA7,  2, 0)

#define ADC1_DMA_OPT       0

// ============================================================================
// Defaults
// ============================================================================
#define SERIALRX_UART                  SERIAL_PORT_USART1
#define SERIALRX_PROVIDER              SERIALRX_FPORT

#define DEFAULT_BLACKBOX_DEVICE        BLACKBOX_DEVICE_FLASH
#define DEFAULT_DSHOT_BURST            DSHOT_DMAR_ON
#define DEFAULT_CURRENT_METER_SOURCE   CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE   VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SCALE    250
#define SYSTEM_HSE_MHZ                 8

#define MAG_I2C_INSTANCE               (I2CDEV_1)
#define BARO_I2C_INSTANCE              (I2CDEV_1)
#define GYRO_1_SPI_INSTANCE            SPI2
#define FLASH_SPI_INSTANCE             SPI3
#define GYRO_1_ALIGN                   CW0_DEG
