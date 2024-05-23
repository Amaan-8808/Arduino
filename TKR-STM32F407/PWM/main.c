#include <__cross_studio_io.h>
#include<stm32f4xx.h>


void main(void)
{
  RCC -> APB2ENR |= (1<<14); //System Configuration controller Clock enabled
  RCC -> AHB1ENR |= (1<<3); // IO Port D Clock enabled 
  RCC -> APB1ENR |= (1<<2); // TIM4 clock enabled 
  GPIOD -> AFR[1] |=(1<<29);
  GPIOD -> MODER |= (1<<31); // D15 set on alternate mode

  

  
 

  TIM4 -> CCER |= (1<<12); // CCE4 channel capture enabled 
  TIM4 -> CR1 |= (1<<7); // TIM4 ARR register is buffered (ARPE pin)

  TIM4 -> CCMR2 |= (1<<14) | (1<<13); // PWM mode 1 enabled 
  TIM4 -> CCMR2 &= ~(1<<12);
  TIM4 -> CCMR2 |= (1<<8); // CC4 channel is configured as input, IC4 is mapped on TI4
  TIM4 -> CCMR1 |= (1<<3); // Preload register enabled 

  
  //Duty Cycle= ARR/CCR4
  //Frequency= Clock/PSC*ARR
  
  TIM4 -> PSC = 8-1;
  TIM4 -> ARR = 1000;
  TIM4 -> CNT = 0;
  TIM4 -> CR1 |= (1<<0); // Counter for Timer4 enabled

  TIM4 -> EGR |= (1<<0);

   

  while(1)
  {
    for(int i=0;i<=1000;i++)
    {
      TIM4->CCR4=i;
      delay(1);
    }

  }
}


void delay(int t)
{
  for(int i=0;i<16000*t; i++);
}

