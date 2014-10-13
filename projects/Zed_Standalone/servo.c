

/***************************** Include Files *******************************/
#include "servo.h"
#include "xstatus.h"

/************************** Function Definitions ***************************/
/*
	作用：	将舵机模块物理地址传递给一个Servo类型的结构体变量
	参数：	1、Servo类型的结构体变量
			2、舵机模块的物理地址，在xparameters.h中有定义
	返回值：成功		
*/
int Servo_Initialize(Servo *InstancePtr,u32 EffectiveAddr)
{
	Xil_AssertNonvoid(InstancePtr != NULL);

	InstancePtr -> BaseAddress = EffectiveAddr;
	InstancePtr -> IsReady = XIL_COMPONENT_IS_READY;
	return XST_SUCCESS;
}


/*
	作用：	将相应舵机占空比写入相应寄存器
	参数：	1、Servo类型的结构体变量
			2、舵机通道，分为1、2、3、4
			3、占空比，最小细分：0.01us，一般舵机占空比范围0.5ms-2.5ms，即5000-250000；
	返回值：无		
*/
void Servo_SetPWMDuty(Servo *InstancePtr,unsigned Servo_Channel,u32 PWM_Duty)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);
	Xil_AssertVoid(Servo_Channel > 0 && Servo_Channel < 5);

	SERVO_mWriteReg(InstancePtr -> BaseAddress,4 * (Servo_Channel - 1),PWM_Duty);
}

/*
	作用：	独吃相应舵机相应寄存器中的占空比
	参数：	1、Servo类型的结构体变量
			2、舵机通道，分为1、2、3、4
	返回值：占空比，最小细分：0.01us，一般舵机占空比范围0.5ms-2.5ms，即5000-250000；
*/
u32 Servo_GetPWMDuty(Servo *InstancePtr,unsigned Servo_Channel)
{
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);
	Xil_AssertNonvoid(Servo_Channel > 0 && Servo_Channel < 5);

	return SERVO_mReadReg(InstancePtr -> BaseAddress,4 * (Servo_Channel - 1));
}

