;==========================================================================================
;
; Project:  LedBlink
; Date:	    13.11.15
; Author:   Filippo Bilardo
;
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;
;  Lampeggio di un led presente nella scheda utilizzando un delay
;
; Ver   Date        Comment
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; A1.0  20.11.15    Versione iniziale
;                   Il firmware è realizzato con il numero minimo indispensabile
;                   di line di codice
;
;==========================================================================================

;------------------------------------------------------------------------------------------
;=== Costanti =============================================================================
;------------------------------------------------------------------------------------------
  		.thumb

GPIO_PORTF_DATA_R  		.EQU 0x400253FC	;PortF Data Register
GPIO_PORTF_DIR_R		.EQU 0x40025400	;PortF Data Direction Register
GPIO_PORTF_AFSEL_R      .EQU 0x40025420	;PortF Alternate function select
GPIO_PORTF_DEN_R  		.EQU 0x4002551C	;PortF Data Enable Register
GPIO_PORTF_AMSEL_R      .EQU 0x40025528	;PortF Analog function
SYSCTL_RCGC2_R 			.EQU 0x400FE108
SYSCTL_RCGC2_GPIOF		.EQU 0x20  		;PortF Clock Gating Control
DELAY					.EQU 800000

;------------------------------------------------------------------------------------------
;=== Definizione dell'area istruzioni =====================================================
;------------------------------------------------------------------------------------------
		.text
		
FSYSCTL_RCGC2_R		.field SYSCTL_RCGC2_R, 32
FGPIO_PORTF_DIR_R	.field GPIO_PORTF_DIR_R, 32
FGPIO_PORTF_DATA_R	.field GPIO_PORTF_DATA_R, 32
FGPIO_PORTF_DEN_R	.field GPIO_PORTF_DEN_R, 32
FGPIO_PORTF_AMSEL_R	.field GPIO_PORTF_AMSEL_R
FGPIO_PORTF_AFSEL_R	.field GPIO_PORTF_AFSEL_R
FDELAY				.field DELAY, 32
			
		.global main

main: 	.asmfunc

	;
	; Inizializzazione del pin 3 della porta F come output
	;
	;FSYSCTL_RCGC2_R |=  SYSCTL_RCGC2_GPIOF; 	// PortF Clock Gating Control 	// activate port
	LDR	R0, FSYSCTL_RCGC2_R			
	LDR R1, [R0]                    ; R1 = [R0]
	ORR	R1, R0, #SYSCTL_RCGC2_GPIOF
	STR	R1, [R0]
	NOP								;allow time for clock to start
	NOP
	;FGPIO_PORTF_DIR_R |= 0x08;		// J4.02 PF3 	// make pin out
	LDR	R0, FGPIO_PORTF_DIR_R
	MOV	R1, #0x08
	ORR	R1, R1, R0
	STR	R1, [R0]
	;GPIO_PORTF_AFSEL_R &= ~0x08;	// disable alt functionality
	LDR	R0, FGPIO_PORTF_AFSEL_R
	MOV	R1, #0x08
	BIC R1, R0, R1
	STR	R1, [R0]
	;GPIO_PORTF_DEN_R |= 0x08; 		// enable digital I/O
	LDR	R0, FGPIO_PORTF_DEN_R		
	MOV	R1, #0x08
	ORR	R1, R1, R0
	STR	R1, [R0]
	;GPIO_PORTF_AMSEL_R &= ~0x08;	// disable analog functionality
	LDR	R0, FGPIO_PORTF_AMSEL_R
	MOV	R1, #0x08
	BIC R1, R0, R1
	STR	R1, [R0]

MainLoop

	;GPIO_PORTF_DATA_R |= 0x08;
	LDR R0, FGPIO_PORTF_DATA_R 		; R0 = &FGPIO_PORTF_DATA_R
	LDR	R1, [R0]					; Leggo lo stato della porta
	MOV	R2, #0x08					; Maschera di accensione
	ORR	R1, R1, R2					; Resetto i bit ai quali sono collegati i led
	STR	R1, [R0]					; Scrivo sulla porta
	
	;for(i=0; i< coefficiente*delay_ms ; ++i) {asm("  nop");}
	LDR R0, FDELAY 	;Load delay count
rit_1
	NOP
	NOP
	SUBS R0,R0,#1
	BNE	rit_1
		
	;GPIO_PORTF_DATA_R &= ~0x08;
	LDR R0, FGPIO_PORTF_DATA_R 		; R0 = &FGPIO_PORTF_DATA_R
	LDR	R1, [R0]					; Leggo lo stato della porta
	MOV	R2, #0x08					; Maschera di accensione
	BIC	R1, R1, R2					; Resetto i bit ai quali sono collegati i led
	STR	R1, [R0]					; Scrivo sulla porta
	
	;for(i=0; i< coefficiente*delay_ms ; ++i) {asm("  nop");}
	LDR R0, FDELAY 	;Load delay count
rit_2
	NOP
	NOP
	SUBS R0,R0,#1
	BNE	rit_2
		
	B MainLoop           ; Branch forever
	

	.endasmfunc
	.end

	