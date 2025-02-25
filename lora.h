/* 
 * File:   lora.h
 * Author: celia
 *
 * Created on 9 janvier 2025, 15:30
 */

#ifndef LORA_H
#define	LORA_H

#define MISO TRISBbits.TRISB14



void SPI_WriteRegister(uint8_t address, uint8_t value);
uint8_t SPI_ReadRegister(uint8_t address);
uint8_t test (uint8_t address, uint8_t value);
void SPI_SendString(const char *data);










#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LORA_H */

