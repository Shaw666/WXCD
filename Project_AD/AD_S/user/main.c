/*
 * main.c
 *  发射端程序 V1.0
 *  Created on: 2017-3-20
 *      Author: Shaw
 */

//GpioDataRegs.GPASET.bit.GPIO5 = 1;   //发射端温度过高拉高打开风扇
//GpioDataRegs.GPASET.bit.GPIO11 = 1;  //检测到输入电压高于350V拉高，闭合继电器
#include "Module_Project.h"

Uint16 Error;
Uint16 Tmp = 0, i = 180;
u8 key = 0;
extern Uint16 RamfuncsLoadSize;

void main(void) {
	InitSysCtrl();
	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
	memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32) &RamfuncsLoadSize);
	GPIO_INit();   //初始化GPIO 区别收发
	ADC_Config();
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	EDIS;
	Timer0_init(); //初始化定时器0用于定时处理相关任务
//	Timer1_init(); //初始化定时器1用于定时处理PID 区别收发
	SCI_Init(115200);   //初始化SCI
	SetupSCI(115200);
	ZM5168_INit();              //初始化zm5168_P0模块
//	open_uart_debug();
//	InitI2C_Gpio();             //io 初始化为IIC
//	I2CA_Init();                //HW IIC初始化，100KHz
	EPWMB_Config(1500);
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;
	//中断配置步骤-----5
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
	EINT;
	// Enable Global interrupt INTM
	ERTM;
//	AdcRegs.ADCSOCFRC1.all = 0X035E; //软件触发AD 的 SOC0--SOC3采样
//	DIP_Scan();   //开机扫描一次拨码开关
//	GpioDataRegs.GPBTOGGLE.bit.GPIO43 	= 1;
	while (1) {
		if (timer0Base.Mark_Para.Status_Bits.OnemsdFlag == 1) {
			timer0Base.Mark_Para.Status_Bits.OnemsdFlag = 0;

			if (STOP_Scan() == Excep_qdyc) {   //驱动异常 拉低所有PWM切断
//    			EPwm1Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    			EPwm1Regs.AQSFRC.bit.RLDCSF =0x03;
    			EPwm1Regs.AQCSFRC.bit.CSFA = 0x01;
    			EPwm1Regs.AQCSFRC.bit.CSFB = 0x01;
			}
			if (timer0Base.msCounter%100==0) {

//				Upper_Uart();
			}
			if (timer0Base.msCounter >= 200) {

				GpioDataRegs.GPBTOGGLE.bit.GPIO43 	= 1;
				timer0Base.msCounter=0;
				switch (key) {
				case 0x01: {
					break;
				}
				case 0x02: {
					break;
				}
				case 0x04: {
					break;
				}
				case 0x08: {
					break;
				}
				}
			}
		}

	}
}

//===========================================================================
// No more.
//===========================================================================

