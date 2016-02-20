//==========================================================================================
//
// Project: FB Comunication Protocol
// Date:    19.02.16
// Author:  Filippo Bilardo
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  Stack di protocolli per la comunicazione seriale tra vari dispositivi
//
//  NOTA: includere nel progetto:
//  nel file search path del linker il file della TI driverlib.lib
//  e nell'include path dell'Arm compiler la cartella TivaWare
//
// Ver   Date      Comment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// A1.0  19.02.16  Versione iniziale. Preso come firmware di base "LedBlink_C1.2"
//
//==========================================================================================
//------------------------------------------------------------------------------------------
//=== Includes =============================================================================
//------------------------------------------------------------------------------------------
// Standard libs
#include <stdint.h>
#include <stdbool.h>
// TI libs
#include "driverlib/sysctl.h"   // Prototypes for the system control driver.
#include "utils/uartstdio.h"    // Utility driver to provide simple UART console functions
// My Libs
#include "DRIVERS/HwConfig.h"   // Hardware Abstraction Layer Drivers
#include "LIBS/SysTick.h"       // SysTick Library
#include "LIBS/Led.h"           // Led Library
#include "LIBS/Puls.h"          // Puls Library
#include "LIBS/Uart.h"          // Uart Library
#include "LIBS/FBCP.h"          // FB Comunication Protocol Library


//------------------------------------------------------------------------------------------
//=== main==== =============================================================================
//------------------------------------------------------------------------------------------
int main(void)
{
    // Inizializzazioni
    //
    // Set the clocking to run directly from the external crystal/oscillator.
    // The Tiva C Series LaunchPad uses a 16.0-MHz crystal to complete the TM4C123GH6PM
    // microcontroller main internal clock circuit.
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    L1_2_PcToMicro_Init();
    L1_MicroToMicro_Init();
	LedInit();
    PulsInit();

    // Autodiagnostica
    LedGreenOn();
    if (P1Press()) Uart00_Test();    // Echo read chars fino alla pressione del del tasto Return
    LedGreenOff();

	// Main loop
	for(;;)
	{
		L1_2_PcToMicro_Rx_Task();
		L7_PcToMicro_Task();
		L1_MicroToMicro_RxTask();
		L1_MicroToMicro_TxTask();
	}
}
