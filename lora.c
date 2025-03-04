#include <stdint.h> 
#include <stdio.h>
#include <xc.h>
#include "user.h"
#include "lora.h"

//test UART
void uart_send(uint8_t retourLora)
{
    while (U2STAbits.UTXBF);  // Attendre la place ds buffer
    U2TXREG = retourLora;  // l'UART2
}

/*
void SPI_WriteRegister(uint8_t address, uint8_t value) {
    CS_LOW();
    SPI1BUF = address | 0x80;  // Adresse (bit MSB = 1 pour lecture)
    while (!SPI1STATbits.SPIRBF);  // Attendre la fin de la transmission
    (void)SPI1BUF;  // Lecture pour vider le buffer

    SPI1BUF = value;  // Envoyer la valeur
    IFS0bits.SPI1RXIF = 0;
    while (!SPI1STATbits.SPIRBF);
    while (!IFS0bits.SPI1RXIF);
    (void)SPI1BUF;  // Lecture pour vider le buffer
    CS_HIGH();
}
*/

void SPI_WriteRegister(uint8_t address, uint8_t value) {
    CS_LOW();  // Activer le périphérique SPI
    SPI1BUF = address | 0x80;  // Adresse avec bit MSB à 1 pour écrire
    while (!SPI1STATbits.SPIRBF);  // Attendre la fin de la transmission
    (void)SPI1BUF;  // Lire et vider le buffer

    SPI1BUF = value;  // Envoyer la valeur à écrire
    while (!SPI1STATbits.SPIRBF);  // Attendre la fin de la transmission
    (void)SPI1BUF;  // Lire et vider le buffer

    CS_HIGH();  // Désactiver le périphérique SPI
}


uint8_t SPI_ReadRegister(uint8_t address) {
    int result;
    CS_LOW(); 
    SPI1BUF = address & 0x7F;  // Adresse (bit MSB = 0 pour écriture)
    while (!SPI1STATbits.SPIRBF); // c un flag qui dit que tant que SPIRBF n'est pas à 1, attend   
    (void)SPI1BUF; //lit et vider le buffer SPI
    
    IFS0bits.SPI1RXIF = 0;
    SPI1BUF = 0x00;  // Envoyer un octet vide pour lire donc car chaque lecture est couplé à une réception
    while (!SPI1STATbits.SPIRBF); // c un flag qui dit que tant que SPIRBF n'est pas à 1, attend   
    (void)SPI1BUF; //lit et vide le buffer SPI

    while (!IFS0bits.SPI1RXIF);
    result = SPI1BUF; // = SPI Receive Buffer Full
//    while (SPI1STATbits.SPIRBF);
    
//    while (!SPI1STATbits.SPIRBF);
//    result = SPI1BUF; // = SPI Receive Buffer Full
   
 
   // result = getcSPI1();
    CS_HIGH();
    return result;
}

void SPI_SendString(const char *data) {
    CS_LOW();
    for(int i =0; data[i] != "\0"; i ++)
    {       
        SPI1BUF = (uint8_t)data[i]; //envoie en caractère ASCII format forcé sur 8 bits (ex si le char est signé on a -128 à 127)
        while (!SPI1STATbits.SPIRBF);  // Attendre la fin de la transmission
       (void)SPI1BUF;  // Lire et vider le buffer SPI
    }
    
    CS_HIGH(); //désac communication avec cet esclave
}
/*
void SPI_SendString(const char *data) {
    CS_LOW();
    
    while (*data) {  // Tant qu'on n'atteint pas la fin de la chaîne
        SPI1BUF = *data;  // Envoyer un caractère
        while (!SPI1STATbits.SPIRBF);  // Attendre la fin de la transmission
        (void)SPI1BUF;  // Lire et vider le buffer SPI
        data++;  // Passer au caractère suivant   
    }
    CS_HIGH();
}*/


uint8_t test(uint8_t address, uint8_t expected_value) 
{
    SPI_WriteRegister(address, expected_value);
    
    uint8_t retourLora = 0;
    retourLora = SPI_ReadRegister(address);
    
    Nop();
    Nop();
    Nop();
    LED1 = 0;
    LED2 = 0;
    if (retourLora == expected_value) 
    {
        LED1 = 0;  
        //uart_send(retourLora); //ENVOYER TRAME A TESTER
        LED1 = 1;
        return 1;  
        Nop();
    } 
    else 
    {
        LED2 = 1;  
        return 0;  
    }
}


