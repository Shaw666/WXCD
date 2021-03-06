/*
 * pwm.c
 *
 *  Created on: 2017-3-20
 *      Author: Shaw
 */
#include "Module_Project.h"

void EPWMA_Config(u16 period) {

	InitEPwm1Gpio();
	EPwm1Regs.TBPRD = period;                        // Set timer period
	EPwm1Regs.TBPHS.half.TBPHS = 0;           // Phase is 0
	EPwm1Regs.TBCTR = 0x0000;                      // Clear counter

	// Setup TBCLK
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
	EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;

	//1500- 60  最小1us死区
	// Setup compare
	EPwm1Regs.CMPA.half.CMPA = 1200;
	EPwm1Regs.CMPB = 1500 - 1200;
	// Set actions
	//0------CAU
	EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm1Regs.AQCTLA.bit.PRD = AQ_CLEAR;
	EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;
	//PRD----CBD
	EPwm1Regs.AQCTLB.bit.ZRO = AQ_CLEAR;
	EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;
	EPwm1Regs.AQCTLB.bit.PRD = AQ_SET;
	EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;
}

void EPWMB_Config(u16 period) {

	InitEPwm2Gpio();

	EPwm2Regs.TBPRD = period;                        // Set timer period
	EPwm2Regs.TBPHS.half.TBPHS = 0;           // Phase is 0
	EPwm2Regs.TBCTR = 0x0000;                      // Clear counter

	// Setup TBCLK
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
//	EPwm2Regs.TBCTL.bit.PHSDIR = TB_UP;
	EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
	EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; 			// sync flow-through
	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;

	//1500- 60  最小1us死区
	// Setup compare
	EPwm2Regs.CMPA.half.CMPA = 0;
	EPwm2Regs.CMPB = 1500 - 0;
	// Set actions
	//0------CAU
	EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm2Regs.AQCTLA.bit.PRD = AQ_CLEAR;
	EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;
	//PRD----CBD
	EPwm2Regs.AQCTLB.bit.ZRO = AQ_CLEAR;
	EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;
	EPwm2Regs.AQCTLB.bit.PRD = AQ_SET;
	EPwm2Regs.AQCTLB.bit.CBD = AQ_CLEAR;
}
//EPwm2Regs.TBPHS.half.TBPHS = 8.3*i;移相
u32 EPWM1_TIMER_TBPRD = 3000;
void InitEPwm1(void) {
	InitEPwm1Gpio();

	EPwm1Regs.TBPRD = EPWM1_TIMER_TBPRD; // Period = EPWM1_TIMER_TBPRD+1 TBCLK counts
	EPwm1Regs.CMPA.half.CMPA = EPWM1_TIMER_TBPRD >> 1; // Set 50% fixed duty for EPWM1Ai
	EPwm1Regs.TBPHS.half.TBPHS = 0; 			// Set Phase register to zero
	EPwm1Regs.TBCTR = 0x0000;                      		// Clear counter

	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; 			// Asymmetrical mode
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE; 			// Master module
	EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; 	// Sync down-stream module
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       	// Clock ratio to SYSCLKOUT
	EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; 	// load on CTR=Zero
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; 	// load on CTR=Zero

	EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET; 				// set actions for EPWM1Ai
	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm1Regs.AQCTLB.bit.ZRO = AQ_CLEAR; 			// set actions for EPWM2Ai
	EPwm1Regs.AQCTLB.bit.CAU = AQ_SET;

	EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL; // EPWMxA In (from the action-qualifier) is the source for both falling-edge and rising-edge delay.
	EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 		// Active Hi complementary
	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;// Dead-band is fully enabled

	EPwm1Regs.DBFED = 60; 							// FED = 50 TBCLKs initially
	EPwm1Regs.DBRED = 60; 							// RED = 70 TBCLKs initially
}

void InitEPwm2(void) {

	InitEPwm2Gpio();
	EPwm2Regs.TBPRD = EPWM1_TIMER_TBPRD; // Period = EPWM1_TIMER_TBPRD+1 TBCLK counts
	EPwm2Regs.CMPA.half.CMPA = EPWM1_TIMER_TBPRD >> 1; // Set 50% fixed duty EPWM2Ai
	EPwm2Regs.TBPHS.half.TBPHS = 0; 	// Set Phase register to zero initially
	EPwm2Regs.TBCTR = 0x0000;                      		// Clear counter

	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; 			// Asymmetrical mode
//	EPwm2Regs.TBCTL.bit.PHSDIR = TB_UP;
	EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE; 				// Slave module
	EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; 			// sync flow-through
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       	// Clock ratio to SYSCLKOUT
	EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; 		// load on CTR=Zero
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; 		// load on CTR=Zero

	EPwm2Regs.AQCTLB.bit.ZRO = AQ_SET; 				// set actions for EPWM2Ai
	EPwm2Regs.AQCTLB.bit.CAU = AQ_CLEAR;
	EPwm2Regs.AQCTLA.bit.ZRO = AQ_CLEAR; 			// set actions for EPWM2Ai
	EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;

	EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL; // EPWMxA In (from the action-qualifier) is the source for both falling-edge and rising-edge delay.
	EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 		// Active Hi complementary
	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;// Dead-band is fully enabled

	EPwm2Regs.DBFED = 60; 							// FED = 30 TBCLKs initially
	EPwm2Regs.DBRED = 60; 							// RED = 40 TBCLKs initially

}

