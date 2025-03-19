#include <stdint.h> 
#include <stdio.h>
#include <xc.h>
#include "user.h"
#include "lora.h"
#include "delay.h"

uint8_t rxFIFO[RX_BUFFER_SIZE];  // Buffer global pour stocker les données reçues
uint8_t fifoIndex = 0;  // Indice pour suivre la position dans le buffer

void uart_send(uint8_t retourLora) //envoyer valeur reçue
{
    while (U2STAbits.UTXBF);  // Attendre la place ds buffer
    U2TXREG = retourLora;  // l'UART2
}

void Transmit (void)
{      
    //uint8_t etat = 0;
    SPI_WriteRegister(RegOpMode, 0x84); //sur reg 0x04 pour activer FTRX 
    delay_ms (2);  //voir p.51/130   
    //etat = SPI_ReadRegister(RegOpMode);   
    SPI_WriteRegister(RegOpMode, 0x85); //mode lora et Rx set    
    //etat = SPI_ReadRegister(RegOpMode);
    delay_ms (2); 
}

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
    SPI1BUF = address & 0x7F;  // Adresse (bit MSB = 0 pour lecture)
    while (!SPI1STATbits.SPIRBF); // c un flag qui dit que tant que SPIRBF n'est pas à 1, attend   
    (void)SPI1BUF; //lit et vider le buffer SPI   
    IFS0bits.SPI1RXIF = 0;
    SPI1BUF = 0x00;  // Envoyer un octet vide pour lire donc car chaque lecture est couplé à une réception
    while (!SPI1STATbits.SPIRBF); // c un flag qui dit que tant que SPIRBF n'est pas à 1, attend   
    (void)SPI1BUF; //lit et vide le buffer SPI
    while (!IFS0bits.SPI1RXIF);
    result = SPI1BUF; // = SPI Receive Buffer Full
    CS_HIGH();
    return result;
}

uint8_t LoRa_SetEtat(uint8_t mode) {
    SPI_WriteRegister(0x01, mode);
    Nop();
}
void Lora_Setrx (void) //change parameters for LoRa mode and 868MHz
{ 
    LoRa_SetEtat(sleep); //pr passer en mode LoRa
    delay_ms (1);
    LoRa_SetEtat(stdby);
    delay_ms (1);
    LoRa_SetEtat(sleep); //pr passer en mode LoRa
    delay_ms (1); 
    SPI_WriteRegister(RegOpMode, 0x80); //sur reg 0x01: 0b1xxx x101 7-0 pour émission continue 
    delay_ms (1);
    Transmit(); //for Rx mode throught TFRX (must be call before, ok in function)         
    SPI_WriteRegister(0x0C, 0x23); //active boost pour un meilleur gain
    delay_ms (1); 
    SPI_WriteRegister(0x1D, 0xB); 
    delay_ms (1);
    SPI_WriteRegister(0x1E, 0xC4); //0b1100 x(0)100, SF12 7-4, 0 car réception -3 
    delay_ms (1);
    SPI_WriteRegister(0x1F, 0x05); //car SF>= 10
    delay_ms (1);
    SPI_WriteRegister(0x23, 0x40); //seule option
    delay_ms (1);
    SPI_WriteRegister(0x39, 0x34); //seule option
    delay_ms (1);
    SPI_WriteRegister(0x33, 0x67); //seule option
    delay_ms (1);
    SPI_WriteRegister(0x3B, 0x19); //seule option
    delay_ms(1);
    //on met 868 MHz
    SPI_WriteRegister(RegFrfMsb, 0xD9);  // Fréquence MSB - 0xFF pour régler au max la puiss émission
    delay_ms (1);
    SPI_WriteRegister(RegFrfMid, 0x20);  // Fréquence MID
    delay_ms (1);
    SPI_WriteRegister(RegFrfLsb, 0x05);  // Fréquence LSB   
    delay_ms (1);
}
uint8_t LoRa_Receive(uint8_t *buffer, uint8_t maxLength) {
    uint8_t packetSize = 0;
    packetSize = SPI_ReadRegister(0x13);  // Lire RegRxNbBytes (taille du paquet reçu) Number of payload bytes of latest packet received
    Nop();
    
    if (packetSize == 0 || packetSize > maxLength) {
        return 0;  // Vérification de la validité de la taille
    }

    uint8_t fifoAddr = SPI_ReadRegister(0x10);  // Lire RegFifoRxCurrentAddr (Start address of last packet received)
    SPI_WriteRegister(0x0D, fifoAddr);  // Régler l'adresse FIFO pour la lecture (RegFifoAddrPtr)

    for (uint8_t i = 0; i < packetSize; i++) {
        buffer[i] = SPI_ReadRegister(0x00);  // Lire chaque octet du FIFO
    }
    return packetSize;  // Retourner le nombre d?octets reçus
}

void TestRx (void)
{    
    uint8_t bytesReceived = LoRa_Receive(rxFIFO, RX_BUFFER_SIZE);

    if (bytesReceived > 0) {
        for (uint8_t i = 0; i < bytesReceived; i++) { // envoie en UART byte/byte pour Raspberry
            uart_send(rxFIFO[i]);
        }
        SPI_WriteRegister(0x12, 0x40); // Remet à zéro UINUQUEMENT RXdone
    }      
}








uint8_t test(uint8_t address, uint8_t expected_value)  //ecriture et lecture regsitre
{
    uint8_t retourLora = 0;
    SPI_WriteRegister(address, expected_value);
    LED1 = 1;
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