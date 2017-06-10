#ifndef _SimpleUI_
#define _SimpleUI_
#include "430ctrl12864.h"
unsigned char Imeasure[]="电流测量模式";
unsigned char Umeasure[]="电压测量模式";
int now_menu=1;
void LCD_refresh()
{
  if(now_menu==1)
  {
    LCD_Line_fresh(0,0,Imeasure);
  }
  if(now_menu==2)
  {
    LCD_Line_fresh(0,0,Umeasure);
  }
}
void input_process(int button_sign)
{
  //return;
  if(button_sign==1)
    now_menu=now_menu-(now_menu==2);
  if(button_sign==2)
    now_menu=now_menu+(now_menu==1);
}
#endif