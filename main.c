#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
GPIO_InitTypeDef GPIO_Struct;
void delay_ms(uint16_t _time)
{
    volatile uint16_t i,j;
    for(i = 0; i < _time; i++)
    {
        for(j = 0; j < 601; j++);
    }
}
void dichtrai()
{
    int x=3;
    while(x--)
    {
        for(int i=0;i<=7;i++)
        {
            GPIOA->ODR=0b10000000>>i;
            delay_ms(1000);
        }
    }

}
void sangxenke()
{
    int x=3;
    while(x--)
    {
        GPIOA->ODR=0b01010101;
        delay_ms(1000);
        GPIOA->ODR=0b10101010;
        delay_ms(1000);
    }
}
void giotnuoc()
{
    int x=3;
    while(x--)
    {
        uint8_t k=0b1,f=0;
        for(int i=7;i>=0;i--)
        {
            for(int j=0;j<=i;j++)
            {
                GPIOA->ODR=(f | k<<j);
                if(j==i) f=f|k<<j;
                delay_ms(400);
            }
        }
    }
}
int main(void)
{
    // cap clock cho GPIOB
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //cai dat cho chan PB2
        GPIO_Struct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Struct.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
        GPIO_Struct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_Struct);
    while(1)
    {
        dichtrai();
        sangxenke();
        giotnuoc();
    }
}
