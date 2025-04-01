/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h" // Parameter definitions for processor periperals
#include "xscugic.h"     // Processor interrupt controller device driver
#include "xil_cache.h"
#include "xfpga417_fir_hw.h"
#include "xfpga417_fir.h"

//Instance Varible to Keep Reference to the HW
XFpga417_fir XFpga417_fir_inst;

void system_init();
void system_deinit();

int fpga417_init(XFpga417_fir *xFpga417_fir);
void fpga417_start(void *InstancePtr);

int run_hardware();

//Keep these small till further notice -- odd bug with the arm core...
#define DATA_LENGTH 1000
#define FILTER_LENGTH 3

int main()
{
	system_init();
	//Initialize the IP Core
	int status;
    //Setup the matrix mult
    status = fpga417_init(&XFpga417_fir_inst);
	if(status != XST_SUCCESS){
	  print("HLS peripheral setup failed\n\r");
	  exit(-1);
	}
	//TODO: Prepare the data to send to the hardware
	//Hint: Inialize 2 arrays (1 filter, 1 data)
	printf("Initializing Filter and Image\n");

	int length;
	int kernel_length

	int input []={};
	int coef  []={};


	u32 * INPUT_BUFFER = XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x20000; //locate a memory reserved for AXI peripherals
	u32 * KERNEL_BUFFER = XPAR_PS7_DDR_0_S_AXI_BASEADDR;


	 memset(INPUT_BUFFER, 0,length<<2 );
	 memset(KERNEL_BUFFER, 0, kernel_length<<2); //clear buffer


	for (int i=0;i<length;i++)
	{
		INPUTBUFFER[i]=............// ASSIGN VALUES TO INPUT BUFFERS, DO SIMILAR THINGS FOR KERNEL_BUFFER
				//.........
	}




	//Set the data variables of the arguments to the HW function
	//HINT: The prototype for the functions thtat set your defined arguments are located in the xfpga417_fir.h file

	XFpga417_fir_Set_input_r(&XFpga417_fir_inst, INPUT_BUFFER);//DO SIMILAR THINGS FOR OTHER ARGUMENTS


	printf("%d",input[3]);

	int err = run_hardware(); //when this function returns the result is ready
	//TODO: Compare results to a similar software functinon, print out the array etc...


	system_deinit();
    return 0;
}
void system_deinit()
{
	printf("Cleaning up...\n");
    cleanup_platform();
}
void system_init()
{
    printf("Initializing Zynq Processing System\n");
	init_platform();
	Xil_DCacheEnable();
	srand(0);
	printf("System Initialization Complete..\n");
}
int run_hardware()
{
	Xil_DCacheFlush();
	if (XFpga417_fir_IsReady(&XFpga417_fir_inst))
	  print("HLS peripheral is ready.  Starting... ");
	else {
	  print("!!! HLS peripheral is not ready! Exiting...\n\r");
	  return 1;
	}
	XFpga417_fir_Start(&XFpga417_fir_inst);
	int c = 0;
	while(!XFpga417_fir_IsReady(&XFpga417_fir_inst)){
	   printf("waiting for complete...%i\r", ++c);
	}
	Xil_DCacheInvalidate();
	return 0;
}
int fpga417_init(XFpga417_fir *fpga_417_ptr)
{
	XFpga417_fir_Config *cfgPtr;
	int status;
	printf("Initializing Accelerator\n");
	cfgPtr = XFpga417_fir_LookupConfig(XPAR_FPGA417_FIR_0_DEVICE_ID);
	if (!cfgPtr) {
	  fprintf(stderr, "ERROR: Lookup of acclerator configuration failed.\n\r");
	  return XST_FAILURE;
	}
	print("SUCCESS: Lookup of acclerator configuration succeeded.\n\r");
	status = XFpga417_fir_CfgInitialize(fpga_417_ptr, cfgPtr);
	if (status != XST_SUCCESS) {
	  print("ERROR: Could not initialize accelerator.\n\r");
	  return XST_FAILURE;
	}
	print("SUCCESS: initialized accelerator.\n\r");
	return status;
}
void fpga417_start(void *InstancePtr)
{
	XFpga417_fir *pAccelerator = (XFpga417_fir *)InstancePtr;
	XFpga417_fir_InterruptEnable(pAccelerator,1);
	XFpga417_fir_InterruptGlobalEnable(pAccelerator);
	XFpga417_fir_Start(pAccelerator);
}
