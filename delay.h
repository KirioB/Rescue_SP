#ifndef TIMER_H
    #define TIMER_H

    #include <xc.h> 

    //Definitions
    #define TIMER_PRESCALER 8                               // Prescaler (1, 8, 64, 256)
    #define SYS_CLOCK 8000000                               // system frequency(Hz)
    #define TIMER_TICK_PERIOD (TIMER_PRESCALER / SYS_CLOCK) // Time/tick of the timer

#endif // TIMER_H
