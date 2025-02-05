#include <stdint.h> 
#include <stdio.h>
#include <xc.h>
#include "user.h"
#include "lora.h"


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
 

uint8_t SPI_ReadRegister(uint8_t address) {
    CS_LOW();
    SPI1BUF = address & 0x7F;  // Adresse (bit MSB = 0 pour écriture)
    while (!SPI1STATbits.SPIRBF);
    (void)SPI1BUF;

    SPI1BUF = 0x00;  // Envoyer un octet vide pour lire
    while (!SPI1STATbits.SPIRBF);
    uint8_t result = SPI1BUF; // = SPI Receive Buffer Full
    CS_HIGH();
    return result;
}

uint8_t test (uint8_t address, uint8_t value) 
    {
  //  SPI_WriteRegister(address, value);
    uint8_t retourLora = SPI_ReadRegister(address);
//    printf("Valeur du registre à l'adresse %d : %d\n", address, retourLora);
    if (  retourLora == value && address == address) //le registre a bien la valeur qu'on lui a donné
        LED2 = 1;  // Allume la LED1
    else 
    {
        //mauvais numéro de registre, autre LED s'allume
        LED1 = 1;
    }   
}







void UART2_Write(char data) {
    while (U2STAbits.UTXBF); // Attendre que le buffer de transmission soit libre
    U2TXREG = data;          // Écrire le caractère dans le registre de transmission
}


char UART2_Read(void) {
    while (!U2STAbits.URXDA); // Attendre qu'un caractère soit reçu
    return U2RXREG;            // Lire le caractère reçu depuis le registre
}

void test_uart() {
    char received_char;
    UART2_Write('H');  // Envoie 'H' via UART
    UART2_Write('e');  // Envoie 'e' via UART
    UART2_Write('l');  // Envoie 'l' via UART
    UART2_Write('l');  // Envoie 'l' via UART
    UART2_Write('o');  // Envoie 'o' via UART

    received_char = UART2_Read();  // Attend un caractère reçu et le lit
    UART2_Write(received_char);    // Renvoie le caractère reçu
}