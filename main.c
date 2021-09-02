#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    P1DIR = 191;
    P2DIR = 253;
    P1DS = BIT7;
    if(P1BIT7 == 0){
    	P1OUT &= BIT3;
    }
	return 0;
}
