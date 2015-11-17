//==========================================================================================
//       _____   ____
//      |  ___| |  _ \
//      | |_    | |_| |
//      |  _|   |  _ /
//	    | |     | |_| |
//	www.|_|     |_____/-labs.blogspot.it
//
// Led driver: Funzioni per l'utilizzo dei led presenti nella scheda
//
// Open Source Licensing
// This program is free software: you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// Author:	Filippo Bilardo
//
// Ver    	Date        Comment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 1.0.0	15.11.15 	Initial version
//
//==========================================================================================
#ifndef _UART
#define _UART

//------------------------------------------------------------------------------------------
//=== Includes =============================================================================
//------------------------------------------------------------------------------------------
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

//------------------------------------------------------------------------------------------
//=== Function prototypes ==================================================================
//------------------------------------------------------------------------------------------
void UartInit(void);
int UartTest(void);

//------------------------------------------------------------------------------------------
#endif //_UART
