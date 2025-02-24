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

// premiere fonction delay de test
/*
void delayms(int n){
    int i;
    for (i=0; i<1000*n; i++){
        continue;
    }
}*/

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int32_t main(void)
{

#ifndef PIC32_STARTER_KIT
    
#endif
   // RST();
    InitApp(); 
    SPI_Init();
    CS_Init();
    

    while(1)
    {
        //identifier les leds: 
   
        /*LED1 = 1;  // Allume la LED
        delay_ms(1000);     // Pause 500 ms
        LED2 = 1; //allume LED2
        delay_ms(1000);
        LED1 = 0; //éteindre led1
        delay_ms(1000);
        LED2 = 0; 
         */
        //delay_ms(100);
        test(0x18,0x32); //VERIFI8ER!!!!!!!!!!!!!!
       // SPI_ReadRegister(0x18);
        
        //delay_ms (100);
    }
}
