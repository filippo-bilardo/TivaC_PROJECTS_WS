//------------------------------------------------------------------------------------------
//=== Includes =============================================================================
//------------------------------------------------------------------------------------------
// Standard libs
#include <stdint.h>
#include <stdbool.h>
// TI libs
#include "utils/uartstdio.h"    // Utility driver to provide simple UART console functions
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"
// My Libs
#include "Led.h"           		// Led Library
#include "Puls.h"          		// Puls Library
#include "Uart.h"          		// Uart Library
#include "FBCP.h"          		// FB Comunication Protocol Library


//------------------------------------------------------------------------------------------
//=== Constants/Local variables ============================================================
//------------------------------------------------------------------------------------------
#define L1_2_BUFF_LEN	  255	// lunghezza del buffer di ricezione
int l1_2_buffer[L1_2_BUFF_LEN];	// buffer di memoria
int l1_2_idx;					// puntatore ai dati del buffer
int l1_2_is_frame_avail;		// flag che segnala l'avvenuta ricezione del frame

//------------------------------------------------------------------------------------------
//=== Global Functions =====================================================================
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//
//  <inserire una breve descrizione della routine>
//
// INPUT:	<elenco dei parametri in ingresso alla funzione>
// OUTPUT:  <valori restituiti>
//
//  19.02.16    1.0     Versione iniziale
//  <data> <Revision History> <Descrivere per ogni revisione o cambio di versione le modifiche apportate>
//
void L1_2_PcToMicro_Init()
{
	Uart00_Init();				//inizializzo uart0
	l1_2_idx=0;					//puntatore a buffer
	l1_2_is_frame_avail=0;		//Flag che segnala l'avvenuta ricezione del frame
    UARTprintf("\nUart pronta...\n");
    UARTprintf("Digitare i caratteri del frame e premere <INVIO> per trasmetterlo.\n");
}

//------------------------------------------------------------------------------------------
//
//  <inserire una breve descrizione della routine>
//
// INPUT:	<elenco dei parametri in ingresso alla funzione>
// OUTPUT:  <valori restituiti>
//
//  19.02.16    1.0     Versione iniziale
//  <data> <Revision History> <Descrivere per ogni revisione o cambio di versione le modifiche apportate>
//
void L1_2_PcToMicro_Rx_Task()
{
	//controllo se e' disponibile un carattere sulla UART0
	if ( UARTCharsAvail(UART0_BASE) )
	{
		//prendo il carattere inviato dalla UART0
		l1_2_buffer[l1_2_idx]=UARTCharGetNonBlocking(UART0_BASE);
		UARTCharPut(UART0_BASE, l1_2_buffer[l1_2_idx]);

		//metto a 1 il semaforo quando ricevo il carattere
		//di fine farme "\n"
		if (l1_2_buffer[l1_2_idx] == 0xD)
		{
			l1_2_is_frame_avail=1;
			UARTCharPut(UART0_BASE, 0xA);
		}

		// incremento il puntatore
		l1_2_idx++;
	}
}

//------------------------------------------------------------------------------------------
//
//  <inserire una breve descrizione della routine>
//
// INPUT:	<elenco dei parametri in ingresso alla funzione>
// OUTPUT:  <valori restituiti>
//
//  19.02.16    1.0     Versione iniziale
//  <data> <Revision History> <Descrivere per ogni revisione o cambio di versione le modifiche apportate>
//
void L7_PcToMicro_Task()
{
	int cmd;

	//contorllo se è stato inviato un carattere tramite il semaforo is_rx_cmd_avail
	if (l1_2_is_frame_avail == 1)
	{
		// recupero il comando presente nel frame
		cmd=l1_2_buffer[0];

		//contollo quale carattere è stato inviato con lo switch case
		switch (cmd)
		{
			case 0x31:
				LedRedOn(); //led red on
				break;
			case 0x32:
				LedBlueOn(); //led red on
				break;
			case 0x33:
			case 115:
				LedOff();
				break;
			default:
				break;
		}

		l1_2_is_frame_avail=0;
		l1_2_idx=0;
	}
}
//------------------------------------------------------------------------------------------
//
//  <inserire una breve descrizione della routine>
//
// INPUT:	<elenco dei parametri in ingresso alla funzione>
// OUTPUT:  <valori restituiti>
//
//  19.02.16    1.0     Versione iniziale
//  <data> <Revision History> <Descrivere per ogni revisione o cambio di versione le modifiche apportate>
//
void L1_MicroToMicro_Init()
{
	Uart01_Init();				//inizializzo uart1
}

//------------------------------------------------------------------------------------------
//
//  <inserire una breve descrizione della routine>
//
// INPUT:	<elenco dei parametri in ingresso alla funzione>
// OUTPUT:  <valori restituiti>
//
//  19.02.16    1.0     Versione iniziale
//  <data> <Revision History> <Descrivere per ogni revisione o cambio di versione le modifiche apportate>
//
void L1_MicroToMicro_RxTask()
{
    char cThisChar;

    if (UARTCharsAvail(UART1_BASE))
    {
        cThisChar = UARTCharGet(UART1_BASE);

    	if (cThisChar == 'a') {
    		LedBlueOn();
    	}
    	if (cThisChar == 'b') {
    		LedBlueOff();
    	}
    }
}

//------------------------------------------------------------------------------------------
//
//  <inserire una breve descrizione della routine>
//
// INPUT:	<elenco dei parametri in ingresso alla funzione>
// OUTPUT:  <valori restituiti>
//
//  19.02.16    1.0     Versione iniziale
//  <data> <Revision History> <Descrivere per ogni revisione o cambio di versione le modifiche apportate>
//
void L1_MicroToMicro_TxTask()
{
    // Put a character to show start of example.  This will display on the
    // terminal.
    if (P1Press())
    {
    	UARTCharPut(UART1_BASE, 'a');
    }
    if (P2Press())
    {
    	UARTCharPut(UART1_BASE, 'b');
    }
}

