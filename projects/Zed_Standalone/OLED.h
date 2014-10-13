
#ifndef OLED_H
#define OLED_H


/****************** Include Files ********************/
#include "xbasic_types.h"
#include "xstatus.h"
#include "xil_io.h"
#include "sleep.h"
#include "xparameters.h"

#define OLED_DC			0
#define OLED_RES		1
#define OLED_SCLK		2
#define OLED_SDIN		3
#define OLED_VBAT		4
#define OLED_VDD		5
//Xil_Out32(OLED_BASE_ADDR,1<<i);

#define OLED_BASE_ADDR XPAR_OLED_0_S00_AXI_BASEADDR


// DC
#define Set_OLED_DC  (Xil_Out32(OLED_BASE_ADDR,Xil_In32(OLED_BASE_ADDR)|(1<<OLED_DC)))
#define Clr_OLED_DC  (Xil_Out32(OLED_BASE_ADDR,Xil_In32(OLED_BASE_ADDR)&(~(1<<OLED_DC))))
// RES
#define Set_OLED_RES  (Xil_Out32(OLED_BASE_ADDR,Xil_In32(OLED_BASE_ADDR)|(1<<OLED_RES)))
#define Clr_OLED_RES  (Xil_Out32(OLED_BASE_ADDR,Xil_In32(OLED_BASE_ADDR)&(~(1<<OLED_RES))))

// SCLK
#define Set_OLED_SCLK  (Xil_Out32(OLED_BASE_ADDR,Xil_In32(OLED_BASE_ADDR)|(1<<OLED_SCLK)))
#define Clr_OLED_SCLK  (Xil_Out32(OLED_BASE_ADDR,Xil_In32(OLED_BASE_ADDR)&(~(1<<OLED_SCLK))))
// SDIN
#define Set_OLED_SDIN  (Xil_Out32(OLED_BASE_ADDR,Xil_In32(OLED_BASE_ADDR)|(1<<OLED_SDIN)))
#define Clr_OLED_SDIN  (Xil_Out32(OLED_BASE_ADDR,Xil_In32(OLED_BASE_ADDR)&(~(1<<OLED_SDIN))))
// OLED_VBAT
#define Set_OLED_VBAT  (Xil_Out32(OLED_BASE_ADDR,Xil_In32(OLED_BASE_ADDR)|(1<<OLED_VBAT)))
#define Clr_OLED_VBAT  (Xil_Out32(OLED_BASE_ADDR,Xil_In32(OLED_BASE_ADDR)&(~(1<<OLED_VBAT))))

// OLED_VDD
#define Set_OLED_VDD  (Xil_Out32(OLED_BASE_ADDR,Xil_In32(OLED_BASE_ADDR)|(1<<OLED_VDD)))
#define Clr_OLED_VDD  (Xil_Out32(OLED_BASE_ADDR,Xil_In32(OLED_BASE_ADDR)&(~(1<<OLED_VDD))))


//OLED
void write_data(u8 data);
void write_cmd(u8 data);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);

void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const char *p);

#endif // OLED_H
