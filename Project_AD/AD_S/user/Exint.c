/*
 * ad.h
 *
 *  Created on: 2017-3-20
 *      Author: Shaw
 */
#include "Module_Project.h"


interrupt void xint1_isr(void);
interrupt void xint2_isr(void);


//###########################################################################
//外部中断，下降沿检测
//开启XINT1外部中断
//急停中断
//---------------------------------------------------------------------------------------------
void ExInt_Init(void)
{
	EALLOW;									//GPIO寄存器受保护
	GpioCtrlRegs.GPAMUX1.bit.GPIO4= 0;		//GPIO6作为普通IO
	GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;		//GPIO6方向为输入
	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;		//开启内部上拉
	GpioCtrlRegs.GPAQSEL1.bit.GPIO4 = 0;   // 引脚采样与系统时钟同步

	GpioCtrlRegs.GPAMUX2.bit.GPIO17= 0;		//GPIO17作为普通IO
	GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;		//GPIO17方向为输入
	GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;		//开启内部上拉
	GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 0;   // 引脚采样与系统时钟同步
	EDIS;

	//中断配置步骤-----2，重映射中断服务函数
	EALLOW;	
    PieVectTable.XINT1 = &xint1_isr;
	EDIS;
	//中断配置步骤-----3，连接CPU中断Y
	IER |= M_INT1;
	//中断配置步骤-----4，连接Y中断里的第几位
	PieCtrlRegs.PIEIER1.bit.INTx4 = 1;          // Enable PIE Gropu 1 INT4   //XINT1
    // Enable CPU INT1
	EALLOW;
	GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 4;
	EDIS;
	XIntruptRegs.XINT1CR.bit.POLARITY = 0;      // 1为上升沿，0和2为下降沿，3为双边沿
	//中断配置步骤-----1,开启模块中断使能，
	XIntruptRegs.XINT1CR.bit.ENABLE = 1;         // Enable XINT1

	//中断配置步骤-----2，重映射中断服务函数
	EALLOW;
    PieVectTable.XINT2 = &xint2_isr;
	EDIS;
	//中断配置步骤-----3，连接CPU中断Y
	IER |= M_INT1;
	//中断配置步骤-----4，连接Y中断里的第几位
	PieCtrlRegs.PIEIER1.bit.INTx5 = 1;          // Enable PIE Gropu 1 INT4   //XINT1
    // Enable CPU INT1
	EALLOW;
	GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 10;
	EDIS;
	XIntruptRegs.XINT2CR.bit.POLARITY = 0;      // 1为上升沿，0和2为下降沿，3为双边沿
	//中断配置步骤-----1,开启模块中断使能，
	XIntruptRegs.XINT2CR.bit.ENABLE = 1;         // Enable XINT1
}

//外部急停按钮 GPIO4
interrupt void xint1_isr(void)
{
	//急停按下 切断PWM驱动
// 将AB置为 0
//	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
	EPwm2Regs.AQSFRC.bit.RLDCSF =0x03;
	EPwm2Regs.AQCSFRC.bit.CSFA = 0x01;
	EPwm2Regs.AQCSFRC.bit.CSFB = 0x01;

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//驱动异常 中断
interrupt void xint2_isr(void)
{
	//急停按下 切断PWM驱动
// 将AB置为 0
//	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
	EPwm2Regs.AQSFRC.bit.RLDCSF =0x03;
	EPwm2Regs.AQCSFRC.bit.CSFA = 0x01;
	EPwm2Regs.AQCSFRC.bit.CSFB = 0x01;

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
