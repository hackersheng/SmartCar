#ifndef __KEY_H__
#define __KEY_H__

#include "common.h"


#define KEY_PORT      PORTC     //KEY���ڵĶ˿� 
//#define KEY_ROW1 11
//#define KEY_ROW2 12
//#define KEY_ROW3 13
//#define KEY_COL1 14
//#define KEY_COL2 15
//#define KEY_COL3 16

#define KEY_ROW1 3
#define KEY_ROW2 4
#define KEY_ROW3 5
#define KEY_COL1 6
#define KEY_COL2 7
#define KEY_COL3 8

//����ֵö��
typedef enum
{   
    KEY_NONE  = 0,//��ʾ�յ�
    KEY_ONE  = 1,    
    KEY_TWO  = 2,
    KEY_THR  = 3,
    KEY_FOU  = 4,
    KEY_FIV  = 5,
    KEY_SIX  = 6, 
    KEY_SEV  = 7,
    KEY_EIG  = 8,
    KEY_NIN  = 9, //�ھŸ���ť

}KEY_Value;
//�����˿ں�
//typedef enum KEY
//{
//  KEY_ROW1    =  11,              //��Ӧ�е����ź�  �޸�ǰΪ 11 12 13
//  KEY_ROW2    =  12,   
//  KEY_ROW3    =  13,
//  KEY_COL1    =  14,           //��Ӧ�е����ź�  �޸�ǰΪ 14 15 16
//  KEY_COL2    =  15,
//  KEY_COL3    =  16,
//}KEY;




void Keyboard_init();                    // KEY��ʼ��    ����
void InitGPIOkey_I();
void InitGPIOkey_O();
uint8 key_scan();              //���key״̬

#endif  //__KEY_H__