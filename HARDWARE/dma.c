#include "dma.h"
#include "usart.h"

/************************************************* 
 File name:   IIC用DMA
 Author:      蒋朔
 Description:  通过DMA使用IIC发送接受数据
*************************************************/	

extern I2C_HandleTypeDef I2C_Handler;
DMA_HandleTypeDef  I2C2_RXDMA_Handler;      //DMA收句柄
DMA_HandleTypeDef  I2C2_TXDMA_Handler;      //DMA发句柄


//I2C通过DMA收数据
void DMA2_I2C2RX_Config(void)
{ 

    __HAL_RCC_DMA1_CLK_ENABLE();//DMA1时钟使能 
	
    
    
	HAL_NVIC_SetPriority(DMA1_Stream2_IRQn,0,0);
	HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
	
	HAL_NVIC_SetPriority(DMA1_Stream7_IRQn,0,0);
	HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);
	
    //Rx DMA配置
    I2C2_RXDMA_Handler.Instance=DMA1_Stream2;                            //数据流选择
    I2C2_RXDMA_Handler.Init.Channel=DMA_CHANNEL_7;                      //通道选择
    I2C2_RXDMA_Handler.Init.Direction=DMA_PERIPH_TO_MEMORY;             //外设到存储器
    I2C2_RXDMA_Handler.Init.PeriphInc=DMA_PINC_DISABLE;                 //外设非增量模式
    I2C2_RXDMA_Handler.Init.MemInc=DMA_MINC_ENABLE;                     //存储器增量模式
    I2C2_RXDMA_Handler.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;    //外设数据长度:8位
    I2C2_RXDMA_Handler.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;       //存储器数据长度:8位
    I2C2_RXDMA_Handler.Init.Mode=DMA_NORMAL;                            //外设普通模式
    I2C2_RXDMA_Handler.Init.Priority=DMA_PRIORITY_MEDIUM;               //中等优先级
    I2C2_RXDMA_Handler.Init.FIFOMode=DMA_FIFOMODE_DISABLE;              
    I2C2_RXDMA_Handler.Init.FIFOThreshold=DMA_FIFO_THRESHOLD_FULL;      
    I2C2_RXDMA_Handler.Init.MemBurst=DMA_MBURST_SINGLE;                 //存储器突发单次传输
    I2C2_RXDMA_Handler.Init.PeriphBurst=DMA_PBURST_SINGLE;              //外设突发单次传输
    
    HAL_DMA_DeInit(&I2C2_RXDMA_Handler);   
    HAL_DMA_Init(&I2C2_RXDMA_Handler);
	__HAL_LINKDMA(&I2C_Handler,hdmarx,I2C2_RXDMA_Handler);    //将DMA与USART1联系起来(发送DMA)
	
    
    //Tx DMA配置
    I2C2_TXDMA_Handler.Instance=DMA1_Stream7;                            //数据流选择
    I2C2_TXDMA_Handler.Init.Channel=DMA_CHANNEL_7;                      //通道选择
    I2C2_TXDMA_Handler.Init.Direction=DMA_MEMORY_TO_PERIPH;             //存储器到外设
    I2C2_TXDMA_Handler.Init.PeriphInc=DMA_PINC_DISABLE;                 //外设非增量模式
    I2C2_TXDMA_Handler.Init.MemInc=DMA_MINC_ENABLE;                     //存储器增量模式
    I2C2_TXDMA_Handler.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;    //外设数据长度:8位
    I2C2_TXDMA_Handler.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;       //存储器数据长度:8位
    I2C2_TXDMA_Handler.Init.Mode=DMA_NORMAL;                            //外设普通模式
    I2C2_TXDMA_Handler.Init.Priority=DMA_PRIORITY_MEDIUM;               //中等优先级
    I2C2_TXDMA_Handler.Init.FIFOMode=DMA_FIFOMODE_DISABLE;              
    I2C2_TXDMA_Handler.Init.FIFOThreshold=DMA_FIFO_THRESHOLD_FULL;      
    I2C2_TXDMA_Handler.Init.MemBurst=DMA_MBURST_SINGLE;                 //存储器突发单次传输
    I2C2_TXDMA_Handler.Init.PeriphBurst=DMA_PBURST_SINGLE;              //外设突发单次传输
    
    HAL_DMA_DeInit(&I2C2_TXDMA_Handler);   
    HAL_DMA_Init(&I2C2_TXDMA_Handler);
	__HAL_LINKDMA(&I2C_Handler,hdmatx,I2C2_TXDMA_Handler);    //将DMA与USART1联系起来(发送DMA)
} 

//I2C通过DMA发数据
void DMA2_I2C2TX_Config(void)
{ 

    __HAL_RCC_DMA1_CLK_ENABLE();//DMA1时钟使能 
	
    __HAL_LINKDMA(&I2C_Handler,hdmatx,I2C2_TXDMA_Handler);    //将DMA与USART1联系起来(发送DMA)
    
    //Tx DMA配置
    I2C2_TXDMA_Handler.Instance=DMA1_Stream7;                            //数据流选择
    I2C2_TXDMA_Handler.Init.Channel=DMA_CHANNEL_7;                      //通道选择
    I2C2_TXDMA_Handler.Init.Direction=DMA_MEMORY_TO_PERIPH;             //存储器到外设
    I2C2_TXDMA_Handler.Init.PeriphInc=DMA_PINC_DISABLE;                 //外设非增量模式
    I2C2_TXDMA_Handler.Init.MemInc=DMA_MINC_ENABLE;                     //存储器增量模式
    I2C2_TXDMA_Handler.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;    //外设数据长度:8位
    I2C2_TXDMA_Handler.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;       //存储器数据长度:8位
    I2C2_TXDMA_Handler.Init.Mode=DMA_NORMAL;                            //外设普通模式
    I2C2_TXDMA_Handler.Init.Priority=DMA_PRIORITY_MEDIUM;               //中等优先级
    I2C2_TXDMA_Handler.Init.FIFOMode=DMA_FIFOMODE_DISABLE;              
    I2C2_TXDMA_Handler.Init.FIFOThreshold=DMA_FIFO_THRESHOLD_FULL;      
    I2C2_TXDMA_Handler.Init.MemBurst=DMA_MBURST_SINGLE;                 //存储器突发单次传输
    I2C2_TXDMA_Handler.Init.PeriphBurst=DMA_PBURST_SINGLE;              //外设突发单次传输
    
    HAL_DMA_DeInit(&I2C2_TXDMA_Handler);   
    HAL_DMA_Init(&I2C2_TXDMA_Handler);
} 
//开启一次DMA传输
//huart:串口句柄
//pData：传输的数据指针
//Size:传输的数据量
void MYDMA_I2C2_Transmit(I2C_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    HAL_DMA_Start(huart->hdmatx, (u32)pData, (uint32_t)&huart->Instance->DR, Size);//开启DMA传输
    

}	  

void DMA1_Stream2_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&I2C2_RXDMA_Handler);
}

void DMA1_Stream7_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&I2C2_TXDMA_Handler);
}
 
 
