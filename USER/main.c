#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "i2c.h"
#include "dma.h"

/************************************************* 
 File name:   硬件IIC-EEPROM
 Author:      蒋朔
 Description:  使用硬件IIC读取EEPROM
*************************************************/ 

I2C_HandleTypeDef I2C_Handler;      //IIC句柄

void IIC_Init(void)
{
	I2C_Handler.Instance = I2C2;
	I2C_Handler.Init.ClockSpeed = 1000000;
//	I2C_Handler.Init.OwnAddress1 = 20;        //用户自己配置的地址
	I2C_Handler.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2C_Handler.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
//	I2C_Handler.Init.OwnAddress2 = 0;        
	I2C_Handler.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2C_Handler.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	

	HAL_I2C_Init(&I2C_Handler);
	
	


}

//I2C底层GPIO配置
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOH_CLK_ENABLE();   //使能GPIOH时钟
	
	
    //PH4,5初始化设置
    GPIO_Initure.Pin = GPIO_PIN_4|GPIO_PIN_5;
    GPIO_Initure.Mode = GPIO_MODE_AF_OD;  //推挽输出
    GPIO_Initure.Speed = GPIO_SPEED_FAST;     //快速
	GPIO_Initure.Alternate = GPIO_AF4_I2C2;
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);



}


int main(void)
{
    
	uint8_t buf[8] = {1,2,3,4,5,6,7,8,};    //待写入数据
	uint8_t buf1[8];							 //读出缓冲区
	u32 success_cnt = 0;
	u32 fail_cnt = 0;

    HAL_Init();                     //初始化HAL库    
    Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
    __HAL_RCC_I2C2_CLK_ENABLE();    //打开IIC2时钟
    delay_init(180);                //初始化延时函数
    uart_init(115200);              //初始化USART	
	IIC_Init();                     //初始化硬件IIC
	DMA2_I2C2TX_Config();           //初始化I2C2DMA发
	DMA2_I2C2RX_Config(); 			//初始化I2C2DMA收
	
	u8 temp1 = 4;
	u8 temp2 = 3;

	

	
		
	while(1)
	{
		

		
		if(HAL_I2C_Mem_Write_DMA(&I2C_Handler, 0xA0, 0, I2C_MEMADD_SIZE_8BIT, &temp1, 1) == HAL_OK)  //查看是否设置成功
		{
			printf("success:%d\r\n",success_cnt);
		}
		else
		{
			printf("fail:%d\r\n",fail_cnt);
		}
		delay_ms(1);

		
		if(HAL_I2C_Mem_Read_DMA(&I2C_Handler, 0xA0, 0, I2C_MEMADD_SIZE_8BIT, &temp2 , 1) == HAL_OK)
		{
			
			printf("Read success:%d\r\n",temp2);
			
//			u8 cnt = 0;
//			uint8_t *p1 = buf;
//			uint8_t *p2 = buf1;
//			for( u8 i = 0; i<8 ; i++)
//				{
//					if(*p1+1+i == *p2+1+i)
//					{
//						cnt++;
//					}
//				}
//			if(8 == cnt)
//			{
//				success_cnt++;
//				printf("Read success:%d\r\n",success_cnt);
//			}

		}
		else
		{	
			fail_cnt++;
			printf("Read fail:%d\r\n", fail_cnt);
		}			
		delay_ms(1);

	}
	
}

