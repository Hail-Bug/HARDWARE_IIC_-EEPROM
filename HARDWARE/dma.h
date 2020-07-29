#ifndef __DMA_H
#define __DMA_H
#include "sys.h"


extern DMA_HandleTypeDef  I2C2_RXDMA_Handler;      //DMA¾ä±ú

void DMA2_I2C2RX_Config(void);
void DMA2_I2C2TX_Config(void);
void MYDMA_I2C2_Transmit(I2C_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
#endif
