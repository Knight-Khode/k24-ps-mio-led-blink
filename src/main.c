#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpiops.h"
#include "xparameters.h"

//Creating GPIO instance
XGpioPs gpio;

//GPIO Configuration Structure
XGpioPs_Config *gpio_config;

void gpio_init(){
    gpio_config = XGpioPs_LookupConfig(0);

    int status = XGpioPs_CfgInitialize(
        &gpio,
        gpio_config,
        XPAR_XGPIOPS_0_BASEADDR);

    if(status == XST_SUCCESS)
		xil_printf("GPIO INIT SUCCESSFUL\n");
	else
		xil_printf("GPIO INIT FAILED\n");
}

int main()
{
    init_platform();
    gpio_init();
    XGpioPs_SetDirectionPin(&gpio, 27, 1);

    print("Hello World\n\r");
    print("Successfully ran Hello World application");

     while(1){
    	XGpioPs_WritePin(&gpio, 27, 1);
    	sleep(1);
    	XGpioPs_WritePin(&gpio, 27, 0);
    	sleep(1);
    }
    cleanup_platform();
    return 0;
}
