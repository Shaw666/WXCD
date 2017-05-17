/*
 * ad.c
 *
 *  Created on: 2017-3-20
 *      Author: Shaw
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Module_Project.h"

interrupt void Module_ADCalibration_ISR(void);

//-------------------------------------------------------------------------
//AD��ʼ��
//��ģ��ֵ���뵽A1ͨ��
//�������P10���루6�룬λ�ڰ������Ͻǣ���RG��Ϊ�ɵ������������ɽ�RGֱ�ӽ��뵽ģ�������A1��������

//##########################################################################
void ADC_Config(void) {

	InitAdc();  // �ȵ��ùٷ�ADĬ�ϵ����ú�����ʼ�������룩

	EALLOW;
	PieVectTable.ADCINT3 = &Module_ADCalibration_ISR;  // AD�жϺ���ӳ��
	EDIS;

	PieCtrlRegs.PIEIER10.bit.INTx3 = 1;	// Enable INT 10.3 in the PIE
	IER |= M_INT10; 						// Enable CPU Interrupt 10

// Configure ADC
	EALLOW;
//	AdcRegs.ADCCTL2.bit.CLKDIV2EN = 0; //ADCclock = CPUclock
	AdcRegs.ADCCTL1.bit.ADCREFSEL = 0;    //REF Int
	AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1; //ADCINT1 trips after AdcResults latch //--> P39 HIKE,EOCx��������Դѡ��
	AdcRegs.INTSEL3N4.bit.INT3E = 1;	//Enabled ADCINT3
	AdcRegs.INTSEL3N4.bit.INT3CONT = 0;	//Disable ADCINT3 Continuous mode��single conversion mode
	//HIKE,ADCINTx EOC Source Select, ���ĸ� EOCx �����ж�
	AdcRegs.INTSEL3N4.bit.INT3SEL = 3;//setup EOC3 to trigger ADCINT1 to fire , EOC3 is trigger for ADCINTx

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//ADC�������ָ����SOCͨ����һ�����������ݲ���ȷ���ӵڶ�����ʼΪ��ȷ�����ݣ�������SOC0 SOC1���ݲ�������
//SOC ������������ֵ��ͨ����������
//0-7ΪA0��A7
//8-16ΪB0��B7
//	AdcRegs.ADCSOC0CTL.bit.CHSEL = 0;	//set SOC0 channel select to ADCINA0
	AdcRegs.ADCSOC1CTL.bit.CHSEL = 1;	//set SOC1 channel select to ADCINB0
	AdcRegs.ADCSOC2CTL.bit.CHSEL = 2;	//set SOC2 channel select to ADCINA1
	AdcRegs.ADCSOC3CTL.bit.CHSEL = 3;	//set SOC3 channel select to ADCINB1
	AdcRegs.ADCSOC4CTL.bit.CHSEL = 4;	//set SOC0 channel select to ADCINA0
//	AdcRegs.ADCSOC5CTL.bit.CHSEL 	= 5;	//set SOC1 channel select to ADCINB0
	AdcRegs.ADCSOC6CTL.bit.CHSEL = 6;	//set SOC2 channel select to ADCINA1
//	AdcRegs.ADCSOC7CTL.bit.CHSEL 	= 7;	//set SOC3 channel select to ADCINB1
	AdcRegs.ADCSOC8CTL.bit.CHSEL = 8;	//set SOC0 channel select to ADCINA0
	AdcRegs.ADCSOC9CTL.bit.CHSEL = 9;	//set SOC1 channel select to ADCINB0
//	AdcRegs.ADCSOC10CTL.bit.CHSEL 	= 10;	//set SOC2 channel select to ADCINA1
//	AdcRegs.ADCSOC11CTL.bit.CHSEL 	= 11;	//set SOC3 channel select to ADCINB1
//	AdcRegs.ADCSOC12CTL.bit.CHSEL 	= 12;	//set SOC0 channel select to ADCINA0
//	AdcRegs.ADCSOC13CTL.bit.CHSEL 	= 13;	//set SOC1 channel select to ADCINB0
//	AdcRegs.ADCSOC14CTL.bit.CHSEL 	= 14;	//set SOC2 channel select to ADCINA1
//	AdcRegs.ADCSOC15CTL.bit.CHSEL 	= 15;	//set SOC3 channel select to ADCINB1

//-->HIKE ,ADѡ�񴥷�Դ,������� P34
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 0x00;
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 0x00; //ADCTRIG0- timer1
	AdcRegs.ADCSOC2CTL.bit.TRIGSEL = 0x00;
	AdcRegs.ADCSOC3CTL.bit.TRIGSEL = 0x00;
	AdcRegs.ADCSOC4CTL.bit.TRIGSEL = 0x00;
//	AdcRegs.ADCSOC5CTL.bit.TRIGSEL 	= 0x00;
	AdcRegs.ADCSOC6CTL.bit.TRIGSEL = 0x00;
//	AdcRegs.ADCSOC7CTL.bit.TRIGSEL 	= 0x00;
	AdcRegs.ADCSOC8CTL.bit.TRIGSEL = 0x00;
	AdcRegs.ADCSOC9CTL.bit.TRIGSEL = 0x00;
//	AdcRegs.ADCSOC10CTL.bit.TRIGSEL 	= 0x00;
//	AdcRegs.ADCSOC11CTL.bit.TRIGSEL 	= 0x00;
//	AdcRegs.ADCSOC12CTL.bit.TRIGSEL 	= 0x00;
//	AdcRegs.ADCSOC13CTL.bit.TRIGSEL 	= 0x00;
//	AdcRegs.ADCSOC14CTL.bit.TRIGSEL 	= 0x00;
//	AdcRegs.ADCSOC15CTL.bit.TRIGSEL 	= 0x00;
// 6+13ADCʱ������
	AdcRegs.ADCSOC0CTL.bit.ACQPS = 6;
	AdcRegs.ADCSOC1CTL.bit.ACQPS = 6; //set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
	AdcRegs.ADCSOC2CTL.bit.ACQPS = 6;
	AdcRegs.ADCSOC3CTL.bit.ACQPS = 6;
	AdcRegs.ADCSOC4CTL.bit.ACQPS = 6;
//	AdcRegs.ADCSOC5CTL.bit.ACQPS 	= 6;	//set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
	AdcRegs.ADCSOC6CTL.bit.ACQPS = 6;
//	AdcRegs.ADCSOC7CTL.bit.ACQPS 	= 6;
	AdcRegs.ADCSOC8CTL.bit.ACQPS = 6;
	AdcRegs.ADCSOC9CTL.bit.ACQPS = 6; //set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
//	AdcRegs.ADCSOC10CTL.bit.ACQPS 	= 6;
//	AdcRegs.ADCSOC11CTL.bit.ACQPS 	= 6;
//	AdcRegs.ADCSOC12CTL.bit.ACQPS 	= 6;
//	AdcRegs.ADCSOC13CTL.bit.ACQPS 	= 6;	//set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
//	AdcRegs.ADCSOC14CTL.bit.ACQPS 	= 6;
//	AdcRegs.ADCSOC15CTL.bit.ACQPS 	= 6;

	EDIS;
}

void Module_ADCalibration_ISR(void) {

	EALLOW;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;   // Acknowledge interrupt to PIE
	EDIS;
	AdcRegs.ADCINTFLGCLR.bit.ADCINT3 = 1;//Clear ADCINT1 flag reinitialize for next SOC

	GpioDataRegs.GPBTOGGLE.bit.GPIO41 = 1;

	Sample.PFCVoltSampleBuffer[ModuleCtlReg.BufferOffset] = ((PFCVolt_ADCResult
			+ Sample.PFCVoltSampleOld * 3) >> 2);
	Sample.PFCVoltSampleOld =
			Sample.PFCVoltSampleBuffer[ModuleCtlReg.BufferOffset];

	Sample.PFCCurrentSampleBuffer[ModuleCtlReg.BufferOffset] =
			((PFCCurr_ADCResult + Sample.PFCCurrentSampleOld * 3) >> 2);
	Sample.PFCCurrentSampleOld =
			Sample.PFCCurrentSampleBuffer[ModuleCtlReg.BufferOffset];

	Sample.DC3P3VoltSampleBuffer[ModuleCtlReg.BufferOffset] =
			((DC3P3VoltADCResult + Sample.DC3P3VoltSampleOld * 3) >> 2);
	Sample.DC3P3VoltSampleOld =
			Sample.DC3P3VoltSampleBuffer[ModuleCtlReg.BufferOffset];

	Sample.DC5VoltSampleBuffer[ModuleCtlReg.BufferOffset] = ((DC5VoltADCResult
			+ Sample.DC5VoltSampleOld * 3) >> 2);
	Sample.DC5VoltSampleOld =
			Sample.DC5VoltSampleBuffer[ModuleCtlReg.BufferOffset];

	Sample.P15VoltSampleBuffer[ModuleCtlReg.BufferOffset] = ((P15Volt_ADCResult
			+ Sample.P15VoltSampleOld * 3) >> 2);
	Sample.P15VoltSampleOld =
			Sample.P15VoltSampleBuffer[ModuleCtlReg.BufferOffset];

	Sample.N15VoltSampleBuffer[ModuleCtlReg.BufferOffset] = ((N15Volt_ADCResult
			+ Sample.N15VoltSampleOld * 3) >> 2);
	Sample.N15VoltSampleOld =
			Sample.N15VoltSampleBuffer[ModuleCtlReg.BufferOffset];

	Sample.TempSampleBuffer[ModuleCtlReg.BufferOffset] = ((Temperature_ADCResult
			+ Sample.TempSampleOld * 3) >> 2);
	Sample.TempSampleOld = Sample.TempSampleBuffer[ModuleCtlReg.BufferOffset];

	Sample.PFCVoltSampleAccSum +=
			Sample.PFCVoltSampleBuffer[ModuleCtlReg.BufferOffset];
	Sample.PFCCurrentSampleAccSum +=
			Sample.PFCCurrentSampleBuffer[ModuleCtlReg.BufferOffset];
	Sample.DC3P3VoltSampleAccSum +=
			Sample.DC3P3VoltSampleBuffer[ModuleCtlReg.BufferOffset];
	Sample.DC5VoltSampleAccSum +=
			Sample.DC5VoltSampleBuffer[ModuleCtlReg.BufferOffset];
	Sample.P15VoltSampleAccSum +=
			Sample.P15VoltSampleBuffer[ModuleCtlReg.BufferOffset];
	Sample.N15VoltSampleAccSum +=
			Sample.N15VoltSampleBuffer[ModuleCtlReg.BufferOffset];
	Sample.TempSampleAccSum +=
			Sample.TempSampleBuffer[ModuleCtlReg.BufferOffset];

	if (FASTBUFLENTH <= ModuleCtlReg.BufferOffset) {
		ModuleCtlReg.BufferOffset = 0;
		// output current
		Sample.PFCVolt = (Uint16) (Sample.PFCVoltSampleAccSum >> 3);
		Sample.PFCVoltSampleAccSum = 0;
		Sample.PFCVoltReal = (Uint16) ((Uint32) Sample.PFCVolt
				* (Uint32) PFCVoltageScale >> 15);

		Sample.PFCCurrent = (Uint16) (Sample.PFCCurrentSampleAccSum >> 3);
		Sample.PFCCurrentSampleAccSum = 0;
		Sample.PFCCurrentReal = (int16) ((Uint32) Sample.PFCCurrent
				* (Uint32) PFCCurrentScale >> 15);
//		if (Sample.PFCCurrentReal < 0) {
//			Sample.PFCCurrentReal = 0;
//		}

		Sample.DC3P3Volt = (Uint16) (Sample.DC3P3VoltSampleAccSum >> 3);
		Sample.DC3P3VoltSampleAccSum = 0;
		Sample.DC3P3VoltReal = (int16) ((Uint32) Sample.DC3P3Volt
				* (Uint32) DC3P3VoltScale >> 15);

		Sample.DC5Volt = (Uint16) (Sample.DC5VoltSampleAccSum >> 3);
		Sample.DC5VoltSampleAccSum = 0;
		Sample.DC5VoltReal = (int16) ((Uint32) Sample.DC5Volt
				* (Uint32) DC5VoltScale >> 15);

		Sample.P15Volt = (Uint16) (Sample.P15VoltSampleAccSum >> 3);
		Sample.P15VoltSampleAccSum = 0;
		Sample.P15VoltReal = (int16) ((Uint32) Sample.P15Volt
				* (Uint32) P15VoltScale >> 15);

		Sample.N15Volt = (Uint16) (Sample.N15VoltSampleAccSum >> 3);
		Sample.N15VoltSampleAccSum = 0;
		Sample.N15VoltReal = (int16) ((Uint32) Sample.N15Volt
				* (Uint32) N15VoltScale >> 15);

		Sample.Temperature = (Uint16) (Sample.TempSampleAccSum >> 3);
		Sample.TempSampleAccSum = 0;
		Sample.TempRealValue = (int16) ((Uint32) Sample.Temperature
				* (Uint32) TemperatureScale >> 15);

		// Calibration use y=ax+b

	}
	ModuleCtlReg.BufferOffset++;
}

void ArbitramentProtect(void) {
}

