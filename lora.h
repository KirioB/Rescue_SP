/* 
 * File:   lora.h
 * Author: celia
 *
 * Created on 9 janvier 2025, 15:30
 */

#ifndef LORA_H
#define	LORA_H

//nommer les registres
#define RegFifo 0x00
#define RegOpMode 0x01
#define RegFrfMsb 0x06
#define RegFrfMid 0x07
#define RegFrfLsb 0x08
#define FifoRxCurrentAddr 0x10
#define RegIrqFlags 0x12

#define RegRxNbBytes 0x13
#define RegModemConfig1 0x1D
#define RegModemConfig2 0x1E

//modes pour RegOpMode
#define sleep 0x00 //0b000
#define stdby 0x01 //0b001
#define Tx 0x03 //0b011
#define Rx 0x05 //0b101

#define MISO TRISBbits.TRISB14

#define RX_BUFFER_SIZE 64  // Taille max du buffer de réception



void uart_send(uint8_t retourLora);
void Transmit (void); //FTRX, call when try reading
void SPI_WriteRegister(uint8_t address, uint8_t value);
uint8_t SPI_ReadRegister(uint8_t address);
uint8_t LoRa_SetEtat(uint8_t mode);
void Lora_Setrx (void);

uint8_t LoRa_Receive(uint8_t *buffer, uint8_t maxLength); //récupère taille paquets
void TestRx (void); //récupère les données avec LoRa_Receive et envoie en UART
uint8_t test (uint8_t address, uint8_t value); //test lecture de registres avec LED







#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LORA_H */

