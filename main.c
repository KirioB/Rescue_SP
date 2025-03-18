/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/
#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

//#include <plib.h>           /* Include to use PIC32 peripheral libraries    */
#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */
#include "system.h"         /* System funct/params, like osc/periph config    */
#include "user.h"           /* User funct/params, such as InitApp             */
#include "lora.h"   
#include "delay.c"          /*for delay_ms function*/


#define _XTAL_FREQ 8000000 // 8 MHz

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint32_t <variable_name>; */


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int32_t main(void)
{

#ifndef PIC32_STARTER_KIT
    
#endif
    RST();
    InitApp(); 
    SPI_Init(); // fonctionnel
    CS_Init();         
    
    Lora_Setrx(); //also set parameters
    LED1 = 1;
    
    while(1)
    {
        Transmit(); //remet en mode RX
        delay_ms(1);        
       if (SPI_ReadRegister(0x12) & 0x40)  // Rx flag change bit 6 => data upcoming TRUE
        {
            TestRx(); //récupère les données + reset flag RXdone
        }
        Nop();

    }
}
