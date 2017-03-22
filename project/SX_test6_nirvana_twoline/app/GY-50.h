#ifndef _GY_50_H_
#define _GY_50_H_
#include "include.h"

//***************************************
// GY-50 L3G4200D IIC���Գ���
// ʹ�õ�Ƭ��STC89C51 
// ����11.0592M
// ��ʾ��LCD1602
// ���뻷�� Keil uVision2
// �ο��꾧��վ24c04ͨ�ų���
// ʱ�䣺2011��9��1��
// QQ��531389319
//****************************************


/********�û����޸�ֵ ��ʼ***********/
//����SCCB�豸��ַ
#define SCCB_DEV_ADR    ADR_OV7725

#define   uchar unsigned char
#define   uint unsigned int	

//����SCL��SDA������
#define SDA       PTA13_O
#define SDA_Read  PTA13_I
#define SDA_Out   DDRA13=1
#define SDA_In    DDRA13=0

#define SCL       PTA12_O
#define SCL_Out   DDRA12=1  

#define ack 1
#define no_ack 0  
#define _nop_() asm("nop");           
//****************************************
#define	SlaveAddress   0x42	  //����������IIC�����еĴӵ�ַ
                               
typedef unsigned char  BYTE;
typedef unsigned short WORD;

//void delay(unsigned int k);
//void InitL3G4200D();                //��ʼ��L3G4200D
void LPLD_IIC_Init(void);
void Delay5us();
void GY_WriteByte(unsigned char Address, unsigned char Thedata);   //����д������
unsigned char GY_ReadByte(unsigned char Address);                //������ȡ�ڲ��Ĵ�������
                             
 #endif