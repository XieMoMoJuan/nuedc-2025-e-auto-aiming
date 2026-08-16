#include "motor_draw.h"
#include "math.h" 
extern volatile bool motor_running; // 电机1运行状态
extern volatile bool motor_ch1_running; // 电机2运行状态

//将目标的xy坐标转换为电机角度（相对于原点）
static float xy_to_theta(float xy, float d) {
    return atan2f(xy, d) * 180.0f / M_PI;//atan2f返回弧度值，转换为角度
}



void motor_draw_line(Point start, Point end, float juli, int N) {
    float prev_theta_x = xy_to_theta(start.x, juli);
    float prev_theta_y = xy_to_theta(start.y, juli);

    // 移动到起点
    // motor1_move_precise_angle(prev_theta_x); // Y轴
    // motor2_move_precise_angle(prev_theta_y); // X轴
    while (motor_running);
    while (motor_ch1_running);

    for (int i = 1; i <= N; ++i) {
        float t = (float)i / N;
        float x = start.x + t * (end.x - start.x);
        float y = start.y + t * (end.y - start.y);

        float theta_x = xy_to_theta(x, juli);
        float theta_y = xy_to_theta(y, juli);

        float delta_theta_x = theta_x - prev_theta_x;
        float delta_theta_y = theta_y - prev_theta_y;

        int steps_x = (int)roundf(delta_theta_x / MOTOR_ANGLE_MIN);
        int steps_y = (int)roundf(delta_theta_y / MOTOR_ANGLE_MIN);

        if (steps_y != 0) {
            motor1_move_precise_steps(steps_y);
        }
        if (steps_x != 0) {
            motor2_move_precise_steps(steps_x);
        }
        // 等待两轴都完成
        while (motor_running || motor_ch1_running);

        prev_theta_x = theta_x;
        prev_theta_y = theta_y;
    }
}