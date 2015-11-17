/*
 * Led_driver.h
 *
 *  Created on: 11/set/2015
 *      Author: Giulio Vitale
 */

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

//Include librerie standard del compilatore
#include <stdbool.h>
#include <stdint.h>	//Libreria per tipi aritmetici C99
//Include librerie standard della CPU
#include "inc/hw_memmap.h"		//Indirizzi delle aree di memoria
#include "inc/hw_types.h"		//Accesso ai registri hardware delle periferiche
//Include driver standard relative alla scheda
//Funzioni di livello 1
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/debug.h"

//*****************************************************************************
//
//! This enumerated type defines either one or both EVALBOT LEDs.  It is used
//! by functions which change the state of the LEDs.
//
//*****************************************************************************
typedef enum
{
    //
    //! Both LEDs will be affected.
    //
    BOTH_LEDS = 0,

    //
    //! LED 1 on the right side of the EVALBOT will be affected.
    //
    LED_1,

    //
    //! LED 2 on the left side of the EVALBOT will be affected.
    //
    LED_2
}
tLED;

//*****************************************************************************
//
// Prototypes for the APIs.
// FUNZIONI driver di LIVELLO 2
//
//*****************************************************************************
extern void LEDsInit(void);
extern void LED_Off(tLED eLED);
extern void LED_On(tLED eLED);
extern void LED_Toggle(tLED eLED);

#endif /* LED_DRIVER_H_ */
