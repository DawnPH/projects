/*
 * iic.h
 *
 *  Created on: 2014-4-22
 *      Author: chenxi
 */

#ifndef IIC_H_
#define IIC_H_
#include "sleep.h"
#include "xbasic_types.h"
#include "xstatus.h"
#include "xgpio.h"
#define uchar unsigned char








#define bit0 0X01   //SCL
#define bit1 0X02   //
#define bit2 0X04
#define bit3 0X08
#define bit_Channel 1

#define SCL_H XGpio_DiscreteSet(&Gpio, 1,bit3);
#define SCL_L XGpio_DiscreteClear(&Gpio,1,bit3);
#define SDA_H XGpio_DiscreteSet(&Gpio, 1,bit1);
#define SDA_L XGpio_DiscreteClear(&Gpio, 1,bit1);
#define ALL_L XGpio_DiscreteClear(&Gpio,1,0X0F);

#define SDA_READ  (u8)(XGpio_ReadBitValue(&Gpio,bit_Channel,bit1))>>1;
#define SDA_IN  XGpio_SetBitDirectionInput(&Gpio,1,bit1);  //0 are output and bits set to 1 are input.
#define SDA_OUT XGpio_SetBitDirectionOut(&Gpio,1,bit1);  //  设定为输出
#define ALL_OUT XGpio_SetBitDirectionOut(&Gpio,1,0x0f);









#define ADP5585_OUTPUT  writeNbyte(0x68,ADP5589_GPIO_DIRECTION_A,0xFF);\
						writeNbyte(0x68,ADP5589_GPIO_DIRECTION_B,0xFF);\
						writeNbyte(0x68,ADP5589_GPO_OUT_MODE_A,0x00);\
						writeNbyte(0x68,ADP5589_GPO_OUT_MODE_B,0x00)
#define ADP5585_RPULL_CONFIG_A		0x19    //是否上下拉
#define ADP5585_RPULL_CONFIG_B		0x1A
#define ADP5585_RPULL_CONFIG_C		0x1B
#define ADP5585_RPULL_CONFIG_D		0x1C

#define ADP5589_ADR_GPI_STATUS_A    0x16
#define ADP5589_ADR_GPI_STATUS_B    0x17
#define ADP5589_ADR_GPI_STATUS_C    0x18

#define ADP5589_GPO_DATA_OUT_A		0x2A	//输出电平
#define ADP5589_GPO_DATA_OUT_B		0x2B
#define ADP5589_GPO_DATA_OUT_C		0x2C

#define ADP5589_GPO_OUT_MODE_A		0x2D	//输出方式
#define ADP5589_GPO_OUT_MODE_B		0x2E
#define ADP5589_GPO_OUT_MODE_C		0x2F

#define ADP5589_GPIO_DIRECTION_A	0x30	//GPIO方向
#define ADP5589_GPIO_DIRECTION_B	0x31
#define ADP5589_GPIO_DIRECTION_C	0x32

#define ADP5589_GPO_OUT_MODE_A		0x2D
#define ADP5589_GPO_OUT_MODE_B		0x2E
#define ADP5589_GPO_OUT_MODE_C		0x2F

#define ADP5585_PIN_CONFIG_A		0x49
#define ADP5585_PIN_CONFIG_B		0x4A
#define ADP5585_PIN_CONFIG_C		0x4B
#define	ADP5585_PIN_CONFIG_D 		0x4C

void XGpio_SetBitDirectionOut();
void XGpio_SetBitDirectionInput();
u32 XGpio_ReadBitValue();
void IIC_GPIO_Congif();
void Get_Temp_dis();
#endif /* IIC_H_ */
