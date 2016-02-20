//==================================================================================================
//       _____   ____
//      |  ___| |  _ \
//      | |_    | |_| |
//      |  _|   |  _ /
//	    | |     | |_| |
//	www.|_|     |_____/-labs.blogspot.it
//
// Filename:    hwconfig.h
// Description: Hardware abstraction layer Drivers for LM4F120
//    
// Open Source Licensing 
//
// This program is free software: you can redistribute it and/or modify it under the terms of 
// the GNU General Public License as published by the Free Software Foundation, either version 3 
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; without
// even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.  
// If not, see <http://www.gnu.org/licenses/>.
//
// Author:	Filippo Bilardo
//
// Ver		Date   		Comment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 1.0.0	12.11.12	Initial version
// 1.0.1	29.10.14 	adeguamento commenti
// 1.0.2	29.12.14 	Aggiunti pin controllo motore (non compatibili con termostato)
//
//==================================================================================================

#ifndef __HWCONFIG_H__
#define __HWCONFIG_H__

#ifdef __cplusplus
extern "C"
{
#endif

//--------------------------------------------------------------------------------------------------
//=== Includes =====================================================================================
//--------------------------------------------------------------------------------------------------
#include "tm4c1231h6pm.h"
#include "HwConfig_Launchpad.h"
//#include "HwConfig_MotBoard-A11.h"

//--------------------------------------------------------------------------------------------------
//=== Global function prototypes ===================================================================
//--------------------------------------------------------------------------------------------------
// file startup.s
extern void DisableInterrupts(void); // Disable interrupts
extern void EnableInterrupts(void);  // Enable interrupts
extern long StartCritical (void);    // previous I bit, disable interrupts
extern void EndCritical(long sr);    // restore I bit to previous value
extern void WaitForInterrupt(void);  // low power mode

//--------------------------------------------------------------------------------------------------
//=== Global constants =============================================================================
//--------------------------------------------------------------------------------------------------
//
// Define pin mapping.
//
//J1.01 3.3V
//J1.02 PB5 57 AIN11 - SSI2Fss - T1CCP1 CAN0Tx - -
//J1.03 PB0 45 - U1Rx - - T2CCP0 - - -
//J1.04 PB1 46 - U1Tx - - T2CCP1 - - -
//J1.05 PE4 59 AIN9 U5Rx - I2C2SCL - CAN0Rx - -
//J1.06 PE5 60 AIN8 U5Tx - I2C2SDA - CAN0Tx - -
//J1.07 PB4 58 AIN10 - SSI2Clk - T1CCP0 CAN0Rx - -
//J1.08 PA5 22 - - SSI0Tx - - - - -
//J1.09 PA6 23 - - - I2C1SCL - - - -
//J1.10 PA7 24 - - - I2C1SDA - - - -

//J3.01 5.0V
//J3.02 GND
//J3.03 PD0 61 AIN7 SSI3Clk SSI1Clk I2C3SCL WT2CCP0 - - -
//J3.04 PD1 62 AIN6 SSI3Fss SSI1Fss I2C3SDA WT2CCP1 - - -
//J3.05 PD2 63 AIN5 SSI3Rx SSI1Rx - WT3CCP0 - - -
//J3.06 PD3 64 AIN4 SSI3Tx SSI1Tx - WT3CCP1 - - -
//J3.07 PE1 8 AIN2 U7Tx - - - - - -
//J3.08 PE2 7 AIN1 - - - - - - -
//J3.09 PE3 6 AIN0 - - - - - - -
//J3.10(1) PF1 29 - U1CTS SSI1Tx - T0CCP1 - C1o TD1
//(1) Not recommended for BoosterPack use. This signal tied to on-board function via a 0-O resistor.

//J2.01 GND
//J2.02 PB2 47 - - - I2C0SCL T3CCP0 - - -
//J2.03 PE0 9 AIN3 U7Rx - - - - - -
//J2.04(1) PF0 28 - U1RTS SSI1Rx CAN0Rx T0CCP0 NMI C0o -
//J2.05 RESET
//J2.06(2) PB7 4 - - SSI2Tx - T0CCP1 - - -
//J2.07(3) PB6 1 - - SSI2Rx - T0CCP0 - - -
//J2.08 PA4 21 - - SSI0Rx - - - - -
//J2.09 PA3 20 - - SSI0Fss - - - - -
//J2.10 PA2 19 - - SSI0Clk - - - - -
//J2.06 (PB7) is also connected via a 0-O resistor to J3.04 (PD1).
//J2.07 (PB6) is also connected via a 0-O resistor to J3.03 (PD0).
//(2) J2.06 (PB7) is also connected via a 0-O resistor to J3.04 (PD1).
//(3) J2.07 (PB6) is also connected via a 0-O resistor to J3.03 (PD0).

//J4.01(1) PF2 30 - - SSI1Clk - T1CCP0 - - TRD0
//J4.02(1) PF3 31 - - SSI1Fss CAN0Tx T1CCP1 - - TRCLK
//J4.03 PB3 48 - - - I2C0SDA T3CCP1 - - -
//J4.04 PC4 16 C1- U4Rx U1Rx - WT0CCP0 U1RTS - -
//J4.05 PC5 15 C1+ U4Tx U1Tx - WT0CCP1 U1CTS - -
//J4.06 PC6 14 C0+ U3Rx - - WT1CCP0 - - -
//J4.07 PC7 13 C0- U3Tx - - WT1CCP1 - - -
//J4.08 PD6 53 - U2Rx - - WT5CCP0 - - -
//J4.09(1) PD7 10 - U2Tx - - WT5CCP1 NMI - -
//J4.10(1) PF4 5 - - - - T2CCP0 - - -
//(1) Not recommended for BoosterPack use. This signal tied to on-board function via a 0-O resistor.



//--------------------------------------------------------------------------------------------------
//=== Global function prototypes ===================================================================
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//=== Type definitions (typedef) ===================================================================
//=== Local constants  =============================================================================
//=== Local variables ==============================================================================
//=== Local function prototypes ====================================================================
//--------------------------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif //  __HWCONFIG_H__
