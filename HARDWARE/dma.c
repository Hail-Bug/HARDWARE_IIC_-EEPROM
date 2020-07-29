#include "dma.h"
#include "usart.h"

/************************************************* 
 File name:   IIC��DMA
 Author:      ��˷
 Description:  ͨ��DMAʹ��IIC���ͽ�������
*************************************************/	

extern I2C_HandleTypeDef I2C_Handler;
DMA_HandleTypeDef  I2C2_RXDMA_Handler;      //DMA�վ��
DMA_HandleTypeDef  I2C2_TXDMA_Handler;      //DMA�����


//I2Cͨ��DMA������
void DMA2_I2C2RX_Config(void)
{ 

    __HAL_RCC_DMA1_CLK_ENABLE();//DMA1ʱ��ʹ�� 
	
    
    
	HAL_NVIC_SetPriority(DMA1_Stream2_IRQn,0,0);
	HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
	
	HAL_NVIC_SetPriority(DMA1_Stream7_IRQn,0,0);
	HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);
	
    //Rx DMA����
    I2C2_RXDMA_Handler.Instance=DMA1_Stream2;                            //������ѡ��
    I2C2_RXDMA_Handler.Init.Channel=DMA_CHANNEL_7;                      //ͨ��ѡ��
    I2C2_RXDMA_Handler.Init.Direction=DMA_PERIPH_TO_MEMORY;             //���赽�洢��
    I2C2_RXDMA_Handler.Init.PeriphInc=DMA_PINC_DISABLE;                 //���������ģʽ
    I2C2_RXDMA_Handler.Init.MemInc=DMA_MINC_ENABLE;                     //�洢������ģʽ
    I2C2_RXDMA_Handler.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;    //�������ݳ���:8λ
    I2C2_RXDMA_Handler.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;       //�洢�����ݳ���:8λ
    I2C2_RXDMA_Handler.Init.Mode=DMA_NORMAL;                            //������ͨģʽ
    I2C2_RXDMA_Handler.Init.Priority=DMA_PRIORITY_MEDIUM;               //�е����ȼ�
    I2C2_RXDMA_Handler.Init.FIFOMode=DMA_FIFOMODE_DISABLE;              
    I2C2_RXDMA_Handler.Init.FIFOThreshold=DMA_FIFO_THRESHOLD_FULL;      
    I2C2_RXDMA_Handler.Init.MemBurst=DMA_MBURST_SINGLE;                 //�洢��ͻ�����δ���
    I2C2_RXDMA_Handler.Init.PeriphBurst=DMA_PBURST_SINGLE;              //����ͻ�����δ���
    
    HAL_DMA_DeInit(&I2C2_RXDMA_Handler);   
    HAL_DMA_Init(&I2C2_RXDMA_Handler);
	__HAL_LINKDMA(&I2C_Handler,hdmarx,I2C2_RXDMA_Handler);    //��DMA��USART1��ϵ����(����DMA)
	
    
    //Tx DMA����
    I2C2_TXDMA_Handler.Instance=DMA1_Stream7;                            //������ѡ��
    I2C2_TXDMA_Handler.Init.Channel=DMA_CHANNEL_7;                      //ͨ��ѡ��
    I2C2_TXDMA_Handler.Init.Direction=DMA_MEMORY_TO_PERIPH;             //�洢��������
    I2C2_TXDMA_Handler.Init.PeriphInc=DMA_PINC_DISABLE;                 //���������ģʽ
    I2C2_TXDMA_Handler.Init.MemInc=DMA_MINC_ENABLE;                     //�洢������ģʽ
    I2C2_TXDMA_Handler.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;    //�������ݳ���:8λ
    I2C2_TXDMA_Handler.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;       //�洢�����ݳ���:8λ
    I2C2_TXDMA_Handler.Init.Mode=DMA_NORMAL;                            //������ͨģʽ
    I2C2_TXDMA_Handler.Init.Priority=DMA_PRIORITY_MEDIUM;               //�е����ȼ�
    I2C2_TXDMA_Handler.Init.FIFOMode=DMA_FIFOMODE_DISABLE;              
    I2C2_TXDMA_Handler.Init.FIFOThreshold=DMA_FIFO_THRESHOLD_FULL;      
    I2C2_TXDMA_Handler.Init.MemBurst=DMA_MBURST_SINGLE;                 //�洢��ͻ�����δ���
    I2C2_TXDMA_Handler.Init.PeriphBurst=DMA_PBURST_SINGLE;              //����ͻ�����δ���
    
    HAL_DMA_DeInit(&I2C2_TXDMA_Handler);   
    HAL_DMA_Init(&I2C2_TXDMA_Handler);
	__HAL_LINKDMA(&I2C_Handler,hdmatx,I2C2_TXDMA_Handler);    //��DMA��USART1��ϵ����(����DMA)
} 

//I2Cͨ��DMA������
void DMA2_I2C2TX_Config(void)
{ 

    __HAL_RCC_DMA1_CLK_ENABLE();//DMA1ʱ��ʹ�� 
	
    __HAL_LINKDMA(&I2C_Handler,hdmatx,I2C2_TXDMA_Handler);    //��DMA��USART1��ϵ����(����DMA)
    
    //Tx DMA����
    I2C2_TXDMA_Handler.Instance=DMA1_Stream7;                            //������ѡ��
    I2C2_TXDMA_Handler.Init.Channel=DMA_CHANNEL_7;                      //ͨ��ѡ��
    I2C2_TXDMA_Handler.Init.Direction=DMA_MEMORY_TO_PERIPH;             //�洢��������
    I2C2_TXDMA_Handler.Init.PeriphInc=DMA_PINC_DISABLE;                 //���������ģʽ
    I2C2_TXDMA_Handler.Init.MemInc=DMA_MINC_ENABLE;                     //�洢������ģʽ
    I2C2_TXDMA_Handler.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;    //�������ݳ���:8λ
    I2C2_TXDMA_Handler.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;       //�洢�����ݳ���:8λ
    I2C2_TXDMA_Handler.Init.Mode=DMA_NORMAL;                            //������ͨģʽ
    I2C2_TXDMA_Handler.Init.Priority=DMA_PRIORITY_MEDIUM;               //�е����ȼ�
    I2C2_TXDMA_Handler.Init.FIFOMode=DMA_FIFOMODE_DISABLE;              
    I2C2_TXDMA_Handler.Init.FIFOThreshold=DMA_FIFO_THRESHOLD_FULL;      
    I2C2_TXDMA_Handler.Init.MemBurst=DMA_MBURST_SINGLE;                 //�洢��ͻ�����δ���
    I2C2_TXDMA_Handler.Init.PeriphBurst=DMA_PBURST_SINGLE;              //����ͻ�����δ���
    
    HAL_DMA_DeInit(&I2C2_TXDMA_Handler);   
    HAL_DMA_Init(&I2C2_TXDMA_Handler);
} 
//����һ��DMA����
//huart:���ھ��
//pData�����������ָ��
//Size:�����������
void MYDMA_I2C2_Transmit(I2C_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    HAL_DMA_Start(huart->hdmatx, (u32)pData, (uint32_t)&huart->Instance->DR, Size);//����DMA����
    

}	  

void DMA1_Stream2_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&I2C2_RXDMA_Handler);
}

void DMA1_Stream7_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&I2C2_TXDMA_Handler);
}
 
 
