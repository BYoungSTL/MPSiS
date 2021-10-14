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
    P1SEL = 0;

    P2OUT = 0;
    P2OUT |= BIT2;
    P2REN |= BIT2;
    //P2DIR &= ~BIT2;
    P2SEL = 0;

    P1DIR |= BIT2;
    P1REN |= BIT2;


    P1DIR |= BIT3;
    P1REN |= BIT3;

    int butt1_flag = 0;
    int butt2_flag = 0;

    while(1){
    	int butt1 = (P1IN & BIT7) == 0;
    	int butt2 = (P2IN & BIT2) == 0;


    	//start of first LED
    	if (butt2 == 1 && butt2_flag == 0) {
    		butt2_flag = 1;
    	}

    	if (butt1 == 0 && butt1_flag == 0){
    		if(butt2_flag == 1 && butt2 == 0){
    			if((P1OUT & BIT3) == 0){
    				P1OUT |= BIT3;
    			}else{
    				P1OUT &= ~BIT3;
    			}
    			butt2_flag = 0;
    		}
    	}
    	//end of first LED

    	//start of second LED
    	if (butt1 == 1 && butt1_flag == 0) {
    		butt1_flag = 1;
    	}

    	if(butt1_flag == 1 && butt1 == 0){
    		butt2_flag = 0;
    		if((P1OUT & BIT2) == 0){
    			P1OUT |= BIT2;
    			butt1_flag = 0;
    		}

    		butt1_flag = 0;
    	}

    	if(butt2_flag == 1){
    	    if(butt1 == 1){
    	    	P1OUT &= ~BIT2;
    	    	//butt1_flag = 0;
    	    }
    	}
    	//end of second LED
    }
}

