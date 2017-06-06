#ifndef _hello149_  //防止重复定义
#define _hello149_
#define uchar unsigned char 
#define uint  unsigned int 
#define ulong unsigned long
#define CPU_F ((double)8000000) 
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
void WatchDog_off() 
{
  WDTCTL = WDTPW + WDTHOLD;       //关闭看门狗
}
#endif