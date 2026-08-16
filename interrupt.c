#include "ti_msp_dl_config.h"
#include "MPU6050.h"
#include "motor.h"
#include "stdlib.h"
#include "string.h"
#include "No_Mcu_Ganv_Grayscale_Sensor_Config.h"
#include "step_motor.h"

Count my_count = {0};
PID pid_left = {0};
PID pid_right = {0};
PID pid_position = {0};
PID pid_yaw = {0};
PID pid_w_speed = {0};
PID pid_step_x = {0};
PID pid_step_y = {0};

// volatile int32_t speed = 0; //速度环测试
// float except_w = 0; //角速度环测试

volatile uint8_t camera_ok_flag = 0; // camera任务开始标志

volatile uint8_t interrupt_task_start = 0; // pid任务开始标志

extern volatile int ec11_now_data; // 旋转编码器计数

extern volatile int32_t left_encoder;  // 左电机编码器计数
extern volatile int32_t right_encoder; // 右电机编码器计数

extern volatile uint32_t pwm_c_pluse_flag;   // pwm_c脉冲计数标志位
extern volatile uint32_t pwm_d_pluse_flag;   // pwm_d脉冲计数标志位
extern volatile uint32_t pwm_c_pluse_cnt;    // pwm_c脉冲计数
extern volatile uint32_t pwm_d_pluse_cnt;    // pwm_d脉冲计数
extern volatile uint32_t pwm_c_pluse_target; // pwm_c脉冲目标数
extern volatile uint32_t pwm_d_pluse_target; // pwm_d脉冲目标数

// while中任务标志位
volatile uint16_t task_oled_200ms_cnt = 0;
volatile uint8_t task_oled_flag = 0;
volatile uint16_t task_key_20ms_cnt = 0;
volatile uint8_t task_key_flag = 0;
volatile uint16_t task_ec11_20ms_cnt = 0;
volatile uint8_t task_ec11_flag = 0;

No_MCU_Sensor sensor = {0}; // 灰度数据

volatile uint8_t read_dmp_flag = 0;    // dmp数据读取标志位
volatile uint8_t dmp_read_cnt = 0;     // dmp读取计数
volatile uint8_t dmp_read_frq = 0;     // dmp读取频率
volatile uint8_t dmp_read_min_frq = 0; // dmp读取最小频率

// 灰度巡线速度,任务参数
volatile int32_t target_speed = 0;
// 灰度巡线圈数,任务参数
volatile uint8_t task_1_num = 0;
// 任务4进度变量,速度环-》距离环-》角速度环-》速度环。。。。
volatile uint8_t task_4_step = 0;

// 15ms任务选择
volatile int32_t interrupt_task_number = 0;

// for pid 15ms
void TIMER_0_INST_IRQHandler(void)
{

    switch (DL_Timer_getPendingInterrupt(TIMER_0_INST))
    {
    case DL_TIMER_IIDX_ZERO:
        if (interrupt_task_start == 1)
        {
            encoder_refresh(&my_count);
            No_Mcu_Ganv_Sensor_Task_Without_tick(&sensor);
            // 速度环测试
            // motor_speed_pid(&my_count, &pid_left, &pid_right, speed, 0);
            // motor_speed_pid_gray(&my_count, &pid_left, &pid_right, target_speed, target_speed)

            switch (interrupt_task_number)
            {
            case 0:

                break;
            case 1:
                switch (task_4_step % 5)
                {
                case 0: // 速度环巡线
                    task_4_step += motor_speed_pid_gray(&my_count, &pid_left, &pid_right, target_speed, target_speed, sensor.Digtal);
                    break;
                case 1: //,到达直角后会设定直线距离环的位置
                    set_target(16.8f, &my_count, &pid_position, &pid_left, &pid_right);
                    task_4_step++;
                    break;
                case 2: // 距离环车长
                    task_4_step += motor_controll(&my_count, &pid_position, &pid_left, &pid_right);
                    break;
                case 3: // 到达后会设定转向环
                    set_trun(90, &my_count, &pid_position, &pid_left, &pid_right, &pid_yaw);
                    task_4_step++;
                    break;
                case 4: // 转向环
                    task_4_step += motor_controll_turn(&my_count, &pid_w_speed, &pid_yaw, &pid_left, &pid_right);
                    break;
                default:
                    break;
                }
                if (task_4_step == 5 * 4 * task_1_num + 1)
                {
                    task_4_step = 0;
                    set_speed_left(0);
                    set_speed_right(0);
                    interrupt_task_number = 0;
                }
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                if (camera_ok_flag == 1)
                {
                    switch (task_4_step % 5)
                    {
                    case 0: // 速度环巡线void uart0_send_char(char ch)
                        DL_GPIO_clearPins(car_PORT, car_car_turn_pin_PIN);
                        task_4_step += motor_speed_pid_gray(&my_count, &pid_left, &pid_right, target_speed, target_speed, sensor.Digtal);
                        break;
                    case 1: //,到达直角后会设定直线距离环的位置
                        set_target(16.8f, &my_count, &pid_position, &pid_left, &pid_right);
                        task_4_step++;
                        break;
                    case 2: // 距离环车长
                        task_4_step += motor_controll(&my_count, &pid_position, &pid_left, &pid_right);
                        break;
                    case 3: // 到达后会设定转向环
                        set_trun(90, &my_count, &pid_position, &pid_left, &pid_right, &pid_yaw);
                        DL_GPIO_setPins(car_PORT, car_car_turn_pin_PIN);

                        task_4_step++;
                        break;
                    case 4: // 转向环
                        task_4_step += motor_controll_turn(&my_count, &pid_w_speed, &pid_yaw, &pid_left, &pid_right);
                        break;
                    default:
                        break;
                    }
                    if (task_4_step == 5 * 4 + 1)
                    {
                        task_4_step = 0;
                        set_speed_left(0);
                        set_speed_right(0);
                        interrupt_task_number = 0;
                    }
                }
                break;
            case 5:
                switch (task_4_step % 5)
                {
                case 0: // 速度环巡线
                    DL_GPIO_clearPins(car_PORT, car_car_turn_pin_PIN);
                    task_4_step += motor_speed_pid_gray(&my_count, &pid_left, &pid_right, target_speed, target_speed, sensor.Digtal);
                    break;
                case 1: //,到达直角后会设定直线距离环的位置
                    set_target(16.8f, &my_count, &pid_position, &pid_left, &pid_right);
                    task_4_step++;
                    break;
                case 2: // 距离环车长
                    task_4_step += motor_controll(&my_count, &pid_position, &pid_left, &pid_right);
                    break;
                case 3: // 到达后会设定转向环
                    set_trun(90, &my_count, &pid_position, &pid_left, &pid_right, &pid_yaw);
                    task_4_step++;
                    break;
                case 4: // 转向环
                    DL_GPIO_setPins(car_PORT, car_car_turn_pin_PIN);
                    task_4_step += motor_controll_turn(&my_count, &pid_w_speed, &pid_yaw, &pid_left, &pid_right);
                    break;
                default:
                    break;
                }
                if (task_4_step == 5 * 8 + 1)
                {
                    task_4_step = 0;
                    set_speed_left(0);
                    set_speed_right(0);
                    interrupt_task_number = 0;
                }
                break;
            case 6:

                break;
            default:
                break;
            }
            // 位置环测试
            // motor_controll(&my_count, &pid_position, &pid_left, &pid_right);

            // 转向环测试
            // motor_controll_turn(&my_count, &pid_w_speed, &pid_yaw, &pid_left, &pid_right);

            // 角速度环测试
            //  motor_w_speed_pid(&my_count, &pid_w_speed, &pid_left, &pid_right, except_w);

            // 巡线环测试
            // motor_controll_gray(&my_count, &pid_position, &pid_left, &pid_right, sensor.Digtal);
        }
        break;

    default:
        break;
    }
}

// for mpu6050 5ms
void TIMER_2_INST_IRQHandler(void)
{
    switch (DL_Timer_getPendingInterrupt(TIMER_2_INST))
    {
    case DL_TIMER_IIDX_ZERO:
        if (read_dmp_flag == 1)
        {
            Read_DMP();
            dmp_read_cnt++;
            read_dmp_flag = 0;
        }
        break;

    default:
        break;
    }
}

// for task 10ms
void TIMER_1_INST_IRQHandler(void)
{
    switch (DL_Timer_getPendingInterrupt(TIMER_1_INST))
    {
    case DL_TIMER_IIDX_ZERO:
        task_oled_200ms_cnt++;
        if (task_oled_200ms_cnt >= 20)
        {
            task_oled_flag = 1;

            // 计算dmp读取频率
            task_oled_200ms_cnt = 0;
            dmp_read_frq = dmp_read_cnt * 5;
            dmp_read_min_frq = dmp_read_min_frq > dmp_read_frq ? dmp_read_frq : dmp_read_min_frq;
            dmp_read_frq = 0;
        }
        task_key_20ms_cnt++;
        if (task_key_20ms_cnt >= 2)
        {
            task_key_flag = 1;
            task_key_20ms_cnt = 0;
        }
        task_ec11_20ms_cnt++;
        if (task_ec11_20ms_cnt >= 2)
        {
            task_ec11_flag = 1;
            task_ec11_20ms_cnt = 0;
        }
        break;

    default:
        break;
    } /*
     if(read_dmp_flag == 1){
         Read_DMP();
         dmp_cnt++;
         read_dmp_flag = 0;
     }*/
}

void GROUP1_IRQHandler(void) // Group1的中断服务函数
{
    // 读取Group1的中断寄存器并清除中断标志
    switch (DL_GPIO_getPendingInterrupt(GPIOA))
    {
    case camera_camera_ok_IIDX:
        camera_ok_flag = 1;
        break;

    case EC11_READ_PIN_2_IIDX:
        // EC11
        // 调试pid时需要把pid的值清0
        PID_Clear(&pid_left);
        if (DL_GPIO_readPins(EC11_READ_PORT, EC11_READ_PIN_1_PIN) > 0)
        {
            ec11_now_data++;
        }
        else
            ec11_now_data--;
        break;

    case GPIO_MPU6050_PIN_MPU6050_INT_IIDX:
        read_dmp_flag = 1;

        break;
    case ENCODER_READ_GRP_READ_A_PIN_IIDX:
        if (DL_GPIO_readPins(ENCODER_READ_GRP_READ_A_INT_PORT, ENCODER_READ_GRP_READ_A_INT_PIN) > 0)
            left_encoder--;
        else
            left_encoder++;
        break;
    case ENCODER_READ_GRP_READ_B_PIN_IIDX:
        if (DL_GPIO_readPins(ENCODER_READ_GRP_READ_B_INT_PORT, ENCODER_READ_GRP_READ_B_INT_PIN) > 0)
            right_encoder++;
        else
            right_encoder--;
        break;

    default:
        break;
    }

    switch (DL_GPIO_getPendingInterrupt(GPIOB))
    {
    case ENCODER_READ_GRP_READ_A_INT_IIDX:
        if (DL_GPIO_readPins(ENCODER_READ_GRP_READ_A_PIN_PORT, ENCODER_READ_GRP_READ_A_PIN_PIN) > 0)
            left_encoder++;
        else
            left_encoder--;
        break;
    case ENCODER_READ_GRP_READ_B_INT_IIDX:
        if (DL_GPIO_readPins(ENCODER_READ_GRP_READ_B_PIN_PORT, ENCODER_READ_GRP_READ_B_PIN_PIN) > 0)
            right_encoder--;
        else
            right_encoder++;
        break;
    default:
        break;
    }
}

uint8_t step = 0;
uint8_t buffer2[6] = {0};
uint8_t data = 0;
// 串口0,用于和云台通信，让云台再小车转向时做好准备（实际上没用，不知道哪里出问题了，发挥题用）
void UART_0_INST_IRQHandler(void)
{
    switch (DL_UART_Main_getPendingInterrupt(UART_0_INST))
    {
    case DL_UART_IIDX_RX:
        data = DL_UART_Main_receiveData(UART_0_INST);
        DL_UART_transmitData(UART_0_INST, data);
        if (step == 0)
        {
            if (data == 'f')
                step = 1;

            else if (step == 1)
            {
                if (data == 'e')
                {
                    // speed = atoi((char *)buffer2);
                    step = 0;
                    memset(buffer2, 0, sizeof(buffer2));
                }
                if (data == 'a')
                {
                    // speed = atoi((char *)buffer2);
                    step = 0;
                    memset(buffer2, 0, sizeof(buffer2));
                }
                buffer2[step - 1] = data;
                step++;
            }
        }
        break;
    default:
        break;
    }
}

void PWM_C_INST_IRQHandler()
{
    switch (DL_Timer_getPendingInterrupt(PWM_C_INST))
    {
    case DL_TIMER_IIDX_CC1_UP:
        if (pwm_c_pluse_flag == 1)
        {
            pwm_c_pluse_cnt++;
            if (pwm_c_pluse_cnt >= pwm_c_pluse_target)
            {
                m1_speed_zero();
                pwm_c_pluse_flag = 0;
                pwm_c_pluse_cnt = 0;
                NVIC_DisableIRQ(PWM_C_INST_INT_IRQN);
            }
        }
        else
            pwm_c_pluse_cnt = 0;
        break;

    default:
        break;
    }
}

void PWM_D_INST_IRQHandler()
{
    switch (DL_Timer_getPendingInterrupt(PWM_D_INST))
    {
    case DL_TIMER_IIDX_CC0_UP:
        if (pwm_d_pluse_flag == 1)
        {
            pwm_d_pluse_cnt++;
            if (pwm_d_pluse_cnt >= pwm_d_pluse_target)
            {
                m2_speed_zero();
                pwm_d_pluse_flag = 0;
                pwm_d_pluse_cnt = 0;
                NVIC_DisableIRQ(PWM_D_INST_INT_IRQN);
            }
        }
        else
            pwm_d_pluse_cnt = 0;
        break;

    default:
        break;
    }
}

void SysTick_Handler(void)
{
    return;
}