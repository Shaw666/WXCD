//============================================================================
// Filename:    A2_Module_GlobalVariableDefAndInit.c                         =
// Author:      xuyq                                                         =
// Built:       20/11/2010                                                   =
// Description: Variable Definitions.                                        =
// Modified:                                                                 =
//============================================================================
// Start here
//============================================================================
#include "GlobalVariableDefAndInits.h"
#include "Module_Project.h"

//============================================================================
//============================================================================
// structure definition
//============================================================================
struct SAMPLE_REG    Sample;
struct MODULECONTROL_REG  ModuleCtlReg;

//===========================================================================
// Variable definition
//===========================================================================

//===========================================================================
// Function definition
//===========================================================================
//===========================================================================
// Function Name: InitB01_50_120V_GlobalVariable()
// Description:   Init the global veriable
//===========================================================================
void Init_GlobalVariable(void)
{
		Uint16 i;

		Sample.PFCVoltSample= 0;
		Sample.PFCVoltSampleOld= 0;
		Sample.PFCVoltSampleAccSum= 0;
		Sample.PFCVolt= 0;
		Sample.PFCVoltReal= 0;

		Sample.PFCCurrentSample= 0;
		Sample.PFCCurrentSampleOld= 0;
		Sample.PFCCurrentSampleAccSum= 0;
		Sample.PFCCurrent= 0;
		Sample.PFCCurrentReal= 0;


		Sample.DC3P3VoltSample= 0;
		Sample.DC3P3VoltSampleOld= 0;
		Sample.DC3P3VoltSampleAccSum= 0;
		Sample.DC3P3Volt= 0;
		Sample.DC3P3VoltReal= 0;

		Sample.DC5VoltSample= 0;
		Sample.DC5VoltSampleOld= 0;
		Sample.DC5VoltSampleAccSum= 0;
		Sample.DC5Volt= 0;
		Sample.DC5VoltReal= 0;

		Sample.P15VoltSample= 0;
		Sample.P15VoltSampleOld= 0;
		Sample.P15VoltSampleAccSum= 0;
		Sample.P15Volt= 0;
		Sample.P15VoltReal= 0;

		Sample.N15VoltSample= 0;
		Sample.N15VoltSampleOld= 0;
		Sample.N15VoltSampleAccSum= 0;
		Sample.N15Volt= 0;
		Sample.N15VoltReal= 0;

		Sample.TempSample= 0;
		Sample.TempSampleOld= 0;
		Sample.TempSampleAccSum= 0;
		Sample.Temperature= 0;
		Sample.TempRealValue= 0;

		for(i = 0; i < FASTBUFLENTH; i++)
		{
				Sample.PFCVoltSampleBuffer[i]  = 0;
				Sample.PFCCurrentSampleBuffer[i]    = 0;
				Sample.DC3P3VoltSampleBuffer[i] = 0;
				Sample.DC5VoltSampleBuffer[i] = 0;
				Sample.P15VoltSampleBuffer[i]   = 0;
				Sample.N15VoltSampleBuffer[i] = 0;
				Sample.TempSampleBuffer[i]   = 0;
		}



		// Module Control
		ModuleCtlReg.BufferOffset                         =0;
		ModuleCtlReg.OutputVoltSet                           = ModultOutputVotInitSet;
		ModuleCtlReg.OutputVoltSetBackup              = ModuleCtlReg.OutputVoltSet;
		ModuleCtlReg.ModuleState                            = MODULE_STATE_OFF;


		ModuleCtlReg.OpenRelaydelayTimeCount				= 0;
		ModuleCtlReg.OpenRelayTimeCount						= 0;

		ModuleCtlReg.OpenPFCTimeCount                       = 0;

		ModuleCtlReg.StateMachineNum                        = 0;
		ModuleCtlReg.SoftStartFanTimeCount                    = 0;
		ModuleCtlReg.ShortRestartTimeCount                  = 0;


		ModuleCtlReg.LEDCtlTimeCount                        = 0;
		ModuleCtlReg.OverloadTimeCount				    = 0;

		// IO Init
		RELAYA_OFF();
		PFC_Disable();


}

//===========================================================================
// End of file.
//===========================================================================
