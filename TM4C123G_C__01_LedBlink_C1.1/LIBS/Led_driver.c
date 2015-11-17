/*
 * Led_driver.c
 *
 *  Created on: 11/set/2015
 *      Author: Giulio Vitale
 */

#include "../LIBS/Led_driver.h"
//*****************************************************************************
//
//! Initializes the EVALBOT's LEDs
//!
//! This function must be called to initialize the GPIO pins used to control
//! EVALBOT's LEDs prior to calling LED_Off(), LED_On() or LED_Toggle().
//!
//! \return None.
//
//*****************************************************************************
void
LEDsInit (void)
{
    //
    // Enable the GPIO port used to control the LEDs.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Set the LED GPIOs as output.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3);

    //
    // Turn off both LEDs
    //
    LED_Off(BOTH_LEDS);
}

//*****************************************************************************
//
//! Turn one or both of the EVALBOT LEDs on.
//!
//! \param eLED indicates the LED or LEDs to turn on.  Valid values are \e
//!        LED_1, \e LED_2 or \e BOTH_LEDS.
//!
//! This function may be used to light either one or both of the LEDs on the
//! EVALBOT.  Callers must ensure that they have previously called LEDsInit().
//!
//! \return None.
//
//*****************************************************************************
void
LED_On(tLED eLED)
{
    //
    // Check for invalid parameter values.
    //
    ASSERT((eLED == BOTH_LEDS) || (eLED == LED_1) || (eLED == LED_2));

    //
    // Which LED are we to turn on?
    //
    switch (eLED)
    {
        //
        // Turn both LEDs on.
        //
        case BOTH_LEDS:
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3,
                             GPIO_PIN_2 | GPIO_PIN_3);
            break;
        }

        //
        // Turn LED 1 on.
        //
        case LED_1:
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
            break;
        }

        //
        // Turn LED 2 on.
        //
        case LED_2:
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            break;
        }

        //
        // An invalid LED value was passed.
        //
        default:
            break;
    }
}

//*****************************************************************************
//
//! Turn one or both of the EVALBOT LEDs off.
//!
//! \param eLED indicates the LED or LEDs to turn off.  Valid values are \e
//!        LED_1, \e LED_2 or \e BOTH_LEDS.
//!
//! This function may be used to turn off either one or both of the LEDs on the
//! EVALBOT.  Callers must ensure that they have previously called LEDsInit().
//!
//! \return None.
//
//*****************************************************************************
void
LED_Off (tLED eLED)
{
    //
    // Check for invalid parameter values.
    //
    ASSERT((eLED == BOTH_LEDS) || (eLED == LED_1) || (eLED == LED_2));

    //
    // Which LED are we to turn off?
    //
    switch (eLED)
    {
        //
        // Turn both LEDs off.
        //
        case BOTH_LEDS:
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3, 0);
            break;
        }

        //
        // Turn LED 1 off.
        //
        case LED_1:
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
            break;
        }

        //
        // Turn LED 2 off.
        //
        case LED_2:
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
            break;
        }

        //
        // An invalid value was passed.
        //
        default:
            break;
    }
}

//*****************************************************************************
//
//! Toggle one or both of the EVALBOT LEDs.
//!
//! \param eLED indicates the LED or LEDs to toggle.  Valid values are \e
//!        LED_1, \e LED_2 or \e BOTH_LEDS.
//!
//! This function may be used to toggle either one or both of the LEDs on the
//! EVALBOT.  If the LED is currently lit, it will be turned off and vice verse.
//! Callers must ensure that they have previously called LEDsInit().
//!
//! \return None.
//
//*****************************************************************************
void
LED_Toggle (tLED eLED)
{
    //
    // Check for invalid parameter values.
    //
    ASSERT((eLED == BOTH_LEDS) || (eLED == LED_1) || (eLED == LED_2));

    //
    // Which LED are we to toggle?
    //
    switch (eLED)
    {
        //
        // Toggle both LEDs.
        //
        case BOTH_LEDS:
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3,
                      ~GPIOPinRead(GPIO_PORTF_BASE,
                                       GPIO_PIN_2 | GPIO_PIN_3));
             break;
        }

        //
        // Toggle LED 1.
        //
        case LED_1:
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,
                             ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2));
            break;
        }

        //
        // Toggle LED 2.
        //
        case LED_2:
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,
                             ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3));
            break;
        }

        //
        // An invalid value was passed.
        //
        default:
            break;
    }
}

