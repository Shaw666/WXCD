/*
 * ad.h
 *
 *  Created on: 2017-3-20
 *      Author: Shaw
 */

#ifndef _AD_H_
#define _AD_H_



extern u32 regulate_V;
extern u32 regulate_I;
extern volatile u16 *ADResReg[16];


void ADC_Config(void);
void ArbitramentProtect(void);

#endif /* AD_H_ */
