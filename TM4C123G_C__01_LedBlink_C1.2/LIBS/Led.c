//------------------------------------------------------------------------------------------
//=== Includes =============================================================================
//------------------------------------------------------------------------------------------
//Include librerie standard del compilatore
#include <stdbool.h>
#include <stdint.h>                 // Libreria per tipi aritmetici C99
//Include librerie standard della CPU
#include "inc/hw_memmap.h"          //Indirizzi delle aree di memoria
#include "inc/hw_types.h"           //Accesso ai registri hardware delle periferiche
//Include driver standard relative alla scheda. Funzioni di livello 1
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/debug.h"
//Include driver personalizzati. Funzioni di livello 2
#include "../DRIVERS/HwConfig.h"    // Hardware Abstraction Layer Drivers
#include "../LIBS/SysTick.h"        // Serve la Routine DelayMs(ms)
#include "Led.h"

//------------------------------------------------------------------------------------------
//=== Global Functions =====================================================================
//------------------------------------------------------------------------------------------
void LedInit(void) {
    // LED1
    #ifdef LED1_PIN
    // Enable the GPIO port used to control the LEDs.
    SysCtlPeripheralEnable(LED1_SYSCTL_PERIPH);
    // Set the LED GPIOs as output.
    GPIOPinTypeGPIOOutput(LED1_PORTF_BASE, LED1_PIN);
    #endif

    // LED BLUE
    #ifdef BLUE_LED_PIN
    SYSCTL_RCGC2_R |= BLUE_LED_SYSCTL_RCGC2;    // activate port
    BLUE_LED_PORT_DIR_R |= BLUE_LED_PIN;        // make pin out
    BLUE_LED_PORT_AFSEL_R &= ~BLUE_LED_PIN;     // disable alt functionality
    BLUE_LED_PORT_DEN_R |= BLUE_LED_PIN;        // enable digital I/O
    BLUE_LED_PORT_AMSEL_R &= ~BLUE_LED_PIN;     // disable analog functionality
    #endif

    // LED GREEN
    #ifdef GREEN_LED_PIN
    SYSCTL_RCGC2_R |= GREEN_LED_SYSCTL_RCGC2;   // activate port
    GREEN_LED_PORT_DIR_R |= GREEN_LED_PIN;      // make pin out
    GREEN_LED_PORT_AFSEL_R &= ~GREEN_LED_PIN;   // disable alt functionality
    GREEN_LED_PORT_DEN_R |= GREEN_LED_PIN;      // enable digital I/O
    GREEN_LED_PORT_AMSEL_R &= ~GREEN_LED_PIN;   // disable analog functionality
    #endif
}
//------------------------------------------------------------------------------------------
void LedOn(void) {
    #ifdef LED0
    Led0On();
    #endif
    #ifdef LED1
    Led1On();
    #endif
    #ifdef LED2
    Led2On();
    #endif
    #ifdef LED3
    Led3On();
    #endif
}
//------------------------------------------------------------------------------------------
void LedOff(void) {
    #ifdef LED0
    Led0Off();
    #endif
    #ifdef LED1
    Led1Off();
    #endif
    #ifdef LED2
    Led2Off();
    #endif
    #ifdef LED3
    Led3Off();
    #endif
}
//------------------------------------------------------------------------------------------
void LedBlink(uint8_t val, uint16_t cont, uint16_t delay) {
    uint8_t i;
    for(i=0;i<cont;++i)
    {
        LedHex(val);
        DelayMs(delay);
        LedOff();
        DelayMs(delay);
    }
}
//------------------------------------------------------------------------------------------
void LedTest(void) {
    #ifdef RED_LED_PIN
    LedRedOn(); DelayMs(34); LedRedOff(); DelayMs(34);
    LedRedOn(); DelayMs(34); LedRedOff(); DelayMs(73);
    #endif
    #ifdef BLUE_LED_PIN
    LedBlueOn(); DelayMs(34); LedBlueOff(); DelayMs(34);
    LedBlueOn(); DelayMs(34); LedBlueOff(); DelayMs(73);
    #endif
    #ifdef GREEN_LED_PIN
    LedGreenOn(); DelayMs(34); LedGreenOff(); DelayMs(34);
    LedGreenOn(); DelayMs(34); LedGreenOff(); DelayMs(73);
    #endif
    #ifdef RED_LED_PIN
    #ifdef BLUE_LED_PIN
    #ifdef GREEN_LED_PIN
    LedWhiteOn(); DelayMs(34); LedWhiteOff(); DelayMs(34);
    LedWhiteOn(); DelayMs(34); LedWhiteOff(); DelayMs(73);
    #endif
    #endif
    #endif
}
//------------------------------------------------------------------------------------------
void LedTest2(void) {
    uint8_t i;
    LedBlink(0xFF,3,50);
    for(i=0; i<4; ++i) {LedHex(2 << i); DelayMs(100);}
    for(i=1; i<4; ++i) {LedHex(8 >> i); DelayMs(100);}
    LedOff();
}
//------------------------------------------------------------------------------------------
void LedHex(uint8_t val) {
    #ifdef LED0
    if((val&0x01) == 0x01) Led0On(); else Led0Off();
    #endif
    #ifdef LED1
    if((val&0x02) == 0x02) Led1On(); else Led1Off();
    #endif
    #ifdef LED2
    if((val&0x04) == 0x04) Led2On(); else Led2Off();
    #endif
    #ifdef LED3
    if((val&0x08) == 0x08) Led3On(); else Led3Off();
    #endif
    #ifdef LED4
    if((val&0x10) == 0x10) Led4On(); else Led4Off();
    #endif
    #ifdef LED5
    if((val&0x20) == 0x20) Led5On(); else Led5Off();
    #endif
    #ifdef LED6
    if((val&0x40) == 0x40) Led6On(); else Led6Off();
    #endif
    #ifdef LED7
    if((val&0x80) == 0x80) Led7On(); else Led7Off();
    #endif
}
//------------------------------------------------------------------------------------------
#ifdef RED_LED_PIN
void LedRedOn(void) {RED_LED_PORT_DATA_R |= RED_LED_PIN;}
void LedRedOff(void) {RED_LED_PORT_DATA_R &= ~RED_LED_PIN;}
void LedRedToggle(void) {RED_LED_PORT_DATA_R ^= RED_LED_PIN;}
#endif
//------------------------------------------------------------------------------------------
#ifdef BLUE_LED_PIN
void LedBlueOn(void) {BLUE_LED_PORT_DATA_R |= BLUE_LED_PIN;}
void LedBlueOff(void) {BLUE_LED_PORT_DATA_R &= ~BLUE_LED_PIN;}
void LedBlueToggle(void) {BLUE_LED_PORT_DATA_R ^= BLUE_LED_PIN;}
#endif
//------------------------------------------------------------------------------------------
#ifdef GREEN_LED_PIN
void LedGreenOn(void) {GREEN_LED_PORT_DATA_R |= GREEN_LED_PIN;}
void LedGreenOff(void) {GREEN_LED_PORT_DATA_R &= ~GREEN_LED_PIN;}
void LedGreenToggle(void) {GREEN_LED_PORT_DATA_R ^= GREEN_LED_PIN;}
#endif
//------------------------------------------------------------------------------------------
#ifdef RED_LED_PIN
#ifdef BLUE_LED_PIN
#ifdef GREEN_LED_PIN
void LedWhiteOn(void) {LedRedOn(); LedBlueOn(); LedGreenOn();}
void LedWhiteOff(void) {LedRedOff(); LedBlueOff(); LedGreenOff();}
void LedWhiteToggle(void) {LedRedToggle(); LedBlueToggle(); LedGreenToggle();}
#endif
#endif
#endif
//------------------------------------------------------------------------------------------
#ifdef LED0
void Led0On(void) {
    #ifdef RED_LED_PIN
    LedRedOn();
    #endif
}
void Led0Off(void) {
    #ifdef RED_LED_PIN
    LedRedOff();
    #endif
}
void Led0Toggle(void) {
    #ifdef RED_LED_PIN
    LedRedToggle();
    #endif
}
#endif
//------------------------------------------------------------------------------------------
#ifdef LED1
void Led1On(void) {LedBlueOn();}
void Led1Off(void) {LedBlueOff();}
void Led1Toggle(void) {LedBlueToggle();}
#endif
//------------------------------------------------------------------------------------------
#ifdef LED2
void Led2On(void) {LedGreenOn();}
void Led2Off(void) {LedGreenOff();}
void Led2Toggle(void) {LedGreenToggle();}
#endif
//------------------------------------------------------------------------------------------
#ifdef LED3
void Led3On(void) {
    #ifdef RED_LED_PIN
    LedWhiteOn();
    #endif
}
void Led3Off(void) {
    #ifdef RED_LED_PIN
    LedWhiteOff();
    #endif
}
void Led3Toggle(void) {
    #ifdef RED_LED_PIN
    LedWhiteToggle();
    #endif
}
#endif
//------------------------------------------------------------------------------------------
