/*
 * led.c
 *
 *  Created on: 2017-3-21
 *      Author: Shaw
 */
#include "Module_Project.h"

void GPIO_INit(void)
{
	   // GPAPUD  --0 Enable       1    Disable    (default for GPIO12-GPIO44=0)
	   //                                                             (default for GPIO0-GPIO11=1)
	   // GPAMUXx --0 GPIO       other  Function   (default=0)
	   // GPADIR  --0 Input        1    Output     (default=0)
	EALLOW;
	   //GPIO0----PWMA
	   GpioCtrlRegs.GPAPUD.bit.GPIO0     		= 1;      // Disable  pull-up on GPIO0
	   GpioCtrlRegs.GPAMUX1.bit.GPIO0    		= 1;      // Configure GPIO0 as EPWM1A
	   //GPIO1----PWMB
	   GpioCtrlRegs.GPAPUD.bit.GPIO1     		= 1;      // Disable pull-up on GPIO1
	   GpioCtrlRegs.GPAMUX1.bit.GPIO1    		= 1;      // Configure GPIO1 as EPWM1B
	   //GPIO2----PWMC_Unused
	   GpioCtrlRegs.GPAPUD.bit.GPIO2     		= 1;      // Disable  pull-up on GPIO2
	   GpioDataRegs.GPACLEAR.bit.GPIO2   	= 1;      // Load output latch low
	   GpioCtrlRegs.GPAMUX1.bit.GPIO2    		= 1;      // Configure GPIO2 as GPIO2
	   GpioCtrlRegs.GPADIR.bit.GPIO2     		= 0;      // Direction is is

	   //GPIO3----PWMD_Unused
	   GpioCtrlRegs.GPAPUD.bit.GPIO3  		= 1;      // Disable  pull-up on GPIO3
	  GpioDataRegs.GPACLEAR.bit.GPIO3   	= 1;      // Load output latch low
	  GpioCtrlRegs.GPAMUX1.bit.GPIO3    		= 1;      // Configure GPIO3 as GPIO3
	  GpioCtrlRegs.GPADIR.bit.GPIO3     		= 1;      // Direction is output

	 //GPIO4----emergence stop
	  GpioCtrlRegs.GPAPUD.bit.GPIO4     		= 1;      // Disable  pull-up on GPIO4
	  GpioDataRegs.GPACLEAR.bit.GPIO4   	= 1;      // Load output latch low
	  GpioCtrlRegs.GPAMUX1.bit.GPIO4    		= 0;      // Configure GPIO4 as GPIO4
	  GpioCtrlRegs.GPADIR.bit.GPIO4    		= 0;      // Direction is output
	//GPIO5----FAN Control
	  GpioCtrlRegs.GPAPUD.bit.GPIO5     		= 1;      // Disable  pull-up on GPIO5
	  GpioDataRegs.GPACLEAR.bit.GPIO5   	= 1;      // Load output latch low
	  GpioCtrlRegs.GPAMUX1.bit.GPIO5    		= 0;      // Configure GPIO5 as GPIO5
	  GpioCtrlRegs.GPADIR.bit.GPIO5     		= 1;      // Direction is output

	 //GPIO6----ZigBee_WAKE
	  GpioCtrlRegs.GPAPUD.bit.GPIO6     		= 1;      // Disable  pull-up on GPIO6
	  GpioDataRegs.GPASET.bit.GPIO9             = 1;	     // Load output latch high
	  GpioCtrlRegs.GPAMUX1.bit.GPIO6    		= 0;      // Configure GPIO6 as GPIO6
	  GpioCtrlRegs.GPADIR.bit.GPIO6     		= 1;      // Direction is output
	   //GPIO9----ZigBee_RST
	   GpioCtrlRegs.GPAPUD.bit.GPIO9     		= 1;      // Disable  pull-up on GPIO9
	   GpioDataRegs.GPASET.bit.GPIO9            = 1;	     // Load output latch High
	   GpioCtrlRegs.GPAMUX1.bit.GPIO9    		= 0;      // Configure GPIO9 as GPIO9
	   GpioCtrlRegs.GPADIR.bit.GPIO9     		= 1;      // Direction is output
	   //GPIO28---ZigBee_RX(SCI-A)
	   GpioCtrlRegs.GPAPUD.bit.GPIO28    		= 0;      // Disable  pull-up on GPIO28
	   GpioCtrlRegs.GPAMUX2.bit.GPIO28   	= 1;      // Configure GPIO28 as SCIRX
	   GpioCtrlRegs.GPAQSEL2.bit.GPIO28         = 3;     // Asynch input GPIO28 (SCIRXDA)
	   //GPIO29---ZigBee_TX(SCI-A)
	   GpioCtrlRegs.GPAPUD.bit.GPIO29    		= 0;      // Enable  pull-up on GPIO29
	   GpioCtrlRegs.GPAMUX2.bit.GPIO29   	= 1;      // Configure GPIO29 as SCITX
	   GpioCtrlRegs.GPAQSEL2.bit.GPIO29  	= 3;      // Asynch input

	 //GPIO7----Switch -3
	  GpioCtrlRegs.GPAPUD.bit.GPIO7    		= 1;      // Disable  pull-up on GPIO7
	  GpioCtrlRegs.GPAMUX1.bit.GPIO7    		= 0;      // Configure GPIO7 as GPIO7
	  GpioCtrlRegs.GPADIR.bit.GPIO7     		= 0;      // Direction is input
	  GpioCtrlRegs.GPAQSEL1.bit.GPIO7           = 0;   // 引脚采样与系统时钟同步
	 //GPIO8----Switch -1
	  GpioCtrlRegs.GPAPUD.bit.GPIO8    		= 1;      // Disable  pull-up on GPIO8
	  GpioCtrlRegs.GPAMUX1.bit.GPIO8    		= 0;      // Configure GPIO8 as GPIO8
	  GpioCtrlRegs.GPADIR.bit.GPIO8     		= 0;      // Direction is input
	  GpioCtrlRegs.GPAQSEL1.bit.GPIO8           = 0;   // 引脚采样与系统时钟同步
	   //GPIO12---Switch -2
	   GpioCtrlRegs.GPAPUD.bit.GPIO12    		= 1;      // Disable pullup on GPIO12
	   GpioCtrlRegs.GPAMUX1.bit.GPIO12   	= 0;      // Configure GPIO12 as GPIO
	   GpioCtrlRegs.GPADIR.bit.GPIO12    		= 0;      // Direction is input
	   GpioCtrlRegs.GPAQSEL1.bit.GPIO12        = 0;   // 引脚采样与系统时钟同步
	   //GPIO22---Switch -4
	   GpioCtrlRegs.GPAPUD.bit.GPIO22    		= 1;      // Disable  pull-up on GPIO22
	   GpioCtrlRegs.GPAMUX2.bit.GPIO22   	= 0;      // Configure GPIO22 as GPIO
	   GpioCtrlRegs.GPADIR.bit.GPIO22    		= 0;      // Direction is input
	   GpioCtrlRegs.GPAQSEL2.bit.GPIO22        = 0;   // 引脚采样与系统时钟同步

	   //GPIO10---PFC_CLS
	   GpioCtrlRegs.GPAPUD.bit.GPIO10    		= 1;      // Disable  pull-up on GPIO10
	   GpioDataRegs.GPACLEAR.bit.GPIO10   	= 1;      // Load output latch low
	   GpioCtrlRegs.GPAMUX1.bit.GPIO10   	= 0;      // Configure GPIO10 as GPIO10
	   GpioCtrlRegs.GPADIR.bit.GPIO10     		= 1;      // Direction is output
	   //GPIO11---Relay-Control
	   GpioCtrlRegs.GPAPUD.bit.GPIO11    	 	= 0;      	// Ensable  pull-up on GPIO11
	   GpioCtrlRegs.GPAMUX1.bit.GPIO11     	= 0;      	// Configure GPIO11 as GPIO11
	   GpioCtrlRegs.GPADIR.bit.GPIO11     	 	= 1;      	// Direction is output
	   GpioDataRegs.GPACLEAR.bit.GPIO11       = 1;      // Load output latch low


	   //GPIO13 GPIO14 GPIO15-- Have NO!

	   //GPIO16---LED1_3.3V
	   GpioCtrlRegs.GPAPUD.bit.GPIO16    		= 0;      // Enable pullup on GPIO16
	   GpioDataRegs.GPASET.bit.GPIO16          = 1;              // Load output latch high
	   GpioCtrlRegs.GPAMUX2.bit.GPIO16   	= 0;      // Configure GPIO16 as GPIO
	   GpioCtrlRegs.GPADIR.bit.GPIO16    		= 1;      // Direction is output
	   //GPIO34---LED2
	   GpioCtrlRegs.GPBPUD.bit.GPIO34    		= 1;      // Disable pullup on GPIO34
	   GpioCtrlRegs.GPBMUX1.bit.GPIO34   	= 0;      // Configure GPIO34 as GPIO34
	   GpioCtrlRegs.GPBDIR.bit.GPIO34    		= 1;      // Direction is input
	   GpioDataRegs.GPBSET.bit.GPIO34          = 1;


	   //GPIO34---LED2
	   GpioCtrlRegs.GPBPUD.bit.GPIO43   		= 1;      // Disable pullup on GPIO34
	   GpioCtrlRegs.GPBMUX1.bit.GPIO43   	= 0;      // Configure GPIO34 as GPIO34
	   GpioCtrlRegs.GPBDIR.bit.GPIO43   		= 1;      // Direction is input
	   GpioDataRegs.GPBSET.bit.GPIO43          = 0;


	   //GPIO17---DRModul_Fualt
	   GpioCtrlRegs.GPAPUD.bit.GPIO17    		= 0;      // Enable pullup on GPIO17
	   GpioDataRegs.GPACLEAR.bit.GPIO17  	= 1;      // Load output latch low
	   GpioCtrlRegs.GPAMUX2.bit.GPIO17   	= 0;      // Configure GPIO17 as GPIO
	   GpioCtrlRegs.GPADIR.bit.GPIO17    		= 0;      // Direction is input
	   GpioCtrlRegs.GPAQSEL2.bit.GPIO17  	= 3;      // asynch input

	   //GPIO18 19---USART_TX  USART_RX
		GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;		// Enable pull-up for GPIO22 (LIN TX)
		GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;		// Enable pull-up for GPIO23 (LIN RX)
		GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;  // Asynch input GPIO23 (LINRXA)
		GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;   // Configure GPIO19 for LIN TX operation	 (3-Enable,0-Disable)
		GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;   // Configure GPIO23 for LIN RX operati

	   //GPIO20---Flash_SDI_Unused
	   GpioCtrlRegs.GPAPUD.bit.GPIO20    		= 1;      // Disable  pull-up on GPIO20
	   GpioDataRegs.GPACLEAR.bit.GPIO20  	= 1;      // Load output latch low
	   GpioCtrlRegs.GPAMUX2.bit.GPIO20   	= 0;      // Configure GPIO20 as GPIO
	   GpioCtrlRegs.GPADIR.bit.GPIO20    		= 1;      // Direction is output
	   //GPIO21---Flash_CLK_Unused
	   GpioCtrlRegs.GPAPUD.bit.GPIO21    		= 1;      // Disable pullup on GPIO21
	   GpioDataRegs.GPACLEAR.bit.GPIO21  	= 1;      // Load output latch low
	   GpioCtrlRegs.GPAMUX2.bit.GPIO21   	= 0;      // Configure GPIO21 as GPIO
	   GpioCtrlRegs.GPADIR.bit.GPIO21    		= 1;      // Direction is output
	   //GPIO23---Flash_CS_Unused
	   GpioCtrlRegs.GPAPUD.bit.GPIO23    		= 1;      // Disable pullup on GPIO23
	   GpioDataRegs.GPACLEAR.bit.GPIO23  	= 1;      // Load output latch low
	   GpioCtrlRegs.GPAMUX2.bit.GPIO23   	= 0;      // Configure GPIO23 as GPIO
	   GpioCtrlRegs.GPADIR.bit.GPIO23    		= 1;      // Direction is output
	   //GPIO24---Flash_SDO_Unused
	   GpioCtrlRegs.GPAPUD.bit.GPIO24    		= 1;      // Enable pullup on GPIO24
	   GpioDataRegs.GPACLEAR.bit.GPIO24  	= 1;      // Load output latch low
	   GpioCtrlRegs.GPAMUX2.bit.GPIO24   	= 0;      // Configure GPIO24 as GPIO
	   GpioCtrlRegs.GPADIR.bit.GPIO24    		= 1;      // Direction is output

	   //GPIO25,GPIO26,GPIO27--- Have NO!

	   //GPIO30 GPIO31---(CANTXA CANRXA)GPIO
	   GpioCtrlRegs.GPAPUD.bit.GPIO30    		= 0;      // Enable pullup on GPIO30
	   GpioCtrlRegs.GPAPUD.bit.GPIO31    		= 0;      // Enable pullup on GPIO31
	   GpioCtrlRegs.GPAMUX2.bit.GPIO30   		= 1;      // Configure GPIO30 as CANTXA
	   GpioCtrlRegs.GPAMUX2.bit.GPIO31   		= 1;      // Configure GPIO31 as CANRXA
	   GpioCtrlRegs.GPAQSEL2.bit.GPIO31  		= 3;      // Asynch input
	   //GPIO32---RTC_SDAA_Unused
	   GpioCtrlRegs.GPBPUD.bit.GPIO32    		= 1;      // Disable pullup on GPIO32
	   GpioDataRegs.GPBCLEAR.bit.GPIO32  		= 1;      // Load output latch low
	   GpioCtrlRegs.GPBMUX1.bit.GPIO32   		= 0;      // Configure GPIO32 as GPIO
	   GpioCtrlRegs.GPBDIR.bit.GPIO32    			= 1;      // Direction is output
	   //GPIO33---RTC_SCLA_Unused
	   GpioCtrlRegs.GPBPUD.bit.GPIO33    		= 1;      // Disable pullup on GPIO33
	   GpioDataRegs.GPBCLEAR.bit.GPIO33  		= 1;      // Load output latch low
	   GpioCtrlRegs.GPBMUX1.bit.GPIO33   		= 0;      // Configure GPIO33 as GPIO
	   GpioCtrlRegs.GPBDIR.bit.GPIO33    			= 1;      // Direction is output

	   EDIS;

}

/*-----------------------------------------------------------
 *自锁型按键慢速扫描
 *会有一个扫描周期的延时反应
 *GPIO 0 1 3 22 ---------- 1  2  4  8
 *---------------------------------------------------------*/
void DIP_Scan(void)
{
	key=0x00;
	if((DIP0()==0||DIP1()==0||DIP2()==0||DIP3()==0))
	{
		if(DIP0()==0)     {
			key|=0x01; //0
		}
		else if(DIP1()==0){
			key|=0x02; //1
		}
		else if(DIP2()==0){
			key|=0x04; //3
		}
		else if(DIP3()==0){
			key|=0x08; //22
		}
	}else{
		key=0x00;
	}
}
//发射端快速扫描
unsigned char STOP_Scan(void)
{
//发射端驱动异常检测
	if(qdyckey()==0){
		return Excep_qdyc;
	}
	return 0;
}

