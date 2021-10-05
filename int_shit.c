#include <msp430.h>
/*
 * main.c
 */
#pragma vector = PORT2_VECTOR
__interrupt void S2_interrupt_handler(void)
{

	if((P1IES & BIT7) == 1){
	    	if((P1OUT & BIT3) == 0){
	    		P1OUT |= BIT3;
	    	}else{
	    		P1OUT &= ~BIT3;
	    	}
	}

//	if((P1IFG & BIT7) == 0){
//		    	if((P1OUT & BIT3) == 0){
//		    		P1OUT |= BIT3;
//		    		P1IFG &= ~BIT7;
//		    		P2IFG &= ~BIT2;
//		    	}else{
//		    		P1OUT &= ~BIT3;
//		    		P1IFG &= ~BIT7;
//		    		P2IFG &= ~BIT2;
//		    	}
//		}

	//P1OUT |= BIT3;

	//button 2
	/*if((P1OUT & BIT2) == 0){
	    			P1OUT |= BIT2;
	    		}else{
	    			if((P2IN & BIT2) == 1){
	    				P1OUT &= ~BIT2;
	    			}
	    		}
	 */
	P1IFG &= ~BIT7;
	P2IFG &= ~BIT2;
}

#pragma vector = PORT1_VECTOR
__interrupt void S1_interrupt_handler(void){
//	if((P1OUT & BIT2) == 0){
//		P1OUT |= BIT2;
//		P1IFG &= ~BIT7;
//		P2IFG &= ~BIT2;
//		//P1IES
//	}

	if((P1IES & BIT7) == 1)
	{
		P1IES &= ~BIT7;
		P1IFG &= ~BIT7;
	}else{
		if((P1IES & BIT7) == 0)
		{
			P1IES |= BIT7;
			P1IFG &= ~BIT7;
		}
	}
}

void main(void) {
 	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    __bis_SR_register(GIE);

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
    P1REN |= BIT2;
    P1OUT &= ~BIT2;

    //LED 2
    P1DIR |= BIT3;
    P1REN |= BIT3;
    P1OUT &= ~BIT3;

    //INTERRUPT
    P1IES |= BIT7;
    P2IES &= ~BIT2;
    P1IFG &= ~BIT7;
    P2IFG &= ~BIT2;
    P1IE |= BIT7;
    P2IE |= BIT2;


    while(1){
    	__no_operation();
    }
}
