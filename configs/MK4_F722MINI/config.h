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

// MK4_F722MINI —— STM32F722RET6 (LQFP-64, U11 = GenericF405/F435/F722 焊盘)
// 引脚全部依据嘉立创打开的原理图网表 (工程 time_over/MK4_F722MINI) 逐一核对：
//   陀螺仪  U1  ICM-42688-P   -> SPI2 (SCK PB13 / MISO PC2 / MOSI PC3 / CS PA5 / INT1=EXTI PB12 / INT2=CLKIN PB11)
//   闪存    U2  PY25Q128HA    -> SPI3 (SCK PB3 / MISO PB4 / MOSI PB5 / CS PA15)
//   气压计  U12 SPL06/SPA06   -> I2C1 (SCL PB8 / SDA PB9, CSB 拉高=I2C 模式, 地址 0x76)
//   OSD     U17 CH32V203F8U6  -> UART4 (MCU PA0=TX->CH32, PA1=RX<-CH32)，走串口 MSP DisplayPort，不使用 MAX7456
//   10V BEC 使能               -> PC13 (10V_EN)；作为 PINIO1/USER1 输出，由遥控器模式控制。
//   状态灯  U6  LED           -> LED0  PB0 (低有效)
//   陀螺灯  U7  LED           -> PC4    (低有效，专属陀螺仪指示，见 GYRO_LED_PIN)

#define FC_TARGET_MCU     STM32F7X2

#define BOARD_NAME        MK4_F722MINI
#define MANUFACTURER_ID   ABCD

// ---------------- 传感器 ----------------
#define USE_ACC
#define USE_GYRO
// 需求陀螺仪：ICM42688 / IIM42652 / “ICM42608”。
// 注意：Betaflight 的 icm426xx 驱动没有 “ICM42608” 这个型号，其近名变体是 ICM-40608
//       （与同厂姊妹板 PR_F722-BT 一致），此处按 ICM40608 启用。
#define USE_ACC_SPI_ICM42688P
#define USE_GYRO_SPI_ICM42688P
#define USE_ACCGYRO_IIM42652
#define USE_ACCGYRO_ICM40608

#define USE_FLASH
#define USE_FLASH_PY25Q128HA

#define USE_BARO
// SPA06-003 / SPL06 属于 DPS310 驱动家族（barometer_dps310.c）。
// Betaflight 没有 USE_BARO_SPL06 这个宏；SPA06-003 芯片 ID=0x11，由 DPS310 驱动的 SPL07/SPA06 分支识别。
#define USE_BARO_DPS310

#define USE_MAG
#define USE_GPS
#define USE_LED_STRIP

// ---------------- 电机 / 蜂鸣器 ----------------
#define BEEPER_PIN  PA4
#define MOTOR1_PIN  PC8
#define MOTOR2_PIN  PC9
#define MOTOR3_PIN  PA9
#define MOTOR4_PIN  PA10
#define MOTOR5_PIN  PB14
#define MOTOR6_PIN  PB15
#define MOTOR7_PIN  PA8
#define MOTOR8_PIN  PB1

#define RX_PPM_PIN  PA3

#define LED_STRIP_PIN PA7

// ---------------- 串口 ----------------
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

// ---------------- I2C (气压计 / 磁力计) ----------------
#define USE_I2C_PULLUP
#define I2C1_SCL_PIN PB8
#define I2C1_SDA_PIN PB9

// ---------------- 指示灯 ----------------
#define LED0_PIN PB0            // 网表 LED0 → U11.25 (F722 PB0)
#define GYRO_LED_PIN PC4        // 陀螺仪专属指示灯 (U7)，在 gyroInit() 中点亮，低有效；仅本配置定义，不影响其他 target

// ---------------- 用户 IO ----------------
// PC13 低电平关闭 10V BEC；只有检测到 VBAT > 6.00V 后才拉高开启。
// USER1 可强制关闭，但不能绕过 VBAT 门限开启；USB 单独供电期间保持关闭。
#define USE_PINIO
#define PINIO1_PIN PC13
#define PINIO1_BOX 40
#define PINIO1_CONFIG 129
#define PINIO1_VBAT_ENABLE_THRESHOLD 600

// ---------------- SPI ----------------
#define SPI2_SCK_PIN PB13
#define SPI2_SDI_PIN PC2
#define SPI2_SDO_PIN PC3

#define SPI3_SCK_PIN PB3
#define SPI3_SDI_PIN PB4
#define SPI3_SDO_PIN PB5

#define ESCSERIAL_PIN PC7

// ---------------- ADC ----------------
#define ADC_VBAT_PIN PC1       // ADC1_IN11；R39=10k / R40=1k 分压 (1:10)，模拟输入、无内部上下拉
#define ADC_CURR_PIN PC0       // ADC1_IN10；模拟输入、无内部上下拉

// ---------------- 陀螺仪 / 闪存总线 ----------------
#define GYRO_1_SPI_INSTANCE SPI2
#define GYRO_1_CS_PIN   PA5
#define GYRO_1_EXTI_PIN PB12
#define GYRO_1_ALIGN    CW0_DEG
#define USE_GYRO_CLKIN
#define GYRO_1_CLKIN_PIN PB11   // 网表 IMUCLK → 陀螺仪 INT2/CLKIN

#define FLASH_SPI_INSTANCE SPI3
#define FLASH_CS_PIN PA15

#define MAG_I2C_INSTANCE  (I2CDEV_1)
#define BARO_I2C_INSTANCE (I2CDEV_1)

// ---------------- DShot / 定时器 ----------------
#define DEFAULT_DSHOT_BITBANG DSHOT_BITBANG_ON
#define DSHOT_BITBANGED_TIMER_DEFAULT DSHOT_BITBANGED_TIMER_TIM1

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, PA3,  2, 0) \
    TIMER_PIN_MAP( 1, PA7,  2, 0) \

#define ADC1_DMA_OPT 0

// ---------------- 默认值 ----------------
#define DEFAULT_BLACKBOX_DEVICE       BLACKBOX_DEVICE_FLASH
#define DEFAULT_MOTOR_DSHOT_SPEED     PWM_TYPE_DSHOT300
#define DEFAULT_DSHOT_BURST           DSHOT_DMAR_OFF
#define DEFAULT_CURRENT_METER_SOURCE  CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE  VOLTAGE_METER_ADC
#define DEFAULT_VOLTAGE_METER_SCALE   110   // 10k:1k 分压 (1:10)
#define DEFAULT_CURRENT_METER_SCALE   250

#define BEEPER_INVERTED
#define SYSTEM_HSE_MHZ 8

// ---------------- 串口功能默认分配 ----------------
#define MSP_DISPLAYPORT_UART SERIAL_PORT_UART4   // OSD (CH32V203) 走串口 MSP，不用 MAX7456
#define MSP_UART             SERIAL_PORT_USART1
#define SERIALRX_UART        SERIAL_PORT_USART2
#define SERIALRX_PROVIDER    SERIALRX_CRSF
