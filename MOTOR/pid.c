#include "ti_msp_dl_config.h"
#include "pid.h"

/*
*    typedef struct PID
*    {
*         float Kp;
*         float Ki;
*         float Kd;
*         
*         float PrevError; //Error[-2];
*         float LastError; //Error[-1];
*         float Error; //Error[0];
*         float DError; //Error-LastError
*         float SumError; //sum of error
*         float Output; //
*         
*         float Integralmax; //积分限幅
*         float Outputmax; //输出限幅
*    }PID;
*/

void PID_Init(PID* PID,float Kp,float Ki,float Kd,uint16_t limit_output,uint16_t limit_Integral)
{
	PID->Kp=Kp;
	PID->Ki=Ki;
	PID->Kd=Kd;
     PID->Error = PID->DError = PID->LastError = PID->PrevError = PID->SumError = 0;
	PID->Outputmax=limit_output;
	PID->Integralmax=limit_Integral;
}

void PID_Set(PID* PID,float Kp,float Ki,float Kd,uint16_t limit_output,uint16_t limit_Integral)
{
	PID->Kp=Kp;
	PID->Ki=Ki;
	PID->Kd=Kd;
	PID->Outputmax=limit_output;
	PID->Integralmax=limit_Integral;
}

float Integral_Limit(PID* PID)
{
     float KIxSUM=PID->Ki*PID->SumError;
	if (KIxSUM > PID->Integralmax) 
	{
          KIxSUM = PID->Integralmax;
	}
	else if (KIxSUM < -PID->Integralmax) 
	{
          KIxSUM = -PID->Integralmax;
	}
     return KIxSUM;
}

void OutPut_Limit(PID* PID)
{
	if (PID->Output > PID->Outputmax) 
	{
          PID->Output = PID->Outputmax;
	}
	else if (PID->Output < -PID->Outputmax) 
	{
          PID->Output = -PID->Outputmax;
	}
}

/*
增量式pid 
P:e(k)-e(k-1);
I:e(k);
D:e(k)-2e(k-1)+e(k-2)
*/
void PID_Increase(PID* PID_V,float excepetion,float now)
{
	PID_V->Error = excepetion - now;
	PID_V->DError = PID_V->Error - PID_V->LastError;

	PID_V->Output = PID_V->Kp*PID_V->DError + PID_V->Ki*PID_V->Error + PID_V->Kd*(PID_V->Error-2*PID_V->LastError+PID_V->PrevError);
	
	PID_V->PrevError = PID_V->LastError;
	PID_V->LastError = PID_V->Error;

     OutPut_Limit(PID_V);
}

/*
位置式pid 
P : e(k)
I : ∑e(i) 误差的累加
D : e(k) - e(k-1) 这次误差-上次误差
*/
uint8_t PID_Position(PID* PID_D,float excepetion,float now)
{
	PID_D->Error = excepetion - now;
	PID_D->DError = PID_D->Error - PID_D->LastError;
	PID_D->SumError += PID_D->Error;
     
	PID_D->Output = PID_D->Kp*PID_D->Error + Integral_Limit(PID_D) + PID_D->Kd*PID_D->DError;
	
	PID_D->LastError = PID_D->Error; 

     OutPut_Limit(PID_D);
	
	return 0;
}

void PID_Clear(PID* pid)
{
     pid->DError = pid->Error = pid->LastError = pid->Output = pid->PrevError = pid->SumError = 0;
}
     
