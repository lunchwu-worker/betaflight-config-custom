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

// FC-30-BT-H7 V1.9：STM32H743VIT6 焊盘 U3（LQFP100）/ STM32H743VIH6 焊盘 U31（TFBGA100，
// 同板二选一贴装，网络名一致），引脚分配以嘉立创工程 PR_FC-30-BT-H7_V1.9
// 网表 Netlist_Schematic1_2026-10-19 为准（已逐脚核对 U3 全部 100 脚）。
// 大幅参考公版 V1.8（PR_H7-BT_v1.8），V1.9 差异：
//   1. 陀螺仪 ICM-42688-P（U1）由 SPI2 改挂 SPI4（PE2/PE5/PE6），CS/EXTI/CLKIN 不变
//   2. 新增模拟 OSD AT7456E（U6）挂 SPI2（PB13/PC2/PC3），CS=PB11
//   3. PC6 由 UART6_TX 改为 CAMERA_CONTROL（CC_MCU→R109→CC_OUT→CN15），UART6 仅留 RX(PC7/R6)
//   4. PC13 仍为 PINIO2，硬件功能为 CAM_SWITCH（CH443L/CH444P 双摄像头切换）
//   5. 气压计 U12=SPA06-003（I2C1），按 DPS310 驱动探测
//   6. SPI3 上 Flash(U2 PY25Q128HA) 与 TF 卡座(U11) 共总线共 CS(PA15)，二选一贴装；
//      本配置为 TF 卡版，Flash 版见 ABCD_PY25Q
// H7 的 DMA/ADC 选项参考 PR_RATEH743 / SAKURAH743 等 H743 目标惯例。
#define FC_TARGET_MCU     STM32H743

#define BOARD_NAME        ABCD
#define MANUFACTURER_ID   ABCD

#define USE_ACC
#define USE_ACC_SPI_ICM42688P
#define USE_ACC_SPI_LSM6DSV16X
#define USE_GYRO
#define USE_GYRO_SPI_ICM42688P
#define USE_GYRO_SPI_LSM6DSV16X
#define USE_ACCGYRO_LSM6DSV16X
// LSM6DSK320X：低量程通道 ±16g / ±2000dps，不启用 ±320g 高G通道
#define USE_ACCGYRO_LSM6DSK320X
#define USE_ACCGYRO_IIM42652
#define USE_ACCGYRO_ICM40608

#define USE_SDCARD
#define USE_SDCARD_SPI
#define USE_BARO
#define USE_BARO_BMP280
#define USE_BARO_DPS310
#define USE_MAG
#define USE_GPS
#define USE_LED_STRIP
#define USE_MAX7456

#define BEEPER_PIN        PA4
#define BEEPER_INVERTED

// Motors — DSHOT bitbang TIM1（网表 M1–M8 → U3，与 V1.8 一致）
#define MOTOR1_PIN        PC8
#define MOTOR2_PIN        PC9
#define MOTOR3_PIN        PA9
#define MOTOR4_PIN        PA10
#define MOTOR5_PIN        PB14
#define MOTOR6_PIN        PB15
#define MOTOR7_PIN        PA8
#define MOTOR8_PIN        PB0

#define SERVO1_PIN        PA6
#define SERVO2_PIN        PB1 // H743（U3/U31）焊盘：按与 F405 一致的 SERVO2；F722 目标见 PR_F722-BT_v1.8（PB2）

#define RX_PPM_PIN        PA3
#define LED_STRIP_PIN     PA7

#define UART1_TX_PIN      PB6
#define UART1_RX_PIN      PB7
#define UART2_TX_PIN      PA2
#define UART2_RX_PIN      PA3
#define UART3_TX_PIN      PC10
#define UART3_RX_PIN      PC11
#define UART4_TX_PIN      PA0
#define UART4_RX_PIN      PA1
#define UART5_TX_PIN      PC12
#define UART5_RX_PIN      PD2
// V1.9：PC6 改作 CAMERA_CONTROL（CC_MCU→CC_OUT），UART6 仅 RX（PC7=R6 焊盘）
#define UART6_RX_PIN      PC7

// V1.9 新增：摄像头 OSD 菜单控制（网表 CC_MCU，经 R109 → CC_OUT → CN15.4）
#define CAMERA_CONTROL_PIN PC6

#define USE_I2C_PULLUP
#define I2C1_SCL_PIN      PB8
#define I2C1_SDA_PIN      PB9

#define LED0_PIN          PC5

// SPI2 — 模拟 OSD：AT7456E（U6）实物 或 CH32V203（U25）模拟 OSD，二选一贴装，
// 共用 SPI2 总线与 OSDCS(PB11)，固件统一走 MAX7456 协议驱动，无需区分。
// SCLK=PB13, SDIN=PC3(MOSI), SDOUT=PC2(MISO)
// （LQFP100 上 PC2/PC3 常为 PC2_C/PC3_C，默认模拟开关闭合）
#define SPI2_SCK_PIN      PB13
#define SPI2_SDI_PIN      PC2
#define SPI2_SDO_PIN      PC3

// SPI3 — TF 卡座（U11，与 Flash U2 共总线共 CS，二选一贴装）
#define SPI3_SCK_PIN      PB3
#define SPI3_SDI_PIN      PB4
#define SPI3_SDO_PIN      PB5

// SPI4 — Gyro ICM-42688-P（U1，V1.9 由 SPI2 改挂 SPI4）
#define SPI4_SCK_PIN      PE2
#define SPI4_SDI_PIN      PE5
#define SPI4_SDO_PIN      PE6

#define ADC_VBAT_PIN      PC1
#define ADC_CURR_PIN      PC0

#define SDCARD_SPI_CS_PIN  PA15
#define SDCARD_SPI_INSTANCE SPI3

#define GYRO_1_CS_PIN     PA5
#define GYRO_1_EXTI_PIN   PB12
#define GYRO_1_SPI_INSTANCE SPI4
#define GYRO_1_ALIGN      CW0_DEG

// IMUCLK: U1.9→U3.46(=PB10)，与 V1.8 一致
#define USE_GYRO_CLKIN
#define GYRO_1_CLKIN_PIN  PB10

#define MAX7456_SPI_CS_PIN    PB11
#define MAX7456_SPI_INSTANCE  SPI2

#define PINIO1_PIN        PC4
#define PINIO1_BOX        40
#define PINIO2_PIN        PC13 // V1.9 硬件功能为 CAM_SWITCH（双摄像头切换）
#define PINIO2_BOX        41

#define DEFAULT_DSHOT_BITBANG DSHOT_BITBANG_ON
#define DSHOT_BITBANGED_TIMER_DEFAULT DSHOT_BITBANGED_TIMER_TIM1

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP(0, PA3, 2, -1) \
    TIMER_PIN_MAP(1, PA7, 2,  0) \
    TIMER_PIN_MAP(2, PA6, 2, -1) \
    TIMER_PIN_MAP(3, PB1, 3, -1)

// H743：参考 PR_RATEH743 / SAKURAH743 的 ADC DMA 分配（DMAMUX）
#define ADC1_DMA_OPT      8
#define ADC3_DMA_OPT      9

#define DEFAULT_BLACKBOX_DEVICE      BLACKBOX_DEVICE_SDCARD
#define DEFAULT_MOTOR_DSHOT_SPEED    PWM_TYPE_DSHOT300
#define DEFAULT_DSHOT_BURST          DSHOT_DMAR_OFF
#define DEFAULT_CURRENT_METER_SOURCE CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC
#define DEFAULT_VOLTAGE_METER_SCALE  232
#define DEFAULT_CURRENT_METER_SCALE  250

#define SYSTEM_HSE_MHZ       8
#define OSD_CANVAS_SIZE_DEBUG

#define BARO_I2C_INSTANCE  (I2CDEV_1)
#define MAG_I2C_INSTANCE   (I2CDEV_1)

#define MSP_DISPLAYPORT_UART SERIAL_PORT_UART4
#define SERIALRX_UART        SERIAL_PORT_USART2
#define SERIALRX_PROVIDER    SERIALRX_CRSF
#define MSP_UART             SERIAL_PORT_USART1

#define ESCSERIAL_PIN        PC7
