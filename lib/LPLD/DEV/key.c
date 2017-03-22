#include "key.h"


/*************************************************************************
*                           �θ�ѧԺ���ܳ���
*
*  �������ƣ�key_init
*  ����˵������ʼ��key�˿ڣ�������Ϊ�������Ϊ��������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2015-10-2   �Ѳ���
*  ��    ע��
*************************************************************************/



  GPIO_InitTypeDef InitGPIOKEY1; 
  GPIO_InitTypeDef InitGPIOKEY2;

void Keyboard_init()                                               // KEY��ʼ�� ����
{
     InitGPIOkey_O();
     InitGPIOkey_I();
} 


/*************************************************************************
*                             �θ�ѧԺ���ܳ���
*
*  �������ƣ�key_scan
*  ����˵��:ɨ�谴�������
*  ����˵������
*  �������أ������µİ�����ֵ,��֧������ͬʱ����
*  �޸�ʱ�䣺2015-10-2   �Ѳ���
*  ��    ע��
*************************************************************************/
uint8 key_scan()
{

    uint8 KeyValue =0;//Ĭ��û�а�������
    int i = 0;//��ʼɨ��Ķ˿�
//    for(i=11;i<=13;i++)
//    {
//      LPLD_GPIO_Output_b(PTC, i, 1);//��������ߵ�ƽ
//      
//      if(LPLD_GPIO_Input_b(PTC, 14)==1)//��ʾ��һ���а�������
//      {
//        keyValue = 1+(i-11)*3;
//       while(LPLD_GPIO_Input_b(PTC, 14)==1);//�ȴ������ſ�
//      }
//      
//      else if(LPLD_GPIO_Input_b(PTC, 15)==1)//��ʾ�ڶ����а�������
//      {
//        keyValue = 2+(i-11)*3;
//        while(LPLD_GPIO_Input_b(PTC, 15)==1);//�ȴ������ſ�
//      }
//      
//      else if(LPLD_GPIO_Input_b(PTC, 16)==1)//��ʾ�������а�������
//      {
//        keyValue = 3+(i-11)*3;
//        while(LPLD_GPIO_Input_b(PTC, 16)==1);//�ȴ������ſ�
//      } 
//     LPLD_GPIO_Output_b(PTC, i, 0);//�ָ��͵�ƽ
//    }//����ɨ��
    
    for(i = 3;i <= 5;i++)
    {
      LPLD_GPIO_Output_b(PTC, i, 1);//��������ߵ�ƽ
      
      if(LPLD_GPIO_Input_b(PTC, 6) == 1)//��ʾ��һ���а�������
      {
        KeyValue = 1 + (i - 3) * 3;
        while(LPLD_GPIO_Input_b(PTC, 6) == 1);//�ȴ������ſ�
      }
      
      else if(LPLD_GPIO_Input_b(PTC, 7) == 1)//��ʾ�ڶ����а�������
      {
        KeyValue = 2 + (i - 3) * 3;
        while(LPLD_GPIO_Input_b(PTC, 7) == 1);//�ȴ������ſ�
      }
      
      else if(LPLD_GPIO_Input_b(PTC, 8) == 1)//��ʾ�������а�������
      {
        KeyValue = 3 + (i - 3) * 3;
        while(LPLD_GPIO_Input_b(PTC, 8) == 1);//�ȴ������ſ�
      }
      LPLD_GPIO_Output_b(PTC, i, 0);//�ָ��͵�ƽ
    }//����ɨ��
    return KeyValue;
}


void InitGPIOkey_O()
{
  /*���ýṹ���GPIO_PTx������ѡ��ʹ��PTD���PTE����
   *���ýṹ���GPIO_Pins������ѡ��ʹ�ñ��ΪE0 -- E6������
   *���ýṹ���GPIO_Dir����������PTD��������ŷ���Ϊ���
   *���ýṹ���GPIO_Output����������PTD��������ų�ʼ�����Ϊ�ߵ�ƽ
   *���ýṹ���GPIO_PinControl���������ö˿ڵĿ���ģʽΪ��ֹ�ж�
   *����GPIO��ʼ���Ŀ⺯����������ʼ���ṹ������������У���ɳ�ʼ��*/

//  InitGPIOKEY1.GPIO_PTx = PTC;
//  InitGPIOKEY1.GPIO_Pins = GPIO_Pin11 | GPIO_Pin12 | GPIO_Pin13;
//  InitGPIOKEY1.GPIO_Dir = DIR_OUTPUT;
//  InitGPIOKEY1.GPIO_Output = OUTPUT_L;
//  InitGPIOKEY1.GPIO_PinControl = IRQC_DIS;
//  LPLD_GPIO_Init(InitGPIOKEY1);
  
  
  InitGPIOKEY1.GPIO_PTx = PTC;
  InitGPIOKEY1.GPIO_Pins = GPIO_Pin3 | GPIO_Pin4 | GPIO_Pin5;
  InitGPIOKEY1.GPIO_Dir = DIR_OUTPUT;
  InitGPIOKEY1.GPIO_Output = OUTPUT_L;
  InitGPIOKEY1.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(InitGPIOKEY1);
}
void InitGPIOkey_I()
{
  /*���ýṹ���GPIO_PTx������ѡ��ʹ��PTD���PTE����
   *���ýṹ���GPIO_Pins������ѡ��ʹ�ñ��ΪE0 -- E6������
   *���ýṹ���GPIO_Dir����������PTD��������ŷ���Ϊ����
   *���ýṹ���GPIO_PinControl���������ö˿ڵĿ���ģʽΪ��ֹ�ж�
   *����GPIO��ʼ���Ŀ⺯����������ʼ���ṹ������������У���ɳ�ʼ��*/
//  InitGPIOKEY2.GPIO_PTx = PTC;
//  InitGPIOKEY2.GPIO_Pins =GPIO_Pin14 | GPIO_Pin15 | GPIO_Pin16;
//  InitGPIOKEY2.GPIO_Dir = DIR_INPUT;
//  InitGPIOKEY2.GPIO_PinControl = INPUT_PULL_DOWN;
//  LPLD_GPIO_Init(InitGPIOKEY2);
  
  InitGPIOKEY2.GPIO_PTx = PTC;
  InitGPIOKEY2.GPIO_Pins =GPIO_Pin6 | GPIO_Pin7 | GPIO_Pin8;
  
  InitGPIOKEY2.GPIO_Dir = DIR_INPUT;
  InitGPIOKEY2.GPIO_PinControl = INPUT_PULL_DOWN;
  LPLD_GPIO_Init(InitGPIOKEY2);
}

