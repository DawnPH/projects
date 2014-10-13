

/***************************** Include Files *******************************/
#include "speed.h"

/************************** Function Definitions ***************************/
/*
	作用：	将测速模块物理地址传递给一个Speed类型的结构体变量
	参数：	1、Speed类型的结构体变量
			2、测速模块的物理地址，在xparameters.h中有定义
	返回值：成功		
*/
int Speed_Initialize(Speed *InstancePtr,u32 EffectiveAddr)
{
	Xil_AssertNonvoid(InstancePtr != NULL);

	InstancePtr -> BaseAddress = EffectiveAddr;
	InstancePtr -> IsReady = XIL_COMPONENT_IS_READY;
	return XST_SUCCESS;
}

/*
	作用：	读出相应测速模块的1s时间内的脉冲数
	参数：	1、Speed类型的结构体变量
			2、测速模块通道，与电机通道相同在car.h中有定义，分为：LEFT和RIGHT
	返回值：方向	
*/
u32 Speed_GetMotorSpeed(Speed *InstancePtr,unsigned Speed_Channel)
{
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);
	Xil_AssertNonvoid(Speed_Channel == LEFT || Speed_Channel == RIGHT);

	return SPEED_mReadReg(InstancePtr -> BaseAddress,4 * Speed_Channel);
}
