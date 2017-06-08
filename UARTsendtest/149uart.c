#ifndef _149uart_
#define _149uart_
#include "hello149.c"
#include <msp430x14x.h>
#include <stdio.h>
/*当BRCLK=CPU_F时用下面的公式可以计算，否则要根据设置加入分频系数*/ 
#define baud           9600                                //设置波特率的大小 
#define baud_setting   (uint)((ulong)CPU_F/((ulong)baud))  //波特率计算公式 
#define baud_h         (uchar)(baud_setting>>8)            //提取高位 
#define baud_l         (uchar)(baud_setting)               //低位
unsigned char buffer[128];
unsigned int bufferstart=0;
unsigned int bufferend=0;
void Clock_Init()
{  
  uchar i;
  BCSCTL1&=~XT2OFF;                 //打开XT2振荡器
  BCSCTL2|=SELM1+SELS;              //MCLK为8MHZ，SMCLK为8MHZ
  do
  {    
    IFG1&=~OFIFG;                   //清楚振荡器错误标志
    for(i=0;i<100;i++)
      _NOP();
  }  
  while((IFG1&OFIFG)!=0);           //如果标志位1，则继续循环等待
  IFG1&=~OFIFG;
}
void UART_Init()
{  
  U1CTL|=SWRST + CHAR;                //复位SWRST，8位数据模式
  U1TCTL|=SSEL1;                      //SMCLK为串口时钟
  U1BR1=baud_h;                       //BRCLK=8MHZ,Baud=BRCLK/N
  U1BR0=baud_l;                       //N=UBR+(UxMCTL)/8
  U1MCTL=0x00;                        //微调寄存器为0，波特率9600bps
  ME2|=UTXE1;                         //UART1发送使能
  ME2|=URXE1;                         //UART1接收使能 
  U1CTL&=~SWRST;
  IE2|=URXIE1;                        //接收中断使能位
  P3SEL|= BIT6 + BIT7;                //设置IO口为第二功能模式，启用UART功能
  P3DIR|= BIT6;                       //设置TXD1口方向为输出
}
void Send_Byte(uchar data) 
{   
  while(!(IFG2&UTXIFG1));             //发送寄存器空的时候发送数据
  U1TXBUF=data;
}

// 重定向c库函数printf到USART1
int putchar(int c)
{
  /* 发送一个字节数据到USART1 */
  Send_Byte((uchar) c);	
  return (c);
}
#pragma vector=UART1RX_VECTOR
__interrupt void UART1_RX_ISR(void)
{
    buffer[bufferend] =U1RXBUF; 
    if(bufferend==127)
      bufferend=0;
    else
      bufferend++;
}
#endif