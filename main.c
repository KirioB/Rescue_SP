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
    
    LED1 = 0;
    while(1)
    {
       // LED1 = 1;
        test(0x18,0x32); //VERIFI8ER!!!!!!!!!!!!!!
       // SPI_ReadRegister(0x18);
        //SPI_SendString("HELLO WORLD");
        
     //  LED1 = 0;
        delay_ms (100);
    }
}
