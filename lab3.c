#include <msp430.h>

int CURRENT_TIMER = 0; // 0 - WT, 1 - TA1
int interruptsCount = 0;
int state_led = 0;



#pragma vector = TIMER1_A0_VECTOR
__interrupt void TIMER_1 (void) {
    interruptsCount++;

    switch(interruptsCount) {
    case 7:
        P1OUT |= BIT0;
        break;
    case 14:
        P8OUT |= BIT1;
        break;
    case 21:
        P8OUT |= BIT2;
        TA1CCTL0 &= ~CCIE;    // stop A1
        TA1CTL = MC_0;
        break;
    }
}

#pragma vector = WDT_VECTOR
__interrupt void WDT_interrupt(void) {
    interruptsCount++;

    switch(interruptsCount) {
    case 88:
        P1OUT |= BIT0;
        break;
    case 176:
        P8OUT |= BIT1;
        break;
    case 264:
        P8OUT |= BIT2;
        SFRIE1 &= ~WDTIE;
        WDTCTL = WDTPW | WDTHOLD;  //stop WD
        break;
    }
}

#pragma vector = PORT1_VECTOR
__interrupt void buttonS1(void)
{
    volatile int i = 0;

    for(i=0; i<1000; i++);

    if((P1IES & BIT7) == 0) {
        TA1CCTL0 &= ~CCIE;    //stop A1
        TA1CTL = MC_0;



        SFRIE1 &= ~WDTIE;
        WDTCTL = WDTPW | WDTHOLD;  //stop WD

        P1OUT &= ~BIT0;
        P8OUT &= ~BIT1;
        P8OUT &= ~BIT2;

        interruptsCount = 0;
    } else if(CURRENT_TIMER == 1){
        TA1CCTL0 = CCIE;
        TA1CCR0 = 10500;                            //start A1
        TA1EX0 = TAIDEX_4;
        TA1CTL = TASSEL_2 | ID_1 | MC_1 | TACLR;
    } else {
        SFRIE1 |= WDTIE;
        WDTCTL = WDTPW | WDTTMSEL | WDTCNTCL | WDTSSEL_0 | WDTIS_5;          //start WD
    }

    P1IES ^= BIT7;
    P1IFG = 0;
}

#pragma vector = PORT2_VECTOR
__interrupt void buttonS2(void)
{
    volatile int i = 0;

    for(i=0; i<2000; i++);

    if((P2IN & BIT2) == 0){
        if(CURRENT_TIMER == 0) {
            SFRIE1 &= ~WDTIE;
            WDTCTL = WDTPW | WDTHOLD;  //stop WD

            P1OUT &= ~BIT2;

            CURRENT_TIMER = 1;
        } else {
            TA1CCTL0 &= ~CCIE;   //stop A1
            TA1CTL = MC_0;

            P1OUT |= BIT2;

            CURRENT_TIMER = 0;
        }
    }

    P2IFG = 0;
}


int main(void){
    WDTCTL = WDTPW | WDTHOLD;

    P8DIR |= BIT1;
    P8OUT &= ~BIT1;

    P8DIR |= BIT2;
    P8OUT &= ~BIT2;

    P8DIR |= BIT1;
    P8OUT &= ~BIT1;

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    P1DIR |= BIT2;
    P1OUT &= ~BIT2;

    P1DIR |= BIT3;
    P1OUT &= ~BIT3;

    P1DIR |= BIT4;
    P1OUT &= ~BIT4;

    P1DIR &= ~BIT7;
    P1OUT |= BIT7;
    P1REN |= BIT7;
    P1IE |= BIT7;
    P1IES |= BIT7;
    P1IFG = 0;

    P2DIR &= ~BIT2;
    P2OUT |= BIT2;
    P2REN |= BIT2;
    P2IE |= BIT2;
    P2IES |= BIT2;
    P2IFG = 0;

    P1DIR |= BIT5;
    P1OUT &= ~BIT5;
    P1SEL |= BIT5;

    TA0CCR0 = 16384;
    TA0CCR4 = 8192;
    TA0CCTL4 = OUTMOD_2;

    TA0EX0 = TAIDEX_7;
    TA0CTL = TASSEL_2 | ID_3 | MC_1 | TACLR;

    __bis_SR_register(GIE);
    __no_operation();
    return 0;
}
