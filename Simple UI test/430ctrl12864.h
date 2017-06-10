#ifndef _430ctrl12864with1line_
#define _430ctrl12864with1line_
#include "hello149.c"
#include <msp430x14x.h>
#define uchar unsigned char
#define uint  unsigned int

//1 GND 2 VCC 5v 4 CS 5 SID 6 SCLK 15 PSB 传输方式 低电平 19BLA 背光正极 5V 20 BLK 背光负极
#define LCD_CS_PORT P2OUT	//片选 高电平有效 单片LCD使用时可固定高电平
#define LCD_CS_DDR P2DIR
#define LCD_CS BIT5 //CS P2.5 lcd RS
#define LCD_DATA_PORT P2OUT
#define LCD_DATA_DDR P2DIR
#define LCD_DATA BIT6 //DATA P2.6 lcd RW(SID)
#define LCD_CLK_PORT P2OUT
#define LCD_CLK_DDR P2DIR
#define LCD_CLK BIT7 //CLK P2.7 lcd E(SCLK)

//sbit PSB   =  P3^7;	//低电平时表示用串口驱动，可固定低电平
//sbit RESET =  P2^5;	//LCD复位，LCD模块自带复位电路。可不接

void delay_lcd(int ms) //lcd用200us延时
{
  //uint t;
  uint i;
   for (i=0;i<ms;i++)
  {
    delay_us(1);
  }
}
/*********************************************************
*                                                        *
* 发送一个字节                                           *
*                                                        *
*********************************************************/
void sendbyte(uchar bbyte) 
{
  uchar i;
  for(i=0;i<8;i++)
  {
  
   if(bbyte&0x80)            //取出最高位
    {
      LCD_DATA_PORT|=LCD_DATA;                     //SID为1
    }
    else
    {
      LCD_DATA_PORT&=~(LCD_DATA);                   //SID为0                       
    }
   LCD_CLK_PORT|=LCD_CLK;
   delay_us(1);
   delay_us(1);
   LCD_CLK_PORT&=~LCD_CLK;
   bbyte<<=1; //左移
  }  
}

void LCD_write(uint start, uchar ddata) //数据/指令，数据
{
  uchar start_data,Hdata,Ldata;

  if(start==0)                   //11111,(0),(0),0
   start_data=0xf8;	             //写指令
   else                          //11111,(0),(1),0
   start_data=0xfa;              //写数据
  
  Hdata=ddata&0xf0;		         //取高四位
  Ldata=(ddata<<4)&0xf0;         //取低四位
  sendbyte(start_data);	         //发送起始信号
  delay_lcd(1);                   //延时
  sendbyte(Hdata);	             //发送高四位
  delay_lcd(1);                   //延时
  sendbyte(Ldata);		         //发送低四位
  delay_lcd(1);                   //延时
}
void LCD_write_data(uchar ddata)
{
  LCD_write(1, ddata);
}
void LCD_write_command(uchar ddata)
{
  LCD_write(0, ddata);
}
void lcdinit()	 
{
  delay_lcd(10);      //延时等待LCM进入工作状态
 // PSB=0; ;   	      //串口驱动模式
  LCD_CS_DDR|=LCD_CS;
  LCD_DATA_DDR|=LCD_DATA;
  LCD_CLK_DDR|=LCD_CLK;
  P2SEL&=~LCD_DATA;
  P2SEL&=~LCD_CLK;
//  RESET=0; 
  delay_lcd(5);
//  RESET=1;           //复位LCD
  LCD_CS_PORT|=LCD_CS;
  //CS=1;              //片选 高电平有效
  
  LCD_write(0,0x30);     //基本指令操作
  LCD_write(0,0x0c);     //显示打开，光标关，反白关
  LCD_write(0,0x01);     //清屏，将DDRAM的地址计数器归零
  LCD_write(0,0x06);  
}

uchar DIS1[] = {"    天祥电子   "};
uchar DIS2[] = {"TX51STAR实验箱 "};
uchar DIS3[] = {"www.tx-power.com"};
uchar DIS4[] = {"TEL:045187572303"};
uchar BLANK[]={"                "};

void LCD_clear() //清屏
{
  LCD_write(0,0x30);          //基本指令操作
  LCD_write(0,0x01);          //清屏 
}
void LCD_set_address(uchar x,uchar y) //设置地址 x y
{
  uchar address;
  if(y ==0)
    address=0x80;
  else if(y==1)
    address=0x90;
  else if(y==2)
    address=0x88;
  else if(y==3)
    address=0x98;
  address=address+x;
  LCD_write(0,address);
}

void LCD_write_string(uchar x,uchar y,uchar *str) //写句子 x y 字符串指针
{
  LCD_set_address(x,y); //写地址
  
  while (*str)          //写显示字符
    {
      LCD_write_data( *str );
      str++;
    }
}

void LCD_Line_fresh(uchar x,uchar y,uchar *str)
{
  LCD_write_string(x,y,BLANK);
  LCD_write_string(x,y,str);
}
#endif