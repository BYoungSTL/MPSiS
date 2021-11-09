#include <msp430.h>

int sourceDivChange = 0;
int lowPowerMode = 0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR &= ~BIT7;
    P1OUT |= BIT7;
    P1REN |= BIT7;
    P2DIR &= ~BIT2;
    P2OUT |= BIT2;
    P2REN |= BIT2;
    __bis_SR_register(GIE);

    P1IFG &= ~BIT7;
    P1IE |= BIT7;
    P1IES |= BIT7;
    P2IFG &= ~BIT2;
    P2IE |= BIT2;
    P2IES |= BIT2;
    P7DIR |= BIT7;
    P7SEL |= BIT7;
    UCSCTL1 = DCORSEL_0;

    UCSCTL3 = SELREF__XT1CLK | FLLREFDIV__1;
    UCSCTL2 = FLLD__2 | FLLN1 | FLLN3;
    UCSCTL4 = SELM__DCOCLK;
    UCSCTL5 = DIVM__32;

    return 0;
}

#pragma vector = PORT1_VECTOR
__interrupt void ISR1()
{
    if ((P1IN & BIT7) == 0)
    {
        __delay_cycles(1000);

        if ((P1IN & BIT7) == 0)
        {
            if (!lowPowerMode)
            {
                __bis_SR_register_on_exit(LPM1_bits);
                lowPowerMode = 1;
            }
            else
            {
                __bic_SR_register_on_exit(LPM1_bits);
                lowPowerMode = 0;
            }
        }
    }
    P1IFG &= ~BIT7;
}

#pragma vector = PORT2_VECTOR
__interrupt void ISR2()
{
    if ((P2IN & BIT2) == 0)
    {
        __delay_cycles(1000);

        if ((P2IN & BIT2) == 0)
        {
            if (!sourceDivChange)
            {
                UCSCTL4 = SELM__XT1CLK;
                UCSCTL5 = DIVM__2;
                sourceDivChange = 1;
            }
            else
            {
                UCSCTL4 = SELM__DCOCLK;
                UCSCTL5 = DIVM__32;
                sourceDivChange = 0;
            }
        }
    }
    P2IFG &= ~BIT2;
}
