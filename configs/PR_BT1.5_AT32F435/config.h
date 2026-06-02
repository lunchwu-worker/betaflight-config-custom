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

// PR_BT v1.5 public board, MCU swapped from STM32F405 to AT32F435.
// GPIO pin assignments are identical to PR_F405-BT_v1.5 (same PCB);
// only the timer/DMA mapping is recomputed for the AT32F435 peripheral set.

#define FC_TARGET_MCU     AT32F435G

#define BOARD_NAME        PR_BT15_AT32F435
#define MANUFACTURER_ID   ABCD

#define USE_ACC
#define USE_ACC_SPI_ICM42688P
#define USE_ACC_SPI_LSM6DSV16X

#define USE_GYRO
#define USE_GYRO_SPI_ICM42688P
#define USE_GYRO_SPI_LSM6DSV16X
#define USE_ACCGYRO_LSM6DSV16X

#define USE_ACCGYRO_IIM42652
#define USE_ACCGYRO_ICM40608

#define USE_FLASH
#define USE_FLASH_PY25Q128HA
#define USE_BARO
#define USE_BARO_BMP280
#define USE_BARO_DPS310
#define USE_MAG
#define USE_GPS
#define USE_LED_STRIP

#define BEEPER_PIN PA4
#define MOTOR1_PIN PC8
#define MOTOR2_PIN PC9
#define MOTOR3_PIN PA9
#define MOTOR4_PIN PA10
#define MOTOR5_PIN PB14
#define MOTOR6_PIN PB15
#define MOTOR7_PIN PA8
#define MOTOR8_PIN PB0
#define SERVO1_PIN PA6
#define SERVO2_PIN PB1

#define LED_STRIP_PIN PA7

#define UART1_TX_PIN PB6
#define UART2_TX_PIN PA2
#define UART3_TX_PIN PC10
#define UART4_TX_PIN PA0
#define UART5_TX_PIN PC12
#define UART6_TX_PIN PC6

#define UART1_RX_PIN PB7
#define UART2_RX_PIN PA3
#define UART3_RX_PIN PC11
#define UART4_RX_PIN PA1
#define UART5_RX_PIN PD2
#define UART6_RX_PIN PC7

#define USE_I2C_PULLUP

#define I2C1_SCL_PIN PB8
#define I2C1_SDA_PIN PB9

#define LED0_PIN PC5

//#define SPI1_SCK_PIN PA5
#define SPI2_SCK_PIN PB13
#define SPI3_SCK_PIN PB3
//#define SPI1_SDI_PIN PA6
#define SPI2_SDI_PIN PC2
#define SPI3_SDI_PIN PB4
//#define SPI1_SDO_PIN PA7
#define SPI2_SDO_PIN PC3
#define SPI3_SDO_PIN PB5
#define ESCSERIAL_PIN PC7

#define ADC_VBAT_PIN PC1
#define ADC_CURR_PIN PC0

#define FLASH_CS_PIN PA15
#define GYRO_1_EXTI_PIN PB12
#define GYRO_1_CS_PIN PA5

#define PINIO1_PIN PC4 //BT
#define PINIO1_BOX 40

#define PINIO2_PIN PC13 //CAM Switch
#define PINIO2_BOX 41

// ============================================================================
// DSHOT Bitbang 配置（与 F405 v1.5 一致）
// ============================================================================
// Bitbang 用一个专用 timer (TIM1) 驱动所有电机的 DSHOT 信号，电机引脚本身
// 由 GPIO+DMA 直接驱动，不占用各自的 timer 通道，从而把 timer 资源留给
// LED_STRIP 和 SERVO。
#define DEFAULT_DSHOT_BITBANG DSHOT_BITBANG_ON
#define DSHOT_BITBANGED_TIMER_DEFAULT DSHOT_BITBANGED_TIMER_TIM1

// ============================================================================
// Timer Pin Mapping（按 AT32F435 的 timer 表重新计算 occurrence 索引）
// ============================================================================
// AT32 bitbang 在初始化时会对每个电机引脚调用 timerGetConfiguredByTag()，
// 因此电机引脚必须出现在此映射中（否则解引用空指针崩溃）。
// occ = 该引脚在 AT32F435 fullTimerHardware 表中的出现次序(1-based)。
//
// MOTOR1 PC8  occ1 -> TMR3_CH3      MOTOR5 PB14 occ3 -> TMR12_CH1
// MOTOR2 PC9  occ1 -> TMR3_CH4      MOTOR6 PB15 occ3 -> TMR12_CH2
// MOTOR3 PA9  occ1 -> TMR1_CH2      MOTOR7 PA8  occ1 -> TMR1_CH1
// MOTOR4 PA10 occ1 -> TMR1_CH3      MOTOR8 PB0  occ2 -> TMR3_CH3
// 电机为 bitbang，不使用通道 DMA，dmaopt = -1。
//
// LED_STRIP PA7 occ1 -> TMR3_CH2 (带 DMA, WS2811)
// SERVO1    PA6 occ2 -> TMR13_CH1 (SERVO 不需要 DMA)
// SERVO2    PB1 occ3 -> TMR8_CH3N (用 TIM8，因 TIM3 已被 LED 占用)
#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, PC8,  1, -1) \
    TIMER_PIN_MAP( 1, PC9,  1, -1) \
    TIMER_PIN_MAP( 2, PA9,  1, -1) \
    TIMER_PIN_MAP( 3, PA10, 1, -1) \
    TIMER_PIN_MAP( 4, PB14, 3, -1) \
    TIMER_PIN_MAP( 5, PB15, 3, -1) \
    TIMER_PIN_MAP( 6, PA8,  1, -1) \
    TIMER_PIN_MAP( 7, PB0,  2, -1) \
    TIMER_PIN_MAP( 8, PA7,  1,  0) \
    TIMER_PIN_MAP( 9, PA6,  2, -1) \
    TIMER_PIN_MAP(10, PB1,  3, -1) \

#define ADC1_DMA_OPT 11

#define DEFAULT_BLACKBOX_DEVICE     BLACKBOX_DEVICE_FLASH
#define DEFAULT_DSHOT_BURST DSHOT_DMAR_OFF
#define DEFAULT_CURRENT_METER_SOURCE CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SCALE 250
#define BEEPER_INVERTED
#define SYSTEM_HSE_MHZ 8
#define OSD_CANVAS_SIZE_DEBUG

#define MAG_I2C_INSTANCE (I2CDEV_1)
#define BARO_I2C_INSTANCE (I2CDEV_1)
#define GYRO_1_SPI_INSTANCE SPI2
#define FLASH_SPI_INSTANCE SPI3
#define GYRO_1_ALIGN CW0_DEG

#define MSP_DISPLAYPORT_UART    SERIAL_PORT_UART4

#define SERIALRX_UART SERIAL_PORT_USART2
#define SERIALRX_PROVIDER SERIALRX_CRSF

#define MSP_UART SERIAL_PORT_USART1
