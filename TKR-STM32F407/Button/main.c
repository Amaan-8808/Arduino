#include <__cross_studio_io.h>
#include<stm32f4xx.h>

void main(void)
{
   RCC -> APB2ENR |=(1<<14); //System configuration controller clock enabled
   RCC-> AHB1ENR |= (1<<0); // IO port A clock enabled
   RCC-> AHB1ENR |= (1<<3); // IO port D clock enabled
   GPIOD -> MODER |= (1<<28); // Pin 14 of Port D put on output mode 
   while(1)
   {
      if(GPIOA -> IDR & (1<<0))
      GPIOD -> ODR |= (1<< 14); //LED ON
      if(~(GPIOA -> IDR & (1<<0)))
      GPIOD -> ODR &= ~(1<<14); // LED OFF
   }
}