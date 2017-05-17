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
//�ⲿ�жϣ��½��ؼ��
//����XINT1�ⲿ�ж�
//��ͣ�ж�
//---------------------------------------------------------------------------------------------
void ExInt_Init(void)
{
	EALLOW;									//GPIO�Ĵ����ܱ���
	GpioCtrlRegs.GPAMUX1.bit.GPIO4= 0;		//GPIO6��Ϊ��ͨIO
	GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;		//GPIO6����Ϊ����
	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;		//�����ڲ�����
	GpioCtrlRegs.GPAQSEL1.bit.GPIO4 = 0;   // ���Ų�����ϵͳʱ��ͬ��

	GpioCtrlRegs.GPAMUX2.bit.GPIO17= 0;		//GPIO17��Ϊ��ͨIO
	GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;		//GPIO17����Ϊ����
	GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;		//�����ڲ�����
	GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 0;   // ���Ų�����ϵͳʱ��ͬ��
	EDIS;

	//�ж����ò���-----2����ӳ���жϷ�����
	EALLOW;	
    PieVectTable.XINT1 = &xint1_isr;
	EDIS;
	//�ж����ò���-----3������CPU�ж�Y
	IER |= M_INT1;
	//�ж����ò���-----4������Y�ж���ĵڼ�λ
	PieCtrlRegs.PIEIER1.bit.INTx4 = 1;          // Enable PIE Gropu 1 INT4   //XINT1
    // Enable CPU INT1
	EALLOW;
	GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 4;
	EDIS;
	XIntruptRegs.XINT1CR.bit.POLARITY = 0;      // 1Ϊ�����أ�0��2Ϊ�½��أ�3Ϊ˫����
	//�ж����ò���-----1,����ģ���ж�ʹ�ܣ�
	XIntruptRegs.XINT1CR.bit.ENABLE = 1;         // Enable XINT1

	//�ж����ò���-----2����ӳ���жϷ�����
	EALLOW;
    PieVectTable.XINT2 = &xint2_isr;
	EDIS;
	//�ж����ò���-----3������CPU�ж�Y
	IER |= M_INT1;
	//�ж����ò���-----4������Y�ж���ĵڼ�λ
	PieCtrlRegs.PIEIER1.bit.INTx5 = 1;          // Enable PIE Gropu 1 INT4   //XINT1
    // Enable CPU INT1
	EALLOW;
	GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 10;
	EDIS;
	XIntruptRegs.XINT2CR.bit.POLARITY = 0;      // 1Ϊ�����أ�0��2Ϊ�½��أ�3Ϊ˫����
	//�ж����ò���-----1,����ģ���ж�ʹ�ܣ�
	XIntruptRegs.XINT2CR.bit.ENABLE = 1;         // Enable XINT1
}

//�ⲿ��ͣ��ť GPIO4
interrupt void xint1_isr(void)
{
	//��ͣ���� �ж�PWM����
// ��AB��Ϊ 0
//	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
	EPwm2Regs.AQSFRC.bit.RLDCSF =0x03;
	EPwm2Regs.AQCSFRC.bit.CSFA = 0x01;
	EPwm2Regs.AQCSFRC.bit.CSFB = 0x01;

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//�����쳣 �ж�
interrupt void xint2_isr(void)
{
	//��ͣ���� �ж�PWM����
// ��AB��Ϊ 0
//	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
	EPwm2Regs.AQSFRC.bit.RLDCSF =0x03;
	EPwm2Regs.AQCSFRC.bit.CSFA = 0x01;
	EPwm2Regs.AQCSFRC.bit.CSFB = 0x01;

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
