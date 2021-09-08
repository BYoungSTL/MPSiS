#include <msp430.h>
/*
 * main.c
 */
void delay(void);

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    P1OUT = 0;
    P1OUT |= BIT7;
    //P1DIR &= ~BIT7;
    P1REN |= BIT7;

    P2OUT = 0;
    P2OUT |= BIT2;
    P2REN |= BIT7;
    //P2DIR &= ~BIT2;

    P1DIR |= BIT3;

    P1SEL = 0;
    P1REN |= BIT3;

    int butt1_flag = 0;
    int butt2_flag = 0;
    int led1_state = 0;

    while(1){
    	int butt1 = (P1IN & BIT7) == 0;
    	int butt2 = (P2IN & BIT2) == 0;

    	if (butt2 == 1 && butt2_flag == 0) {
    		butt2_flag = 1;
    	}

    	if(butt1 == 1 && butt1_flag == 0) {
    		if(butt2 == 1) {
    			if(!led1_state) {
    				P1OUT |= BIT3;
    		    	led1_state = 1;
    		    } else {
    		    	P1OUT &= ~BIT3;
    		    	led1_state = 0;
    		    }
    		}
    	}



    	//hui mocha pizda jopa

    }
}

