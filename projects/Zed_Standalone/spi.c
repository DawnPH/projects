#include "SPI.h"
#include "sleep.h"



void delayspi(u8 time)
{
	for(;time>0;time--);

}
void  spi_out_byt(u8 outbyte)       //写入一个字节
{
   u8 i;
   for(i=0;i<8;i++)
   {

        if((outbyte&0x80)!=0)  SPI_DAOUT_H;//IOSET=ADC_MOSI;
        else                   SPI_DAOUT_L;//IOCLR=ADC_MOSI;
        SPI_SCL_H;// IOSET=ADC_SCLK;
       //  delaymax1230(1);
        SPI_SCL_L;//IOCLR=ADC_SCLK;
        outbyte=outbyte<<1;
        // delaymax1230(1);
   }
}

u16 spi_input_byt(void)           //读出一个字节
{
   u8  i;
   u16  bbyte=0;
   u8 flagtest=0;
   for(i=0;i<16;i++)
   {

	   delayspi(10);
	   SPI_SCL_L;// IOSET=ADC_SCLK;
        // delaymax1230(1);
	   delayspi(10);
	   flagtest=SPI_DA_READ;
        if((flagtest&0X01)!=0)
            bbyte=bbyte|0x01;         //输出信号在下降沿移出
        else
            bbyte=bbyte&0xFFFE;
        bbyte=bbyte<<1;
        SPI_SCL_H;// IOCLR=ADC_SCLK;
        delayspi(10);

   }

   bbyte=bbyte>>1;
   return  bbyte;
}


u8 LightData(void)
{
	u8  Ldata=0;
	u16 ADdata=0;
	SPI_CS_H;
	SPI_SCL_H;
	usleep(1);
	SPI_CS_L;
	usleep(1);
	ADdata=spi_input_byt();
	usleep(1);
	SPI_CS_H;
	ADdata=(ADdata&0x0ff0)>>4;
	Ldata=(u8)ADdata;

	return  Ldata;

}

