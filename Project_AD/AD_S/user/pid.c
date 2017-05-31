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
	int Error, Last1Error, Last2Error;  //前一次和前两次误差
	float kp, ki, kd;
} PID_type;

PID_type PID_V;
PID_type PID_F;

//Uint16 I_OUT;  //输出
Uint16 V_OUT = 0;  //输出

//PID参数初始化
void PID_Init() {
	/*电压环初始化*/
	PID_V.Input = 0;
	PID_V.Output = 0;
	PID_V.MyOutput = 0;   //当前PWM输出
	PID_V.Error = 0, PID_V.Last1Error = 0, PID_V.Last2Error = 0;  //前一次和前两次误差
	PID_V.kp = 0.5, PID_V.ki = 0.1, PID_V.kd = 0; //放大

//	PID_F.Input = 0;
//	PID_F.Output = 0;
//	PID_F.MyOutput = 0;   //当前PWM输出
//	PID_F.Error = 0,PID_F.Last1Error = 0,PID_F.Last2Error = 0;  //前一次和前两次误差
//	PID_F.kp = 0.1,PID_F.ki = 0.2,PID_F.kd = 0;
}
Uint16 flashFreq = 0, flashFreqCount = 0, flagSW = 0;
Uint32 PIDtimeOutCount = 0, restartCount,startCount;
void PID_Control_V(Uint16 Volttmp, Uint16 Ctmp) //电压环前级输入pfc后电压为Um=400（1/1500*100%=0.06%） U有效=D*Um=1---0.24V理论
{
//	key = key^0x01;
//	if(key==0x01){
//	GpioDataRegs.GPASET.bit.GPIO10 = 1;
//	}
//	else {GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;}

	PID_V.MySetPoint = ModuleCtlReg.OutputVoltSet;
	PID_V.Input = Volttmp;  //  输入为输出电压扩大十倍
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

	V_OUT = PID_V.MyOutput * 0.1; //压缩百倍

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

unsigned char Send_Count; //串口需要发送的数据个数
int j = 0;     //串口发送数据计数
void Upper_Uart(void)     //上位机发送程序
{
//	DataScope_Get_Channel_Data(Sample.PFCVoltReal,1);   //将电压环PID输入 写入通道
//	DataScope_Get_Channel_Data(Sample.PFCCurrentReal,2);     //将电压环PID输入 写入通道
//	DataScope_Get_Channel_Data(Sample.DC5VoltReal,3);     //将电压环PID输入 写入通道
//	DataScope_Get_Channel_Data(Sample.TempRealValue,4);   //将电压环PID输入 写入通道
//	DataScope_Get_Channel_Data(PID_V.kp * PVAL_V + PID_V.ki * IVAL_V+ PID_V.kd * DVAL_V, 1);
//	DataScope_Get_Channel_Data(PID_V.Error, 2);
//	DataScope_Get_Channel_Data(PID_V.Output, 3);
	DataScope_Get_Channel_Data(PIDtimeOutCount, 1);
//	DataScope_Get_Channel_Data(EPwm2Regs.CMPA.half.CMPA, 5);
	/*******************
	 串口发送数据给上位机
	 ********************/
	Send_Count = DataScope_Data_Generate(1); //生成4个通道的 格式化帧数据，返回帧数据长度
	for (j = 0; j < Send_Count; j++)  //循环发送,直到发送完毕
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
