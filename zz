#include<reg51.h>
#include<stdio.h>
#define OSC 11059200
#define BAUDRATE 9600
sbit BUZ_CON=P3^7;

void Delay1ms(int ms)
{
	int i;
	while(ms--)
	for(i=0;i<100;i++);
}

main(void)
{
	unsigned char Mask,ScanCode,Line,Col,i;
	TMOD=0x20;
	PCON|=0x80;
	SCON=0x50;
	TH1=256-(OSC/12/16/BAUDRATE);
	TL1=256-(OSC/12/16/BAUDRATE);
	TR1=1;
	TI=1;
	printf("\r\nKey pad 4X4 test running...");
	printf("\r\nKey pad 4X4 test running...");

	while(1)
	{
		P1=0xff;
		Line=1;
		Mask=0x01;
		for(i=0;i<4;i++)
		{
			Col=0;
			P1=~Mask;
			ScanCode=P1&0xf0;
			if(ScanCode!=0xf0)
			{
				BUZ_CON=0;
				Delay1ms(20);
				BUZ_CON=1;
			}
			ScanCode=P1&0xf0;
			switch(ScanCode)
			{
				case 0xe0:Col=1;
					break;
				case 0xd0:Col=2;
					break;
				case 0xb0:Col=3;
					break;
				case 0x70:Col=4;
					break;
				default:Col=0;
					break;
			}
			if(Col>0)
			{
				printf("\r\nKey pressed:Line=%bd,Column=%bd",Line,Col);
				while(1)
				{
					ScanCode=P1&0xf0;
					if(ScanCode==0xf0)break;
				}
			}
			Mask<<=1;
			Line++;
		}
	}
}
