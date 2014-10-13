/*
 * IIC_JE4_PS.c
 *
 *  Created on: 2014-4-13
 *      Author: user
 */
#include "iic.h"
#include "temp.h"
uchar current_value_c=0x00;
uchar str[]="TEMPERATURE:   C";
uchar num[]="0123456789";

extern XGpio Gpio; /* The driver instance for GPIO Device configured as O/P */
void XGpio_SetBitDirectionOut(XGpio * InstancePtr, unsigned Channel,
			    u32 DirectionMask)
{
	u32 Current;
	unsigned DataOffset;
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	Xil_AssertVoid((Channel == 1) ||
		     ((Channel == 2) && (InstancePtr->IsDual == TRUE)));
	DataOffset=((Channel - 1) * XGPIO_CHAN_OFFSET) + XGPIO_TRI_OFFSET;
	Current = XGpio_ReadReg(InstancePtr->BaseAddress,DataOffset);
	Current &= ~DirectionMask;
	XGpio_WriteReg(InstancePtr->BaseAddress,DataOffset,	Current);
}

u32 XGpio_ReadBitValue(XGpio * InstancePtr, unsigned Channel,
			    u32 ValueMask)
{
	u32 Current;
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	Xil_AssertNonvoid((Channel == 1) ||
			((Channel == 2) && (InstancePtr->IsDual == TRUE)));

	Current=XGpio_ReadReg(InstancePtr->BaseAddress,
			      ((Channel - 1) * XGPIO_CHAN_OFFSET) +
			      XGPIO_DATA_OFFSET);
	Current &=ValueMask;
	return Current;

}



void XGpio_SetBitDirectionInput(XGpio * InstancePtr, unsigned Channel,
			    u32 DirectionMask)
{
	u32 Current;
	unsigned DataOffset;
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	Xil_AssertVoid((Channel == 1) ||
		     ((Channel == 2) && (InstancePtr->IsDual == TRUE)));
	DataOffset=((Channel - 1) * XGPIO_CHAN_OFFSET) + XGPIO_TRI_OFFSET;
	Current = XGpio_ReadReg(InstancePtr->BaseAddress,DataOffset);
	Current |= DirectionMask;
	XGpio_WriteReg(InstancePtr->BaseAddress,DataOffset,	Current);
}



void delay(void)
{
    uchar i;

	for(i = 0;i < 15;i++);
}
void lcd_delay(uchar n) //延时函数
{
 uchar x,y;
 for(x=n;x>0;x--)
  for(y=250;y>0;y--);
}

void IIC_GPIO_Congif(void)
{
	XGpio_Initialize(&Gpio, XPAR_AXI_GPIO_4_DEVICE_ID);
	//XGpioPs_CfgInitialize(&psGpioInstancePtr,GpioConfigPtr, GpioConfigPtr->BaseAddr);

	ALL_OUT;

}
/*******************************************
函数名称：start
功    能：完成IIC的起始条件操作
参    数：无
返回值  ：无
********************************************/
void IIC_Start(void)
{
	SCL_H;
	SDA_H;
	delay();
	SDA_L;
	delay();
	SCL_L;
	delay();
}
/*******************************************
函数名称：stop
功    能：完成IIC的终止条件操作
参    数：无
返回值  ：无
********************************************/
void IIC_Stop(void)
{
	SDA_L;
	delay();
	SCL_H;
	delay();
	SDA_H;
	delay();
}
/*******************************************
函数名称：mack
功    能：完成IIC的主机应答操作
参    数：无
返回值  ：无
********************************************/
void mack(void)
{
	SDA_L;
	;;
	SCL_H;
	delay();
	SCL_L;
	;;
	SDA_H;
	delay();
}
/*******************************************
函数名称：mnack
功    能：完成IIC的主机无应答操作
参    数：无
返回值  ：无
********************************************/
void mnack(void)
{
	SDA_H;
	; ;
	SCL_H;
	delay();
	SCL_L;
	; ;
	SDA_L;
	delay();
}

/**********检查应答信号函数******************/
/*如果返回值为0则证明有应答信号，反之没有*/
/*******************************************
函数名称：check
功    能：检查从机的应答操作
参    数：无
返回值  ：从机是否有应答：1--有，0--无
********************************************/
uchar IIC_Ack(void)
{
	uchar slaveack;

	SDA_H;
	; ;
	SCL_H;
	; ;
    SDA_IN;
    ; ;
	slaveack = SDA_READ;   //读入SDA数值,如果为1说明没有应答
	SCL_L;
	delay();
    SDA_OUT;
    if(slaveack)
    {
    	return 1;
    }
    else
    {
    	return 0;
    }
}
/*******************************************
函数名称：write1
功    能：向IIC总线发送一个1
参    数：无
返回值  ：无
********************************************/
void write1(void)
{
	SDA_H;
	delay();
	SCL_H;
	delay();
	SCL_L;
	delay();
}
/*******************************************
函数名称：write0
功    能：向IIC总线发送一个0
参    数：无
返回值  ：无
********************************************/
void write0(void)
{
	SDA_L;
	delay();
	SCL_H;
	delay();
	SCL_L;
	delay();
}
/*******************************************
函数名称：write1byte
功    能：向IIC总线发送一个字节的数据
参    数：wdata--发送的数据
返回值  ：无
********************************************/
void write1byte(uchar wdata)
{
	uchar i;

	for(i = 8;i > 0;i--)
	{
		if(wdata & 0x80)
		{
			write1();
		}
		else
		{
			write0();
		}
		wdata <<= 1;
	}

	SDA_H;
	;
}
/*******************************************
函数名称：writeNbyte
功    能：向IIC总线发送N个字节的数据
参    数：outbuffer--指向发送数据存放首地址
          的指针
          n--数据的个数
返回值  ：发送是否成功的标志：1--成功，0--失败
********************************************/
uchar writeNbyte(uchar address,uchar reg,uchar dat)
{
		IIC_Start();
		write1byte(address);
		if(IIC_Ack())//没有应答就退出
		{
			IIC_Stop();
			return 1;
		}
		write1byte(reg);
		if(IIC_Ack())//没有应答就退出
		{
			IIC_Stop();
			return 1;
		}
		write1byte(dat);
		if(IIC_Ack())//没有应答就退出
		{
			IIC_Stop();
			return 1;
		}
		IIC_Stop();
		return 0;
}
/*******************************************
函数名称：read1byte
功    能：从IIC总线读取一个字节
参    数：无
返回值  ：读取的数据
********************************************/
uchar read1byte(void)
{
	uchar  rdata = 0x00,i;
    uchar flag;

	for(i = 0;i < 8;i++)//一位一位的读取一个字节
	{
		SDA_H;
		delay();
		SCL_H;
        SDA_IN;
		delay();
		flag = SDA_READ;
		rdata <<= 1;
		if(flag)	rdata |= 0x01;
        SDA_OUT;
		SCL_L;
		delay();
	}

	return rdata;
}
/*******************************************
函数名称：readNbyte
功    能：从IIC总线读取N个字节的数据
参    数：inbuffer--读取后数据存放的首地址
          n--数据的个数
返回值  ：无
********************************************/
uchar readNbyte(uchar address_w,uchar reg,uchar address_r)
{
	uchar value;
	IIC_Start();
	write1byte(address_w);
	if(IIC_Ack())//没有应答就退出
	{
		IIC_Stop();
		return 1;
	}
	write1byte(reg);
	if(IIC_Ack())//没有应答就退出
	{
		IIC_Stop();
		return 1;
	}
	IIC_Start();
	write1byte(address_r);
	if(IIC_Ack())//没有应答就退出
	{
		IIC_Stop();
		return 1;
	}
	value=read1byte();
	IIC_Stop();
	return value;
}
void lcd1602_w_cmd(unsigned char d)
{
	writeNbyte(0x68,ADP5589_GPO_DATA_OUT_B,current_value_c &= 0xFE);//PORTC的第0位清零RS=0
	writeNbyte(0x68,ADP5589_GPO_DATA_OUT_B,current_value_c &= 0xFD);//PORTC的第1位清零RW=0;

	/*将要写入的参数d的高四位写入1602*/
	writeNbyte(0x68,ADP5589_GPO_DATA_OUT_B,current_value_c= (d&0xF0) | (current_value_c&0x0F));
	/*将要写入的参数d的低四位写入1602*/
	writeNbyte(0x68,ADP5589_GPO_DATA_OUT_A,d<<4);

	lcd_delay(200);

	writeNbyte(0x68,ADP5589_GPO_DATA_OUT_B,current_value_c |= 0x04);//PORTC的第2位置位en=1;
	writeNbyte(0x68,ADP5589_GPO_DATA_OUT_B,current_value_c &= 0xFB);//PORTC的第2位清零en=0;
}
void lcd1602_w_dat(char d)
{
	writeNbyte(0x68,ADP5589_GPO_DATA_OUT_B,current_value_c |= 0x01);//PORTC的第0位置位RS=1;
	writeNbyte(0x68,ADP5589_GPO_DATA_OUT_B,current_value_c &= 0xFD);//PORTC的第1位清零RW=0;
	/*将要写入的参数d的高四位写入1602*/
	writeNbyte(0x68,ADP5589_GPO_DATA_OUT_B,current_value_c= (d&0xF0) | (current_value_c&0x0F));
	/*将要写入的参数d的低四位写入1602*/
	writeNbyte(0x68,ADP5589_GPO_DATA_OUT_A,d<<4);

	lcd_delay(200);

	writeNbyte(0x68,ADP5589_GPO_DATA_OUT_B,current_value_c |= 0x04);//PORTC的第2位置位en=1;
	writeNbyte(0x68,ADP5589_GPO_DATA_OUT_B,current_value_c &= 0xFB);//PORTC的第2位清零en=0;
}
void lcd1602_init(void)
{
	lcd1602_w_cmd(0x38);
	lcd1602_w_cmd(0x0c);
	lcd1602_w_cmd(0x06);
	lcd1602_w_cmd(0x01);
}


void Get_Temp_dis()
{
	volatile uchar i,TCN75A_Temp;
	    IIC_GPIO_Congif();



		ADP5585_OUTPUT;
		lcd1602_init();

		lcd1602_w_cmd(0x80+0x00);
		for(i=0;i<16;i++)
		{
			lcd1602_w_dat(str[i]);
		}
		lcd1602_w_cmd(0x80+0x0E);
		lcd1602_w_dat(0xDF);
		while(1)
		{
			TCN75A_Temp=GetTemp();
			lcd1602_w_cmd(0x80+0x0C);
			lcd1602_w_dat(num[TCN75A_Temp/10]);
			lcd1602_w_dat(num[TCN75A_Temp%10]);
		}

	}





