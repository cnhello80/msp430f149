#ifndef _SimpleUI_
#define _SimpleUI_
#include "430ctrl12864.h"
unsigned char Imeasure[]="��������ģʽ";
unsigned char Umeasure[]="��ѹ����ģʽ";
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