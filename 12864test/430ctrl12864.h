#ifndef _430ctrl12864with1line_
#define _430ctrl12864with1line_
#include "hello149.c"
#include <msp430x14x.h>
#define uchar unsigned char
#define uint  unsigned int

//1 GND 2 VCC 5v 4 CS 5 SID 6 SCLK 15 PSB ���䷽ʽ �͵�ƽ 19BLA �������� 5V 20 BLK ���⸺��
#define LCD_CS_PORT P2OUT	//Ƭѡ �ߵ�ƽ��Ч ��ƬLCDʹ��ʱ�ɹ̶��ߵ�ƽ
#define LCD_CS_DDR P2DIR
#define LCD_CS BIT5 //CS P2.5 lcd RS
#define LCD_DATA_PORT P2OUT
#define LCD_DATA_DDR P2DIR
#define LCD_DATA BIT6 //DATA P2.6 lcd RW(SID)
#define LCD_CLK_PORT P2OUT
#define LCD_CLK_DDR P2DIR
#define LCD_CLK BIT7 //CLK P2.7 lcd E(SCLK)

//sbit PSB   =  P3^7;	//�͵�ƽʱ��ʾ�ô����������ɹ̶��͵�ƽ
//sbit RESET =  P2^5;	//LCD��λ��LCDģ���Դ���λ��·���ɲ���

void delay_lcd(int ms) //lcd��200us��ʱ
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
* ����һ���ֽ�                                           *
*                                                        *
*********************************************************/
void sendbyte(uchar bbyte) 
{
  uchar i;
  for(i=0;i<8;i++)
  {
  
   if(bbyte&0x80)            //ȡ�����λ
    {
      LCD_DATA_PORT|=LCD_DATA;                     //SIDΪ1
    }
    else
    {
      LCD_DATA_PORT&=~(LCD_DATA);                   //SIDΪ0                       
    }
   LCD_CLK_PORT|=LCD_CLK;
   delay_us(1);
   delay_us(1);
   LCD_CLK_PORT&=~LCD_CLK;
   bbyte<<=1; //����
  }  
}

void LCD_write(uint start, uchar ddata) //����/ָ�����
{
  uchar start_data,Hdata,Ldata;

  if(start==0)                   //11111,(0),(0),0
   start_data=0xf8;	             //дָ��
   else                          //11111,(0),(1),0
   start_data=0xfa;              //д����
  
  Hdata=ddata&0xf0;		         //ȡ����λ
  Ldata=(ddata<<4)&0xf0;         //ȡ����λ
  sendbyte(start_data);	         //������ʼ�ź�
  delay_lcd(1);                   //��ʱ
  sendbyte(Hdata);	             //���͸���λ
  delay_lcd(1);                   //��ʱ
  sendbyte(Ldata);		         //���͵���λ
  delay_lcd(1);                   //��ʱ
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
  delay_lcd(10);      //��ʱ�ȴ�LCM���빤��״̬
 // PSB=0; ;   	      //��������ģʽ
  LCD_CS_DDR|=LCD_CS;
  LCD_DATA_DDR|=LCD_DATA;
  LCD_CLK_DDR|=LCD_CLK;
  P2SEL&=~LCD_DATA;
  P2SEL&=~LCD_CLK;
//  RESET=0; 
  delay_lcd(5);
//  RESET=1;           //��λLCD
  LCD_CS_PORT|=LCD_CS;
  //CS=1;              //Ƭѡ �ߵ�ƽ��Ч
  
  LCD_write(0,0x30);     //����ָ�����
  LCD_write(0,0x0c);     //��ʾ�򿪣����أ����׹�
  LCD_write(0,0x01);     //��������DDRAM�ĵ�ַ����������
  LCD_write(0,0x06);  
}

uchar DIS1[] = {"    �������   "};
uchar DIS2[] = {"TX51STARʵ���� "};
uchar DIS3[] = {"www.tx-power.com"};
uchar DIS4[] = {"TEL:045187572303"};


void LCD_clear() //����
{
  LCD_write(0,0x30);          //����ָ�����
  LCD_write(0,0x01);          //���� 
}
void LCD_set_address(uchar x,uchar y) //���õ�ַ x y
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

void LCD_write_string(uchar x,uchar y,uchar *str) //д���� x y �ַ���ָ��
{
  LCD_set_address(x,y); //д��ַ
  
  while (*str)          //д��ʾ�ַ�
    {
      LCD_write_data( *str );
      str++;
    }
}
#endif