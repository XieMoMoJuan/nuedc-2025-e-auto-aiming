#include "step_motor.h"
#include "ti_msp_dl_config.h"
#include "stdlib.h"
#include "pid.h"
#include "interrupt.h"

volatile uint32_t pwm_c_pluse_flag = 0;//pwm_c脉冲计数标志位
volatile uint32_t pwm_d_pluse_flag = 0;//pwm_d脉冲计数标志位
volatile uint32_t pwm_c_pluse_cnt = 0;//pwm_c脉冲计数
volatile uint32_t pwm_d_pluse_cnt = 0;//pwm_d脉冲计数
volatile uint32_t pwm_c_pluse_target = 0;//pwm_c脉冲目标数
volatile uint32_t pwm_d_pluse_target = 0;//pwm_d脉冲目标数


//pwm的load_value：1000对应hz10000
//load_v = 100000 / frq
//compare = 1oad_v / 2 * （100 - duty）/ 100；
//duty = 100 - 200*compare / load_v ；
//设置频率，占空比，frq最大10000
void set_m1_frq_duty(uint32_t frq, uint8_t duty)
{
    if(frq > 10000)
        return;
    if(duty > 100 || duty < 0)
        return;
    DL_Timer_stopCounter(PWM_C_INST);
    // uint32_t old_duty = 100 - 200 * DL_Timer_getCaptureCompareValue(PWM_C_INST, DL_TIMER_CC_1_INDEX) / DL_Timer_getLoadValue(PWM_C_INST);
    uint32_t new_load = 100000 / 2 / frq;
    uint32_t new_compare = (new_load * duty) / 100;
    DL_Timer_setLoadValue(PWM_C_INST, new_load);
    DL_Timer_setCaptureCompareValue(PWM_C_INST, new_compare ,DL_TIMER_CC_1_INDEX);
    DL_Timer_startCounter(PWM_C_INST);
}


// pwm的load_value：1000对应hz10000
// load_v = 100000 / frq
// compare = 1oad_v / 2 * （100 - duty）/ 100；
// duty = 100 - 200*compare / load_v ；
// 设置频率，占空比,frq最大10000
void set_m2_frq_duty(uint32_t frq, uint8_t duty)
{
    if(frq > 10000)
        return;
    if(duty > 100 || duty < 0)
        return;
    DL_Timer_stopCounter(PWM_D_INST);
    // uint32_t old_duty = 100 - 200 * DL_Timer_getCaptureCompareValue(PWM_C_INST, DL_TIMER_CC_1_INDEX) / DL_Timer_getLoadValue(PWM_C_INST);
    uint32_t new_load = 100000 / 2 / frq;
    uint32_t new_compare = (new_load * duty) / 100;
    DL_Timer_setLoadValue(PWM_D_INST, new_load);
    DL_Timer_setCaptureCompareValue(PWM_D_INST, new_compare ,DL_TIMER_CC_0_INDEX);
    DL_Timer_startCounter(PWM_D_INST);
}

void m1_speed_zero(void)
{
    set_m1_frq_duty(100, 0);
}

void m2_speed_zero(void)
{
    set_m2_frq_duty(100, 0);
}

//设置速度频率，可负
void m1_speed_control(int32_t frq)
{
    if(frq >= 0)
        SET_M1_DIR(1);
    else
        SET_M1_DIR(0);
    set_m1_frq_duty(abs(frq), 50);
}

//设置速度频率，可负
void m2_speed_control(int32_t frq)
{
    if(frq >= 0)
        SET_M2_DIR(1);
    else
        SET_M2_DIR(0);
    set_m2_frq_duty(abs(frq), 50);
}

//设置频率脉冲数，可负
void m1_pluse_control(int32_t frq, uint32_t pluse)
{
    if(frq >= 0)
        SET_M1_DIR(1);
    else
        SET_M1_DIR(0);
    DL_Timer_stopCounter(PWM_C_INST);
    NVIC_EnableIRQ(PWM_C_INST_INT_IRQN);
    pwm_c_pluse_target = pluse;
    pwm_c_pluse_flag = 1;
    set_m1_frq_duty(abs(frq), 50);
}

//设置频率脉冲数，可负
void m2_pluse_control(int32_t frq, uint32_t pluse)
{
    if(frq >= 0)
        SET_M2_DIR(1);
    else
        SET_M2_DIR(0);
    DL_Timer_stopCounter(PWM_D_INST);
    NVIC_EnableIRQ(PWM_D_INST_INT_IRQN);
    pwm_d_pluse_target = pluse;
    pwm_d_pluse_flag = 1;
    set_m2_frq_duty(abs(frq), 50);
}

//位置环，内有步进电机频率做速度环
void m1_pid_control(PID *pid_step_x, int16_t pixel_err)
{
    PID_Position(pid_step_x, 0, pixel_err);
    m1_speed_control(pid_step_x->Output);
}

//位置环，内有步进电机频率做速度环
void m2_pid_control(PID *pid_step_y, int16_t pixel_err)
{
    PID_Position(pid_step_y, 0, pixel_err);
    m2_speed_control(pid_step_y->Output);
}