#include <msp430.h>

/*
* Task:
*  DCOCLK frequency : 558000Hz // 720 kHz       // 720 000 / 32 768 = 21,972  // 32 768/1 * (10 + 1) * 2 = 720 896
*  MCLK frequency : 3467Hz (default frequency / 16) DF/32 = 22 500 Hz
*  Alternative MCLK source: DCOCLKDIV / XT1CLK
*  Alternative MCLK divider: 4 / 2
*  Low Power Mode (LPM): 1 / 1
*/

volatile int short ALTERNATIVE_FREQUENCY_ON = 0;
volatile int short LPM_MODE_1_ON = 0;

#pragma vector = PORT1_VECTOR
__interrupt void PORT1_S1(void)
{
    __delay_cycles(1000);

    if (LPM_MODE_1_ON)
    {
        _bic_SR_register_on_exit(LPM1_bits);
        LPM_MODE_1_ON = 0;
    }
    else
    {
        LPM_MODE_1_ON = 1;
        _bis_SR_register_on_exit(LPM1_bits);
    }

    P1IFG &= ~BIT7;
}

#pragma vector = PORT2_VECTOR
__interrupt void PORT2_S2(void)
{
    __delay_cycles(1000);

    if (ALTERNATIVE_FREQUENCY_ON)
    {
        UCSCTL4 = SELM__DCOCLK;
        UCSCTL5 = DIVM__32;  // divide 32
        ALTERNATIVE_FREQUENCY_ON = 0;
    }
    else
    {
        UCSCTL4 = SELM__XT1CLK;
        UCSCTL5 = DIVM__2; // divide 2
        ALTERNATIVE_FREQUENCY_ON = 1;
    }

    P2IFG &= ~BIT2;
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    P1DIR &= ~BIT7;
    P1OUT |= BIT7;
    P1REN |= BIT7;

    P2DIR &= ~BIT2;
    P2OUT |= BIT2;
    P2REN |= BIT2;

    __bis_SR_register(GIE); //Enabling CPU interrupts

    P1IES |= BIT7;
    P1IFG &= ~BIT7;
    P1IE |= BIT7;

    P2IES |= BIT2;
    P2IFG &= ~BIT7;
    P2IE |= BIT2;

    P7DIR |= BIT7;
    P7SEL |= BIT7;

    // 32 768 / 1 * (10 + 1) * 2 = 720 896
    //DCOCLK = FLLREFCLK / FLLREFDIV * (FLLN + 1) * FLLD

    UCSCTL1 |= DCORSEL_0;
    UCSCTL2 |= (FLLD1 | (FLLN1 | FLLN3));
    UCSCTL3 |= (SELREF__XT1CLK | FLLREFDIV__1);
    UCSCTL4 |= SELM__DCOCLK;
    UCSCTL5 |= DIVM__32;

    return 0;
}
