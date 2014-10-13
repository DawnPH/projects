/*
 * adp5589.h
 *
 *  Created on: 2014-4-24
 *      Author: chenxi
 */

#ifndef ADP5589_H_
#define ADP5589_H_


#define ADP5585_RPULL_CONFIG_A		0x19    //是否上下拉  11为disable
#define ADP5585_RPULL_CONFIG_B		0x1A
#define ADP5585_RPULL_CONFIG_C		0x1B
#define ADP5585_RPULL_CONFIG_D		0x1C

#define ADP5589_ADR_GPI_STATUS_A    0x16   //读i/o状态，1为高电平
#define ADP5589_ADR_GPI_STATUS_B    0x17
#define ADP5589_ADR_GPI_STATUS_C    0x18

#define ADP5589_GPO_DATA_OUT_A		0x2A	//输出电平
#define ADP5589_GPO_DATA_OUT_B		0x2B	//0=low
#define ADP5589_GPO_DATA_OUT_C		0x2C	//1=high

#define ADP5589_GPO_OUT_MODE_A		0x2D	//输出方式
#define ADP5589_GPO_OUT_MODE_B		0x2E	//0=push/pull
#define ADP5589_GPO_OUT_MODE_C		0x2F	//1=open drain

#define ADP5589_GPIO_DIRECTION_A	0x30	//GPIO方向
#define ADP5589_GPIO_DIRECTION_B	0x31	//0=input
#define ADP5589_GPIO_DIRECTION_C	0x32	//1=output



#define ADP5585_PIN_CONFIG_A		0x49
#define ADP5585_PIN_CONFIG_B		0x4A
#define ADP5585_PIN_CONFIG_C		0x4B
#define	ADP5585_PIN_CONFIG_D 		0x4C
void IOKZ_test();
u8 iic_io_test();
#endif /* ADP5589_H_ */
