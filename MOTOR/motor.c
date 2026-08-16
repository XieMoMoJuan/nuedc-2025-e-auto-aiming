#include "ti_msp_dl_config.h"
#include "motor.h"
#include "stdlib.h" 

volatile int32_t target_dis = 0;
volatile int32_t target_yaw = 0;
volatile uint8_t car_state = STOP;

// 设定转动角度,设定全局变量target_yaw,左正右负
void set_trun(int16_t trun_angle, Count *count, PID *pid_position, PID *pid_left, PID *pid_right, PID *pid_yaw)
{
    encoder_delete_all(count);
    PID_Clear(pid_left);
    PID_Clear(pid_right);
    PID_Clear(pid_position);
    PID_Clear(pid_yaw);

    target_yaw = mpu6050.yaw + trun_angle;
}


// 返回车辆状态：循迹，巡线，停止，左右转，回转
uint8_t get_car_state(void)
{
    return car_state;
}

// speed -1000--1000
void set_speed_left(int16_t speed)
{
    if (speed > 1000)
        speed = 1000;
    else if (speed < -1000)
        speed = -1000;
    else if (speed == 0)
    {
        DL_GPIO_setPins(TB6612_CONTROL_GRP_PORT, TB6612_CONTROL_GRP_AIN2_PIN);
        DL_GPIO_setPins(TB6612_CONTROL_GRP_PORT, TB6612_CONTROL_GRP_AIN1_PIN);
        DL_Timer_setCaptureCompareValue(PWM_0_INST, 0, DL_TIMER_CC_0_INDEX);
    }
    else if (speed >= 0)
    {
        DL_GPIO_setPins(TB6612_CONTROL_GRP_PORT, TB6612_CONTROL_GRP_AIN2_PIN);
        DL_GPIO_clearPins(TB6612_CONTROL_GRP_PORT, TB6612_CONTROL_GRP_AIN1_PIN);
        DL_Timer_setCaptureCompareValue(PWM_0_INST, speed, DL_TIMER_CC_0_INDEX);
    }
    else if (speed < 0)
    {
        DL_GPIO_setPins(TB6612_CONTROL_GRP_PORT, TB6612_CONTROL_GRP_AIN1_PIN);
        DL_GPIO_clearPins(TB6612_CONTROL_GRP_PORT, TB6612_CONTROL_GRP_AIN2_PIN);
        DL_Timer_setCaptureCompareValue(PWM_0_INST, -speed, DL_TIMER_CC_0_INDEX);
    }
}

// speed -1000--1000
void set_speed_right(int16_t speed)
{
    if (speed > 1000)
        speed = 1000;
    else if (speed < -1000)
        speed = -1000;
    else if (speed == 0)
    {
        DL_GPIO_setPins(TB6612_CONTROL_GRP_PORT, TB6612_CONTROL_GRP_BIN2_PIN);
        DL_GPIO_setPins(TB6612_CONTROL_GRP_PORT, TB6612_CONTROL_GRP_BIN1_PIN);
        DL_Timer_setCaptureCompareValue(PWM_0_INST, 0, DL_TIMER_CC_1_INDEX);
    }
    else if (speed > 0)
    {
        DL_GPIO_setPins(TB6612_CONTROL_GRP_PORT, TB6612_CONTROL_GRP_BIN1_PIN);
        DL_GPIO_clearPins(TB6612_CONTROL_GRP_PORT, TB6612_CONTROL_GRP_BIN2_PIN);
        DL_Timer_setCaptureCompareValue(PWM_0_INST, speed, DL_TIMER_CC_1_INDEX);
    }
    else if (speed < 0)
    {
        DL_GPIO_setPins(TB6612_CONTROL_GRP_PORT, TB6612_CONTROL_GRP_BIN2_PIN);
        DL_GPIO_clearPins(TB6612_CONTROL_GRP_PORT, TB6612_CONTROL_GRP_BIN1_PIN);
        DL_Timer_setCaptureCompareValue(PWM_0_INST, -speed, DL_TIMER_CC_1_INDEX);
    }
}

// 1cm对应35.650707个脉冲~~35.65071
// 设定目标距离
void set_target(float cm, Count *count, PID *pid_position, PID *pid_left, PID *pid_right)
{

    encoder_delete_all(count);
    PID_Clear(pid_position);
    PID_Clear(pid_left);
    PID_Clear(pid_right);
    car_state = TRACK;
    // 计算需要的脉冲数
    target_dis = (int)(35.65071f * (float)cm);
}

// 两电机速度环
void motor_speed_pid(Count *count, PID *pid_left, PID *pid_right, int excpet_left, int except_right)
{
    PID_Position(pid_left, excpet_left, count->err_left);
    PID_Position(pid_right, except_right, count->err_right);
    set_speed_left(pid_left->Output);
    set_speed_right(pid_right->Output);
}

// 两电机位置环，无循迹
uint8_t motor_controll(Count *count, PID *pid_position, PID *pid_left, PID *pid_right)
{
    PID_Position(pid_position, target_dis, ((float)count->sum_left + (float)count->sum_right) / 2.0f);

    if (fabs(pid_position->Error) < 5 && fabs(count->err_left + count->err_right) < 5)
    {
        motor_speed_pid(count, pid_left, pid_right, 0, 0);
        return ON_POSITION;
    }

    motor_speed_pid(count, pid_left, pid_right, pid_position->Output, pid_position->Output);
    return OFF_POSITION;
}

float set_offset(uint8_t gray_data, uint8_t *detect_angle_flag)
{
    float err = 0;
    static float last_err = 0;

    switch (gray_data)
    {
    case 0xe7: // 11100111
        err = 0;
        break;
    case 0xcf: // 11001111
        err = 3.5;
        break;
    case 0x9f: // 10011111
        err = 5.0;
        break;
    case 0x3f: // 00111111
        err = 6.0;
        //*detect_angle_flag = 1;
        break;
    case 0xf3: // 11110011
        err = -3.5;
        break;
    case 0xf9: // 11111001
        err = -5.0;
        break;
    case 0xfc: // 11111100
        err = -6.0;
        break;
    case 0xef: // 11101111
        err = 2.0;
        break;
    case 0xdf: // 11011111
        err = 3.0;
        break;
    case 0xbf: // 10111111
        err = 3.5;
        break;
    case 0x7f: // 01111111
        err = 7.0;
        break;
    case 0xf7: // 11110111
        err = -2.0;
        break;
    case 0xfb: // 11111011
        err = -3.0;
        break;
    case 0xfd: // 11111101
        err = -4.5;
        break;
    case 0xfe: // 11111110
        err = -7.0;
        break;
    case 0x1f: // 00011111
        *detect_angle_flag = 1;
        err = 8.0;
        break;
    case 0xf8: // 11111000
        *detect_angle_flag = 1;
        err = -3.0;
        break;
    case 0x0f: // 00001111
        *detect_angle_flag = 1;
        err = 13.0;
        break; 
    case 0xf0: // 11110000
        *detect_angle_flag = 1;
        err = -13.0;
        break;
    case 0x07: // 00000111
        *detect_angle_flag = 1;
        err = 13.0;
        break;
    case 0x03: // 00000011
        *detect_angle_flag = 1;
        err = 13.0;
        break;
   case 0xe0: // 11100000
        *detect_angle_flag = 1;
        err = -13.0;
        break;
  case 0xc0: // 11000000
        *detect_angle_flag = 1;
        err = -13.0;
        break;
  case 0x80: // 10000000
        *detect_angle_flag = 1;
        err = -13.0;
        break;
  case 0x01: // 00000001
        *detect_angle_flag = 1;
        err = 13.0;
        break;
  case 0x00: // 00000000
        *detect_angle_flag = 1;
        err = last_err;
        break;
    default:
        err = last_err;
        break;
    }
        last_err = err;
    return err;
}

// 两电机位置环，灰度循迹
uint8_t motor_controll_gray(Count *count, PID *pid_position, PID *pid_left, PID *pid_right, uint8_t gray_data)
{
    uint8_t null = 0;

    float offset = set_offset(gray_data, &null);

    PID_Position(pid_position, target_dis, ((float)count->sum_left + (float)count->sum_right) / 2.0f);

    if (-5 < pid_position->Error && pid_position->Error < 5)
    {
        return ON_POSITION;
    }

    // 加偏移量
    motor_speed_pid(count, pid_left, pid_right, pid_position->Output + offset, pid_position->Output - offset);
    return OFF_POSITION;
}

// 两电机速度环,灰度循迹
uint8_t motor_speed_pid_gray(Count *count, PID *pid_left, PID *pid_right, int excpet_left, int except_right, uint8_t gray_data)
{
    uint8_t detect_flag = 0;
    float offset = set_offset(gray_data, &detect_flag);
    offset = offset * 1.5;
    if (detect_flag)
    {
        PID_Position(pid_left, 0, count->err_left);
        PID_Position(pid_right, 0, count->err_right);
        set_speed_left(pid_left->Output);
        set_speed_right(pid_right->Output);
        return 1;
    }
    else
    {
        // 平缓，稳，尝试pid or 偏差
        PID_Position(pid_left, excpet_left + offset, count->err_left);
        PID_Position(pid_right, except_right - offset, count->err_right);
        set_speed_left(pid_left->Output);
        set_speed_right(pid_right->Output);
    }
    return 0;
}

// 直线走6050
uint8_t motor_controll_6050(Count *count, PID *pid_position, PID *pid_left, PID *pid_right, PID *pid_yaw)
{
    PID_Position(pid_yaw, target_dis, ((float)count->sum_left + (float)count->sum_right) / 2.0f);

    PID_Position(pid_position, target_dis, ((float)count->sum_left + (float)count->sum_right) / 2.0f);

    if (-5 < pid_position->Error && pid_position->Error < 5)
    {
        return ON_POSITION;
    }

    // 加偏移量
    motor_speed_pid(count, pid_left, pid_right, pid_position->Output, pid_position->Output);
    return OFF_POSITION;
}

// 两电机位置环，摄像头循迹
uint8_t motor_controll_camera(Count *count, PID *pid_theta, PID *pid_rho, PID *pid_position, PID *pid_left, PID *pid_right, int16_t rho_err, int16_t theta_err)
{
    PID_Position(pid_position, target_dis, ((float)count->sum_left + (float)count->sum_right) / 2.0f);
    static float sum = 0;
    PID_Position(pid_theta, 0, theta_err);
    PID_Position(pid_rho, 0, rho_err);
    sum = pid_rho->Output + pid_theta->Output;
    motor_speed_pid(count, pid_left, pid_right, pid_position->Output - (int)sum, pid_position->Output + (int)sum);
    if (-5 < pid_position->Error && pid_position->Error < 5)
    {
        return ON_POSITION;
    }
    else
        return OFF_POSITION;
}

float normalize_angle(float angle)
{
    while (angle > 180.0f)
        angle -= 360.0f;
    while (angle < -180.0f)
        angle += 360.0f;
    return angle;
}


// 通过全局变量target_yaw计算yaw与目标值的差值,用于pid计算
float yaw_error(void)
{
    float err = target_yaw - mpu6050.yaw;
    while (err > 180.0f)
        err -= 360.0f;
    while (err < -180.0f)
        err += 360.0f;
    return err;
}

// 角速度环
void motor_w_speed_pid(Count *count, PID *pid_w_speed, PID *pid_left, PID *pid_right, float except_w)
{
    PID_Position(pid_w_speed, except_w, mpu6050.gyro.z);
    motor_speed_pid(count, pid_left, pid_right, -pid_w_speed->Output, pid_w_speed->Output);
}

// 姿态环+转向环实现转向
uint8_t motor_controll_turn(Count *count, PID *pid_w_speed, PID *pid_yaw, PID *pid_left, PID *pid_right)
{

    PID_Position(pid_yaw, 0.0f, yaw_error());
    if (-2 < pid_yaw->Error && pid_yaw->Error < 2)
    {
        return ON_POSITION;
    }
    else
    {
        motor_w_speed_pid(count, pid_w_speed, pid_left, pid_right, -pid_yaw->Output);
    }
    return OFF_POSITION;
}
