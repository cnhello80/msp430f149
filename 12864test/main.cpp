#include <msp430x14x.h>
#include "430ctrl12864.h"

int main( void )
{
  WatchDog_off();//关闭看门狗
  lcdinit();                  //初始化LCD 
  LCD_clear(); //清屏
  LCD_write_string(0,0,DIS1);
  delay_ms(2000);
  return 0;
}
