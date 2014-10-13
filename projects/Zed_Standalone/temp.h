/*
 * temp.h
 *
 *  Created on: 2014-4-23
 *      Author: chenxi
 */

#ifndef TEMP_H_
#define TEMP_H_

int TempSensor(u32 IicBaseAddress,u8 TempSensorAddress,u8 *TemperaturePtr);
u8 GetTemp();

#endif /* TEMP_H_ */
