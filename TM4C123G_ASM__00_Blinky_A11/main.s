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
; A1.1  13.11.15    Strutturazione del codice utilizzando routine e costanti
;
;==========================================================================================

;------------------------------------------------------------------------------------------
;=== Costanti =============================================================================
;------------------------------------------------------------------------------------------
  		.thumb

GPIO_PORTF_DATA_R       .EQU 0x400253FC	;PortF Data Register
GPIO_PORTF_DIR_R        .EQU 0x40025400	;PortF Data Direction Register
GPIO_PORTF_AFSEL_R      .EQU 0x40025420	;PortF Alternate function select
GPIO_PORTF_DEN_R        .EQU 0x4002551C	;PortF Data Enable Register
GPIO_PORTF_AMSEL_R      .EQU 0x40025528	;PortF Analog function
_SYSCTL_RCGC2_R         .EQU 0x400FE108
SYSCTL_RCGC2_GPIOF      .EQU 0x20  		;PortF Clock Gating Control

_DELAY					.EQU 800000

; Hardware Abstraction Layer
LED0_PIN                .EQU 0x04	;J4.02 PF3 31 - - SSI1Fss CAN0Tx T1CCP1 - - TRCLK
LED0_SYSCTL_PORT    	.EQU SYSCTL_RCGC2_GPIOF

;------------------------------------------------------------------------------------------
;=== Definizione dell'area dati ===========================================================
;------------------------------------------------------------------------------------------
		.data
   		.align 4
;------------------------------------------------------------------------------------------
;=== Definizione dell'area stack ==========================================================
;------------------------------------------------------------------------------------------
		.global __stack
STACKSIZE 	.set 256
__stack:	.usect ".stack", STACKSIZE, 4
;------------------------------------------------------------------------------------------
;=== Definizione dell'area istruzioni =====================================================
;------------------------------------------------------------------------------------------
		.text
		
SYSCTL_RCGC2_R		.field _SYSCTL_RCGC2_R, 32

LED0_PORT_DATA_R    .field GPIO_PORTF_DATA_R, 32
LED0_PORT_DIR_R     .field GPIO_PORTF_DIR_R, 32
LED0_PORT_AFSEL_R   .field GPIO_PORTF_AFSEL_R, 32
LED0_PORT_DEN_R     .field GPIO_PORTF_DEN_R, 32
LED0_PORT_AMSEL_R   .field GPIO_PORTF_AMSEL_R, 32

DELAY				.field _DELAY, 32
			
		.global main

;--------------------------------------------------------------------------------------------------
; VERSIONE:         1.0.0
; ULTIMA MODIFICA:  12.05.13
; INPUT:            nessuno
; OUTPUT:           nessuno
; REGISTRI USATI:	R0-R2
;
; Configurazione dell'hardware per l'utilizzo del led
;
; 1.0.0		12.05.13	Versione iniziale
;--------------------------------------------------------------------------------------------------
LedInit
		; Enable the GPIO port (clock) that is used for the on-board LED.
		;SYSCTL_RCGC2_R |=  LED0_SYSCTL_PORT; 	// PortF Clock Gating Control 	// activate port
		LDR R0, SYSCTL_RCGC2_R          ; R1 = &SYSCTL_RCGC2_R
		LDR R1, [R0]                    ; R1 = [R0]
		ORR R1, R1, #LED0_SYSCTL_PORT	; R1 = R1|LED0_SYSCTL_PORT
		STR R1, [R0]                    ; [R0] = R1
		;allow time for clock to start
		NOP								
		NOP
		; Imposta la direzione dei pin ai quali sono collegati i led (1=Output)
		;LED0_PORT_DIR_R |= LED0_PIN;           // J4.02 PF3   // make pin out
		LDR R0, LED0_PORT_DIR_R  		; R0 = &LED_DIR_R
		LDR R1, [R0]					; R1 = [R0]
		MOV	R2, #LED0_PIN				; R2 = LED0_PIN
		ORR R1, R1, R2					; R1 |= LED0_PIN
		STR R1, [R0]                    ; [R0] = R1
		; Abilitazione dei pin ai quali sono collegati i led
		;LED0_PORT_DEN_R |= 0x08;               // enable digital I/O
		LDR R0, LED0_PORT_DEN_R  		; R0 = &LED0_PORT_DEN_R
		LDR R1, [R0]                    ; R1 = [R0]
		MOV	R2, #LED0_PIN               ; R2 = LED0_PIN
		ORR R1, R1, R2                  ; R1 |= LED0_PIN
		STR	R1, [R0]                    ; [R0] = R1
		;LED0_PORT_AFSEL_R &= ~LED0_PIN;        // disable alt functionality
		LDR R0, LED0_PORT_AFSEL_R  		; R0 = &LED0_PORT_AFSEL_R
		LDR R1, [R0]                    ; R1 = [R0]
		MOV	R2, #LED0_PIN               ; R2 = LED0_PIN
		BIC R1, R1, R2                  ; R1 &= ~LED0_PIN
		STR	R1, [R0]                    ; [R0] = R1

		BX LR

main: 	.asmfunc

		; INIZIALIZZAZIONI
		BL 	LedInit

MainLoop

	;GPIO_PORTF_DATA_R |= 0x08;
	LDR R0, LED0_PORT_DATA_R 		; R0 = &FGPIO_PORTF_DATA_R
	LDR	R1, [R0]					; Leggo lo stato della porta
	MOV	R2, #0x08					; Maschera di accensione
	ORR	R1, R1, R2					; Resetto i bit ai quali sono collegati i led
	STR	R1, [R0]					; Scrivo sulla porta
	
	;for(i=0; i< coefficiente*delay_ms ; ++i) {asm("  nop");}
	LDR R0, DELAY 	;Load delay count
rit_1
	NOP
	NOP
	SUBS R0,R0,#1
	BNE	rit_1
		
	;GPIO_PORTF_DATA_R &= ~0x08;
	LDR R0, LED0_PORT_DATA_R 		; R0 = &FGPIO_PORTF_DATA_R
	LDR	R1, [R0]					; Leggo lo stato della porta
	MOV	R2, #0x08					; Maschera di accensione
	BIC	R1, R1, R2					; Resetto i bit ai quali sono collegati i led
	STR	R1, [R0]					; Scrivo sulla porta
	
	;for(i=0; i< coefficiente*delay_ms ; ++i) {asm("  nop");}
	LDR R0, DELAY 	;Load delay count
rit_2
	NOP
	NOP
	SUBS R0,R0,#1
	BNE	rit_2
		
	B MainLoop           ; Branch forever
	

	.endasmfunc
	.end

	