/*
 * spi.h
 *
 *  Created on: 2014-4-25
 *      Author: chenxi
 */

#ifndef SPI_H_
#define SPI_H_
#include "xbasic_types.h"
XGpio Gpio;
#define	SPI_DAOUT_H 	XGpio_DiscreteSet(&Gpio, 1, 1<<1)
#define	SPI_DAOUT_L		XGpio_DiscreteClear(&Gpio, 1, 1<<1)
#define SPI_SCL_H		XGpio_DiscreteSet(&Gpio, 1, 1<<3)
#define SPI_SCL_L    	XGpio_DiscreteClear(&Gpio, 1, 1<<3)
#define SPI_CS_H		XGpio_DiscreteSet(&Gpio, 1, 1<<2)
#define SPI_CS_L    	XGpio_DiscreteClear(&Gpio, 1, 1<<2)
#define SPI_DA_READ     (u8)XGpio_DiscreteRead(&Gpio, 1)

void  spi_out_byt(u8 outbyte);
u16 spi_input_byt(void) ;
void delayspi(u8 time);
u8 LightData(void);
#endif /* SPI_H_ */
