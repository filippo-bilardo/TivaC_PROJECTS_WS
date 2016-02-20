//==========================================================================================
//       _____   ____
//      |  ___| |  _ \
//      | |_    | |_| |
//      |  _|   |  _ /
//      | |     | |_| |
//  www.|_|     |_____/-labs.blogspot.it
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
// Author:  Filippo Bilardo
//
// Ver    Date       Comment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 1.0.0  27.11.13   Initial version
// 1.0.1  29.10.14   adeguamento commenti
//
//==========================================================================================
#ifndef _PULS
#define _PULS

//------------------------------------------------------------------------------------------
//=== Global constants =====================================================================
//------------------------------------------------------------------------------------------
#define PULS_NONE           0
#define PULS_P1             1
#define PULS_P2             2
#define PULS_P3             4
#define PULS_P4             8
#define _PULS_PRESS_TIME    10      // circa 10 msec - durata minimima pressione pulsante
#define _PULS_LLPRESS_TIME  3000    // circa 3 sec - durata minimima pressione lunga pulsante

//------------------------------------------------------------------------------------------
//=== Global function prototypes ===========================================================
//------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

extern void PulsInit(void);
extern int PulsGetClick(void);
extern int PulsGetPress(void);
extern int PulsGetLPress(void);
extern void PulsTestTask(void);
extern void PulsTest2(void);
//#ifdef PULS_D1
extern int P1Press(void);
extern int P1LPress(void);
extern int P1LLPress(void);
extern int P1Click(void);
//#endif
//#ifdef PULS_D2
extern int P2Press(void);
extern int P2LPress(void);
extern int P2LLPress(void);
extern int P2Click(void);
//#endif

#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------------------

#endif //_PULS
