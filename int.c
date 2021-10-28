#include <msp430.h>
#include "stdio.h"

/*
 * main.c
 */
#pragma vector = PORT2_VECTOR
__interrupt void S2_interrupt_handler(void)
{

	//V1.0 works
	__delay_cycles(180000);
		if((P1IN & BIT7) != 0){
	    		P1OUT ^= BIT3;

		}


	P2IFG &= ~BIT2;

}

#pragma vector = PORT1_VECTOR
__interrupt void S1_interrupt_handler(void){
	__delay_cycles(180000);
	if((P1OUT & BIT2) == 0){
		P1OUT |= BIT2;
		P1IFG &= ~BIT7;
		P1IES |= BIT7;
	}else{
		if((P2IN & BIT2) == 0){
			P1OUT &= ~BIT2;
			P1IFG &= ~BIT7;
			P1IES &= ~BIT7;
		}
	}

	P1IFG &= ~BIT7;
	__delay_cycles(180000);
}

void main(void) {
 	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer



    //BUTTON 1
    P1DIR &= ~BIT7;
    P1REN |= BIT7;
    P1SEL = 0;

    //BUTTON 2
    P2DIR &= ~BIT2;
    P2REN |= BIT2;
    P2SEL = 0;

    //LED 1
    P1DIR |= BIT2;
    P1OUT &= ~BIT2;

    //LED 2
    P1DIR |= BIT3;
    P1OUT &= ~BIT3;

    //INTERRUPT
    __bis_SR_register(GIE);

    P1IE |= BIT7;
    P2IE |= BIT2;
    P1IES &= ~BIT7;
    P2IES &= ~BIT2;
    P1IFG &= ~BIT7;
    P2IFG &= ~BIT2;

    __no_operation();

}
