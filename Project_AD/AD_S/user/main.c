/*
 * main.c
 *  ����˳��� V1.0
 *  Created on: 2017-3-20
 *      Author: Shaw
 */

//GpioDataRegs.GPASET.bit.GPIO5 = 1;   //������¶ȹ������ߴ򿪷���
//GpioDataRegs.GPASET.bit.GPIO11 = 1;  //��⵽�����ѹ����350V���ߣ��պϼ̵���
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
	GPIO_INit();   //��ʼ��GPIO �����շ�
	ADC_Config();
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	EDIS;
	Timer0_init(); //��ʼ����ʱ��0���ڶ�ʱ�����������
//	Timer1_init(); //��ʼ����ʱ��1���ڶ�ʱ����PID �����շ�
	SCI_Init(115200);   //��ʼ��SCI
	SetupSCI(115200);
	ZM5168_INit();              //��ʼ��zm5168_P0ģ��
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
//	DIP_Scan();   //����ɨ��һ�β��뿪��
//	GpioDataRegs.GPBTOGGLE.bit.GPIO43 	= 1;
	while (1) {
		if (timer0Base.Mark_Para.Status_Bits.OnemsdFlag == 1) {
			timer0Base.Mark_Para.Status_Bits.OnemsdFlag = 0;

			if (STOP_Scan() == Excep_qdyc) {   //�����쳣 ��������PWM�ж�
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

