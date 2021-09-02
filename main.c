#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    P1OUT = 0x00;
    P1DIR &= ~BIT7;
    P2DIR &= ~BIT2;
    P1DIR |= BIT3;
    P1SEL = 0;
    P1REN |= BIT3;
    //P1DS |= BIT7;
    //__no_operation();
    while(1){
    	if(P1IN&BIT7 == 0){
    		P1OUT |= BIT3;
    	}
    }
	return 0;
}
