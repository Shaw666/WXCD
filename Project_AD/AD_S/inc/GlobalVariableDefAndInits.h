//============================================================================
// Filename:    Module_GlobalVariableDefAndInits.h                           =
// Author:      xuyq                                                         =
// Built:       2012/01/12                                                   =
// Description: Macro define and Variable Definitions.                       =
// Modified:                                                                 =
// Cali = calibration                                                        =
// Para = parameter                                                          =
//============================================================================
// Start here
//============================================================================
#ifndef  MODULE_GLOBALVARIABLEDEFANDINITS_H
#define  MODULE_GLOBALVARIABLEDEFANDINITS_H

/******************************************************************************
* INCLUDE FILE
******************************************************************************/
#include "Module_Project.h"

#ifdef __cplusplus
extern "C" {
#endif

//===========================================================================
// STRUCT DEFINE
//===========================================================================
// SAMPLE FOR PHASE
struct  SAMPLE_REG{
		// Signal sample
		Uint16		PFCVoltSample;
		Uint16		PFCVoltSampleOld;
		Uint16		PFCVoltSampleBuffer[64];
		Uint32		PFCVoltSampleAccSum;
		Uint16		PFCVolt;
		Uint16		PFCVoltReal;

		Uint16		PFCCurrentSample;
		Uint16		PFCCurrentSampleOld;
		Uint16		PFCCurrentSampleBuffer[64];
		Uint32		PFCCurrentSampleAccSum;
		Uint16		PFCCurrent;
		Uint16		PFCCurrentReal;


		Uint16		DC3P3VoltSample;
		Uint16		DC3P3VoltSampleOld;
		Uint16		DC3P3VoltSampleBuffer[64];
		Uint32		DC3P3VoltSampleAccSum;
		Uint16		DC3P3Volt;
		Uint16		DC3P3VoltReal;

		Uint16		DC5VoltSample;
		Uint16		DC5VoltSampleOld;
		Uint16		DC5VoltSampleBuffer[64];
		Uint32		DC5VoltSampleAccSum;
		Uint16		DC5Volt;
		Uint16		DC5VoltReal;

		Uint16		P15VoltSample;
		Uint16		P15VoltSampleOld;
		Uint16		P15VoltSampleBuffer[64];
		Uint32		P15VoltSampleAccSum;
		Uint16		P15Volt;
		Uint16		P15VoltReal;

		Uint16		N15VoltSample;
		Uint16		N15VoltSampleOld;
		Uint16		N15VoltSampleBuffer[64];
		Uint32		N15VoltSampleAccSum;
		Uint16		N15Volt;
		Uint16		N15VoltReal;

		Uint16		TempSample;
		Uint16		TempSampleOld;
		Uint16		TempSampleBuffer[64];
		Uint32		TempSampleAccSum;
		Uint16		Temperature;
		Uint16		TempRealValue;

};

// CONTROL FOR MODULE
struct  MODULECONTROL_REG{

		// control
	    Uint16   BufferOffset;
		Uint16  OutputVoltSet;
		Uint16  OutputVoltSetBackup;
		Uint16  ModuleState;
		Uint16  StateMachineNum;
		Uint16  WorkState;
		//Uint16  WorkCmd;
		// relay
		Uint16  OpenRelaydelayTimeCount;
		Uint16  OpenRelayTimeCount;
		// PFC
		Uint16  OpenPFCTimeCount;
		Uint16  CheckPFCTimeCount;
		// FAN
		Uint16  SoftStartFanTimeCount;
		// Protect
		Uint16  PeotectDelayTimeCount;
		Uint16  ShortRestartTimeCount;

		// LED
		Uint16  LEDCtlTimeCount;
		Uint16  OverloadTimeCount;
};

//===========================================================================
// Control and fault and state bit field definition
//===========================================================================

// Module PFC fault msg
// Module PFC fault msg
struct Module_Fault_BITS {                   // bit   Init description
//发射端
	Uint16 PFCVoltTooLow :1;     		       //    0    0-- ok    .1-  error
	Uint16 PFCVoltTooHigh :1;     		      //      0    0-- ok    .1-  error
	Uint16 IGBTTemperatureFault :1;				//       0-- ok    .1-  error
	Uint16 FSAuxiliaryPower :1;				// 0--ok 1- error
	Uint16 FANFault :1;						//暂无     0-- ok    .1-  error

//接收端
	Uint16 JSACVoltHighFault :1;		//      0    0-- ok    .1-  error
	Uint16 JSACCurrentHighFault :1;   //      0    0-- ok    .1-  error
	Uint16 JSOutputVoltHighFault:1;
	Uint16 JSOutputCurrentHighFault:1;
	Uint16 BuckVoltHighFault :1;		//0 0--ok  .1-- error
//共用
	Uint16 CommunicationFault :1;			//      0-- ok    .1-  error
	Uint16 SCICommFault :1;
	Uint16 rsvd :4;                         			//  reserved
};
union   Module_Fault_REG{
		Uint16                       all;
		struct  Module_Fault_BITS   bit;
};

// Module state msg
struct  Module_State_BITS{                   	 // bit  Init description
		char  RELAY_STATE:1;                  //     0----OFF  .1---ON
		char  PFC_STATE:1;                    //    0----OFF  .1---ON
		char  STARTENABLE:1;                   //     0----OFF  .1---ON
		char  MODULE_STATE:1;                  //    0----OFF  .1---ON
		char  rsvd:4;                          //      reserved
};
union   Module_State_REG{
		Uint32                      all;
		struct  Module_State_BITS   bit;
};


//============================================================================
// External References & Function Declarations:
//============================================================================
// struct
extern  struct SAMPLE_REG   Sample;

extern  struct MODULECONTROL_REG  ModuleCtlReg;
extern  union  Module_Fault_REG  ModuleFault;

/******************************************************************************
* EXTERN FUNCTION PROTOTYPE
******************************************************************************/
extern  void Init_GlobalVariable(void);

//===========================================================================
#ifdef __cplusplus
}
#endif

#endif  // end of A2_MODULE_GLOBALVARIABLEDEFANDINITS_H definition

//===========================================================================
// End of file.
//===========================================================================
