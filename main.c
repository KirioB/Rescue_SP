/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/
#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

//#include <plib.h>           /* Include to use PIC32 peripheral libraries      */
#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */
#include <string.h>
#include "system.h"         /* System funct/params, like osc/periph config    */
#include "user.h"     /* User funct/params, such as InitApp             */

#define _XTAL_FREQ 8000000

void writeUART2(char * string);
void readUART2(char * message, int maxLength);
/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint32_t <variable_name>; */

// premiere fonction delay de test
void delayms(int n){
    int i;
    for (i=0; i<1000*n; i++){
        continue;
    }
}

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
char message[100] ;
int32_t main(void)
{

#ifndef PIC32_STARTER_KIT
    /*The JTAG is on by default on POR.  A PIC32 Starter Kit uses the JTAG, but
    for other debug tool use, like ICD 3 and Real ICE, the JTAG should be off
    to free up the JTAG I/O */
 //   DDPCONbits.JTAGEN = 0;
#endif

    /*Refer to the C32 peripheral library documentation for more
    information on the SYTEMConfig function.
    
    This function sets the PB divider, the Flash Wait States, and the DRM
    /wait states to the optimum value.  It also enables the cacheability for
    the K0 segment.  It could has side effects of possibly alter the pre-fetch
    buffer and cache.  It sets the RAM wait states to 0.  Other than
    the SYS_FREQ, this takes these parameters.  The top 3 may be '|'ed
    together:
    
    SYS_CFG_WAIT_STATES (configures flash wait states from system clock)
    SYS_CFG_PB_BUS (configures the PB bus from the system clock)
    SYS_CFG_PCACHE (configures the pCache if used)
    SYS_CFG_ALL (configures the flash wait states, PB bus, and pCache)*/

    /* TODO Add user clock/system configuration code if appropriate.  */
 //   SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL); 

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /*Configure Multivector Interrupt Mode.  Using Single Vector Mode
    is expensive from a timing perspective, so most applications
    should probably not use a Single Vector Mode*/
//    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    /* TODO <INSERT USER APPLICATION CODE HERE> */

    
    while(1)
    {
        LATAbits.LATA0 = 1;// Allume la LED
        readUART2(message, 100);
        strcat(message, " recu par le PIC\n\r"); //attention \n\r obligatoire pour la comm ble

        writeUART2(message);
        delayms(500);     // Pause 500 ms

        
        LATAbits.LATA0 = 0;  // Eteint la LED
        delayms(500);     // Pause 500 ms

    }
}

void writeUART2(char * string){
    while (*string != '\0'){
        while (U2STAbits.UTXBF){
            ;
        }
        U2TXREG = *string;
        ++string;
    }
}

void readUART2(char * message, int maxLength){
    char data = 0;
    int complete = 0, num_bytes = 0;
    while (!complete){ //loop until you get \r or \n
        if(U2STAbits.URXDA){ //if data is available
            data = U2RXREG; //send the data
            if ((data == '\n') || (data == '\r')){
                complete = 1;
            }else {
                message[num_bytes] = data;
                ++num_bytes;
                if (num_bytes >= maxLength){ //roll over if the array is too small
                    num_bytes = 0;
                }
            }
        }
    }
    message[num_bytes] = '\0'; //end of string
}
