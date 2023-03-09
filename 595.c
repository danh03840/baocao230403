
// Blink led
// include libarary//#include"stm32f10x_time.h"
// khai bao ham
// ti sua lai gpiob thành gpioc và là ở port c(kit cua danh)
// pin thanh 13 vì kí tự trên mạch của danh
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#define latch_pin GPIO_Pin_1
#define clock_pin GPIO_Pin_2
#define data_pin GPIO_Pin_0


void Delay(unsigned int time);
GPIO_InitTypeDef GPIO_Struct;
void delay_ms(uint16_t _time)
{
    volatile uint16_t i,j;
    for(i = 0; i < _time; i++)
    {
        for(j = 0; j < 601; j++);
    }
}
void ic595(int8_t a)
{
   // int8_t a=0b11110000;
    int b;
    GPIO_ResetBits(GPIOA, latch_pin);
    for(int i=0;i<8;i++)
    {
        GPIO_ResetBits(GPIOA, clock_pin);
        b=(a>>i)&1;
        if(b==1)
        {
            GPIO_SetBits(GPIOA, data_pin);
        }
        else
        {
            GPIO_ResetBits(GPIOA, data_pin);
        }
        GPIO_SetBits(GPIOA, clock_pin);
        delay_ms(20);

        }
        GPIO_SetBits(GPIOA, latch_pin);
        delay_ms(20);
}
void traiqua()
{
    int8_t e=0b1;
    for(int i=0;i<=7;i++)
    {
        ic595(e<< i);
        delay_ms(1000);
    }

}
void giotnuoc()
{
    uint8_t k=0b1,f=0;
    for(int i=7;i>=0;i--)
    {
        for(int j=0;j<=i;j++)
        {
            ic595(f | k<<j);
            if(j==i) f=f|k<<j;
            delay_ms(400);
        }
        // delay_ms(500);

    }
}
int main(void)
{
    // cap clock cho GPIOB
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //cai dat cho chan PB2
        GPIO_Struct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Struct.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
        GPIO_Struct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_Struct);
    while(1)
    {
        giotnuoc();
    }

}


//delay chinh xac
//void delay_ms(uint16_t time)
//{
//// tang bien dem len 12000 lan
//uint32_t time_n=time*12000;
//// cho den khi biem time_n giam =0 thi thoat
//while(time_n!=0){time_n--;}
//}


