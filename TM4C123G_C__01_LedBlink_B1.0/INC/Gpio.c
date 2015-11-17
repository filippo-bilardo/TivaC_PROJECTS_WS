//------------------------------------------------------------------------------------------
//=== Includes =====================================================================================
//------------------------------------------------------------------------------------------
#include "Gpio.h"

//------------------------------------------------------------------------------------------
//=== Global Functions =============================================================================
//------------------------------------------------------------------------------------------
void GpioInitPortF()
{
	SYSCTL_RCGC2_R |= SYSCTL_PORTF;						// Abilitazione del clock per la portaF
	asm("NOP");	// è necessario aspettare che si propaghi

	//Sblocco la porta
	SET_REGISTER(PORTF, GPIOLOCK) = 0x4C4F434B;			// Sblocco la BaseAddress
	SET_REGISTER(PORTF, GPIOCR) = 0xFF;					// Abilito la modifica della porta

	//GREEN_LED_PORT_DIR_R |= GREEN_LED_PIN; 			// make pin out
	//GREEN_LED_PORT_AFSEL_R &= ~GREEN_LED_PIN;			// disable alt functionality
	//GREEN_LED_PORT_DEN_R |= GREEN_LED_PIN; 			// enable digital I/O
	//GREEN_LED_PORT_AMSEL_R &= ~GREEN_LED_PIN;			// disable analog functionality

	//Imposto tutti i pin come output digitali
	SET_REGISTER(PORTF, GPIODIR) |= GREEN_LED_PIN;  	// make pin out
	SET_REGISTER(PORTF, GPIODIR) |= BLUE_LED_PIN;   	// make pin out
	SET_REGISTER(PORTF, GPIOAMSEL) &= ~BLUE_LED_PIN;	// disable analog functionality
	SET_REGISTER(PORTF, GPIOAMSEL) &= ~GREEN_LED_PIN;	// disable analog functionality
	SET_REGISTER(PORTF, GPIOAFSEL) &= ~BLUE_LED_PIN;	// disable alt functionality
	SET_REGISTER(PORTF, GPIOAFSEL) &= ~GREEN_LED_PIN;	// disable alt functionality
	SET_REGISTER(PORTF, GPIODEN) |= GREEN_LED_PIN; 	// enable digital I/O
	SET_REGISTER(PORTF, GPIODEN) |= BLUE_LED_PIN; 		// enable digital I/O
	//SET_REGISTER(PORTF, GPIOPCTL) = 0;				// Multiplexer out = GPIO PORT

	//Disabilito le modifiche su tutti i pin
	SET_REGISTER(PORTF,GPIOCR) = 0x00;					// Disabilito la modifica della porta
}

void GpioSet(uint32_t Port, uint8_t Pin, uint8_t Stato)
{
	// Abilito la modifiche dei bit relativi a questo pin in tutti i registri del port
	SET_REGISTER(Port, GPIOCR) |= (1 << Pin);

	// Se voglio impostarlo come output
	if (Stato)
	{
		// Forzo il bit a 1
		SET_REGISTER(Port, GPIODIR) |= (1 << Pin);
		SET_REGISTER(Port, GPIODEN) |= (1 << Pin);
	}
	// Se voglio impostarlo come input
	else
	{
		// Forzo il bit a 0
		SET_REGISTER(Port, GPIODIR) &= ~(1 << Pin);
		SET_REGISTER(Port, GPIODEN) &= ~(1 << Pin);
	}

	// Disabilito la modifica della porta
	SET_REGISTER(Port, GPIOCR) = 0x00;
}

uint8_t GpioRead(uint32_t Port, uint8_t Pins)
{
	return (SET_REGISTER(Port,GPIODATA) & Pins);
}

void GpioWrite(uint32_t Port, uint8_t Pins, uint8_t Level)
{
	if (Level)
	{
		SET_REGISTER(Port,GPIODATA) |= Pins;
	}
	else
	{
		SET_REGISTER(Port,GPIODATA) &= ~Pins;
	}
}

