/*
 * AMP.h
 *
 *  Created on: 2014-3-31
 *      Author: Administrator
 */
 
 /**
		处理器数据交互
 **/

#ifndef AMP_H_
#define AMP_H_

#include "xparameters.h"
#include <stdio.h>
#include "xil_io.h"
#include "xil_mmu.h"
#include "xil_cache.h"
#include "xil_printf.h"
#include "xil_exception.h"
#include "xscugic.h"
#include "sleep.h"
#include "xpseudo_asm.h"

/**************************** Type Definitions *******************************/

#ifdef XPAR_INTC_0_DEVICE_ID
#define INTC		    XIntc
#define INTC_HANDLER	XIntc_InterruptHandler
#else
#define INTC		    XScuGic
#define INTC_HANDLER	XScuGic_InterruptHandler
#endif /* XPAR_INTC_0_DEVICE_ID */



#define INTC_DEVICE_ID	    XPAR_PS7_SCUGIC_0_DEVICE_ID
#define PL_IRQ_ID           XPS_IRQ_INT_ID

#define IRQ_PCORE_GEN_BASE  XPAR_IRQ_GEN_0_BASEADDR

#define COMM_VAL        (*(volatile unsigned long *)(0xFFFF8000))

#define COMM_TX_FLAG    (*(volatile unsigned long *)(0xFFFF9000))
#define COMM_TX_DATA    (*(volatile unsigned long *)(0xFFFF9004))
#define COMM_RX_FLAG    (*(volatile unsigned long *)(0xFFFF9008))
#define COMM_RX_DATA    (*(volatile unsigned long *)(0xFFFF900C))

#define UART_TX_FLAG    (*(volatile unsigned long *)(0xFFFFC000))
//标志寄存器，有 0 和 1 两种状态
//当被设为 1 则代表数据已被 CPU0 写入数据发送寄存器，等待 CPU1 读取
//当清 0 则代表数据已被 CPU1 取走，CPU0 可以写入新数据
#define UART_TX_DATA    (*(volatile unsigned long *)(0xFFFFC004))
//数据传送寄存器，每次可传送 4 字节 0->1
#define UART_RX_FLAG    (*(volatile unsigned long *)(0xFFFFC008))
//数据接收标志寄存器，有 0 和 1 两种状态
//当被设为 1 则代表数据已被 CPU1 写入数据接收寄存器，等待 CPU0 读取
//当清 0 则代表数据已被 CPU0 取走，CPU1 可以写入新数据
#define UART_RX_DATA    (*(volatile unsigned long *)(0xFFFFC00C))
//数据接收寄存器，用于 CPU1 向 CPU0 传入数据，每次可传送 4 字节



/**
 * This typedef contains configuration information for the device driver.
 */
typedef struct {
	u16 DeviceId;		/**< Unique ID of device */
	u32 BaseAddress;	/**< Base address of the device */
} Pl_Config;


/**
 * The driver instance data. The user is required to allocate a
 * variable of this type.
 * A pointer to a variable of this type is then passed to the driver API
 * functions.
 */
typedef struct {
	Pl_Config Config;   /**< Hardware Configuration */
	u32 IsReady;		/**< Device is initialized and ready */
	u32 IsStarted;		/**< Device is running */
} XPlIrq;



void        Xil_L1DCacheFlush(void);


extern u32 MMUTable;

/**
 * Assign the driver structures for the interrupt controller and
 * PL Core interrupt source
 */
INTC   IntcInstancePtr;
XPlIrq PlIrqInstancePtr;


/**
 * Modified DCacheFlush to prevent L2 Cache controller access
 */
void MyXil_DCacheFlush(void)
{
	Xil_L1DCacheFlush();
	//Xil_L2CacheFlush();
}

/**
 * Modified SetTlbAttributes to call MyXil_DCacheFlush in order
 * to prevelt L2 Cache controller accesses
 */
void MyXil_SetTlbAttributes(u32 addr, u32 attrib)
{
	u32 *ptr;
	u32 section;

	mtcp(XREG_CP15_INVAL_UTLB_UNLOCKED, 0);
	dsb();

	mtcp(XREG_CP15_INVAL_BRANCH_ARRAY, 0);
	dsb();
	MyXil_DCacheFlush();

	section = addr / 0x100000;
	ptr = &MMUTable + section;
	*ptr = (addr & 0xFFF00000) | attrib;
	dsb();
}

/*
 * Function to send data to OCM which is consumed by Linux Application
 */
void myPutchar(char c) {

	while(COMM_TX_FLAG);	//wait for cpu0 to consume previous value
	COMM_TX_DATA = (volatile unsigned long)c;
	dmb();
	COMM_TX_FLAG = 1;

}

/*
 * Since there is no STDIO assigned to the BSP, outbyte() is not created
 * by libgen. So add outbyte() call to myPutchar() to enable STDOUT functionality
 * for print() and xil_printf()
 */void outbyte(char c) {
	myPutchar(c);
}

#endif /* AMP_H_ */
