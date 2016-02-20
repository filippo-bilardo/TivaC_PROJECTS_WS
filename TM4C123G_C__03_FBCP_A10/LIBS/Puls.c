//------------------------------------------------------------------------------------------
//=== Includes =============================================================================
//------------------------------------------------------------------------------------------
#include "../DRIVERS/HwConfig.h"    // Hardware Abstraction Layer Drivers
#include "../LIBS/SysTick.h"        // Serve la Routine DelayMs(ms)
//#include "HwTypes.h"
#include "Puls.h"
#include "Led.h"

//------------------------------------------------------------------------------------------
//=== Global Functions =====================================================================
//------------------------------------------------------------------------------------------
void PulsInit(void) {

	#ifdef PULS_D2
	SYSCTL_RCGC2_R |= PULS_D2_SYSCTL_RCGC2; 	// activate port
	PULS_D2_PORT_LOCK_R = GPIO_LOCK_KEY;			// Unlocks the GPIO_CR register
	GPIO_PORTF_CR_R = 0x01;        						// enable commit for PF0
	PULS_D2_PORT_DIR_R &= ~PULS_D2; 					// make pin in
	PULS_D2_PORT_DEN_R |= PULS_D2; 						// enable digital I/O
	PULS_D2_PORT_AFSEL_R &= ~PULS_D2;					// disable alt functionality
	PULS_D2_PORT_AMSEL_R &= ~PULS_D2;					// disable analog functionality
	PULS_D2_PORT_PUR_R |= PULS_D2;						// enable weak pull-up
	PULS_D2_PORT_PDR_R &= ~PULS_D2;						// disable weak pull-down
	//GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFF0FFF0)+0x00000000;
	#endif

	// PULS_D1
	#ifdef PULS_D1
	SYSCTL_RCGC2_R |= PULS_D1_SYSCTL_RCGC2; 	// activate port
	PULS_D1_PORT_DIR_R &= ~PULS_D1; 					// make pin in
	PULS_D1_PORT_DEN_R |= PULS_D1; 						// enable digital I/O
	PULS_D1_PORT_AFSEL_R &= ~PULS_D1;					// disable alt functionality
	PULS_D1_PORT_AMSEL_R &= ~PULS_D1;					// disable analog functionality
	PULS_D1_PORT_PUR_R |= PULS_D1;						// enable weak pull-up
	PULS_D1_PORT_PDR_R &= ~PULS_D1;						// disable weak pull-down
	#endif
}
//------------------------------------------------------------------------------------------
void PulsTestTask(void) {

	int p;

	for(;;)
	{
		p = PulsGetPress();
		if (p == (PULS_P1|PULS_P2)) {LedOff(); return;}

		//if (P1Press()) {led_red_on();} else {led_red_off();}
		//if (P2Press()) {led_blue_on();} else {led_blue_off();}
		if (P2Click()) {LedBlueToggle();}
		if (P1LPress()) {LedGreenToggle();}
		//if (P1LLPress()) {led_blue_toggle();}
		//if (P2LLPress()) {led_green_toggle();}
	}


	//	int p_status;
	//	p_status = HWREG(GPIO_PORTF_BASE + ((PULS_D1|PULS_D2) << 2));
	//	switch(p_status){                    // switches are negative logic on PF0 and PF4
	//		case 0x01: led_red_on(); break;   // SW1 pressed
	//		case 0x10: led_blue_on(); break;    // SW2 pressed
	//		case 0x00: led_green_on(); break;  // both switches pressed
	//		case 0x11: led_red_off(); led_blue_off(); led_green_off(); break;      // neither switch pressed
	//		default: led_red_off(); led_blue_off(); led_green_off(); // unexpected return value
	//	}
}
//------------------------------------------------------------------------------------------
#ifdef PULS_D1
int P1Press(void) {
	//return !HWREG(GPIO_PORTF_BASE + ((PULS_D1) << 2));
	return !(PULS_D1_PORT_DATA_R & PULS_D1);
}
//------------------------------------------------------------------------------------------
int P1LPress(void) {
// pressione pulsante - return quando press > PRESS_TIME

    int cont;
    // Controllo la pressione del tasto
    if(P1Press()) {
        // Controllo che il pulsante sia premuto per un tempo minimo
        for(cont=0; cont<_PULS_PRESS_TIME; ++cont) {
            DelayMs(1);
            if(!P1Press()) return 0;
        }
        return 1;
    }
    return 0;
}
//------------------------------------------------------------------------------------------
int P1LLPress(void) {
// pressione pulsante - return quando press > PRESS_TIME

    int cont;
    // Controllo la pressione del tasto
    if(P1Press()) {
        // Controllo che il pulsante sia premuto per un tempo minimo
        for(cont=0; cont<_PULS_LLPRESS_TIME; ++cont) {
            DelayMs(1);
            if(!P1Press()) return 0;
        }
        return 1;
    }
    return 0;
}
//------------------------------------------------------------------------------------------
int P1Click(void) {
// Timeout di 10 secondi
//
    int cont = 10000;

    // verifico che il pulsante sia stato premuto per un tempo minimo
    if(P1LPress()) {
        // aspetto che il pulsante venga rilasciato
        while(P1Press()) {
			if(--cont == 0) break;
			DelayMs(1);
		}
        return 1;
    }
    return 0;
}
#endif
//------------------------------------------------------------------------------------------
#ifdef PULS_D2
int P2Press(void) {
	//return !HWREG(GPIO_PORTF_BASE + ((PULS_D2) << 2));
	return !(PULS_D2_PORT_DATA_R & PULS_D2);
}
//------------------------------------------------------------------------------------------
int P2LPress(void) {
// pressione pulsante - return quando press > PRESS_TIME

    int cont;
    // Controllo la pressione del tasto
    if(P2Press()) {
        // Controllo che il pulsante sia premuto per un tempo minimo
        for(cont=0; cont<_PULS_PRESS_TIME; ++cont) {
            DelayMs(1);
            if(!P2Press()) return 0;
        }
        return 1;
    }
    return 0;
}
//------------------------------------------------------------------------------------------
int P2LLPress(void) {
// pressione pulsante - return quando press > PRESS_TIME

    int cont;
    // Controllo la pressione del tasto
    if(P2Press()) {
        // Controllo che il pulsante sia premuto per un tempo minimo
        for(cont=0; cont<_PULS_LLPRESS_TIME; ++cont) {
            DelayMs(1);
            if(!P2Press()) return 0;
        }
        return 1;
    }
    return 0;
}
//------------------------------------------------------------------------------------------
int P2Click(void) {
// Timeout di 10 secondi

    int cont = 10000;

    // verifico che il pulsante sia stato premuto per un tempo minimo
    if(P2LPress()) {
        // aspetto che il pulsante venga rilasciato
        while(P2Press()) {
			if(--cont == 0) break;
			DelayMs(1);
		}
        return 1;
    }
    return 0;
}
#endif
//------------------------------------------------------------------------------------------
int PulsGetClick(void) {
    #ifdef PULS_D1
    if(P1Click()) return PULS_P1;
    #endif
    #ifdef PULS_D2
    if(P2Click()) return PULS_P2;
    #endif
    #ifdef PULS_D3
    if(P3Click()) return PULS_P3;
    #endif
    #ifdef PULS_D4
    if(P4Click()) return PULS_P4;
    #endif
    return PULS_NONE;
}
//------------------------------------------------------------------------------------------
int PulsGetPress(void) {

	int puls = PULS_NONE;

	#ifdef PULS_D1
	if(P1Press()) puls |= PULS_P1;
	#endif
	#ifdef PULS_D2
	if(P2Press()) puls |= PULS_P2;
	#endif
	#ifdef PULS_D3
	if(P3Press()) puls |= PULS_P3;
	#endif
	#ifdef PULS_D4
	if(P4Press()) puls |= PULS_P4;
	#endif
	return puls;
}
//------------------------------------------------------------------------------------------
int PulsGetLPress(void) {
    #ifdef PULS_D1
    if(P1LPress()) return PULS_P1;
    #endif
    #ifdef PULS_D2
    if(P2LPress()) return PULS_P2;
    #endif
    #ifdef PULS_D3
    if(P3LPress()) return PULS_P3;
    #endif
    #ifdef PULS_D4
    if(P4LPress()) return PULS_P4;
    #endif
    return PULS_NONE;
}

//------------------------------------------------------------------------------------------
void PulsTest2(void) {
    #ifdef PULS_D1
    int p1=0;
    #endif
    #ifdef PULS_D2
    int p2=0;
    #endif
    #ifdef PULS_D3
    int p3=0;
    #endif
    #ifdef PULS_D4
    int p4=0;
    #endif

    #ifdef _LCD
	lcd_init();
    lcd_puts("\f Test pulsanti\nP1=5,P2=20-Fine");
    #endif
	//fprintf(stdout, "	Test pulsanti, P1=5,P2=20 -> Fine\n");
    for(;;)
    {
        #ifdef PULS_D1
        if((p1==5) && (p2==20))
        {
			#ifdef _LED
			LedInit();
            LedOff();
            #endif
            #ifdef _LCD
			lcd_init();
            lcd_puts("\f      Fine      \n Test pulsanti");
            #endif
			//fprintf(stdout, "	Fine test pulsanti \n");
            break;
        }
        #endif

        #ifdef PULS_D1
		//PulsInit();
        if(P1Click())
        {
            p1++;
			//fprintf(stdout, "	P1Click, p1=%d\n",p1);
            #ifdef _LCD
			lcd_init();
            sprintf(msg,"\fP1C P2P P3LP P4C\n%03u %03u  %03u %03u",p1,p2,p3,p4);
            lcd_puts(msg);
            #endif
            #ifdef LED0
			//LedInit();
            LedBlink(1, 1, 50);
            #endif
        }
        #endif

        #ifdef PULS_D2
		//PulsInit();
        if(P2LPress())
        {
            p2++;
			//fprintf(stdout, "	P2LPress, p2=%d\n",p2);
            #ifdef _LCD
			//lcd_init();
            sprintf(msg,"\fP1C P2P P3LP P4C\n%03u %03u  %03u %03u",p1,p2,p3,p4);
            lcd_puts(msg);
            #endif
            #ifdef LED1
			//LedInit();
            LedBlink(2, 1, 50);
            #endif
        }
        #endif

        #ifdef PULS_D3
		//PulsInit();
        if(P3LLPress())
        {
            p3++;
			//fprintf(stdout, "	P3LLPress, p3=%d\n",p3);
            #ifdef _LCD
			lcd_init();
            sprintf(msg,"\fP1C P2P P3LP P4C\n%03u %03u  %03u %03u",p1,p2,p3,p4);
            lcd_puts(msg);
            #endif
            #ifdef LED2
			//LedInit();
            LedBlink(4, 1, 50);
            #endif
		}
        #endif

        #ifdef PULS_D4
		//PulsInit();
        if(P4Click()) {
            p4++;
			//fprintf(stdout, "	P4Click p4=%d\n",p4);
            #ifdef _LCD
			lcd_init();
            sprintf(msg,"\fP1C P2P P3LP P4C\n%03u %03u  %03u %03u",p1,p2,p3,p4);
            lcd_puts(msg);
            #endif
            #ifdef LED3
			//LedInit();
            LedBlink(8, 1, 50);
            #endif
        }
        #endif
	}
	//fprintf(stdout, "... test pulsanti end.\n");
}
//------------------------------------------------------------------------------------------



