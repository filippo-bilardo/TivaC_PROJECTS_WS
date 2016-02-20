//==========================================================================================
//
// Project: LedBlink
// Date:    13.11.15
// Author:  Filippo Bilardo
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  Lampeggio di un led presente nella scheda utilizzando un delay
//
//  Nota: includere nel progetto:
//  nel file search path del linker il file della TI driverlib.lib
//  e nell'include path dell'Arm compiler la cartella TivaWare
//
// Ver   Date      Comment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// C1.0  13.11.15  Versione iniziale. Il firmware è realizzato utilizzando le librerie
//                 fornite dalla TI
// C1.1  13.11.15  Integrazione delle librerie fornite dalla TI con dei driver
//                 personalizzati di secondo livello per l'accesso all'hardware
// C1.2  14.11.15  Aggiunta di un livello di astrazione dell'hardware (HAL)
//                 che permette di utilizzare lo stesso progetto su più hardware simili
//
//==========================================================================================
//------------------------------------------------------------------------------------------
//=== Includes =============================================================================
//------------------------------------------------------------------------------------------
#include <stdbool.h>
#include "DRIVERS/HwConfig.h"   // Hardware Abstraction Layer Drivers
#include "LIBS/Led.h"           // Led Library
#include "LIBS/Uart.h"          // Uart Library
#include "LIBS/Puls.h"
#include "LIBS/SysTick.h"       // SysTick Library
#include "UTILS/uartstdio.h"    // Utility driver to provide simple UART console functions
#include "driverlib/sysctl.h"   // Prototypes for the system control driver.

//--------------------------------------------------------------------------------------------------
//=== Main =========================================================================================
//--------------------------------------------------------------------------------------------------
int main(void)
{
    // Inizializzazioni
    //
    // Set the clocking to run directly from the external crystal/oscillator.
    // The Tiva C Series LaunchPad uses a 16.0-MHz crystal to complete the TM4C123GH6PM
    // microcontroller main internal clock circuit.
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    LedInit();
    PulsInit();
    UartInit();

    // Autodiagnostica
    LedGreenOn();
    if(P1Press()) UartTest();        // Echo read chars fino alla pressione del del tasto Return
    if(P2Press()) UARTprintf("\nUart pronta...\n");
    LedGreenOff();

    // Ciclo infinito
    for(;;)
    {
        Led1On();
        DelayMs(100);
        Led1Off();
        DelayMs(900);
    }
}
//--------------------------------------------------------------------------------------------------
