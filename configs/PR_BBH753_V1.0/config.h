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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// BBH753 (AIRBOT H743VIH6)：按当前原理图 PR_BB-H7-ICM-20-V1.0 的网络改引脚。
// Gyro1 = ICM-42688-P，SPI4。Gyro2 = ST LSM6DSK320X（客户称 LSM320x），SPI3，默认空贴。
// 两个陀螺仪安装方向都保持 CW0_DEG，本次不改。
// 4 路电机都在 TIM1：M1 PE13 / M2 PE14 / M3 PE9 / M4 PE11。
// OSD = MSP DisplayPort，UART7（PE8/PE7，接到 CH32）。蓝牙 = UART8（PE1/PE0）。无 MAX7456，无 PPM。
#define FC_TARGET_MCU        STM32H743

#define BOARD_NAME           BBH753
#define MANUFACTURER_ID      AIRB

// X4 = 8MHz 晶振（PH0/PH1）
#define SYSTEM_HSE_MHZ       8

#define USE_ACC
#define USE_GYRO
// Gyro1 实贴 ICM-42688-P。不要打开 ICM206xx/MPU6500：
// MPU6500 检测会先匹配 WHO_AM_I=0x47，把 ICM-42688-P 初始化错。
#define USE_ACC_SPI_ICM42688P
#define USE_GYRO_SPI_ICM42688P
// Gyro2：固件里的型号名是 LSM6DSK320X（K，不是 V），和 LSM6DSV16X 共用驱动、WHO_AM_I=0x75。
// 位号默认空贴，所以默认只用 Gyro1。
#define USE_ACCGYRO_LSM6DSK320X
// 客户要求可识别：ICM42688 / ICM40608 / IIM42652 / LSM6DSK320X / LSM6DSV16X
#define USE_ACCGYRO_ICM40608
#define USE_ACCGYRO_IIM42652
#define USE_ACCGYRO_LSM6DSV16X

#define USE_BARO
#define USE_BARO_DPS310
#define USE_BARO_BMP280
#define USE_BARO_MS5611
#define USE_BARO_LPS22H

#define USE_MAG

#define USE_FLASH
#define USE_FLASH_W25Q128FV
#define USE_FLASH_W25N01G

#define USE_GPS

// OSD — MSP DisplayPort，HD 与 PAL/NTSC 都可选（默认 HD）。无 MAX7456。
#define USE_OSD
#define USE_OSD_HD
#define USE_OSD_SD
// CH32 的 USART1：PA9=TX 接飞控 UART7_RX(PE7)，PA10=RX 接飞控 UART7_TX(PE8)。
#define MSP_DISPLAYPORT_UART SERIAL_PORT_USART7

// 蜂鸣器 PB0。NPN（Q2 射极接地），高电平鸣，所以不再反相。
// 无源蜂鸣器用 PWM，2500Hz。定时器必须是 TIM3_CH3（PB0 序号 2），不能占 TIM1。
#define BEEPER_PIN           PB0
#define BEEPER_PWM_HZ        2500

// 电机（QUADX）。四路同一端口、同一 TIM1，DShot 用 bitbang。
#define MOTOR1_PIN           PE13
#define MOTOR2_PIN           PE14
#define MOTOR3_PIN           PE9
#define MOTOR4_PIN           PE11

// 原理图上没有灯带数据脚。PD12 的网络名是 PINIO1，接到蓝牙模块 PA15。
#define PINIO1_PIN           PD12
#define PINIO1_BOX           40
// 视频切换，原理图网络 CAM_SWITCH。BT_EN(PC5) 只有 MCU 脚，模块上没接，不定义。
#define PINIO2_PIN           PC14
#define PINIO2_BOX           41
// 摄像头控制，原理图网络 CAM_CTRL_MCU。
#define CAMERA_CONTROL_PIN   PE10

// UART x8。UART2 在 PD5/PD6。UART3 在 PD8/PD9（不是 OSD）。
// UART7 = OSD（PE8 TX / PE7 RX）。UART8 = 蓝牙（PE1 TX / PE0 RX，接到模块 U1RX/U1TX）。
#define UART1_TX_PIN         PA9
#define UART1_RX_PIN         PA10
#define UART2_TX_PIN         PD5
#define UART2_RX_PIN         PD6
#define UART3_TX_PIN         PD8
#define UART3_RX_PIN         PD9
#define UART4_TX_PIN         PA0
#define UART4_RX_PIN         PA1
#define UART5_TX_PIN         PB6
#define UART5_RX_PIN         PB5
#define UART6_TX_PIN         PC6
#define UART6_RX_PIN         PC7
#define UART7_TX_PIN         PE8
#define UART7_RX_PIN         PE7
#define UART8_TX_PIN         PE1
#define UART8_RX_PIN         PE0

// I2C2（气压计 SPL06，走 DPS310 驱动）+ I2C3
#define I2C2_SCL_PIN         PB10
#define I2C2_SDA_PIN         PB11
#define I2C3_SCL_PIN         PA8
#define I2C3_SDA_PIN         PC9

// 状态灯。VIH6 没有 PF11，原理图接在 PD0。
#define LED0_PIN             PD0

// SPI2 — Flash（PY28Q128HA，命令集同 W25Q128）
#define SPI2_SCK_PIN         PB13
#define SPI2_SDI_PIN         PB14
#define SPI2_SDO_PIN         PB15
// SPI3 — Gyro 2
#define SPI3_SCK_PIN         PC10
#define SPI3_SDI_PIN         PC11
#define SPI3_SDO_PIN         PC12
// SPI4 — Gyro 1
#define SPI4_SCK_PIN         PE2
#define SPI4_SDI_PIN         PE5
#define SPI4_SDO_PIN         PE6

// PC2_C / PC3_C 只进 ADC3。PC0 原理图悬空，不再定义外部 ADC。
#define ADC_VBAT_PIN         PC3
#define ADC_CURR_PIN         PC2

#define FLASH_SPI_INSTANCE   SPI2
#define FLASH_CS_PIN         PB4

// Gyro 1 — ICM-42688-P，SPI4。方向保持 CW0_DEG。
#define GYRO_1_SPI_INSTANCE  SPI4
#define GYRO_1_CS_PIN        PE4
#define GYRO_1_ALIGN         CW0_DEG
// Gyro 2 — LSM6DSK320X，SPI3，默认空贴。方向保持 CW0_DEG。
#define GYRO_2_SPI_INSTANCE  SPI3
#define GYRO_2_CS_PIN        PB12
#define GYRO_2_ALIGN         CW0_DEG

// 外部时钟只接到 ICM-42688-P 的 CLKIN。固件固定输出 32kHz。
// PA6 如果用定时器序号 1 会落到 TIM3_CH1，和蜂鸣器的 TIM3 共用周期，所以必须用序号 2（TIM13_CH1）。
#define USE_GYRO_CLKIN
#define GYRO_1_CLKIN_PIN     PA5
#define GYRO_2_CLKIN_PIN     PA6

#define GYRO_1_EXTI_PIN      PC4
#define GYRO_2_EXTI_PIN      PB7

// 定时器序号按 timer_stm32h7xx.c 里同一引脚的出现顺序，从 1 计。
// 电机：PE13/PE14/PE9/PE11 都只有 TIM1，序号 1。DMA 0–3。
// 蜂鸣器：PB0 序号 2 = TIM3_CH3，无 DMA。
// CLKIN：PA5 序号 1 = TIM2_CH1；PA6 序号 2 = TIM13_CH1。不要用 TIM8。
#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, PE13, 1,  0) \
    TIMER_PIN_MAP( 1, PE14, 1,  1) \
    TIMER_PIN_MAP( 2, PE9,  1,  2) \
    TIMER_PIN_MAP( 3, PE11, 1,  3) \
    TIMER_PIN_MAP( 4, PB0,  2, -1) \
    TIMER_PIN_MAP( 5, PA5,  1, -1) \
    TIMER_PIN_MAP( 6, PA6,  2, -1)

#define ADC1_DMA_OPT         8
#define ADC3_DMA_OPT         9
// 电机 DMA 已占用 0–3，TIM1 更新 DMA 不能再用 0。
#define TIMUP1_DMA_OPT       10

#define BARO_I2C_INSTANCE    I2CDEV_2
#define MAG_I2C_INSTANCE     I2CDEV_3

#define DEFAULT_BLACKBOX_DEVICE        BLACKBOX_DEVICE_NONE
// Gyro2 默认空贴，开机只用 Gyro1。
#define DEFAULT_GYRO_TO_USE            GYRO_CONFIG_USE_GYRO_1
#define DEFAULT_CURRENT_METER_SOURCE   CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE   VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SCALE    80
#define DEFAULT_VOLTAGE_METER_SCALE    110

#define SERIALRX_PROVIDER    SERIALRX_SBUS
