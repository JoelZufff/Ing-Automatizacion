// -------------------------- Input/Output -------------------------- //
#byte   TRISA       = 0xF92
#byte   TRISB       = 0xF93
#byte   TRISC       = 0xF94
#byte   TRISD       = 0xF95
#byte   TRISE       = 0xF96

#byte   LATA        = 0xF89
#byte   LATB        = 0xF8A
#byte   LATC        = 0xF8B
#byte   LATD        = 0xF8C
#byte   LATE        = 0xF8D

#byte   PORTA       = 0xF80
#byte   PORTB       = 0xF81
#byte   PORTC       = 0xF82
#byte   PORTD       = 0xF83
#byte   PORTE       = 0xF84

// ------------------ Analog to Digital Converter ------------------- //
#byte   ADCON0      = 0xFC2
#byte   ADCON1      = 0xFC1
#byte   ADCON2      = 0xFC0
#word   ADRES       = 0xFC3

// ------------------------- INTERRUPCIONES ------------------------- //
#byte   INTCON      = 0xFF2
#byte   INTCON2     = 0xFF1
#byte   INTCON3     = 0xFF0

#byte   IPR1        = 0xF9F
#byte   IPR2        = 0xFA2

// ---------------------------- A D C ------------------------------- //
#word   ADRES       = 0xFC3
#byte   ADCON0      = 0xFC2
#byte   ADCON1      = 0xFC1
#byte   ADCON2      = 0xFC0

#byte   IPR1        = 0xF9F
#byte   IPR2        = 0xFA2

#byte   PIR1        = 0xF9E
#byte   PIR2        = 0xFA1

#byte   PIE1        = 0xF9D
#byte   PIE2        = 0xFA0

// --------------------------- TIMER 0 ------------------------------ //
const long *TMR0    = 0xFD6;
#byte   T0CON       = 0xFD5

// --------------------------- TIMER 1 ------------------------------ //
const long *TMR1    = 0xFCE;
#byte   T1CON       = 0xFCD

// --------------------------- TIMER 2 ------------------------------ //
#byte   TMR2        = 0xFCC
#byte   PR2         = 0xFCB
#byte   T2CON       = 0xFCA

// --------------------------- TIMER 3 ------------------------------ //
const long *TMR3    = 0xFB2;
#byte   T3CON       = 0xFB1

// -------------------------- Modulo CCP ---------------------------- //
const long *CCPR1   = 0xFBE;
#byte   CCP1CON     = 0xFBD

const long *CCPR2   = 0xFBB;
#byte   CCP2CON     = 0xFBA

#byte   ECCP1DEL    = 0xFB7
#byte   ECCP1AS     = 0xFB6














//const int   catodo[10]  = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67 };
//#define get_adc()                   (DONE = 1, delay_us(10), *ADRES)
