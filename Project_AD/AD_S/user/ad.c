/*
 * ad.c
 *
 *  Created on: 2017-3-20
 *      Author: Shaw
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "HK_all_include.h"
//ADC
u32 regulate_V;
u32 regulate_I;

//AdcRegs.ADCSOCFRC1.all = 0X000F; //软件触发SOC0--SOC3采样

interrupt void adc_isr(void);


//-------------------------------------------------------------------------
//AD初始化
//将模拟值输入到A1通道
//开发板的P10排针（6针，位于板子左上角）的RG，为可调电阻的输出，可将RG直接接入到模拟输入口A1进行试验

//##########################################################################
void ADC_Config(void)
{

   InitAdc();  // 先调用官方AD默认的配置函数初始化（必须）

   EALLOW;
   PieVectTable.ADCINT3 = &adc_isr;// AD中断函数映射
   EDIS;

   PieCtrlRegs.PIEIER10.bit.INTx3 = 1;	// Enable INT 10.3 in the PIE
   IER |= M_INT10; 						// Enable CPU Interrupt 10

// Configure ADC
	EALLOW;
//	AdcRegs.ADCCTL2.bit.CLKDIV2EN = 0; //ADCclock = CPUclock
	AdcRegs.ADCCTL1.bit.ADCREFSEL	= 0;    //REF Int
	AdcRegs.ADCCTL1.bit.INTPULSEPOS	= 1;	//ADCINT1 trips after AdcResults latch //--> P39 HIKE,EOCx产生来自源选择
	AdcRegs.INTSEL3N4.bit.INT3E     = 1;	//Enabled ADCINT3
	AdcRegs.INTSEL3N4.bit.INT3CONT  = 0;	//Disable ADCINT3 Continuous mode，single conversion mode
	//HIKE,ADCINTx EOC Source Select, 即哪个 EOCx 触发中断
	AdcRegs.INTSEL3N4.bit.INT3SEL	= 3;	//setup EOC3 to trigger ADCINT1 to fire , EOC3 is trigger for ADCINTx


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//ADC勘误表上指出，SOC通道第一个采样的数据不正确，从第二个开始为正确的数据，故这里SOC0 SOC1数据不做处理

//	//P17 P35 同步采样的话，两个SOC的CHSEL设置一样
//	//Simultaneous sampling enable for SOC2/SOC3
//	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN0=1;	//SOC0/1 Simultaneous Sampling Enable	,SOC0蚐OC1组合工作
//	AdcRegs.ADCSOC0CTL.bit.CHSEL 	= 1;	//SOC0 (ADCINA1/ADCINB1 pair)，配置模拟通道连接
//	AdcRegs.ADCSOC1CTL.bit.CHSEL 	= 1;	//SOC1 (ADCINA1/ADCINB1 pair)，配置模拟通道连接
//
//	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN2=1;	//SOC2/3 Simultaneous Sampling Enable	,SOC2蚐OC3组合工作
//	AdcRegs.ADCSOC2CTL.bit.CHSEL 	= 1;	//SOC2 (ADCINA1/ADCINB1 pair)，配置模拟通道连接
//	AdcRegs.ADCSOC3CTL.bit.CHSEL 	= 1;	//SOC3 (ADCINA1/ADCINB1 pair)，配置模拟通道连接


//SOC 连续采样，赋值与通道连接如下
//0-7为A0到A7
//8-16为B0到B7
	AdcRegs.ADCSOC0CTL.bit.CHSEL 	= 0;	//set SOC0 channel select to ADCINA0
	AdcRegs.ADCSOC1CTL.bit.CHSEL 	= 1;	//set SOC1 channel select to ADCINB0
	AdcRegs.ADCSOC2CTL.bit.CHSEL 	= 2;	//set SOC2 channel select to ADCINA1
	AdcRegs.ADCSOC3CTL.bit.CHSEL 	= 3;	//set SOC3 channel select to ADCINB1
	AdcRegs.ADCSOC4CTL.bit.CHSEL 	= 4;	//set SOC0 channel select to ADCINA0
//	AdcRegs.ADCSOC5CTL.bit.CHSEL 	= 5;	//set SOC1 channel select to ADCINB0
	AdcRegs.ADCSOC6CTL.bit.CHSEL 	= 6;	//set SOC2 channel select to ADCINA1
//	AdcRegs.ADCSOC7CTL.bit.CHSEL 	= 7;	//set SOC3 channel select to ADCINB1
	AdcRegs.ADCSOC8CTL.bit.CHSEL 	= 8;	//set SOC0 channel select to ADCINA0
	AdcRegs.ADCSOC9CTL.bit.CHSEL 	= 9;	//set SOC1 channel select to ADCINB0
//	AdcRegs.ADCSOC10CTL.bit.CHSEL 	= 10;	//set SOC2 channel select to ADCINA1
//	AdcRegs.ADCSOC11CTL.bit.CHSEL 	= 11;	//set SOC3 channel select to ADCINB1
//	AdcRegs.ADCSOC12CTL.bit.CHSEL 	= 12;	//set SOC0 channel select to ADCINA0
//	AdcRegs.ADCSOC13CTL.bit.CHSEL 	= 13;	//set SOC1 channel select to ADCINB0
//	AdcRegs.ADCSOC14CTL.bit.CHSEL 	= 14;	//set SOC2 channel select to ADCINA1
//	AdcRegs.ADCSOC15CTL.bit.CHSEL 	= 15;	//set SOC3 channel select to ADCINB1

//-->HIKE ,AD选择触发源,软件触发 P34
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL 	= 0x00;
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL 	= 0x00; //ADCTRIG0- Software only
	AdcRegs.ADCSOC2CTL.bit.TRIGSEL 	= 0x00;
	AdcRegs.ADCSOC3CTL.bit.TRIGSEL 	= 0x00;
	AdcRegs.ADCSOC4CTL.bit.TRIGSEL 	= 0x00;
//	AdcRegs.ADCSOC5CTL.bit.TRIGSEL 	= 0x00; //ADCTRIG0- Software only
	AdcRegs.ADCSOC6CTL.bit.TRIGSEL 	= 0x00;
//	AdcRegs.ADCSOC7CTL.bit.TRIGSEL 	= 0x00;
	AdcRegs.ADCSOC8CTL.bit.TRIGSEL 	= 0x00;
	AdcRegs.ADCSOC9CTL.bit.TRIGSEL 	= 0x00; //ADCTRIG0- Software only
//	AdcRegs.ADCSOC10CTL.bit.TRIGSEL 	= 0x00;
//	AdcRegs.ADCSOC11CTL.bit.TRIGSEL 	= 0x00;
//	AdcRegs.ADCSOC12CTL.bit.TRIGSEL 	= 0x00;
//	AdcRegs.ADCSOC13CTL.bit.TRIGSEL 	= 0x00; //ADCTRIG0- Software only
//	AdcRegs.ADCSOC14CTL.bit.TRIGSEL 	= 0x00;
//	AdcRegs.ADCSOC15CTL.bit.TRIGSEL 	= 0x00;
// 6+13ADC时钟周期
	AdcRegs.ADCSOC0CTL.bit.ACQPS 	= 6;
	AdcRegs.ADCSOC1CTL.bit.ACQPS 	= 6;	//set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
	AdcRegs.ADCSOC2CTL.bit.ACQPS 	= 6;
	AdcRegs.ADCSOC3CTL.bit.ACQPS 	= 6;
	AdcRegs.ADCSOC4CTL.bit.ACQPS 	= 6;
//	AdcRegs.ADCSOC5CTL.bit.ACQPS 	= 6;	//set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
	AdcRegs.ADCSOC6CTL.bit.ACQPS 	= 6;
//	AdcRegs.ADCSOC7CTL.bit.ACQPS 	= 6;
	AdcRegs.ADCSOC8CTL.bit.ACQPS 	= 6;
	AdcRegs.ADCSOC9CTL.bit.ACQPS 	= 6;	//set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
//	AdcRegs.ADCSOC10CTL.bit.ACQPS 	= 6;
//	AdcRegs.ADCSOC11CTL.bit.ACQPS 	= 6;
//	AdcRegs.ADCSOC12CTL.bit.ACQPS 	= 6;
//	AdcRegs.ADCSOC13CTL.bit.ACQPS 	= 6;	//set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
//	AdcRegs.ADCSOC14CTL.bit.ACQPS 	= 6;
//	AdcRegs.ADCSOC15CTL.bit.ACQPS 	= 6;

	EDIS;
}


volatile u16 *ADResReg[16];
//-------------------------------------------------------------------------
//AD 中断处理函数
//##########################################################################
interrupt void  adc_isr(void)
{
	EALLOW;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;   // Acknowledge interrupt to PIE
	EDIS;
	AdcRegs.ADCINTFLGCLR.bit.ADCINT3 = 1;		//Clear ADCINT1 flag reinitialize for next SOC

    ADResReg[0] =  &AdcResult.ADCRESULT0;//空置
    ADResReg[1] =  &AdcResult.ADCRESULT1;//3.3v掉电检测     2.2v以下
    ADResReg[2] =  &AdcResult.ADCRESULT2;//5v检测   2v以下
    ADResReg[3] =  &AdcResult.ADCRESULT3;//-15v检测  2.5v以下
    ADResReg[4] =  &AdcResult.ADCRESULT4;//15v检测    2v以下
//    ADResReg[5] =  &AdcResult.ADCRESULT5;
    ADResReg[6] =  &AdcResult.ADCRESULT6;//过温igbt检测
//    ADResReg[7] =  &AdcResult.ADCRESULT7;//保留

    ADResReg[8] =  &AdcResult.ADCRESULT8;//输入电压检测 15/3k
    ADResReg[9] =  &AdcResult.ADCRESULT9;//输入电流检测 0.1972*Iin
//    ADResReg[10] = &AdcResult.ADCRESULT10;//保留
//    ADResReg[11] = &AdcResult.ADCRESULT11;//保留
//    ADResReg[12] = &AdcResult.ADCRESULT12;//保留
//    ADResReg[13] = &AdcResult.ADCRESULT13;
//    ADResReg[14] = &AdcResult.ADCRESULT14;//保留
//    ADResReg[15] = &AdcResult.ADCRESULT15;//保留

//1111 1010 1100 0000
	AdcRegs.ADCSOCFRC1.all = 0XFAC0; //软件触发AD 的 SOC0--SOC3采样

//	printf("\r\nAD Result is SOC0-A1:%0.2fV  SOC1-B1:%0.2fV  SOC2-A1:%0.2fV  SOC3-B1:%0.2fV",(float)((AdcResult.ADCRESULT0)*3.3/4096),(float)((AdcResult.ADCRESULT1)*3.3/4096),(float)((AdcResult.ADCRESULT2)*3.3/4096),(float)((AdcResult.ADCRESULT3)*3.3/4096));
}


