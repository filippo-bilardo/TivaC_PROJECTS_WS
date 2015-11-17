//==========================================================================================
//
// Project:	LedBlink
// Date:	13.11.15
// Author:	Filippo Bilardo
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  Lampeggio di un led presente nella scheda utilizzando un delay
//
//  Nota: includere nel progetto:
//	nel file search path del linker il file della TI driverlib.lib
//  e nell'include path dell'Arm compiler la cartella TivaWare
//
// Ver		Date		Comment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// C1.0		13.11.15	Versione iniziale
//						Il firmware è realizzato utilizzando le librerie fornite dalla TI
// C1.1		13.11.15	integrazione delle librerie fornite dalla TI con dei driver
//						personalizzati di secondo livello per l'accesso all'hardware
//
//==========================================================================================
//------------------------------------------------------------------------------------------
//=== Includes =============================================================================
//------------------------------------------------------------------------------------------
#include "LIBS/Led_driver.h"
#include "LIBS/SysTick.h"

//------------------------------------------------------------------------------------------
//=== Main =================================================================================
//------------------------------------------------------------------------------------------
void main(void)
{
	// Inizializzazioni
	LEDsInit();

	// Ciclo infinito
	for(;;)
	{
		LED_On(LED_1);
		DelayMs(300);
		LED_Off(LED_1);
		DelayMs(300);
		LED_On(LED_2);
		DelayMs(300);
		LED_Off(LED_2);
		DelayMs(300);
	}
}
