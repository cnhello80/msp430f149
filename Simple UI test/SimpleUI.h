#ifndef _SimpleUI_
#define _SimpleUI_
#include "430ctrl12864.h"
const unsigned char Imeasure[]="电流测量模式";
const unsigned char Umeasure[]="电压测量模式";
const uchar UPLOAD1[]="联网上传数据模式";
const uchar UPLOAD2[]="记录数据数:";
const uchar UPLOAD3[]="点击确认开始上传";
const uchar UPLOADING[]="上传中...";
const uchar UPLOADED[]="上传完成";
int now_menu=1;
int measure_mode=1;
int upload_status=0;
void LCD_refresh()
{
  if(now_menu==1)
  {
    if(measure_mode==1)
    {
      LCD_Line_fresh(0,0,Imeasure);
    }
    else if(measure_mode==1)
    {
      LCD_Line_fresh(0,0,Umeasure);
    }
  }
  if(now_menu==2)
  {
    LCD_Line_fresh(0,0,UPLOAD1);
    LCD_Line_fresh(0,1,UPLOAD2);
    switch(upload_status)
    {
    case 0:LCD_Line_fresh(0,2,UPLOAD3);break;
    case 1:LCD_Line_fresh(0,2,UPLOADING);break;
    case 2:LCD_Line_fresh(0,2,UPLOADED);break;
    }
  }
}
void input_process(int button_sign)
{
  //return;
  if(button_sign==1)
    now_menu=now_menu-(now_menu==2);
  if(button_sign==2)
    now_menu=now_menu+(now_menu==1);
  if(button_sign==3&&now_menu==2)
    upload_status=1;
}
#endif