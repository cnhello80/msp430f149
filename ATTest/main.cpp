#include <msp430x14x.h>
#include "hello149.c"
#include "149uart.c"
#include "atcommand.h"
void main(void) 
{   
  WatchDog_off();
  Clock_Init();
  UART_Init();
  Init_Wifi();
  while(1)
  {
    Send_Command(POSTTEST);
    //Send_Byte('a');
    delay_ms(10000);       
  }
}
