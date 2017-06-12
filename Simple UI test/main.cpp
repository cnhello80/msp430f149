#include <msp430x14x.h>
#include "hello149.c"
#include "149uart.c"
#include "atcommand.h"
#include "430ctrl12864.h"
#include "SimpleUI.h"
int read_buffer_button() //读取UART传来的简单指令
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
    else if(buffer[bufferstart]=='R')
    {
      bufferstart++;
      return 2;
    }
    else if (buffer[bufferstart]=='O')
    {
      bufferstart++;
      return 3;
    }
  }
  return 0;
}

int main( void )
{
  WatchDog_off();
  Clock_Init();
  UART_Init();
  lcdinit();                  //初始化LCD 
  LCD_clear(); //清屏
  _EINT();
  while(1)
  {
    input_process(read_buffer_button());
    //LCD_Line_fresh(0,0,Imeasure);
    LCD_refresh();
    delay_ms(1000);
  }
  return 0;
}
