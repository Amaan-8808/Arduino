#include <__cross_studio_io.h>
#include<stm32f4xx.h>

double val=100,i=0;

void main(void)
{
   //Set GPIO port A pin1 as push pull input state
   RCC -> APB2ENR |=(1<<14); //System configuration controller clock enabled
   RCC-> AHB1ENR |= (1<<0); // IO port A clock enabled
   RCC -> AHB1ENR |= (1<<1); // IO port B clock enabled
   RCC ->APB2ENR |= (1<<8); //ADC1 clock enabled
   
   GPIOB -> MODER |= (1<<0) | (1<<1); //B0 on analog mode


   ADC1 -> CR1 |= (1<<8); // SCAN mode enabled
   ADC1 -> CR1 |= (1<<24);
   

   ADC1 -> SMPR2 |= (1<<3); //Set sampling time

   ADC1 -> CR2 |= (1<<1); //ADC set to continuous mode
   ADC1 -> CR2 |= (1<<10); // EOC is set at the end of each regular conversion
   ADC1 -> CR2 &= ~(1<<11); 
    
   
   //Calibration

   while(1)
   {
      ADC1 -> SQR2 = 0;
      ADC1 -> SQR2 |= (0<<6); // channel 8 - conversion in regular sequence
      ADC1 -> SR = 0;
      ADC1 -> CR2 |=(1<<0); // ADC ON
      ADC1 -> CR2 |= (1<<30); // To start conversion of regular channels      
      val = ADC1 -> DR ; // to read converted value and store it in a variable
      ADC1 -> CR2 &= ~(1<<0); //ADC OFF
     

   }
}



void delay(double x)
{
  for(int i=0;i<(x*16000000.0);i++);
}

