#ifndef HM10_H
#define HM10_H

#include "LPC407x_8x_177x_8x.h"
#include "Library/SystemStructures.h"

#include <stdio.h>
#include <string.h>

#pragma anon_unions

typedef struct
{
	union
	{
		volatile  uint8_t  RBR;
		volatile  uint8_t  THR;
		volatile	uint8_t  DLL;
							uint32_t RESERVED0;
	};
	union
	{
		volatile	uint8_t  DLM;
		volatile	uint32_t IER;
	};
	union
	{
		volatile  uint32_t IIR;
		volatile  uint8_t  FCR;
	};
	volatile	uint8_t  LCR;
						uint8_t  RESERVED1[7];
	volatile  uint8_t  LSR;
						uint8_t  RESERVED2[7];
	volatile	uint8_t  SSCR;
						uint8_t  RESERVED3[3];
	volatile	uint32_t ACR;
	volatile	uint8_t  ICR;
						uint8_t  RESERVED4[3];
	volatile	uint8_t  FDR;
						uint8_t  RESERVED5[7];
	volatile	uint8_t  TER;
						uint8_t  RESERVED8[27];
	volatile	uint8_t  RS485CTRL;
						uint8_t  RESERVED9[3];
	volatile	uint8_t  ADRMATCH;
						uint8_t  RESERVED10[3];
	volatile	uint8_t  RS485DLY;
						uint8_t  RESERVED11[3];
	volatile  uint8_t  FIFOLVL;
}UART_TypeDef;

#define HM10BufferSize 256

#define HM10_UART_BASE	0x4009C000
#define HM10_UART	((UART_TypeDef*) HM10_UART_BASE)

#define HM10_UART_TX_PIN_ADDRESS	0x4002C004
#define HM10_UART_TX_PIN	*((volatile uint32_t*)(HM10_UART_TX_PIN_ADDRESS))

#define HM10_UART_RX_PIN_ADDRESS	0x4002C000
#define HM10_UART_RX_PIN	*((volatile uint32_t*)(HM10_UART_RX_PIN_ADDRESS))

extern uint8_t HM10CurrentBufferIndex;
extern uint8_t HM10NewDataAvailable;

extern char HM10Buffer[HM10BufferSize];

void HM10_Init(void);
void HM10_SendCommand(char* command);
void HM10_ClearBuffer(void);

char HM10_ReadData(void);
void HM10_WriteData(char data);
void HM10_Write(char* data);


#endif
