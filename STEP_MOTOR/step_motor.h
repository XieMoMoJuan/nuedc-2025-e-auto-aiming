#include "ti_msp_dl_config.h"
#include "pid.h"
//设定使能，1为使能，0为失能
#define SET_M1_EN(x) x ? DL_GPIO_setPins(STEP_MOTOR_EN1_PORT, STEP_MOTOR_EN1_PIN) : DL_GPIO_clearPins(STEP_MOTOR_EN1_PORT, STEP_MOTOR_EN1_PIN)
#define SET_M2_EN(x) x ? DL_GPIO_setPins(STEP_MOTOR_EN2_PORT, STEP_MOTOR_EN2_PIN) : DL_GPIO_clearPins(STEP_MOTOR_EN2_PORT, STEP_MOTOR_EN2_PIN)
//设定方向，1为正，0为负
#define SET_M1_DIR(x) x ? DL_GPIO_setPins(STEP_MOTOR_DIR1_PORT, STEP_MOTOR_DIR1_PIN) : DL_GPIO_clearPins(STEP_MOTOR_DIR1_PORT, STEP_MOTOR_DIR1_PIN)
#define SET_M2_DIR(x) x ? DL_GPIO_setPins(STEP_MOTOR_DIR2_PORT, STEP_MOTOR_DIR2_PIN) : DL_GPIO_clearPins(STEP_MOTOR_DIR2_PORT, STEP_MOTOR_DIR2_PIN)
//设置速度频率，可负
void m1_speed_control(int32_t frq);
//设置速度频率，可负
void m2_speed_control(int32_t frq);

void m1_speed_zero(void);

void m2_speed_zero(void);

void m2_pid_control(PID *pid_step_y, int16_t pixel_err);

void m1_pid_control(PID *pid_step_x, int16_t pixel_err);