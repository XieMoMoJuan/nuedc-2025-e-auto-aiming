# 2025 电赛 E 题：简易自行瞄准装置

本项目是 **2025 年 TI 杯全国大学生电子设计竞赛本科组 E 题——简易自行瞄准装置** 的参赛工程，基于 TI MSPM0G3507 实现自动寻迹小车与瞄准控制，完成了赛题基本要求第（1）～（3）项。

官方赛题：[简易自行瞄准装置（E 题）](https://res.nuedc-training.com.cn/topic/2025/topic_124.html)

## 完成内容

1. 小车沿 100 cm × 100 cm 正方形轨迹自动寻迹，可设置行驶圈数。
2. 小车静止且位置、姿态任意时，瞄准模块自动搜索并瞄准靶心。
3. 小车位于轨迹指定位置、瞄准方向任意时，自动完成靶心瞄准。

## 主要功能

- 八路灰度传感器循迹与直角检测
- 双路编码器、电机速度环和位置环控制
- MPU6050/DMP 姿态测量
- 航向环与角速度环 PID 控制
- OLED、按键和 EC11 模式/圈数设置
- 瞄准模块状态握手与双轴步进电机 PWM 控制
- 基础题、发挥题模式入口及循迹状态机

## 工程结构

- `empty.c`：系统初始化、OLED 菜单和任务选择
- `interrupt.c`：定时任务、循迹状态机及外设中断
- `MOTOR/`：电机、编码器及多环 PID
- `GRAY/`：灰度传感器采集和归一化
- `MPU6050/`：姿态传感器和 DMP 驱动
- `STEP_MOTOR/`：双轴步进电机控制
- `OLED/`、`KEY/`、`EC11/`：人机交互模块
- `empty.syscfg`：MSPM0 SysConfig 配置
- `keil/`：Keil 工程文件
- `source/`：工程随附的 TI MSPM0 SDK 源码

## 开发环境

- MCU：TI MSPM0G3507
- SDK：TI MSPM0 SDK 2.05.01.00
- IDE：Keil MDK（打开 `keil/empty_LP_MSPM0G3507_nortos_keil.uvprojx`）
