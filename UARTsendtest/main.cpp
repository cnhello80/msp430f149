#include <msp430x14x.h>
#include "hello149.c"
#include "149uart.c"
#include "atcommand.h"
void main(void) 
{   
   WatchDog_off();
  Clock_Init();
  UART_Init();
  _EINT();
  while(1)
  {
    if(bufferend!=bufferstart)
    {
      Send_Byte(buffer[bufferstart]);
      if(bufferstart==127)
        bufferstart=0;
      else
        bufferstart++;
    }
    //printf(HELLOWORLD);
    delay_ms(10);       
  }
}
