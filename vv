#include <reg51.h>
unsigned char DisplayBuf[8];
unsigned char code CharCode[]=
{
0xc0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E
};

void Delay(void)
{
  int i;
  i=100;
  while(i--);
}

void main(void)
{
 unsigned char i,pos;
 
 P0=0;
 P1=0xff;
 for(i=0;i<8;i++)
 DisplayBuf[i]=i;
 
 while(1)
{
 pos=0x80;
 for(i=0;i<8;i++)
 {
  P1=CharCode[DisplayBuf[i]];
  P0=pos;
  pos>>=1;
  Delay();
 }
}
}
			
