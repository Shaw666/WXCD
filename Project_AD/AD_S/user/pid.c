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

typedef struct _pid
{
	int MySetPoint; 
	int Input;
	int Output;
	int MyOutput;   
	int Error,Last1Error,Last2Error;  //前一次和前两次误差
	float kp,ki,kd;
}PID_type;

PID_type PID_V;
PID_type PID_F;

//Uint16 I_OUT;  //输出
Uint16 V_OUT;  //输出

//PID参数初始化
void PID_Init()
{
	/*电压环初始化*/	
    PID_V.Input = 0;
	PID_V.Output = 0;
	PID_V.MyOutput = 0;   //当前PWM输出
	PID_V.Error = 0,PID_V.Last1Error = 0,PID_V.Last2Error = 0;  //前一次和前两次误差
	PID_V.kp = 10,PID_V.ki = 20,PID_V.kd = 0; //放大一百倍

//	PID_F.Input = 0;
//	PID_F.Output = 0;
//	PID_F.MyOutput = 0;   //当前PWM输出
//	PID_F.Error = 0,PID_F.Last1Error = 0,PID_F.Last2Error = 0;  //前一次和前两次误差
//	PID_F.kp = 0.1,PID_F.ki = 0.2,PID_F.kd = 0;

}

u8 xfeq;
void PID_Control_I(void)     //
{
	PID_F.MySetPoint = 50;
	PID_F.Input = xfeq;  //  输入为输出电压
	PID_F.Error = PID_F.MySetPoint-PID_F.Input; 
  	if((PID_F.MySetPoint-PID_F.Input)<10&&(PID_F.MySetPoint-PID_F.Input)>0){}
//		TIM_SetCompare1(TIM1,V_OUT);
	else 
	{
	PID_F.Output = PID_F.MyOutput + PID_F.kp*PVAL_F + PID_F.ki*IVAL_F+PID_F.kd*DVAL_F;//output为电压值	
	PID_F.MyOutput = PID_F.Output; 
	PID_F.Last2Error = PID_F.Last1Error;     
	PID_F.Last1Error = PID_F.Error;
	if(PID_F.MyOutput>647){PID_F.MyOutput=647;}
	if(PID_F.MyOutput<72) {PID_F.MyOutput=72; }
    V_OUT = PID_F.MyOutput;
//	gai(F_OUT);
	}	
}
u16 temp[6],count=0,x;
void PID_Control_V(Uint16* tmp)     //电压环前级输入pfc后电压为Um=400（1/1500*100%=0.06%） U有效=D*Um=1---0.24V理论
{
	PID_V.MySetPoint =2200;
	PID_V.Input = (Uint16) ((Uint32) tmp* (Uint32) OutDCVoltageScale >> 15);  //  输入为输出电压扩大十倍
	
	PID_V.Error = PID_V.MySetPoint-PID_V.Input; 
	PID_V.Output = PID_V.MyOutput + PID_V.kp*PVAL_V + PID_V.ki*IVAL_V+PID_V.kd*DVAL_V;
	PID_V.MyOutput = PID_V.Output; 
	PID_V.Last2Error = PID_V.Last1Error;     
	PID_V.Last1Error = PID_V.Error;
	if(PID_V.MyOutput>1440) {PID_V.MyOutput=1440; } //死区1us 即最大理论值不超过1440 限定电压值为
	if(PID_V.MyOutput<60) {PID_V.MyOutput=60; }
	V_OUT = PID_V.MyOutput/100; //压缩百倍

	EPwm2Regs.CMPA.half.CMPA = V_OUT;
	EPwm2Regs.CMPB = 1500-V_OUT;
}


//#################################################
//串口接收中断函数
//采用FIFO机制（缓存）
//SCI_FIFO_LEN 定义为 1，最大为4
//-----------------------------------------------
interrupt void uartRx_isr(void) {

	if (SciaRegs.SCIFFRX.bit.RXFFST == 1){
	temp[count] = SciaRegs.SCIRXBUF.bit.RXDT;
	SciaRegs.SCITXBUF = temp[count];
	count++;
	if(count==6) {count=0;}
	if(temp[0]==0xAA){

	}
	else if(temp[0]==0xA5){

	}
	}

	SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;   // Clear Interrupt flag
	PieCtrlRegs.PIEACK.bit.ACK9 = 1;
}


__interrupt void cpu_timer1_isr(void)
{
	EDIS;
//	AdcRegs.ADCSOCFRC1.all = 0X035E; //软件触发AD 的 SOC0--SOC3采样
//	Upper_Uart();
//	PID_Control_V();
}


unsigned char Send_Count; //串口需要发送的数据个数
int j=0;     //串口发送数据计数
void Upper_Uart(void)//上位机发送程序
{
//	DataScope_Get_Channel_Data(Sample.PFCVoltReal,1);   //将电压环PID输入 写入通道
//	DataScope_Get_Channel_Data(Sample.PFCCurrentReal,2);     //将电压环PID输入 写入通道
//	DataScope_Get_Channel_Data(Sample.DC3P3VoltReal,3);   //将电压环PID输入 写入通道
//	DataScope_Get_Channel_Data(Sample.DC5VoltReal,4);     //将电压环PID输入 写入通道
//	DataScope_Get_Channel_Data(Sample.P15VoltReal,5);   //将电压环PID输入 写入通道
//	DataScope_Get_Channel_Data(Sample.N15VoltReal,6);     //将电压环PID输入 写入通道
//	DataScope_Get_Channel_Data(Sample.TempRealValue,7);   //将电压环PID输入 写入通道
	DataScope_Get_Channel_Data(V_OUT,1);
	DataScope_Get_Channel_Data(PID_V.Input,2);
	/*******************
	串口发送数据给上位机
	********************/
	Send_Count = DataScope_Data_Generate(7); //生成4个通道的 格式化帧数据，返回帧数据长度
    for( j = 0;j<Send_Count;j++)  //循环发送,直到发送完毕
	{
//    while (SciaRegs.SCIFFTX.bit.TXFFST != 0);
//    //while(SciaRegs.SCICTL2.bit.TXEMPTY != 1)
//    SciaRegs.SCITXBUF = DataScope_OutPut_Buffer[j];

	while(LinaRegs.SCIFLR.bit.TXRDY == 0);
	//Begin transmission
	LinaRegs.SCITD = DataScope_OutPut_Buffer[j];
	}
}
