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

// BBH753 (AIRBOT H743)：依据 E:\AI\BB-H7 的 BetaFlight CLI 备份(BTFL_cli_20260624) 和原理图还原。
// 双 ICM42688P：Gyro1=SPI4(PE2/PE5/PE6)、Gyro2=SPI3(PC10/PC11/PC12)；MAX7456 OSD=SPI1；Flash=SPI2。
// 4 路电机(QUADX)：M1/M2 在 TIM3，M3/M4 在 TIM1。
#define FC_TARGET_MCU        STM32H743

#define BOARD_NAME           BBH753
#define MANUFACTURER_ID      AIRB

#define USE_ACC
#define USE_GYRO
// 仅启用实际焊接的 ICM42688P。不要打开 ICM206xx/MPU6500 兼容驱动；
// MPU6500 检测路径会先于 ICM42688P 驱动匹配 WHO_AM_I=0x47，导致用错初始化流程。
#define USE_ACC_SPI_ICM42688P
#define USE_GYRO_SPI_ICM42688P

#define USE_BARO
#define USE_BARO_DPS310
#define USE_BARO_BMP280
#define USE_BARO_MS5611

#define USE_MAG

#define USE_FLASH
#define USE_FLASH_W25Q128FV
#define USE_FLASH_W25N01G

#define USE_MAX7456
#define USE_MS7456
#define USE_GPS
#define USE_LED_STRIP

// Beeper — PD15（CLI: beeper_inversion = ON）
// 无源蜂鸣器：用 PWM 方波驱动，2500Hz 音调（TIM4_CH4 / AF2）
#define BEEPER_PIN           PD15
#define BEEPER_INVERTED
#define BEEPER_PWM_HZ        2500

// Motors（QUADX，4 路）：M1/M2 TIM3，M3/M4 TIM1
#define MOTOR1_PIN           PB0
#define MOTOR2_PIN           PB1
#define MOTOR3_PIN           PE9
#define MOTOR4_PIN           PE11

// PPM 输入焊盘 — PE13（TIM1 CH3）
#define RX_PPM_PIN           PE13

#define LED_STRIP_PIN        PD12

// UART x8
#define UART1_TX_PIN         PA9
#define UART1_RX_PIN         PA10
#define UART2_TX_PIN         PA2
#define UART2_RX_PIN         PA3
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

// I2C2（气压计）+ I2C3
#define I2C2_SCL_PIN         PB10
#define I2C2_SDA_PIN         PB11
#define I2C3_SCL_PIN         PA8
#define I2C3_SDA_PIN         PC9

// 状态指示灯
#define LED0_PIN             PF11

// SPI1 — MAX7456 OSD
#define SPI1_SCK_PIN         PA5
#define SPI1_SDI_PIN         PA6
#define SPI1_SDO_PIN         PA7
// SPI2 — Flash
#define SPI2_SCK_PIN         PB13
#define SPI2_SDI_PIN         PB14
#define SPI2_SDO_PIN         PB15
// SPI3 — Gyro 2 (MISO=SDI, MOSI=SDO)
#define SPI3_SCK_PIN         PC10
#define SPI3_SDI_PIN         PC11
#define SPI3_SDO_PIN         PC12
// SPI4 — Gyro 1 (MISO=SDI, MOSI=SDO)
#define SPI4_SCK_PIN         PE2
#define SPI4_SDI_PIN         PE5
#define SPI4_SDO_PIN         PE6

// ADC — PC2/PC3 在 STM32H743 上仅支持 ADC3，PC0 也可由 ADC3 采样
#define ADC_VBAT_PIN         PC3
#define ADC_CURR_PIN         PC2
#define ADC_EXTERNAL1_PIN    PC0
#define ADC_INSTANCE         ADC3

// OSD — MAX7456 在 SPI1
#define MAX7456_SPI_INSTANCE SPI1
#define MAX7456_SPI_CS_PIN   PA15

// Flash — SPI2
#define FLASH_SPI_INSTANCE   SPI2
#define FLASH_CS_PIN         PB4

// Gyro 1 — SPI4
#define GYRO_1_SPI_INSTANCE  SPI4
#define GYRO_1_CS_PIN        PE4
#define GYRO_1_ALIGN         CW0_DEG
// Gyro 2 — SPI3
#define GYRO_2_SPI_INSTANCE  SPI3
#define GYRO_2_CS_PIN        PB12
#define GYRO_2_ALIGN         CW0_DEG

// === 轮询模式（POLLED）排障版 ===
// 经底层排查：H743 的 SPI DMA 走 DMAMUX，4 条 SPI 都能分到互不冲突的干净流，
// 且 RX 后有 D-Cache 失效处理 —— SPI 总线干扰/DMA 不是元凶。
// 唯一差异变量是 EXTI 数据就绪脚：Gyro1=PC4、Gyro2=PB7，二者都是原理图飞线
// (PB7 NC-->42688_INT, MPU_INT PE8-->PC4)。飞线信号不可靠会导致“转一下卡住、
// 过会儿猛跳”的现象，且 PB7(Gyro2) 比 PC4(Gyro1) 更差，与实测吻合。
// 故暂时不定义 EXTI 脚，强制陀螺仪走定时轮询读取，不依赖飞线。
// 若此版顺滑，则确诊为飞线 EXTI 问题；要恢复中断模式可取消下面两行注释：
// #define GYRO_1_EXTI_PIN      PC4
// #define GYRO_2_EXTI_PIN      PB7

// 定时器映射（序号据 timer_stm32h7xx.c；dmaopt 沿用 CLI 备份的 dma pin 值）
#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, PB0,  2,  0) \
    TIMER_PIN_MAP( 1, PB1,  2,  1) \
    TIMER_PIN_MAP( 2, PE9,  1,  2) \
    TIMER_PIN_MAP( 3, PE11, 1,  3) \
    TIMER_PIN_MAP( 4, PD12, 1,  4) \
    TIMER_PIN_MAP( 5, PE13, 1,  5) \
    TIMER_PIN_MAP( 6, PD15, 1, -1)

#define ADC1_DMA_OPT         8
#define ADC3_DMA_OPT         9
#define TIMUP1_DMA_OPT       0
#define TIMUP3_DMA_OPT       2

#define BARO_I2C_INSTANCE    I2CDEV_2
#define MAG_I2C_INSTANCE     I2CDEV_2

#define DEFAULT_BLACKBOX_DEVICE        BLACKBOX_DEVICE_NONE
#define DEFAULT_GYRO_TO_USE            GYRO_CONFIG_USE_GYRO_BOTH
#define DEFAULT_CURRENT_METER_SOURCE   CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE   VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SCALE    80
#define DEFAULT_VOLTAGE_METER_SCALE    110

#define SERIALRX_PROVIDER    SERIALRX_SBUS
