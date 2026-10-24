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
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// MAMBA_REACTOR_H743：STM32H743VIH6（TFBGA-100，U31），引脚分配以嘉立创原理图网表为准。
// 板载外设：ICM-40608-P 陀螺仪（SPI1 + CLKIN）、SPA06-003 气压计（I2C1，DPS310 驱动兼容）、
// PY25Q128HA 128Mbit Flash（SPI3）、CH591 蓝牙模块（UART1）、ESP8285+SX1280 板载 ELRS（UART2）、
// CH32V203 OSD 协处理器（UART3，MSP DisplayPort）、8 路电机输出。
#define FC_TARGET_MCU     STM32H743

#define BOARD_NAME        MAMBA_REACTOR_H743
#define MANUFACTURER_ID   PRMB

#define USE_ACC
#define USE_GYRO
#define USE_ACC_SPI_ICM42688P
#define USE_GYRO_SPI_ICM42688P
#define USE_ACCGYRO_ICM40608

#define USE_FLASH
#define USE_FLASH_PY25Q128HA
#define USE_BARO
#define USE_BARO_DPS310    // SPA06-003 芯片 ID 0x11，由 DPS310 驱动 SPL07/SPA06 分支支持
#define USE_MAG
#define USE_GPS
#define USE_LED_STRIP

// 蜂鸣器：PC0 经 R48 驱动 NPN（Q2 MMBT3904），高电平有效
#define BEEPER_PIN        PC0
#define BEEPER_INVERTED

// Motors — 网表 M1–M8
#define MOTOR1_PIN        PA3
#define MOTOR2_PIN        PA2
#define MOTOR3_PIN        PA1
#define MOTOR4_PIN        PA0
#define MOTOR5_PIN        PB0
#define MOTOR6_PIN        PB1
#define MOTOR7_PIN        PC8
#define MOTOR8_PIN        PC9

#define LED0_PIN          PB3
#define LED_STRIP_PIN     PB9

// UART1 — CH591 蓝牙模块（MSP）
#define UART1_TX_PIN      PA9
#define UART1_RX_PIN      PA10
// UART2 — 板载 ELRS 接收机（ESP8285+SX1280，CRSF）
#define UART2_TX_PIN      PD5
#define UART2_RX_PIN      PD6
// UART3 — CH32V203 OSD（MSP DisplayPort），同时引出至 CN13 数传连接器 3/4 脚
#define UART3_TX_PIN      PD8
#define UART3_RX_PIN      PD9
// UART4 — 焊盘
#define UART4_TX_PIN      PD1
#define UART4_RX_PIN      PD0
// UART5 — RX 引出至 CN13 连接器 6 脚（可作 SBUS 输入）
#define UART5_TX_PIN      PC12
#define UART5_RX_PIN      PD2
// UART6 — 焊盘（GPS）
#define UART6_TX_PIN      PC6
#define UART6_RX_PIN      PC7
// UART7 — RX 经 R24 引出至 ESC 连接器（CN1）第 6 脚，作普通串口使用
#define UART7_TX_PIN      PE8
#define UART7_RX_PIN      PE7
// UART8 — 焊盘
#define UART8_TX_PIN      PE1
#define UART8_RX_PIN      PE0

// I2C1 — 板载 SPA06-003 气压计；I2C2 — 外接焊盘（罗盘）
#define I2C1_SCL_PIN      PB6
#define I2C1_SDA_PIN      PB7
#define I2C2_SCL_PIN      PB10
#define I2C2_SDA_PIN      PB11

// SPI1 — 陀螺仪；SPI2/SPI4 — 扩展焊盘；SPI3 — Flash（注意 SDO 为 PB5）
#define SPI1_SCK_PIN      PA5
#define SPI1_SDI_PIN      PA6
#define SPI1_SDO_PIN      PA7
#define SPI2_SCK_PIN      PB13
#define SPI2_SDI_PIN      PB14
#define SPI2_SDO_PIN      PB15
#define SPI3_SCK_PIN      PC10
#define SPI3_SDI_PIN      PC11
#define SPI3_SDO_PIN      PB5
#define SPI4_SCK_PIN      PE12
#define SPI4_SDI_PIN      PE13
#define SPI4_SDO_PIN      PE14

// ADC：PC2/PC3 在 TFBGA-100 上为 PC2_C/PC3_C 直连 ADC3 通道
#define ADC_VBAT_PIN      PC1
#define ADC_RSSI_PIN      PC2
#define ADC_CURR_PIN      PC3

#define FLASH_CS_PIN      PA15
#define FLASH_SPI_INSTANCE SPI3

#define GYRO_1_CS_PIN     PC4
#define GYRO_1_EXTI_PIN   PC5
#define GYRO_1_SPI_INSTANCE SPI1
#define GYRO_1_ALIGN      CW270_DEG   // 在原理图基准 CW0 上 YAW +270°

// IMUCLK：PD15（TIM4_CH4）→ ICM-40608 CLKIN
#define USE_GYRO_CLKIN
#define GYRO_1_CLKIN_PIN  PD15

// PINIO1 — PE2 控制 CH591 蓝牙模块（PA15 使能脚）
// PINIO2 — PD4 控制 10V BEC 使能（10VEN→PAD2→U46.EN，图传供电）；
//          EN 经 R5 上拉 3V3，配 0x81 反相推挽使上电默认拉高=BEC 通电，USER2 可断电
#define PINIO1_PIN        PE2
#define PINIO1_BOX        40
#define PINIO1_CONFIG     1
#define PINIO2_PIN        PD4
#define PINIO2_BOX        41
#define PINIO2_CONFIG     129   // PINIO_CONFIG_OUT_INVERTED | OUT_PP：上电默认开启 10V BEC
#define BOX_USER2_NAME    "VTX-SW"   // USER2 显示名（图传电源开关）

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP(  0, PA3 , 2,  0 ) \
    TIMER_PIN_MAP(  1, PA2 , 2,  1 ) \
    TIMER_PIN_MAP(  2, PA1 , 2,  2 ) \
    TIMER_PIN_MAP(  3, PA0 , 2,  3 ) \
    TIMER_PIN_MAP(  4, PB0 , 2,  4 ) \
    TIMER_PIN_MAP(  5, PB1 , 2,  5 ) \
    TIMER_PIN_MAP(  6, PC8 , 2,  6 ) \
    TIMER_PIN_MAP(  7, PC9 , 2,  7 ) \
    TIMER_PIN_MAP(  8, PB9 , 1,  0 ) \
    TIMER_PIN_MAP(  9, PD15, 1, -1 )

#define ADC1_DMA_OPT      8
#define ADC3_DMA_OPT      9
#define TIMUP3_DMA_OPT    2
#define TIMUP5_DMA_OPT    0
#define TIMUP8_DMA_OPT    4

// 板上仅 I2C1（PB6/PB7）为完整总线（带上拉 R1/R2，挂 SPA06 气压计）；
// I2C2（PB10/PB11）只接到 MCU、无上拉无器件无引出，外接磁力计须走 I2C1。
#define BARO_I2C_INSTANCE (I2CDEV_1)
#define MAG_I2C_INSTANCE  (I2CDEV_1)

#define DEFAULT_BLACKBOX_DEVICE      BLACKBOX_DEVICE_FLASH
#define DEFAULT_CURRENT_METER_SOURCE CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC
#define DEFAULT_VOLTAGE_METER_SCALE  110
#define DEFAULT_CURRENT_METER_SCALE  250

#define SYSTEM_HSE_MHZ    8

#define SERIALRX_UART         SERIAL_PORT_USART2
#define SERIALRX_PROVIDER     SERIALRX_CRSF
#define MSP_UART              SERIAL_PORT_USART1
#define MSP_DISPLAYPORT_UART  SERIAL_PORT_USART3
