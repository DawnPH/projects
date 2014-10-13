

/***************************** Include Files *******************************/
#include "ultrasonic.h"
#include "sleep.h"



/************************** Function Definitions ***************************/
int Ultrasonic_Initialize(Ultrasonic *InstancePtr,u32 EffectiveAddr)
{
	Xil_AssertNonvoid(InstancePtr != NULL);

	InstancePtr -> BaseAddress = EffectiveAddr;
	InstancePtr -> IsReady = XIL_COMPONENT_IS_READY;
	return XST_SUCCESS;
}

//	返回-1，代表溢出
//	返回正数，代表距离，单位CM
//	可能偶尔系统不稳定，导致偶尔返回-1
float Ultrasonic_GetDistance(Ultrasonic *InstancePtr,unsigned Ultrasonic_Channel)
{
	u32 temp_dis;
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);
	Xil_AssertNonvoid(Ultrasonic_Channel == ULTRASONIC_LEFT || Ultrasonic_Channel == ULTRASONIC_MIDDLE
									|| Ultrasonic_Channel == ULTRASONIC_RIGHT);

	ULTRASONIC_mWriteReg(InstancePtr -> BaseAddress,0,0x1);
	usleep(15);
	ULTRASONIC_mWriteReg(InstancePtr -> BaseAddress,0,0x0);
	while((~ULTRASONIC_mReadReg(InstancePtr -> BaseAddress,0)) & (1 << Ultrasonic_Channel));
	temp_dis = ULTRASONIC_mReadReg(InstancePtr -> BaseAddress,4*Ultrasonic_Channel);
	if(temp_dis == 0xffffffff)
		return 0;
	return 0.00017 * temp_dis;
}
