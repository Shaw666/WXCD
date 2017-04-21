/*
 * pwm.h
 *
 *  Created on: 2017-3-20
 *      Author: Shaw
 */

#ifndef _PWM_H_
#define _PWM_H_

void EPWM1_Config(Uint16 period);
void EPWM2_Config(u16 period);
void InitEPwm1(void);
void InitEPwm2(void);

#endif /* PWM_H_ */
