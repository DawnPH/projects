

/***************************** Include Files *******************************/
#include "motor.h"

/************************** Function Definitions ***************************/
/*
	作用：	将电机模块物理地址传递给一个Motor类型的结构体变量
	参数：	1、Motor类型的结构体变量
			2、电机模块的物理地址，在xparameters.h中有定义
	返回值：成功		
*/
int Motor_Initialize(Motor *InstancePtr,u32 EffectiveAddr)
{
	Xil_AssertNonvoid(InstancePtr != NULL);

	InstancePtr -> BaseAddress = EffectiveAddr;
	InstancePtr -> IsReady = XIL_COMPONENT_IS_READY;
	return XST_SUCCESS;
}

/*
	作用：	将车子相应车轮方向写入相应寄存器
	参数：	1、Motor类型的结构体变量
			2、电机通道，在car.h中有定义，分为：LEFT和RIGHT
			3、电机方向，在car.h中有定义，分为：FORWARD和BACKWARD
	返回值：无		
*/

void Motor_SetDirection(Motor *InstancePtr,unsigned Motor_Channel,u32 Direction)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);
	Xil_AssertVoid(Motor_Channel == LEFT || Motor_Channel == RIGHT);

	MOTOR_mWriteReg(InstancePtr -> BaseAddress,MOTOR_S00_AXI_SLV_REG1_OFFSET + 8 * Motor_Channel,Direction);
}

/*
	作用：	读出车子相应车轮方向
	参数：	1、Motor类型的结构体变量
			2、电机通道，在car.h中有定义，分为：LEFT和RIGHT
	返回值：方向	
*/
u32 Motor_GetDirection(Motor *InstancePtr,unsigned Motor_Channel)
{
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);
	Xil_AssertNonvoid(Motor_Channel == LEFT || Motor_Channel == RIGHT);

	return MOTOR_mReadReg(InstancePtr -> BaseAddress,MOTOR_S00_AXI_SLV_REG1_OFFSET + 8 * Motor_Channel);
}

/*
	作用：	将车子相应车轮方向写入相应寄存器
	参数：	1、Motor类型的结构体变量
			2、电机通道，在car.h中有定义，分为：LEFT和RIGHT
			3、电机占空比，周期最大值为10000，所以占空比最大值为10000。
	返回值：无		
*/
void Motor_SetPWMDuty(Motor *InstancePtr,unsigned Motor_Channel,u32 PWM_Duty)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);
	Xil_AssertVoid(Motor_Channel == LEFT || Motor_Channel == RIGHT);

	MOTOR_mWriteReg(InstancePtr -> BaseAddress,MOTOR_S00_AXI_SLV_REG0_OFFSET + 8 * Motor_Channel,PWM_Duty);
}

/*
	作用：	读出车子相应车轮占空比
	参数：	1、Motor类型的结构体变量
			2、电机通道，在car.h中有定义，分为：LEFT和RIGHT
	返回值：电机占空比，周期最大值为10000，所以占空比最大值为10000。
*/

u32 Motor_GetPWMDuty(Motor *InstancePtr,unsigned Motor_Channel)
{
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);
	Xil_AssertNonvoid(Motor_Channel == LEFT || Motor_Channel == RIGHT);

	return MOTOR_mReadReg(InstancePtr -> BaseAddress,MOTOR_S00_AXI_SLV_REG0_OFFSET + 8 * Motor_Channel);
}
