/*
 * pid.h
 *
 *  Created on: 2017-3-20
 *      Author: Shaw
 */
#ifndef _PID_H
#define _PID_H

extern u16 V_OUT;


void PID_Init(void);
void PID_Control_V(Uint16 Volttmp, Uint16 Ctmp);
void Upper_Uart(void);//上位机发送程序
#endif
