/*
 * main.c
 *  ����˳��� V1.0
 *  Created on: 2017-3-20
 *      Author: Shaw
 */

//GpioDataRegs.GPASET.bit.GPIO5 = 1;   //������¶ȹ������ߴ򿪷���
//GpioDataRegs.GPASET.bit.GPIO11 = 1;  //��⵽�����ѹ����350V���ߣ��պϼ̵���
#include "Module_Project.h"

u8 key = 0;
extern Uint16 RamfuncsLoadSize;

void main(void) {
	Uint16 duty=0;
	InitSysCtrl();
	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
	memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32) &RamfuncsLoadSize);
	GPIO_INit();   //��ʼ��GPIO �����շ�
	Init_GlobalVariable();
	ADC_Config();
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	EDIS;
	Timer0_init(); //��ʼ����ʱ��0���ڶ�ʱ�����������
//	Timer1_init(); //��ʼ����ʱ��1���ڶ�ʱ����PID �����շ�
	SCI_Init(57600);   //��ʼ��SCI
	SetupSCI(115200);
//	ZM5168_INit();              //��ʼ��zm5168_P0ģ��

//	open_uart_debug();
//	InitI2C_Gpio();             //io ��ʼ��ΪIIC
//	I2CA_Init();                //HW IIC��ʼ����100KHz
	EPWMB_Config(1500);
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;
	//�ж����ò���-----5
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
	EINT;
	// Enable Global interrupt INTM
	ERTM;
//	AdcRegs.ADCSOCFRC1.all = 0X035E; //�������AD �� SOC0--SOC3����
//	DIP_Scan();   //ɨ�貦�뿪��
	DealRxLenth = 5;
	AdcRegs.ADCSOCFRC1.all = 0X035E;
	while (1) {
			if(ModuleFault.bit.JSOutputVoltHighFault==0){
			if(timer0Base.msCounter%10==0){
				timer0Base.msCounter=0;
				if(duty<300){
				duty +=10;
				if(duty>=300)
					duty=300;
				EPwm2Regs.CMPA.half.CMPA = duty;
				EPwm2Regs.CMPB = 1500 - duty;
			}
			}
	}

	}
}

//===========================================================================
// No more.
//===========================================================================

