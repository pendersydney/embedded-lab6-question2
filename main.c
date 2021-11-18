//lab6-question2

#include <msp430.h> 
volatile long temp, temRaw, photoRaw;
void reset();
void temperature();
void light();

void main(void)
/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;               // stop watchdog timer
    _delay_cycles(5);                       // wait for ADC Ref to settle
    while (1)
    {
        reset();
        temperature();
        _delay_cycles(100);
        tempRaw = ADC10MEM;                 // read the converted date into a variable
        temp = (((tempRaw - 673) * 423) / 1024);  // converts to degree celsius

        reset();
        light();
    }
}

// Configure Temperature
void temperature()
{
    ADC10CTL1 = INCH_10 + ADC10DIV_0 + CONSEQ_2;
    ADC10CTL0 = SREF_1 | ADC10SHT_3 | REFON | ADC10ON;  // Vref+, Vss, 64 ATD clocks per sample, internal references, turn ADCON
    ADC10CTL0 | = ENC + ADC10SC + MSC;
}

// Configure Light
void light()
{
    ADC10CTL1 = INCH_6 + ADC10DIV_0 + CONSEQ_2;
    ADC10CTL0 = SREF_1 | ADC10SHT_3 | REFON | ADC10ON;  // Vref+, Vss, 64 ATD clocks per sample, internal references, turn ADCON
    ADC10CTL0 | = ENC + ADC10SC + MSC;
}

// Reset
void reset()
{
    ADC10CTL0 &= ~ADC10IFG; // Clear flag
    ADC10MEM = 0x00000000;
    ADC1AE0 = 0x00;
    ADC10CTL = 0x0000;
}
