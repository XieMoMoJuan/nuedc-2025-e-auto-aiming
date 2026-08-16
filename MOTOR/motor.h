#ifndef __MOTOR_H_
#define __MOTOR_H_
#include "pid.h"
#include "encoder.h"
#include "MPU6050.h"

#define STOP 0  
#define TRACK 1  
#define TURN_LEFT 2 
#define TURN_RIGHT 3 
#define TURN_BACK 4

#define ON_POSITION 1 
#define OFF_POSITION 0
float yaw_error(void);
void set_speed_left(int16_t speed);
void set_speed_right(int16_t speed);

uint8_t get_car_state(void);
void set_speed_left(int16_t speed);
void set_speed_right(int16_t speed);
void set_target(float cm, Count *count, PID *pid_position, PID *pid_left, PID *pid_right);
void set_trun(int16_t trun_angle, Count *count, PID *pid_position, PID *pid_left, PID *pid_right, PID *pid_yaw);

void motor_speed_pid(Count *count, PID *pid_left, PID *pid_right, int excpet_left, int except_right);
void motor_w_speed_pid(Count *count,PID *pid_w_speed, PID *pid_left, PID *pid_right, float except_w);

uint8_t motor_controll(Count *count, PID *pid_position, PID *pid_left, PID *pid_right);
uint8_t motor_controll_gray(Count *count, PID *pid_position, PID *pid_left, PID *pid_right, uint8_t gray_data);
uint8_t motor_controll_camera(Count *count, PID *pid_theta, PID *pid_rho, PID *pid_position, PID *pid_left, PID *pid_right, int16_t rho_err, int16_t theta_err);
uint8_t motor_controll_turn(Count *count,PID *pid_w_speed, PID *pid_yaw, PID *pid_left, PID *pid_right);
uint8_t motor_speed_pid_gray(Count *count, PID *pid_left, PID *pid_right, int excpet_left, int except_right, uint8_t gray_data);
float set_offset(uint8_t gray_data, uint8_t *detect_angle_flag);
#endif