#ifndef _atcom_
#define _atcom_
#include "149uart.c"

const char HELLOWORLD []= "hello world!";
const char EOLTEST[]="The line.\r\nAnother line.\r\n";
const char SETMODE[]="AT+CWMODE_CUR=1";   //�趨����ģʽΪ1��station
const char LINKWIFI[]="AT+CWJAP_CUR=\"Xiaomi_hello\",\"wewewewe\"";   //����WiFi SSID ���� ���洢��оƬ
const char SETLINK[]="AT+CIPMUX=0";    //����Ϊ������ģʽ
const char SETCIP[]="AT+CIPMODE=1";   //����͸��ģʽ����
const char LINKSERVER[]="AT+CIPSTART=\"TCP\",\"hello80.fangyuwang.com\",80";  //���ӵ�������
const char CIPSTART[]="AT+CIPSEND"; //��ʼ͸��ģʽ
const char POSTTEST[]="POST /esptest.php HTTP/1.1\r\nHost: hello80.fangyuwang.com\r\nContent-Length:16\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ndata=hello world";
void Init_Wifi()
{
  Send_Command(SETMODE);
  delay_ms(500);
  Send_Command(LINKWIFI);
  delay_ms(5000);
  Send_Command(SETLINK);
  delay_ms(200);
  Send_Command(SETCIP);
  delay_ms(200);
  Send_Command(LINKSERVER);
  delay_ms(500);
  Send_Command(CIPSTART);
  delay_ms(200);
}
#endif