/*
 * adp5589.c
 *
 *  Created on: 2014-4-24
 *      Author: chenxi
 */


#include "xparameters.h"
#include "xiic_l.h"
#include "adp5589.h"
#include "sleep.h"
#include "xparameters.h"
#include "TEMP.h"

//#include "temp.h"
u8 PL_value_a=0x00;
u8 tmpstr[]="TEMPERATURE:   C";
u8 tmpnum[]="0123456789";

void PL_write2byte(u8 address,u8 reg,u8 dat)
{
	u8 buf1[2];
	buf1[0]=reg;
	buf1[1]=dat;
	XIic_Send(XPAR_IIC_0_BASEADDR, address,buf1, 2, 0);
}
void ADP5589int(void)
{
	u8 databuf[3]={ADP5589_GPIO_DIRECTION_A,0xff,0xff};

	XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,databuf, 3, 0);
	databuf[0]=ADP5589_GPO_OUT_MODE_A;  //输出方式
	databuf[1]=0x00;
	databuf[2]=0x00;
	XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,databuf, 3, 0);
	/*
	databuf[0]=ADP5589_GPO_DATA_OUT_A;	//输出电平
	databuf[1]=0x00;					//0=low
	databuf[2]=0x00;
	XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,databuf, 3, 0);
	sleep(1);
	databuf[0]=ADP5589_GPO_DATA_OUT_A;  //输出电平
	databuf[1]=0xff;					//1=high
	databuf[2]=0xff;
	XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,databuf, 3, 0);
	sleep(1);
	 */
}
u8 iic_io_test()
{	u8 id=0;
	u8  write_reg[1]={0};
	u8 databuf[2]={ADP5589_GPIO_DIRECTION_A,0xfc};//a低两位输入
	XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,databuf, 2, 0);
	databuf[0]=ADP5589_GPO_OUT_MODE_A;
	databuf[1]=0x00;					//输出方式   ：上/下拉
	XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,databuf, 2, 0);

	databuf[0]=ADP5589_GPO_DATA_OUT_A;
	databuf[1]=0xfc;								//a低两位00,高位1
	XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,databuf, 2, 0);
	databuf[0]=ADP5589_ADR_GPI_STATUS_A;  //写   ,发读的寄存器
	XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,write_reg,1, 1);
					//读
	XIic_Recv(XPAR_IIC_0_BASEADDR, 0x34, &id, 1, XIIC_STOP);
	return id;
	}

void PL_lcd_w_cmd(u8 d)
{
	//write2byte(0x34,ADP5589_GPO_DATA_OUT_B,PL_value_a &= 0xFE);//PORTC的第0位清零RS=0
	//write2byte(0x34,ADP5589_GPO_DATA_OUT_B,PL_value_a &= 0xFD);//PORTC的第1位清零RW=0;
	u8 buf2[2];
	u8 a;
	buf2[0]=ADP5589_GPO_DATA_OUT_B;
	PL_value_a &= 0xFE;
	buf2[1]=PL_value_a;
	XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,buf2, 2, 0);

	    buf2[0]=ADP5589_GPO_DATA_OUT_B;
		PL_value_a &= 0xFD;
		buf2[1]=PL_value_a;
		XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,buf2, 2, 0);
	/*将要写入的参数d的高四位写入1602*/
	//write2byte(0x34,ADP5589_GPO_DATA_OUT_B,PL_value_a= (d&0xF0) | (PL_value_a&0x0F));
	/*将要写入的参数d的低四位写入1602*/
	//write2byte(0x34,ADP5589_GPO_DATA_OUT_A,d<<4);
	    buf2[0]=ADP5589_GPO_DATA_OUT_B;
	   // a=(d&0xF0);
	   // b=(PL_value_a&0x0F);
	    PL_value_a=(d&0xF0) | (PL_value_a&0x0F);
	    a=PL_value_a;
		buf2[1]=a;//;
		XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,buf2, 2, 0);

	    buf2[0]=ADP5589_GPO_DATA_OUT_A;
	   // PL_value_a= d<<4;
		buf2[1]=d<<4;//PL_value_a;
		XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,buf2, 2, 0);

	usleep(200);

	//write2byte(0x34,ADP5589_GPO_DATA_OUT_B,PL_value_a |= 0x04);//PORTC的第2位置位en=1;
	//write2byte(0x34,ADP5589_GPO_DATA_OUT_B,PL_value_a &= 0xFB);//PORTC的第2位清零en=0;
	        buf2[0]=ADP5589_GPO_DATA_OUT_B;
	        PL_value_a |= 0x04;
			buf2[1]=PL_value_a;
			XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,buf2, 2, 0);

		      buf2[0]=ADP5589_GPO_DATA_OUT_B;
		      PL_value_a &= 0xFB;
			buf2[1]=PL_value_a;
			XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,buf2, 2, 0);


}
void PL_lcd_w_dat(u8 d)
{
	//write2byte(0x68,ADP5589_GPO_DATA_OUT_B,PL_value_a |= 0x01);//PORTC的第0位置位RS=1;
	//write2byte(0x68,ADP5589_GPO_DATA_OUT_B,PL_value_a &= 0xFD);//PORTC的第1位清零RW=0;
	u8 buf2[2];
	u8 a;
		buf2[0]=ADP5589_GPO_DATA_OUT_B;
		PL_value_a |= 0x01;
		buf2[1]=PL_value_a;
		XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,buf2, 2, 0);

		    buf2[0]=ADP5589_GPO_DATA_OUT_B;
			PL_value_a &= 0xFD;
			buf2[1]=PL_value_a;
			XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,buf2, 2, 0);

	/*将要写入的参数d的高四位写入1602*/
//	write2byte(0x68,ADP5589_GPO_DATA_OUT_B,PL_value_a= (d&0xF0) | (PL_value_a&0x0F));
	/*将要写入的参数d的低四位写入1602*/
//	write2byte(0x68,ADP5589_GPO_DATA_OUT_A,d<<4);

	buf2[0]=ADP5589_GPO_DATA_OUT_B;
	PL_value_a=(d&0xF0) | (PL_value_a&0x0F);
	a=PL_value_a;
	buf2[1]=a;
	XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,buf2, 2, 0);

	buf2[0]=ADP5589_GPO_DATA_OUT_A;

	buf2[1]=d<<4;
	XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,buf2, 2, 0);

	usleep(1);

	 buf2[0]=ADP5589_GPO_DATA_OUT_B;
		        PL_value_a |= 0x04;//PORTC的第2位置位en=1;
				buf2[1]=PL_value_a;
				XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,buf2, 2, 0);

			      buf2[0]=ADP5589_GPO_DATA_OUT_B;
			      PL_value_a &= 0xFB;//PORTC的第2位清零en=0;
				buf2[1]=PL_value_a;
				XIic_Send(XPAR_IIC_0_BASEADDR, 0x34,buf2, 2, 0);
}
void lcd_init(void)
{
	PL_lcd_w_cmd(0x38);
	usleep(1);
	PL_lcd_w_cmd(0x0c);
	usleep(1);
	PL_lcd_w_cmd(0x06);
	usleep(1);
	PL_lcd_w_cmd(0x01);
	usleep(1);
}

void IOKZ_test(void)
{
	volatile u8 i,TCN75A_Temp;
	ADP5589int();
	lcd_init();

	PL_lcd_w_cmd(0x80+0x00);
	usleep(1);
	for(i=0;i<16;i++)
	{
		PL_lcd_w_dat(tmpstr[i]);
		usleep(1);
	}


	PL_lcd_w_cmd(0x80+0x0E);
	usleep(1);
	PL_lcd_w_dat(0xDF);
	usleep(1);
//	while(1)
	//{
		TCN75A_Temp=GetTemp();
		PL_lcd_w_cmd(0x80+0x0C);
		usleep(1);
		PL_lcd_w_dat(tmpnum[TCN75A_Temp/10]);
		usleep(1);
		PL_lcd_w_dat(tmpnum[TCN75A_Temp%10]);
		usleep(1);
	//}
}
