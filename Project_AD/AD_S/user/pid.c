/*
 * pid.c
 *
 *  Created on: 2017-3-20
 *      Author: Shaw
 */
#include "Module_Project.h"

#define PVAL_V (PID_V.Error-PID_V.Last1Error)
#define IVAL_V (PID_V.Error)
#define DVAL_V (PID_V.Error-2*PID_V.Last1Error+PID_V.Last2Error)

#define PVAL_F (PID_F.Error-PID_F.Last1Error)
#define IVAL_F (PID_F.Error)
#define DVAL_F (PID_F.Error-2*PID_F.Last1Error+PID_F.Last2Error)

typedef struct _pid {
	int MySetPoint;
	int Input;
	long Output;
	long MyOutput;
	int Error, Last1Error, Last2Error;  //ǰһ�κ�ǰ�������
	float kp, ki, kd;
} PID_type;

PID_type PID_V;
PID_type PID_F;

//Uint16 I_OUT;  //���
Uint16 V_OUT = 0;  //���

//PID������ʼ��
void PID_Init() {
	/*��ѹ����ʼ��*/
	PID_V.Input = 0;
	PID_V.Output = 0;
	PID_V.MyOutput = 0;   //��ǰPWM���
	PID_V.Error = 0, PID_V.Last1Error = 0, PID_V.Last2Error = 0;  //ǰһ�κ�ǰ�������
	PID_V.kp = 0.5, PID_V.ki = 0.1, PID_V.kd = 0; //�Ŵ�

//	PID_F.Input = 0;
//	PID_F.Output = 0;
//	PID_F.MyOutput = 0;   //��ǰPWM���
//	PID_F.Error = 0,PID_F.Last1Error = 0,PID_F.Last2Error = 0;  //ǰһ�κ�ǰ�������
//	PID_F.kp = 0.1,PID_F.ki = 0.2,PID_F.kd = 0;
}
Uint16 flashFreq = 0, flashFreqCount = 0, flagSW = 0;
Uint32 PIDtimeOutCount = 0, restartCount,startCount;
void PID_Control_V(Uint16 Volttmp, Uint16 Ctmp) //��ѹ��ǰ������pfc���ѹΪUm=400��1/1500*100%=0.06%�� U��Ч=D*Um=1---0.24V����
{
//	key = key^0x01;
//	if(key==0x01){
//	GpioDataRegs.GPASET.bit.GPIO10 = 1;
//	}
//	else {GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;}

	PID_V.MySetPoint = ModuleCtlReg.OutputVoltSet;
	PID_V.Input = Volttmp;  //  ����Ϊ�����ѹ����ʮ��
	PID_V.Error = PID_V.MySetPoint - PID_V.Input;

	PID_V.Output = PID_V.MyOutput + PID_V.kp * PVAL_V + PID_V.ki * IVAL_V
			+ PID_V.kd * DVAL_V;
	PID_V.MyOutput = PID_V.Output;
	PID_V.Last2Error = PID_V.Last1Error;
	PID_V.Last1Error = PID_V.Error;

	if (PID_V.MyOutput > 12000) {
		PID_V.MyOutput = 12000;
	}
	if (PID_V.MyOutput < 0) {
		PID_V.MyOutput = 0;
	}
	startCount++;
	if ((Volttmp <= 0x0834) && (startCount >= 5000)) {
		PIDtimeOutCount++;
		PID_V.MyOutput = 12000;
//			LinaRegs.SCITD = (PID_V.MyOutput&0xff00)>>8;
//			while (LinaRegs.SCIFLR.bit.TXRDY == 0);
//			LinaRegs.SCITD = (PID_V.MyOutput&0x00ff);
	}
	if ((Volttmp >= 0x09c4) && (startCount >= 5000)) {
		PID_V.MyOutput = 0;
	}

	V_OUT = PID_V.MyOutput * 0.1; //ѹ���ٱ�

	if(V_OUT<300){
		EPwm2Regs.CMPA.half.CMPA = 0;
		EPwm2Regs.CMPB = 1500 - 0;
		flashFreq += V_OUT;
		flashFreqCount++;
		if(flashFreqCount==2){
			EPwm2Regs.CMPA.half.CMPA = flashFreq;
			EPwm2Regs.CMPB = 1500 - flashFreq;
		}
	}
	if (V_OUT >= 1200)
		V_OUT = 1200;
	EPwm2Regs.CMPA.half.CMPA = V_OUT;
	EPwm2Regs.CMPB = 1500 - V_OUT;
}

unsigned char Send_Count; //������Ҫ���͵����ݸ���
int j = 0;     //���ڷ������ݼ���
void Upper_Uart(void)     //��λ�����ͳ���
{
//	DataScope_Get_Channel_Data(Sample.PFCVoltReal,1);   //����ѹ��PID���� д��ͨ��
//	DataScope_Get_Channel_Data(Sample.PFCCurrentReal,2);     //����ѹ��PID���� д��ͨ��
//	DataScope_Get_Channel_Data(Sample.DC5VoltReal,3);     //����ѹ��PID���� д��ͨ��
//	DataScope_Get_Channel_Data(Sample.TempRealValue,4);   //����ѹ��PID���� д��ͨ��
//	DataScope_Get_Channel_Data(PID_V.kp * PVAL_V + PID_V.ki * IVAL_V+ PID_V.kd * DVAL_V, 1);
//	DataScope_Get_Channel_Data(PID_V.Error, 2);
//	DataScope_Get_Channel_Data(PID_V.Output, 3);
	DataScope_Get_Channel_Data(PIDtimeOutCount, 1);
//	DataScope_Get_Channel_Data(EPwm2Regs.CMPA.half.CMPA, 5);
	/*******************
	 ���ڷ������ݸ���λ��
	 ********************/
	Send_Count = DataScope_Data_Generate(1); //����4��ͨ���� ��ʽ��֡���ݣ�����֡���ݳ���
	for (j = 0; j < Send_Count; j++)  //ѭ������,ֱ���������
			{
//    while (SciaRegs.SCIFFTX.bit.TXFFST != 0);
//    //while(SciaRegs.SCICTL2.bit.TXEMPTY != 1)
//    SciaRegs.SCITXBUF = DataScope_OutPut_Buffer[j];

		while (LinaRegs.SCIFLR.bit.TXRDY == 0)
			;
		//Begin transmission
		LinaRegs.SCITD = DataScope_OutPut_Buffer[j];
	}
}
