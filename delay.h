#ifndef DELAY_H
#define DELAY_H

#include <xc.h>  // Inclusion des définitions spécifiques au microcontrôleur

// *** Définitions ***
#define TIMER_PRESCALER 8             // Prescaler utilisé (1:8)
#define SYS_CLOCK 8000000             // Fréquence système en Hz (8 MHz)
#define TIMER_TICK_PERIOD 1000        // Valeur de PR1 pour une période de 1 ms (calculée)

// *** Prototypes de fonctions ***
/**
 * @brief Implémente un délai bloquant basé sur Timer1.
 * 
 * @param millisec Nombre de millisecondes de délai.
 */
void delay_ms(unsigned int millisec);

#endif // DELAY_H
