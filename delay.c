#include <delay.h>

// Timer config for a delay function
void delay_ms(unsigned int milliseconds) {
    T1CON = 0x8000; // Timer 1 ON, prescaler 1:8
    TMR1 = 0;       // Reset timer regist
    PR1 = 1000;     // Period for 1ms

    for (unsigned int i = 0; i < milliseconds; i++) {
        TMR1 = 0;   // Reset timer
        while (!IFS0bits.T1IF); // wait for overflow
        IFS0bits.T1IF = 0; // Reset flag
    }
}