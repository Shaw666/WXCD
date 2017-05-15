/*
 * zm5168.c
 *
 *  Created on: 2017-3-24
 *      Author: Shaw
 */
#include "Module_Project.h"


void SetupSCI(Uint32 buad)
{
	Uint16 brr_reg = (1875000 / buad) - 1;	//15000000/8 = 1875000
	//Allow write to protected registers
	EALLOW;

	LinaRegs.SCIGCR0.bit.RESET = 0; //Into reset
	LinaRegs.SCIGCR0.bit.RESET = 1; //Out of reset

	LinaRegs.SCIGCR1.bit.SWnRST = 0; //Into software reset

	//SCI Configurations
	LinaRegs.SCIGCR1.bit.COMMMODE = 0;   //Idle-Line Mode
	LinaRegs.SCIGCR1.bit.TIMINGMODE = 1; //Asynchronous Timing
	LinaRegs.SCIGCR1.bit.PARITYENA = 0;  //No Parity Check
	LinaRegs.SCIGCR1.bit.PARITY = 0;	 //Odd Parity
	LinaRegs.SCIGCR1.bit.STOP = 0;		 //One Stop Bit
	LinaRegs.SCIGCR1.bit.CLK_MASTER = 1; //Enable SCI Clock
	LinaRegs.SCIGCR1.bit.LINMODE = 0;	 //SCI Mode
	LinaRegs.SCIGCR1.bit.SLEEP = 0;      //Ensure Out of Sleep
	LinaRegs.SCIGCR1.bit.MBUFMODE = 0;	 //No Buffers Mode
	LinaRegs.SCIGCR1.bit.LOOPBACK = 0;   //External Loopback
	LinaRegs.SCIGCR1.bit.CONT = 1;		 //Continue on Suspend
	LinaRegs.SCIGCR1.bit.RXENA = 1;		 //Enable RX
	LinaRegs.SCIGCR1.bit.TXENA = 1;		 //Enable TX

	//Ensure IODFT is disabled
    LinaRegs.IODFTCTRL.bit.IODFTENA = 0x0;

    //Set transmission length
    LinaRegs.SCIFORMAT.bit.CHAR = 7;	 //Eight bits
    LinaRegs.SCIFORMAT.bit.LENGTH = 0;   //One byte

	//Set baudrate
    LinaRegs.BRSR.bit.SCI_LIN_PSL =  brr_reg & 0x00FF; //0XC2-->9600 ; 97--> 19200 ;0x30-->38400;14-->128000
    LinaRegs.BRSR.bit.SCI_LIN_PSH = (brr_reg >> 8) & 0x00FF;
    // baud = LSPCLK/8/((BRR+1)

    LinaRegs.BRSR.bit.M = 5;

    LinaRegs.SCIGCR1.bit.SWnRST = 1;  //bring out of software reset

	//Disable write to protected registers
	EDIS;
	//�ȴ�׼�����
	while(LinaRegs.SCIFLR.bit.IDLE == 1);



//	//Wait for a charachter to by typed
//	if(LinaRegs.SCIFLR.bit.RXRDY == 1)
//	{
//		ReceivedChar = LinaRegs.SCIRD;
//
//		//Wait for the module to be ready to transmit
//		while(LinaRegs.SCIFLR.bit.TXRDY == 0);
//		//Begin transmission
//		LinaRegs.SCITD = ReceivedChar;
//	}
}
/*
 * ������չ���zm5168����zigbee��������
 * GPIO 2 6
 * DSPTX---- RX13
 * DSPRX---- TX12
 */
void ZM5168_INit(void)
{
	//��ʼ��linaΪuartģʽ
//	SetupSCI(128000);
	EALLOW;
	//GPIO�Ĵ����ܱ���  reset WAKE RX TX ----- GPIO9 GPIO6 LINTX LINRX
	GpioCtrlRegs.GPAMUX1.bit.GPIO9  = 0;	//GPIO2��Ϊ��ͨIO  1ms�͵�ƽ��Ч
	GpioCtrlRegs.GPAMUX1.bit.GPIO6  = 0;	//GPIO6��Ϊ��ͨIO

	GpioCtrlRegs.GPADIR.bit.GPIO9  = 1;		//GPIO2����Ϊ���
	GpioCtrlRegs.GPADIR.bit.GPIO6  = 1;		//GPIO6����Ϊ���

	GpioDataRegs.GPASET.bit.GPIO9 = 1;		//GPIO2����ߵ�ƽ
	GpioDataRegs.GPASET.bit.GPIO6 = 1;  	//GPIO6����ߵ�ƽ
	EDIS;

//	GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;  	//GPIO6����͵�ƽ
	DELAY_US(1024);                        //��ʱ1024us
}
