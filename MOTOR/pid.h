#ifndef __PID_H_
#define __PID_H_

typedef struct PID
{
	float Kp;
	float Ki;
	float Kd;
	
	float PrevError; //Error[-2];
	float LastError; //Error[-2];
	float Error; //Error[-2];
	float DError; //Error-LastError
	float SumError; //sum of error
	float Output; //
	
	float Integralmax; //积分限幅
	float Outputmax; //输出限幅
}PID;
void PID_Clear(PID* pid);
void PID_Init(PID* PID,float Kp,float Ki,float Kd,uint16_t limit_output,uint16_t limit_Integral);
void PID_Increase(PID* PID_V,float excepetion,float now);
uint8_t PID_Position(PID* PID_D,float excepetion,float now);
void PID_Set(PID* PID,float Kp,float Ki,float Kd,uint16_t limit_output,uint16_t limit_Integral);

#endif

