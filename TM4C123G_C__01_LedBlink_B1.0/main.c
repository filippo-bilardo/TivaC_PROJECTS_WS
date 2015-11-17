//==========================================================================================
//
// Project:	LedBlink
// Date:	13.11.15
// Author:	Filippo Bilardo
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  Lampeggio di un led presente nella scheda utilizzando un soft delay
//
// Ver		Date		Comment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// B1.0		13.11.15	Versione iniziale
//						Utilizzo di macro per l'accesso ai registri del microcontrollore
//
//==========================================================================================
//------------------------------------------------------------------------------------------
//=== Includes =============================================================================
//------------------------------------------------------------------------------------------
//#include <stdint.h>	//Libreria per tipi aritmetici C99
#include "INC/Gpio.h"

//------------------------------------------------------------------------------------------
//=== Prototipi delle funzioni =============================================================
//------------------------------------------------------------------------------------------
void SoftDelay(uint32_t millis);

//------------------------------------------------------------------------------------------
//=== Main =================================================================================
//------------------------------------------------------------------------------------------
void main(void)
{
	// Inizializzazioni
	GpioInitPortF();
	//GpioSet(PORTF, GREEN_LED_PIN, OUTPUT);
	//GpioSet(PORTF, BLUE_LED_PIN, OUTPUT);

	// Ciclo infinito
	for(;;)
	{
		//SET_REGISTER(PORTF, GPIODATA) = 0x8;        //output to the port
		GpioWrite(PORTF, BLUE_LED_PIN, HIGH);
		GpioWrite(PORTF, GREEN_LED_PIN, LOW);

		SoftDelay(100);

		//SET_REGISTER(PORTF, GPIODATA) = 0x0;        //output to the port
		GpioWrite(PORTF, BLUE_LED_PIN, LOW);
		GpioWrite(PORTF, GREEN_LED_PIN, HIGH);
		SoftDelay(100);
	}
}

//------------------------------------------------------------------------------------------
//=== Routines =============================================================================
//------------------------------------------------------------------------------------------
void SoftDelay(uint32_t millis)
{
	uint32_t i, TIME_MULTIPLIER=1500;

	for (i=0; i < millis*TIME_MULTIPLIER; i++)
	{
		asm("	NOP");
	}
}

