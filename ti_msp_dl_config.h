/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define GPIO_LFXT_PORT                                                     GPIOA
#define GPIO_LFXIN_PIN                                             DL_GPIO_PIN_3
#define GPIO_LFXIN_IOMUX                                          (IOMUX_PINCM8)
#define GPIO_LFXOUT_PIN                                            DL_GPIO_PIN_4
#define GPIO_LFXOUT_IOMUX                                         (IOMUX_PINCM9)
#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMA0
#define PWM_0_INST_IRQHandler                                   TIMA0_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMA0_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                              2000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOA
#define GPIO_PWM_0_C0_PIN                                          DL_GPIO_PIN_8
#define GPIO_PWM_0_C0_IOMUX                                      (IOMUX_PINCM19)
#define GPIO_PWM_0_C0_IOMUX_FUNC                     IOMUX_PINCM19_PF_TIMA0_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_0_C1_PORT                                                 GPIOA
#define GPIO_PWM_0_C1_PIN                                          DL_GPIO_PIN_9
#define GPIO_PWM_0_C1_IOMUX                                      (IOMUX_PINCM20)
#define GPIO_PWM_0_C1_IOMUX_FUNC                     IOMUX_PINCM20_PF_TIMA0_CCP1
#define GPIO_PWM_0_C1_IDX                                    DL_TIMER_CC_1_INDEX

/* Defines for PWM_C */
#define PWM_C_INST                                                         TIMG7
#define PWM_C_INST_IRQHandler                                   TIMG7_IRQHandler
#define PWM_C_INST_INT_IRQN                                     (TIMG7_INT_IRQn)
#define PWM_C_INST_CLK_FREQ                                               100000
/* GPIO defines for channel 1 */
#define GPIO_PWM_C_C1_PORT                                                 GPIOA
#define GPIO_PWM_C_C1_PIN                                          DL_GPIO_PIN_7
#define GPIO_PWM_C_C1_IOMUX                                      (IOMUX_PINCM14)
#define GPIO_PWM_C_C1_IOMUX_FUNC                     IOMUX_PINCM14_PF_TIMG7_CCP1
#define GPIO_PWM_C_C1_IDX                                    DL_TIMER_CC_1_INDEX

/* Defines for PWM_D */
#define PWM_D_INST                                                         TIMG0
#define PWM_D_INST_IRQHandler                                   TIMG0_IRQHandler
#define PWM_D_INST_INT_IRQN                                     (TIMG0_INT_IRQn)
#define PWM_D_INST_CLK_FREQ                                               100000
/* GPIO defines for channel 0 */
#define GPIO_PWM_D_C0_PORT                                                 GPIOA
#define GPIO_PWM_D_C0_PIN                                         DL_GPIO_PIN_12
#define GPIO_PWM_D_C0_IOMUX                                      (IOMUX_PINCM34)
#define GPIO_PWM_D_C0_IOMUX_FUNC                     IOMUX_PINCM34_PF_TIMG0_CCP0
#define GPIO_PWM_D_C0_IDX                                    DL_TIMER_CC_0_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG8)
#define TIMER_0_INST_IRQHandler                                 TIMG8_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG8_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                          (2999U)
/* Defines for TIMER_1 */
#define TIMER_1_INST                                                     (TIMG6)
#define TIMER_1_INST_IRQHandler                                 TIMG6_IRQHandler
#define TIMER_1_INST_INT_IRQN                                   (TIMG6_INT_IRQn)
#define TIMER_1_INST_LOAD_VALUE                                          (3999U)
/* Defines for TIMER_2 */
#define TIMER_2_INST                                                     (TIMA1)
#define TIMER_2_INST_IRQHandler                                 TIMA1_IRQHandler
#define TIMER_2_INST_INT_IRQN                                   (TIMA1_INT_IRQn)
#define TIMER_2_INST_LOAD_VALUE                                           (499U)




/* Defines for I2C_MPU6050 */
#define I2C_MPU6050_INST                                                    I2C0
#define I2C_MPU6050_INST_IRQHandler                              I2C0_IRQHandler
#define I2C_MPU6050_INST_INT_IRQN                                  I2C0_INT_IRQn
#define I2C_MPU6050_BUS_SPEED_HZ                                          400000
#define GPIO_I2C_MPU6050_SDA_PORT                                          GPIOA
#define GPIO_I2C_MPU6050_SDA_PIN                                   DL_GPIO_PIN_0
#define GPIO_I2C_MPU6050_IOMUX_SDA                                (IOMUX_PINCM1)
#define GPIO_I2C_MPU6050_IOMUX_SDA_FUNC                 IOMUX_PINCM1_PF_I2C0_SDA
#define GPIO_I2C_MPU6050_SCL_PORT                                          GPIOA
#define GPIO_I2C_MPU6050_SCL_PIN                                   DL_GPIO_PIN_1
#define GPIO_I2C_MPU6050_IOMUX_SCL                                (IOMUX_PINCM2)
#define GPIO_I2C_MPU6050_IOMUX_SCL_FUNC                 IOMUX_PINCM2_PF_I2C0_SCL

/* Defines for I2C_1_OLED */
#define I2C_1_OLED_INST                                                     I2C1
#define I2C_1_OLED_INST_IRQHandler                               I2C1_IRQHandler
#define I2C_1_OLED_INST_INT_IRQN                                   I2C1_INT_IRQn
#define I2C_1_OLED_BUS_SPEED_HZ                                           400000
#define GPIO_I2C_1_OLED_SDA_PORT                                           GPIOA
#define GPIO_I2C_1_OLED_SDA_PIN                                   DL_GPIO_PIN_16
#define GPIO_I2C_1_OLED_IOMUX_SDA                                (IOMUX_PINCM38)
#define GPIO_I2C_1_OLED_IOMUX_SDA_FUNC                 IOMUX_PINCM38_PF_I2C1_SDA
#define GPIO_I2C_1_OLED_SCL_PORT                                           GPIOA
#define GPIO_I2C_1_OLED_SCL_PIN                                   DL_GPIO_PIN_15
#define GPIO_I2C_1_OLED_IOMUX_SCL                                (IOMUX_PINCM37)
#define GPIO_I2C_1_OLED_IOMUX_SCL_FUNC                 IOMUX_PINCM37_PF_I2C1_SCL


/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                           40000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_40_MHZ_115200_BAUD                                      (21)
#define UART_0_FBRD_40_MHZ_115200_BAUD                                      (45)




/* Defines for SPI_0 */
#define SPI_0_INST                                                         SPI1
#define SPI_0_INST_IRQHandler                                   SPI1_IRQHandler
#define SPI_0_INST_INT_IRQN                                       SPI1_INT_IRQn
#define GPIO_SPI_0_PICO_PORT                                              GPIOB
#define GPIO_SPI_0_PICO_PIN                                      DL_GPIO_PIN_15
#define GPIO_SPI_0_IOMUX_PICO                                   (IOMUX_PINCM32)
#define GPIO_SPI_0_IOMUX_PICO_FUNC                   IOMUX_PINCM32_PF_SPI1_PICO
#define GPIO_SPI_0_POCI_PORT                                              GPIOB
#define GPIO_SPI_0_POCI_PIN                                      DL_GPIO_PIN_14
#define GPIO_SPI_0_IOMUX_POCI                                   (IOMUX_PINCM31)
#define GPIO_SPI_0_IOMUX_POCI_FUNC                   IOMUX_PINCM31_PF_SPI1_POCI
/* GPIO configuration for SPI_0 */
#define GPIO_SPI_0_SCLK_PORT                                              GPIOB
#define GPIO_SPI_0_SCLK_PIN                                      DL_GPIO_PIN_16
#define GPIO_SPI_0_IOMUX_SCLK                                   (IOMUX_PINCM33)
#define GPIO_SPI_0_IOMUX_SCLK_FUNC                   IOMUX_PINCM33_PF_SPI1_SCLK



/* Defines for ADC_12_0_GRY */
#define ADC_12_0_GRY_INST                                                   ADC0
#define ADC_12_0_GRY_INST_IRQHandler                             ADC0_IRQHandler
#define ADC_12_0_GRY_INST_INT_IRQN                               (ADC0_INT_IRQn)
#define ADC_12_0_GRY_ADCMEM_0                                 DL_ADC12_MEM_IDX_0
#define ADC_12_0_GRY_ADCMEM_0_REF                DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC_12_0_GRY_ADCMEM_0_REF_VOLTAGE_V                                     3.3
#define GPIO_ADC_12_0_GRY_C0_PORT                                          GPIOA
#define GPIO_ADC_12_0_GRY_C0_PIN                                  DL_GPIO_PIN_27



/* Port definition for Pin Group GPIO_MPU6050 */
#define GPIO_MPU6050_PORT                                                (GPIOA)

/* Defines for PIN_MPU6050_INT: GPIOA.31 with pinCMx 6 on package pin 5 */
// groups represented: ["camera","ENCODER_READ_GRP","EC11_READ","GPIO_MPU6050"]
// pins affected: ["camera_ok","READ_A_PIN","READ_B_PIN","PIN_2","PIN_MPU6050_INT"]
#define GPIO_MULTIPLE_GPIOA_INT_IRQN                            (GPIOA_INT_IRQn)
#define GPIO_MULTIPLE_GPIOA_INT_IIDX            (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define GPIO_MPU6050_PIN_MPU6050_INT_IIDX                   (DL_GPIO_IIDX_DIO31)
#define GPIO_MPU6050_PIN_MPU6050_INT_PIN                        (DL_GPIO_PIN_31)
#define GPIO_MPU6050_PIN_MPU6050_INT_IOMUX                        (IOMUX_PINCM6)
/* Port definition for Pin Group W25Q32_CS */
#define W25Q32_CS_PORT                                                   (GPIOB)

/* Defines for PIN_0: GPIOB.17 with pinCMx 43 on package pin 36 */
#define W25Q32_CS_PIN_0_PIN                                     (DL_GPIO_PIN_17)
#define W25Q32_CS_PIN_0_IOMUX                                    (IOMUX_PINCM43)
/* Port definition for Pin Group car */
#define car_PORT                                                         (GPIOA)

/* Defines for car_turn_pin: GPIOA.21 with pinCMx 46 on package pin 39 */
#define car_car_turn_pin_PIN                                    (DL_GPIO_PIN_21)
#define car_car_turn_pin_IOMUX                                   (IOMUX_PINCM46)
/* Port definition for Pin Group camera */
#define camera_PORT                                                      (GPIOA)

/* Defines for camera_ok: GPIOA.22 with pinCMx 47 on package pin 40 */
#define camera_camera_ok_IIDX                               (DL_GPIO_IIDX_DIO22)
#define camera_camera_ok_PIN                                    (DL_GPIO_PIN_22)
#define camera_camera_ok_IOMUX                                   (IOMUX_PINCM47)
/* Defines for READ_A_INT: GPIOB.2 with pinCMx 15 on package pin 14 */
#define ENCODER_READ_GRP_READ_A_INT_PORT                                 (GPIOB)
// pins affected by this interrupt request:["READ_A_INT","READ_B_INT"]
#define ENCODER_READ_GRP_GPIOB_INT_IRQN                         (GPIOB_INT_IRQn)
#define ENCODER_READ_GRP_GPIOB_INT_IIDX         (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define ENCODER_READ_GRP_READ_A_INT_IIDX                     (DL_GPIO_IIDX_DIO2)
#define ENCODER_READ_GRP_READ_A_INT_PIN                          (DL_GPIO_PIN_2)
#define ENCODER_READ_GRP_READ_A_INT_IOMUX                        (IOMUX_PINCM15)
/* Defines for READ_B_INT: GPIOB.3 with pinCMx 16 on package pin 15 */
#define ENCODER_READ_GRP_READ_B_INT_PORT                                 (GPIOB)
#define ENCODER_READ_GRP_READ_B_INT_IIDX                     (DL_GPIO_IIDX_DIO3)
#define ENCODER_READ_GRP_READ_B_INT_PIN                          (DL_GPIO_PIN_3)
#define ENCODER_READ_GRP_READ_B_INT_IOMUX                        (IOMUX_PINCM16)
/* Defines for READ_A_PIN: GPIOA.28 with pinCMx 3 on package pin 3 */
#define ENCODER_READ_GRP_READ_A_PIN_PORT                                 (GPIOA)
#define ENCODER_READ_GRP_READ_A_PIN_IIDX                    (DL_GPIO_IIDX_DIO28)
#define ENCODER_READ_GRP_READ_A_PIN_PIN                         (DL_GPIO_PIN_28)
#define ENCODER_READ_GRP_READ_A_PIN_IOMUX                         (IOMUX_PINCM3)
/* Defines for READ_B_PIN: GPIOA.24 with pinCMx 54 on package pin 44 */
#define ENCODER_READ_GRP_READ_B_PIN_PORT                                 (GPIOA)
#define ENCODER_READ_GRP_READ_B_PIN_IIDX                    (DL_GPIO_IIDX_DIO24)
#define ENCODER_READ_GRP_READ_B_PIN_PIN                         (DL_GPIO_PIN_24)
#define ENCODER_READ_GRP_READ_B_PIN_IOMUX                        (IOMUX_PINCM54)
/* Port definition for Pin Group TB6612_CONTROL_GRP */
#define TB6612_CONTROL_GRP_PORT                                          (GPIOB)

/* Defines for AIN1: GPIOB.6 with pinCMx 23 on package pin 20 */
#define TB6612_CONTROL_GRP_AIN1_PIN                              (DL_GPIO_PIN_6)
#define TB6612_CONTROL_GRP_AIN1_IOMUX                            (IOMUX_PINCM23)
/* Defines for AIN2: GPIOB.7 with pinCMx 24 on package pin 21 */
#define TB6612_CONTROL_GRP_AIN2_PIN                              (DL_GPIO_PIN_7)
#define TB6612_CONTROL_GRP_AIN2_IOMUX                            (IOMUX_PINCM24)
/* Defines for BIN1: GPIOB.8 with pinCMx 25 on package pin 22 */
#define TB6612_CONTROL_GRP_BIN1_PIN                              (DL_GPIO_PIN_8)
#define TB6612_CONTROL_GRP_BIN1_IOMUX                            (IOMUX_PINCM25)
/* Defines for BIN2: GPIOB.9 with pinCMx 26 on package pin 23 */
#define TB6612_CONTROL_GRP_BIN2_PIN                              (DL_GPIO_PIN_9)
#define TB6612_CONTROL_GRP_BIN2_IOMUX                            (IOMUX_PINCM26)
/* Port definition for Pin Group GRY_READ_GRP */
#define GRY_READ_GRP_PORT                                                (GPIOB)

/* Defines for ADDR_0: GPIOB.18 with pinCMx 44 on package pin 37 */
#define GRY_READ_GRP_ADDR_0_PIN                                 (DL_GPIO_PIN_18)
#define GRY_READ_GRP_ADDR_0_IOMUX                                (IOMUX_PINCM44)
/* Defines for ADDR_1: GPIOB.19 with pinCMx 45 on package pin 38 */
#define GRY_READ_GRP_ADDR_1_PIN                                 (DL_GPIO_PIN_19)
#define GRY_READ_GRP_ADDR_1_IOMUX                                (IOMUX_PINCM45)
/* Defines for ADDR_2: GPIOB.20 with pinCMx 48 on package pin 41 */
#define GRY_READ_GRP_ADDR_2_PIN                                 (DL_GPIO_PIN_20)
#define GRY_READ_GRP_ADDR_2_IOMUX                                (IOMUX_PINCM48)
/* Port definition for Pin Group KEYS */
#define KEYS_PORT                                                        (GPIOA)

/* Defines for KEY0: GPIOA.26 with pinCMx 59 on package pin 46 */
#define KEYS_KEY0_PIN                                           (DL_GPIO_PIN_26)
#define KEYS_KEY0_IOMUX                                          (IOMUX_PINCM59)
/* Defines for KEY1: GPIOA.25 with pinCMx 55 on package pin 45 */
#define KEYS_KEY1_PIN                                           (DL_GPIO_PIN_25)
#define KEYS_KEY1_IOMUX                                          (IOMUX_PINCM55)
/* Port definition for Pin Group EC11_READ */
#define EC11_READ_PORT                                                   (GPIOA)

/* Defines for PIN_1: GPIOA.2 with pinCMx 7 on package pin 8 */
#define EC11_READ_PIN_1_PIN                                      (DL_GPIO_PIN_2)
#define EC11_READ_PIN_1_IOMUX                                     (IOMUX_PINCM7)
/* Defines for PIN_2: GPIOA.23 with pinCMx 53 on package pin 43 */
#define EC11_READ_PIN_2_IIDX                                (DL_GPIO_IIDX_DIO23)
#define EC11_READ_PIN_2_PIN                                     (DL_GPIO_PIN_23)
#define EC11_READ_PIN_2_IOMUX                                    (IOMUX_PINCM53)
/* Defines for EN1: GPIOB.24 with pinCMx 52 on package pin 42 */
#define STEP_MOTOR_EN1_PORT                                              (GPIOB)
#define STEP_MOTOR_EN1_PIN                                      (DL_GPIO_PIN_24)
#define STEP_MOTOR_EN1_IOMUX                                     (IOMUX_PINCM52)
/* Defines for EN2: GPIOA.17 with pinCMx 39 on package pin 32 */
#define STEP_MOTOR_EN2_PORT                                              (GPIOA)
#define STEP_MOTOR_EN2_PIN                                      (DL_GPIO_PIN_17)
#define STEP_MOTOR_EN2_IOMUX                                     (IOMUX_PINCM39)
/* Defines for DIR1: GPIOA.14 with pinCMx 36 on package pin 29 */
#define STEP_MOTOR_DIR1_PORT                                             (GPIOA)
#define STEP_MOTOR_DIR1_PIN                                     (DL_GPIO_PIN_14)
#define STEP_MOTOR_DIR1_IOMUX                                    (IOMUX_PINCM36)
/* Defines for DIR2: GPIOA.13 with pinCMx 35 on package pin 28 */
#define STEP_MOTOR_DIR2_PORT                                             (GPIOA)
#define STEP_MOTOR_DIR2_PIN                                     (DL_GPIO_PIN_13)
#define STEP_MOTOR_DIR2_IOMUX                                    (IOMUX_PINCM35)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_PWM_C_init(void);
void SYSCFG_DL_PWM_D_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_TIMER_1_init(void);
void SYSCFG_DL_TIMER_2_init(void);
void SYSCFG_DL_I2C_MPU6050_init(void);
void SYSCFG_DL_I2C_1_OLED_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_SPI_0_init(void);
void SYSCFG_DL_ADC_12_0_GRY_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
