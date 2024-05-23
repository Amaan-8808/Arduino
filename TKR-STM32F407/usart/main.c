#include <__cross_studio_io.h>
#include<stm32f4xx.h>
int i=0;
int check=0;

char getInt();
void charSend(char c);
void stringSend(char *s);
void delay(int t);

void main(void)
{
  RCC -> APB2ENR |= (1<<14); // System configuration controller clock enabled
  RCC -> APB1ENR |= (1<<4); //TIMER 6 clock enabled
  RCC -> APB1ENR |= (1<<17); // USART2 clock enabled
  RCC -> AHB1ENR |= (1<<0); // GPIOA clock enabled 
  RCC -> AHB1ENR |= (1<<3); //GPIOD clock enabled  

  GPIOA -> MODER |= (1<<5);
  GPIOA -> MODER &= ~(1<<4); // A2 set on alternate function mode
  GPIOA -> MODER |= (1<<7);
  GPIOA -> MODER &= ~(1<<6); // A3 set on alternate function mode
  GPIOD -> MODER |= (1<<28); // LED 14 set on output mode
  GPIOA -> AFR[0] |= (1<<8);
  GPIOA -> AFR[0] |= (1<<9);
  GPIOA -> AFR[0] |= (1<<10); // ALternate Function for A2 set on USART2
  GPIOA -> AFR[0] |= (1<<12);
  GPIOA -> AFR[0] |= (1<<13);
  GPIOA -> AFR[0] |= (1<<14); // Alternate Function for A3 set on USART2
  GPIOA -> OSPEEDR |= (1<<4);
  GPIOA -> OSPEEDR |= (1<<5); // A2 set on High Speed
  GPIOA -> OSPEEDR |= (1<<6);
  GPIOA -> OSPEEDR |= (1<<7); // A3 set on High Speedtd



  USART2 -> CR1 |= (1<<13); // USART enabled
  USART2 -> CR1 &= ~(1<<12); // Word length set to 8 bits

  USART2 -> GTPR |= (1<<0); 

  //BAUD rate
  USART2 -> BRR |= (0x3<<0) | (0x68<<4); // 104 is assigned to mantissa part and 3 is assigned to fractional part 

  USART2 -> CR1 |= (1<<2); // Receiver enabled
  USART2 -> CR1 |= (1<<3); // Transmitter enabled
  
  while(1)
  {
    int data= getInt();
    if(data==0x01)
    GPIOD -> ODR |= (1<<14);
    
   

  }
    
    


    
 }
void charSend(char c)
{
  USART2 -> DR =c;
  while(!(USART2 -> SR & (1<<7))); //Runs until data has been trnasmitted
  USART2 -> SR &= ~(1<<7);

}

void stringSend(char *s)
{
  while(*s)
  {
    charSend(*s++);
  }
  i++;

}

char getInt(void)
{
  char value;
  
    while(!(USART2 -> SR & (1<<5))); // Wait for the RXNE bit to set in 
    value= USART2 -> DR; // Reads the data as well clears the RXNE bit
    return value;
  
 
}

void delay(int t)
{
  for(int i=0;i<16000*t;i++);
}