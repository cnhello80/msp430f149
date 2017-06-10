#include <msp430x14x.h>
#include "hello149.c"
#include "149uart.c"
#include "atcommand.h"
#include "430ctrl12864.h"
#include "SimpleUI.h"
int read_buffer()
{
  if(bufferstart==bufferend)
    return 0;
  else
  {
    //now_menu=2;
    if(buffer[bufferstart]=='L')
    {
      bufferstart++;
      return 1;
    }
    else
    {
      bufferstart++;
      return 2;
    }
  }
}

int main( void )
{
  WatchDog_off();
  Clock_Init();
  UART_Init();
  lcdinit();                  //≥ı ºªØLCD 
  LCD_clear(); //«Â∆¡
  _EINT();
  while(1)
  {
    input_process(read_buffer());
    //LCD_Line_fresh(0,0,Imeasure);
    LCD_refresh();
    delay_ms(1000);
  }
  return 0;
}
