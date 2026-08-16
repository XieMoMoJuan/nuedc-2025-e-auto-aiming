#ifndef __INTRRUPT_H_
#define __INTRRUPT_H_
#include "pid.h"
#include "No_Mcu_Ganv_Grayscale_Sensor_Config.h"
#include "encoder.h"
//pid变量
extern Count my_count;
extern PID pid_left;
extern PID pid_right;
extern PID pid_position;
extern PID pid_yaw;
extern PID pid_w_speed;
extern PID pid_step_x;
extern PID pid_step_y;

extern volatile uint8_t task_oled_flag;//while任务标志位
extern volatile uint8_t task_key_flag;//while任务标志位
extern volatile uint8_t task_ec11_flag;//while任务标志位


extern volatile uint8_t dmp_read_frq;//dmp读取频率
extern volatile uint8_t dmp_read_min_frq;//dmp读取最小频率

extern No_MCU_Sensor sensor;//灰度数据

extern volatile int32_t target_speed;
extern volatile uint8_t task_1_num;
/*
mode = 1：快速循迹
mode = 2：描点
mode = 3：找瞄
mode = 4：巡线找瞄，1圈
mode = 5：巡线找瞄，2圈
*/
extern volatile int32_t interrupt_task_number;
#endif