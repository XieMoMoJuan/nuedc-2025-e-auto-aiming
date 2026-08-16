/*
 * Copyright (c) 2021, Texas Instruments Incorporated
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

#include "ti_msp_dl_config.h"
#include "OLED.h"
#include "stdlib.h"
#include "ec11.h"
#include "key.h"
#include "stdio.h"
#include "bsp_siic.h"
#include "bsp_systick.h"
#include "interrupt.h"
#include "motor.h"
#include "No_Mcu_Ganv_Grayscale_Sensor_Config.h"
#include "step_motor.h"

extern volatile int32_t target_dis; // 位置环目标
extern volatile int32_t target_yaw; // 转向换目标

// extern volatile int32_t speed; //速度环测试
// extern float except_w; //角速度环测试

extern uint8_t u2_rx_packet[6];

uint8_t mode = 0;

extern volatile uint8_t interrupt_task_start; // 定时器中断任务开始标志位

// oled选择
uint8_t oled_select = 0;
static uint8_t first_flag = 0;

int main(void)
{
    // pid初始化
    PID_Init(&pid_left, 30.0f, 1.0f, 0, 800, 700);
    PID_Init(&pid_right, 30.0f, 1.0f, 0, 800, 700);
    PID_Init(&pid_position, 0.1f, 0, 0.02f, 20, 0);
    PID_Init(&pid_yaw, 2, 0, 0.75f, 150, 0);
    PID_Init(&pid_w_speed, 0.1f, 0.005f, 0, 10, 10);
    // 系统初始化
    SYSCFG_DL_init();

    // oled初始化
    OLED_Init();

    // 初始化灰度，设定阈值
    No_MCU_Ganv_Sensor_Init_Frist(&sensor);
    set_gray();
    No_MCU_Ganv_Sensor_Init(&sensor);

    // iic，mpu6050及dmp初始化
    pIICInterface_t siic = &User_sIICDev;
    siic->init();
    MPU6050_initialize();
    DMP_Init();

    // 开启中断，开始中断中的事务处理
    NVIC_EnableIRQ(SysTick_IRQn);
    NVIC_EnableIRQ(UART0_INT_IRQn);
    NVIC_EnableIRQ(ENCODER_READ_GRP_GPIOB_INT_IRQN);
    DL_Timer_startCounter(TIMER_0_INST);
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_Timer_startCounter(TIMER_1_INST);
    NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);
    DL_Timer_startCounter(PWM_0_INST);
    NVIC_EnableIRQ(GPIO_MULTIPLE_GPIOA_INT_IRQN);
    DL_Timer_startCounter(TIMER_2_INST);
    NVIC_EnableIRQ(TIMER_2_INST_INT_IRQN);

    // 等待6050校准
    OLED_ShowString(0, 0, "CALIBRATION", OLED_8X16);
    OLED_ShowString(0, 20, "RPESS KYE0", OLED_8X16);
    OLED_Update();
    while (DL_GPIO_readPins(KEYS_PORT, KEYS_KEY0_PIN) != KEYS_KEY0_PIN)
    {
        uint8_t temp_buf[] = {0};
        OLED_Printf(0, 40, OLED_6X8, "YAW:%2.1f", mpu6050.yaw);
        OLED_UpdateArea(0, 40, 54, 8);
    }
    OLED_Clear();

    delay_ms(500);
    // 开始15ms定时器内任务
    interrupt_task_start = 1;

    OLED_ShowString(0, 0, "Normal 1", OLED_6X8);
    OLED_ShowString(0, 0 + 11, "Normal 2", OLED_6X8);
    OLED_ShowString(0, 0 + 11 + 11, "Normal 3", OLED_6X8);
    OLED_ShowString(0, 0 + 11 + 11 + 11, "Extend 1", OLED_6X8);
    OLED_ShowString(0, 0 + 11 + 11 + 11 + 11, "Extend 2", OLED_6X8);
    OLED_ShowString(0, 0 + 11 + 11 + 11 + 11 + 11, "Extend 3", OLED_6X8);

    while (1)
    {

        // 速度pid调值
        // printf("%d,%f,%f,%d,%f,%f,%f,%f\r\n",speed, pid_left.Kp, pid_left.Ki, DL_Timer_getCaptureCompareValue(PWM_0_INST, DL_TIMER_CC_0_INDEX), pid_left.DError, pid_left.Error,pid_left.Output, my_count.err_left);
        // 位置pid调值
        // printf("%d,%f,%f,%f,%f,%f,%f\r\n",target_dis*2, pid_position.Kp, pid_position.Kd, pid_position.DError, pid_position.Error,pid_position.Output, my_count.sum_left);
        // 位置pid调值
        // printf("%d,%f,%f,%f,%f,%f,%f,%f\r\n", target_yaw, pid_yaw.Kp, pid_yaw.Kd, pid_yaw.DError, pid_yaw.Error, pid_yaw.Output, mpu6050.yaw, yaw_error());
        // 角速度环
        // printf("%f,%f,%f,%f,%f,%f,%f\r\n", except_w, pid_w_speed.Kp, pid_w_speed.Ki, pid_w_speed.DError, pid_w_speed.Error, pid_w_speed.Output, mpu6050.gyro.z);

        // 步进电机位置环
        // printf("%f,%f,%f,%f,%f,%f,%d\r\n", 0.0f, pid_step_x.Kp, pid_step_x.Ki, pid_step_x.DError, pid_step_x.Error, pid_step_x.Output, pixel_x_err);

        if (task_oled_flag == 1)
        {

            if (mode == 0)
            {
                // spped_left += get_ec11_err() * 20;
                // set_speed_left(spped_left);

                // pid_left.Kp += (float)get_ec11_err();
                //  PID_Set(&pid_left, pid_left.Kp, pid_left.Ki, pid_left.Kd, 800, 800);

                // pid_position.Kp += (float)get_ec11_err() * 0.001f;
                //(&pid_position, pid_position.Kp, pid_position.Ki, pid_position.Kd, 30, 0);

                // pid_yaw.Kp += (float)get_ec11_err() * 0.02f;

                // pid_yaw.Kp += (float)get_ec11_err() * 0.1f;
                // PID_Set(&pid_yaw, pid_yaw.Kp, pid_yaw.Ki, pid_yaw.Kd, 150, 80);

                //                pid_step_x.Kp += (float)get_ec11_err() * 0.01f;
                //                PID_Set(&pid_step_x, pid_step_x.Kp, pid_step_x.Ki, pid_step_x.Kd, 3200, 1600);
            }
            else if (mode == 1)
            {
                // spped_right += get_ec11_err() * 20;
                // set_speed_right(spped_left);
                //  pid_left.Ki += (float)get_ec11_err() * 0.2f;
                // PID_Set(&pid_left, pid_left.Kp, pid_left.Ki, pid_left.Kd, 1000, 1000);

                // pid_position.Kd += (float)get_ec11_err() * 0.001f;
                // PID_Set(&pid_position, pid_position.Kp, pid_position.Ki, pid_position.Kd, 30, 0);

                // pid_yaw.Kd += (float)get_ec11_err() * 0.02f;
                // PID_Set(&pid_yaw, pid_yaw.Kp, pid_yaw.Ki, pid_yaw.Kd, 10, 0);

                // pid_yaw.Kd += (float)get_ec11_err() * 0.1f;
                // PID_Set(&pid_yaw, pid_yaw.Kp, pid_yaw.Ki, pid_yaw.Kd, 150, 80);
                //                pid_step_x.Ki += (float)get_ec11_err() * 0.01f;
                //                PID_Set(&pid_step_x, pid_step_x.Kp, pid_step_x.Ki, pid_step_x.Kd, 3200, 1600);
            }
            else if (mode == 2)
            {
                // speed += get_ec11_err();
            }
            else if (mode == 3)
            {
                // pid_left.Kd += (float)get_ec11_err() * 0.1f;
                // PID_Set(&pid_left, pid_left.Kp, pid_left.Ki, pid_left.Kd, 700, 700);
            }
            OLED_ShowBinNum(54, 11, sensor.Digtal, 8, OLED_6X8);
            uint8_t angle_flag = 0;
            OLED_ShowSignedNum(54, 11 + 11, set_offset(sensor.Digtal, &angle_flag), 8, OLED_6X8);
            OLED_ShowSignedNum(54, 11 + 11 + 11, angle_flag, 1, OLED_6X8);
            OLED_Update();

            task_oled_flag = 0;
        }
        if (task_key_flag == 1)
        {

            switch (scanKeys())
            {
            case KEY0:
                mode = 0;

                switch (oled_select % 6)
                {
                case 0:
                    interrupt_task_number = 6;
                    break;
                case 1:
                    target_speed = 24;
                    interrupt_task_number = 1;
                    break;
                case 2:

                    interrupt_task_number = 2;
                    break;
                case 3:

                    interrupt_task_number = 3;
                    break;
                case 4:
                    target_speed = 24;
                    interrupt_task_number = 4;
                    break;
                case 5:
                    target_speed = 24;
                    interrupt_task_number = 5;
                    break;
                default:
                    interrupt_task_number = 0;
                    break;
                }

                // set_trun(90, &my_count, &pid_position, &pid_left, &pid_right, &pid_yaw);
                OLED_ShowString(127 - 6 * OLED_6X8, 0 + 9 + 9 + 9 + 3, "Key0:S", OLED_6X8);
                break;
            case KEY1:
                // except_w = -60;

                switch (oled_select++ % 6)
                {
                case 0:
                    if (first_flag == 1)
                        OLED_ReverseArea(0, 0 + 11 + 11 + 11 + 11 + 11, 48, 8);
                    else
                        first_flag = 1;
                    OLED_ReverseArea(0, 0, 48, 8);
                    break;
                case 1:
                    OLED_ReverseArea(0, 0, 48, 8);
                    OLED_ReverseArea(0, 0 + 11, 48, 8);
                    break;
                case 2:
                    OLED_ReverseArea(0, 0 + 11, 48, 8);
                    OLED_ReverseArea(0, 0 + 11 + 11, 48, 8);
                    break;
                case 3:
                    OLED_ReverseArea(0, 0 + 11 + 11, 48, 8);
                    OLED_ReverseArea(0, 0 + 11 + 11 + 11, 48, 8);
                    break;
                case 4:
                    OLED_ReverseArea(0, 0 + 11 + 11 + 11, 48, 8);
                    OLED_ReverseArea(0, 0 + 11 + 11 + 11 + 11, 48, 8);
                    break;
                case 5:
                    OLED_ReverseArea(0, 0 + 11 + 11 + 11 + 11, 48, 8);
                    OLED_ReverseArea(0, 0 + 11 + 11 + 11 + 11 + 11, 48, 8);
                    break;
                }

                mode = 2;
                // encoder_delete_sum(&my_count);
                // set_target(1000, &my_count, &pid_position, &pid_left, &pid_right);
                // set_trun(-60, &my_count, &pid_position, &pid_left, &pid_right, &pid_yaw);

                OLED_ShowString(127 - 6 * OLED_6X8, 0 + 9 + 9 + 9 + 3 + 9, "Key1:S", OLED_6X8);
                break;
            case KEY0_LONG:
                mode = 1;

                OLED_ShowString(127 - 6 * OLED_6X8, 0 + 9 + 9 + 9 + 3, "Key0:L", OLED_6X8);
                break;
            case KEY1_LONG:
                // except_w = 70;
                //  if(mode == 3){
                //      mode = 4;
                //      set_target(100, &my_count, &pid_position, &pid_left, &pid_right);
                //  }
                //  else {
                //      mode = 3;
                //      set_target(-200, &my_count, &pid_position, &pid_left, &pid_right);
                //  }
                mode = 3;
                // set_trun(-180, &my_count, &pid_position, &pid_left, &pid_right, &pid_yaw);
                // set_trun(180, &my_count, &pid_position, &pid_left, &pid_right, &pid_yaw);

                OLED_ShowString(127 - 6 * OLED_6X8, 0 + 9 + 9 + 9 + 3 + 9, "Key1:L", OLED_6X8);
                break;
            default:
                break;
            }
            task_key_flag = 0;
        }

        if (task_ec11_flag == 1)
        {
            switch (oled_select % 6)
            {
            case 0:

                break;
            case 1:
                task_1_num = abs(get_ec11_now()) % 5 + 1;
                OLED_Printf(54, 0, OLED_6X8, "Num:%.1u", task_1_num);
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            }
            task_ec11_flag = 0;
        }
    }
}
