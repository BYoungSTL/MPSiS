#include <msp430.h>
/*
 * main.c
 */
#pragma vector = PORT1_VECTOR
__interrupt void S1_interrupt_handler(void)
{
	if ((P1IN & BIT7) == 1){
	    if((P2IN & BIT2) == 0){
	    	if((P1OUT & BIT3) == 0){
	    		P1OUT |= BIT3;
	    	}else{
	    		P1OUT &= ~BIT3;
	    	}
	    }
	}
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    P1DIR &= ~BIT7;
    P1REN |= BIT7;
    P1SEL = 0;

    P2REN |= BIT2;
    P2DIR &= ~BIT2;
    P2SEL = 0;

    P1DIR |= BIT2;
    P1REN |= BIT2;


    P1DIR |= BIT3;
    P1REN |= BIT3;

    P1IES &= ~BIT7;
    P2IES &= ~BIT2;
    P1IFG &= ~BIT7;
    P2IFG &= ~BIT2;
    P1IE |= BIT7;
    P2IE |= BIT2;

    __bis_SR_register(GIE);
    while(1){
    	__no_operation();
    }
}
