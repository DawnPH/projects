/*
 * Copyright (c) 2009 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * standalone application for AMP
 */

#include "xparameters.h"
#include <stdio.h>
#include <string.h>
#include "AMP.h"
#include "xgpio.h"
#include "car.h"
#include "Speed.h"
#include "sleep.h"
//#include "iic.h"
#include "ADP5589.H"
#include "xtime_l.h"
#include "spi.h"
const char *char_num = {"0123456789"};

Motor motor_test;
Servo servo_test;
Speed speed_test;
XGpio optical_test;
Ultrasonic ultra_test;
XGpio Gpio;

unsigned char black_flag=0;    //黑线标志位
float ultrasonic;    //超声波距离
char cv_num;
char enable =0;


void HW_Init()
{
	OLED_Init();

	Motor_Initialize(&motor_test,XPAR_MOTOR_0_S00_AXI_BASEADDR);
	Motor_SetDirection(&motor_test,LEFT,FORWARD);
	Motor_SetPWMDuty(&motor_test,LEFT,4000);
	Motor_SetDirection(&motor_test,RIGHT,FORWARD);
	Motor_SetPWMDuty(&motor_test,RIGHT,4000);

	Servo_Initialize(&servo_test,XPAR_SERVO_0_S00_AXI_BASEADDR);
	//Servo_SetPWMDuty(&servo_test,1,150000);
	//Servo_SetPWMDuty(&servo_test,2,150000);



	Speed_Initialize(&speed_test,XPAR_SPEED_0_S00_AXI_BASEADDR);

	XGpio_Initialize(&optical_test,XPAR_AXI_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(&optical_test,1,0xff);

	Ultrasonic_Initialize(&ultra_test,XPAR_ULTRASONIC_0_S00_AXI_BASEADDR);//test



}
void init_servo()
{
	Servo_SetPWMDuty(&servo_test,1,0x0C000);//上面的舵机
	Servo_SetPWMDuty(&servo_test,2,0x27000);//下面的舵机

	}
void In_Grage_app()  //回城
{
			ultrasonic=Ultrasonic_GetDistance(&ultra_test,ULTRASONIC_MIDDLE);//测距离
				//OLED_Clear();
				OLED_ShowNum(0,0,ultrasonic,4,16);
				OLED_ShowNum(0,32,black_flag,4,16);
				OLED_Refresh_Gram();   //显示距离
				Motor_SetDirection(&motor_test,LEFT,FORWARD);
				Motor_SetPWMDuty(&motor_test,LEFT,4200);   //左前进
				Motor_SetDirection(&motor_test,RIGHT,FORWARD);
				Motor_SetPWMDuty(&motor_test,RIGHT,4000);    //右前进

	           if((ultrasonic==23)||(ultrasonic==22)||(ultrasonic==24))
	           {
				Motor_SetDirection(&motor_test,LEFT,FORWARD);
				Motor_SetPWMDuty(&motor_test,LEFT,4000);//左
				Motor_SetDirection(&motor_test,RIGHT,BACKWARD);
				Motor_SetPWMDuty(&motor_test,RIGHT,4700);//右
				//拐弯
				sleep(1);	//end
				Motor_SetDirection(&motor_test,LEFT,FORWARD);
				Motor_SetPWMDuty(&motor_test,LEFT,4500);   //左前进
				Motor_SetDirection(&motor_test,RIGHT,FORWARD);
				Motor_SetPWMDuty(&motor_test,RIGHT,4000);    //右前进
				sleep(3);   //驱动舵机
				Motor_SetDirection(&motor_test,LEFT,FORWARD);
				Motor_SetPWMDuty(&motor_test,LEFT,0);   //左前进
				Motor_SetDirection(&motor_test,RIGHT,FORWARD);
				Motor_SetPWMDuty(&motor_test,RIGHT,0);    //右前进
				sleep(999);   //结束
	           }
}
void Stop_Distance_app()  //停，测距显示
{
		Motor_SetPWMDuty(&motor_test,LEFT,0);
		Motor_SetPWMDuty(&motor_test,RIGHT,0);
		//测量距离,驱动舵机
		ultrasonic=Ultrasonic_GetDistance(&ultra_test,ULTRASONIC_MIDDLE);
		OLED_Clear();
		OLED_ShowNum(0,0,ultrasonic,4,16);
		OLED_ShowNum(0,32,black_flag,4,16);
		OLED_Refresh_Gram();
}
void Passing_Black_app()   //过黑线
{
		Motor_SetDirection(&motor_test,LEFT,FORWARD);
		Motor_SetPWMDuty(&motor_test,LEFT,4300);
		Motor_SetDirection(&motor_test,RIGHT,FORWARD);
		Motor_SetPWMDuty(&motor_test,RIGHT,4000);
		usleep(1000*500);	//end
}
int Servo_Set_app()   //舵机动作
{
	   u32 dat_1=LEVEL_MIN,dat_2=0x2d000;   //1上。2下
	   u32 dat_3=LEVEL_MIN,dat_4=0x0b000;   //1上。2下
	   u32 dat_5=LEVEL_MIN,dat_6=0x27000;   //1上。2下
	   u32 dat_1c,dat_2c,dat_3c,dat_4c,dat_5c,dat_6c;   //data change
	   XTime tEnd, tCur;
if(enable==1)
{	   
	while(black_flag==1)
	{
	Stop_Distance_app(); //停车  测距离
	if(COMM_TX_FLAG == 1)  //舵机动作：检测到数据,显示数字,前进
			{
				cv_num = COMM_TX_DATA / 1000;
				OLED_ShowNum(32,50,cv_num,8,16);//显示数字
			    OLED_Refresh_Gram();   //送入内存
			    init_servo();  //恢复舵机
				Passing_Black_app();
				COMM_TX_FLAG=0;
				enable=0;
				return 1;
			}
	XTime_GetTime(&tCur); //获取当前时间	
	while(COMM_TX_FLAG!=1)   //舵机动作：未检测到数据
			{
			    dat_1c=dat_1++;dat_2c=dat_2++;
			    usleep(500);
			    Servo_SetPWMDuty(&servo_test,1,dat_1c);//上面的舵机
			    Servo_SetPWMDuty(&servo_test,2,dat_2c);//下面的舵机
			    if (dat_1>=LEVEL_MAX)dat_1=LEVEL_MIN;
			    if (dat_2>=0x32000)dat_2=0x2d000;
			    XTime_GetTime(&tEnd);  //获取结束时间
				if((tEnd-tCur)/XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ>10) //时间溢出，前进
				{	init_servo();  //恢复舵机
					Passing_Black_app();//前进一小段距离
					COMM_TX_FLAG=0;
					enable=0;
					return 0 ;     //清除数据， 跳出循环
				}
			}
	}
	while(black_flag==2)
	{
	Stop_Distance_app(); //停车  测距离
	if(COMM_TX_FLAG == 1)  //舵机动作：检测到数据,显示数字,前进
			{
				cv_num = COMM_TX_DATA / 1000;
				OLED_ShowNum(32,50,cv_num,8,16);//显示数字
			    OLED_Refresh_Gram();   //送入内存
			    init_servo();  //恢复舵机
				Passing_Black_app();
				COMM_TX_FLAG=0;
				enable=0;
				return 2;
			}
	XTime_GetTime(&tCur); //获取当前时间	
	while(COMM_TX_FLAG!=1)   //舵机动作：未检测到数据
			{
			    dat_3c=dat_3++;dat_4c=dat_4++;
			    usleep(500);
			    Servo_SetPWMDuty(&servo_test,1,dat_3c);//上面的舵机
			    Servo_SetPWMDuty(&servo_test,2,dat_4c);//下面的舵机
			    if (dat_3>=LEVEL_MAX)dat_3=LEVEL_MIN;
			    if (dat_4>=0x0e000)dat_4=0x0b000;
			    XTime_GetTime(&tEnd);  //获取结束时间
				if((tEnd-tCur)/XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ>10) //时间溢出，前进
				{	init_servo();  //恢复舵机
					Passing_Black_app();//前进一小段距离
					COMM_TX_FLAG=0;
					enable=0;
					return 0 ;     //清除数据， 跳出循环
				}
			}
	}
	while(black_flag==3)
	{
		Stop_Distance_app(); //停车  测距离
	if(COMM_TX_FLAG == 1)  //舵机动作：检测到数据,显示数字,前进
			{
				cv_num = COMM_TX_DATA / 1000;
				OLED_ShowNum(32,50,cv_num,8,16);//显示数字
			    OLED_Refresh_Gram();   //送入内存
			    init_servo();  //恢复舵机
				Passing_Black_app();
				COMM_TX_FLAG=0;
				enable=0;
				In_Grage_app();//回城
				return 3;
			}
	XTime_GetTime(&tCur); //获取当前时间	
	while(COMM_TX_FLAG!=1)   //舵机动作：未检测到数据
			{
			    dat_5c=dat_5++;dat_6c=dat_6++;
			    usleep(500);
			    Servo_SetPWMDuty(&servo_test,1,dat_5c);//上面的舵机
			    Servo_SetPWMDuty(&servo_test,2,dat_6c);//下面的舵机
			    if (dat_5>=LEVEL_MAX)dat_5=LEVEL_MIN;
			    if (dat_6>=0x2b000)dat_6=0x27000;
			    XTime_GetTime(&tEnd);  //获取结束时间
				if((tEnd-tCur)/XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ>10) //时间溢出，前进
				{	init_servo();  //恢复舵机
					Passing_Black_app();//前进一小段距离
					COMM_TX_FLAG=0;
					enable=0;
					In_Grage_app();//回城
					return 0 ;     //清除数据， 跳出循环
				}
			}
	}

}	
COMM_TX_FLAG=0;
enable=0;
return 0 ;
}



int main()
{
	// Disable L1 cache for OCM
	MyXil_SetTlbAttributes(0xFFFF0000,0x04de2);           // S=b0 TEX=b100 AP=b11, Domain=b1111, C=b0, B=b0

	//heart beat in OCM for Linux to monitor
    COMM_VAL = 1;
    HW_Init();



/*
    while(1)
    {
	Servo_Set_app();
		if((XGpio_DiscreteRead(&optical_test,1) & 0xf) == 0)
			{
				black_flag++;
				enable=1;
			}
    else if((XGpio_DiscreteRead(&optical_test,1) & 0x1) == 0){
		    		Motor_SetDirection(&motor_test,LEFT,BACKWARD);
		    	}
    else if((XGpio_DiscreteRead(&optical_test,1) & 0x8) == 0){
		    		Motor_SetDirection(&motor_test,RIGHT,BACKWARD);
		    	}
    else {
		    		Motor_SetDirection(&motor_test,LEFT,FORWARD);
		    		Motor_SetDirection(&motor_test,RIGHT,FORWARD);
		    	}


    }
*/

  //  ADP5589int();
   //
    u16 spi_read_data=0;
   // u8  io_read=0;
    while(1)
    {
    //io_read=iic_io_test();
    spi_read_data=LightData();
    OLED_ShowNum(0,0,spi_read_data,16,16);//显示数字
  //  OLED_ShowNum(32,32,io_read,16,16);
    OLED_Refresh_Gram();   //送入内存
    }
    			    return 0;
}

