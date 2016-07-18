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
 * helloworld.c: simple test application
 */




#include <stdio.h>
#include "fraps.h"
#include "platform.h"
#include "xparameters.h"

void print(char *str);

int main()
{
	int source_word = 0xDEADBEEF;
	int hello[10] = {0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xBEEFDEAD, 0xBEEFDEAD, 0xBEEFDEAD, 0xBEEFDEAD, 0xBEEFDEAD};
	int destination_word = 0x0;
	int dest_hello[10] = {0,0,0,0,0,0,0,0,0,0};
	int i = 0;

    init_platform();

    print("Hello World\n\r");
    cleanup_platform();
    printf("Printing value before DMA transfer.\n\r");
    for(i = 0; i < 10; i++)
	{
		xil_printf("%x\r\n", dest_hello[i]);
	}

    FRAPS_mWriteReg(XPAR_FRAPS_0_BASEADDR,FRAPS_SLV_REG0_OFFSET, &hello );
    FRAPS_mWriteReg(XPAR_FRAPS_0_BASEADDR,FRAPS_SLV_REG1_OFFSET, &dest_hello);
    FRAPS_mWriteReg(XPAR_FRAPS_0_BASEADDR,FRAPS_SLV_REG2_OFFSET, 1-1);

    //FRAPS_MasterRecvWord(XPAR_FRAPS_0_BASEADDR, (Xuint32) &source_word);
    //FRAPS_MasterSendWord(XPAR_FRAPS_0_BASEADDR, (Xuint32) &destination_word);

    Xil_Out16(XPAR_FRAPS_0_BASEADDR+FRAPS_MST_BE_REG_OFFSET, 0xFFFF);
    Xil_Out8(XPAR_FRAPS_0_BASEADDR+FRAPS_MST_GO_PORT_OFFSET, MST_START);

    printf("Printing value after DMA transfer.\n\r");
    for(i = 0; i < 10; i++)
    {
    	xil_printf("%x\r\n", dest_hello[i]);
    }

//    cleanup_platform();

    return 0;
}
