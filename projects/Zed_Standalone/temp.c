/*
 * temp.c
 *
 *  Created on: 2014-4-23
 *      Author: chenxi
 */

#include "xparameters.h"
#include "xiic_l.h"

#define IIC_BASE_ADDRESS	XPAR_IIC_0_BASEADDR

#define TEMP_SENSOR_ONCHIP_ADDRESS  0x48 //温度传感器器件地址

int TempSensor(u32 IicBaseAddress,u8  TempSensorAddress,u8 *TemperaturePtr)
{
	int ByteCount;
	ByteCount = XIic_Recv(IicBaseAddress, TempSensorAddress, TemperaturePtr, 1, XIIC_STOP);
	return ByteCount;
}

u8 GetTemp()
{
	u8 Temp;
	TempSensor(IIC_BASE_ADDRESS, TEMP_SENSOR_ONCHIP_ADDRESS, &Temp);
	return Temp;
}
