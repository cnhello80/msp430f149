#include <msp430x14x.h>
#include "430ctrl12864.h"

int main( void )
{
  WatchDog_off();//�رտ��Ź�
  lcdinit();                  //��ʼ��LCD 
  LCD_clear(); //����
  LCD_write_string(0,0,DIS1);
  delay_ms(2000);
  return 0;
}
