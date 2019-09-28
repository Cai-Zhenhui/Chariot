#include "hwjs.h"
#include "SysTick.h"

unsigned char IRcord[4];//用来存放分离后的四个字节的数据 其中数据码 在IRcord[2]中

unsigned char IRok;

void Hwjs_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* 开启GPIO时钟及管脚复用时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;//红外接收
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15); //选择GPIO管脚用作外部中断线路
	EXTI_ClearITPendingBit(EXTI_Line15);
	
	/* 设置外部中断的模式 */ 
	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure); 

	/* 设置NVIC参数 */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;   //打开全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 	 //响应优先级为1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   //使能
	NVIC_Init(&NVIC_InitStructure);

}

void EXTI15_10_IRQHandler(void)	  //红外遥控外部中断
{
	//static unsigned char i;
	//static unsigned char startflag;
	unsigned int t=0;
	unsigned char startflag=0,i,j,k,temp;
	unsigned int IRdata[32];//用存储32位红外数据
	u32 data=0;
	while(1)
	{
		IRok=0;
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15))
		{
			for(t=0;GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);++t)
			{
				delay_us(20);
			}
			if(t>=210 && t<=216)
			{
				//Recevied boot code 8.5ms-9.5ms
				//start recevie 32 bits data
				startflag=1;
				i=0;
				continue ;
			}
			if(!startflag)
			{
				continue;
			}
			data<<=1;
			if(t>=80 && t<=88)
			{
				
				data+=1;
			}
			else
			{
				;
			}
			++i;
			//IRdata[i]=t;
			if(i==32)
			{
				//32-bit data recevied
				for(j=0;j<4;++j)
				{
					for(k=0,temp=0;k<8;++k)
					{
						temp=temp>>1;
						if(IRdata[8*j+k]>=80 && IRdata[8*j+k]<=88)
						{
							//1
							temp|=0x80;
						}
						else
						{
							;//0
						}
					}
					IRcord[j]=temp;
				}
				IRok=1;
				
				break;
			}
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line15);	
}

