//------------------------------------------------------------------------------------------
//=== Includes =============================================================================
//------------------------------------------------------------------------------------------
// Standard libs
#include <stdbool.h>
#include <stdint.h>
// TI libs
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"    // Utility driver to provide simple UART console functions
// My libs
#include "Led.h"
#include "Puls.h"
#include "Uart.h"

//------------------------------------------------------------------------------------------
//=== Global Functions =====================================================================
//------------------------------------------------------------------------------------------
void Uart00_Init()
{
    // Enable the GPIO Peripheral used by the UART.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Configure GPIO Pins for UART mode.
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Use the internal 16MHz oscillator as the UART clock source.
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    // Configure the UART for 115,200, 8-N-1 operation.
    // This function uses SysCtlClockGet() or ui32SysClock to get the system clock
    // frequency.  This could be also be a variable or hard coded value
    // instead of a function call.
    UARTStdioConfig(0,115200,SysCtlClockGet());
    //BUGFIX: la seguente routine a volte non funziona
    //UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
    //		(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}


int Uart00_Test()
{
    char cThisChar;

    // Put a character to show start of example.  This will display on the
    // terminal.
    UARTCharPut(UART0_BASE, '\n');
    UARTCharPut(UART0_BASE, '!');

    // Enter a loop to read characters from the UART, and write them back
    // (echo).  When a line end is received, the loop terminates.
    do
    {
        // Read a character using the blocking read function.  This function
        // will not return until a character is available.
        cThisChar = UARTCharGet(UART0_BASE);

        // Write the same character using the blocking write function.  This
        // function will not return until there was space in the FIFO and
        // the character is written.
        UARTCharPut(UART0_BASE, cThisChar);
    }
    while((cThisChar != '\n') && (cThisChar != '\r'));

    // Put a character to show the end of the example.  This will display on
    // the terminal.
    //BUGFIX: tre charPut non permettono la compilazione
    //UARTCharPut(UART0_BASE, '@');
    UARTCharPut(UART0_BASE, '\n');
    UARTCharPut(UART0_BASE, '\r');

    // Return no errors
    return(0);
}

void Uart01_Init()
{
    // Enable the GPIO Peripheral used by the UART.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Configure GPIO Pins for UART mode.
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Use the internal 16MHz oscillator as the UART clock source.
    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);

    // Configure the UART for 115,200, 8-N-1 operation.
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,
    		(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}


