#include <__cross_studio_io.h>
#include<stm32f4xx.h>

void main(void)
{
   ClockPortSetup();
   generalInputOutput();
   interruptSetup();
}

void EXTI0_IRQHandler(void)
{
   GPIOD -> ODR |= (1<< 14); //LED ON
   EXTI -> PR |= (1<<0);
  
}
 void interruptSetup()
 {
    EXTI -> IMR |= (1<<0); //  Interrupt request from line I0 is not masked
    EXTI -> RTSR |= (1<<0); // Rising trigger enabled for input line
    NVIC_EnableIRQ(EXTI0_IRQn); // Enable interrupt
 } 
 void ClockPortSetup()
 {
    RCC -> APB2ENR |=(1<<14); //System configuration controller clock enabled
    RCC-> AHB1ENR |= (1<<0); // IO port A clock enabled
    RCC-> AHB1ENR |= (1<<3); // IO port D clock enabled
 }
 void generalInputOutput()
 {
    GPIOD -> MODER |= (1<<28); // Pin 14 of Port D put on output mode 
 }