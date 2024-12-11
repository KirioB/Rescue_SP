/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

//#include <plib.h>            /* Include to use PIC32 peripheral libraries     */
#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* TODO Initialize User Ports/Peripherals/Project here */

void init_uart(void)
{
    // init UART 1 for USB
    U2MODEbits.BRGH = 0;
    U2BRG = (8000000/9600/16)-1;     // (freq/4*9600)-1
    
    U2STAbits.UTXEN = 1; // configure as output pin
    U2STAbits.URXEN = 1; // configure as input pin
    
    U2MODEbits.PDSEL = 0; //No parity bit
    U2MODEbits.STSEL = 0; //1 stop bit
    
    U2MODEbits.ON = 1; //enable UART
    
}

void InitApp(void)
{
    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
    
    // Initialisation de la broche RA0 comme sortie
    TRISAbits.TRISA0 = 0;  // RA0 en sortie
    LATAbits.LATA0 = 0;    // RA0 initialisé à LOW
    
    
        //---------------UART2-----------------------
    //RB10 (RP17) -> GPIO a config pour Tx UART
    TRISBbits.TRISB10 = 0;   //Set as Output
    RPOR4bits.RP17R = 1;  //Map RB10 to UART2 Tx
    
    //RB12 (RP12) -> CTS UART config
    //TRISBbits.TRISB12 = 1;   //Set as Input
    RPINR9bits.U2CTSR = 12; //mapped RB12 to CTS
    
    //RB13 (RP13) -> RTS UART config
    //TRISBbits.TRISB13 = 0;   //Set as Output
    RPOR3bits.RP13R = 2;  //Map RB13 to RTS
    
    //RB11 (RP18) -> GPIO a config pour Rx UART
    TRISBbits.TRISB11 = 1;   //Set as Input
    RPINR9bits.U2RXR = 18; //mapped RP18 to UART2 Rx
    
    init_uart();
}
