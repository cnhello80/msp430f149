#ifndef _149uart_
#define _149uart_
#include "hello149.c"
#include <msp430x14x.h>
#include <stdio.h>
/*��BRCLK=CPU_Fʱ������Ĺ�ʽ���Լ��㣬����Ҫ�������ü����Ƶϵ��*/ 
#define baud           9600                                //���ò����ʵĴ�С 
#define baud_setting   (uint)((ulong)CPU_F/((ulong)baud))  //�����ʼ��㹫ʽ 
#define baud_h         (uchar)(baud_setting>>8)            //��ȡ��λ 
#define baud_l         (uchar)(baud_setting)               //��λ
unsigned char buffer[128];
unsigned int bufferstart=0;
unsigned int bufferend=0;
void Clock_Init()
{  
  uchar i;
  BCSCTL1&=~XT2OFF;                 //��XT2����
  BCSCTL2|=SELM1+SELS;              //MCLKΪ8MHZ��SMCLKΪ8MHZ
  do
  {    
    IFG1&=~OFIFG;                   //������������־
    for(i=0;i<100;i++)
      _NOP();
  }  
  while((IFG1&OFIFG)!=0);           //�����־λ1�������ѭ���ȴ�
  IFG1&=~OFIFG;
}
void UART_Init()
{  
  U1CTL|=SWRST + CHAR;                //��λSWRST��8λ����ģʽ
  U1TCTL|=SSEL1;                      //SMCLKΪ����ʱ��
  U1BR1=baud_h;                       //BRCLK=8MHZ,Baud=BRCLK/N
  U1BR0=baud_l;                       //N=UBR+(UxMCTL)/8
  U1MCTL=0x00;                        //΢���Ĵ���Ϊ0��������9600bps
  ME2|=UTXE1;                         //UART1����ʹ��
  ME2|=URXE1;                         //UART1����ʹ�� 
  U1CTL&=~SWRST;
  IE2|=URXIE1;                        //�����ж�ʹ��λ
  P3SEL|= BIT6 + BIT7;                //����IO��Ϊ�ڶ�����ģʽ������UART����
  P3DIR|= BIT6;                       //����TXD1�ڷ���Ϊ���
}
void Send_Byte(uchar data) 
{   
  while(!(IFG2&UTXIFG1));             //���ͼĴ����յ�ʱ��������
  U1TXBUF=data;
}

// �ض���c�⺯��printf��USART1
int putchar(int c)
{
  /* ����һ���ֽ����ݵ�USART1 */
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