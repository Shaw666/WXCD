/*
 * testpwm.c
 *
 *  Created on: 2017-5-26
 *      Author: Shaw
 */
#include "Module_Project.h"

Uint16 yyyy=0,xyxy=0;
void testpwm(Uint16 x,Uint16 y)
{
	yyyy++;
	xyxy = xyxy^0x01;
		if(xyxy==0x01){
		GpioDataRegs.GPASET.bit.GPIO10 = 1;
		}
		else {GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;}
	//220 150 190 140  160 120
	if((x<=1600)&&(yyyy>=5000)){
		EPwm2Regs.CMPA.half.CMPA = 0;
		EPwm2Regs.CMPB = 1500-0;
		GpioDataRegs.GPASET.bit.GPIO10 = 1;
		LinaRegs.SCITD = (x&0xff00)>>8;
		while (LinaRegs.SCIFLR.bit.TXRDY == 0);
		LinaRegs.SCITD = (x&0x00ff);

	}

}
