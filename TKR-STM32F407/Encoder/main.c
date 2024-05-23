#include <__cross_studio_io.h>
#include <stm32f4xx.h>
int val=0;
void main(void)
{
  RCC -> APB2ENR |= (1<<14); // System configuration clock enabled 
  RCC -> APB1ENR |= (1<<0); // TIM2 clock enabled 
  RCC -> AHB1ENR |= (1<<0); // GPIOA clock enabled 

  GPIOA -> AFR[0] |= (1<<0) | (1<<4); // Alternate function F1
  GPIOA -> MODER |= (1<<1); // A0 set on alternate function mode
  GPIOA -> MODER &= ~(1<<0);
  GPIOA -> MODER &= ~(1<<2);
  GPIOA -> MODER |= (1<<3); // A1 set on alternate function mode


  

  TIM2 -> SMCR |= (1<<0) | (1<<1); // SMS- Encoder mode 3 ( both TI1 and TI2 )
 //TIM2 -> CCER |= (1<<1) | (1<<5);
  TIM2 -> CCMR1 |= (1<<0); // CC1 channel is configured as input, IC1 is mapped on TI1.
  TIM2 -> CCMR1 |= (1<<8); // CC2 channel is configured as input, IC2 is mapped on TI2
  TIM2 -> CR1 |= (1<<0); // Counter enabled 
  // TIM2 -> DIR |= (1<<4);

  TIM2 -> ARR = 1024;
  
  // interruptfunc();
  
  while(1)
  {
    val=TIM2 -> CNT;
    
  }

}


void interruptfunc()
{
  RCC -> APB2ENR |= (1<<14); // System configuration clock enabled 
  RCC -> APB1ENR |= (1<<0); // TIM2 clock enabled 
  RCC -> AHB1ENR |= (1<<0); // GPIOA clock enabled 
  EXTI -> IMR |= (1<<0);
  EXTI -> IMR |= (1<<1);
  EXTI -> RTSR |= (1<<0)|(1<<1);
  //EXTI -> FTSR |= (1<<1);
    NVIC_EnableIRQ(EXTI1_IRQn);
  NVIC_EnableIRQ(EXTI0_IRQn);

}

void EXTI1_IRQHandler(void)
{
  
  if(GPIOA -> IDR & (1<<0))
  {
    val++;
  }
  else 
  {
    val--;
  }
  EXTI -> PR |= (1<<1);
}

void EXTI0_IRQHandler(void)
{
  
  if(GPIOA -> IDR & (1<<1))
  {
    val++;
  }
  else 
  {
    val--;
  }
  EXTI -> PR |= (1<<0);
} 

