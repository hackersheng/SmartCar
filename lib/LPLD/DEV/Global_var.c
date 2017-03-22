#include "include.h"


uint8 Pix_Data[MAX_ROW*MAX_COL/8];     //�ɼ�60�� 80�е�ͼ������  60*80/8;
uint8 Img[MAX_ROW][MAX_COL];          //��ѹ�������
uint8 camera_flag = 0;                //0��ʾ���ɲɼ���1��ʾ���Բɼ�
uint8 show_img_flag = 0;              //0��ʾ������ʾ��1��ʾ������ʾ
uint8 device_id = 0;



/*--------------------ȫ�ֳ�ʼ����--------------------*/
uint8 keyValue = 0;                   //������̵�ֵ
float P = 35;
float D = 35;
int angle = 720;                  //�����ʼ��ֵ
int leftMaxAngle = 635;           //�������
int rightMaxAngle = 815;          //����Ҵ��
int midAngle = 720;               //����е�ֵ
float CAR_SPEED_SET = 100;        //Ԥ���ٶ�
float crossScale = 0.8;           //������
int SPEED = 2000;

/*-------------�ٶȿ��Ʊ���-------------*/
 
uint8 start = 0;
int speedCount = 0;
//uint8 speedFlag = 0;
float P_Speed = 50;                             //�ٶȿ���P   
float I_Speed = 25;                             //�ٶȿ���I  
float D_Speed = 8;                              //�ٶȿ���D  
float P_speed_out = 0;                          //�ٶȿ�����P�������
float I_speed_out = 0;                          //�ٶȿ�����I�������
float D_speed_out = 0;                          //�ٶȿ�����D�������
float speed_control_integeral = 0;              //i�Ļ���
float speed_control_integeral_Max = 10000;      //i�Ļ������ֵ
float speed_control_integeral_Min = -10000;     //i�Ļ�����Сֵ
float dir_speed_radio = 0;                      //΢���ٶȱ�
float Speed_Control_Max = 9500;                 //�ٶȿ������ֵ
float Speed_Control_Min = -8000;                //�ٶȿ�����Сֵ
int   Speed_Control_Period = 0;                 //���ٿ��Ƶ�������
float SPEED_CONTROL_PERIOD = 8;  
float Speed_Car_Old;                            //���ٶ�(�ٶȿ���PID���õ�)
float Speed_Car_New = 1000;                            //���ٶ�(�ٶȿ���PID���õ�)
float Speed_Car;                                //��ǰ�ٶ�
float Speed_Control_Out;                        //�ٶȿ�������ٶ�
float Speed_Car_err = 0;             
float ref_speed = 0;                            //�Ӽ��� 
float last_ref_speed = 0;                       //��ȥ�Ӽ���
float before_last_ref_speed = 0;   

/*----------------------------------------------------------------------*/



/*-----------ɨ��ͼ��------------*/
//ͼ���ڸ��е����һ���׵�
int leftDot[MAX_ROW];         //��ߵ�λ��
int rightDot[MAX_ROW];        //�ұߵ�λ��
int midDot[MAX_ROW];          //�е�λ��
int countBlack[MAX_ROW];      //�ڵ����
int absMid = MAX_COL/2 - 6;     //ͼ����ֵ
int startLine = MAX_ROW-13;    //��ʼ��
int endLine = 20;             //������ <= Ԥ����
int Left;                     //�������߽�
int Right;                    //�������߽�
int lostSide = 0;             //�����ı߶���


/*------------ʮ���ж�------------*/
int vertical[MAX_COL];        //��ֱ�ѵ�
int runwayType = 9;           //��������
int crossFlag = 0;            //ʮ�ֱ�־

int index1 = -1;              //ͻ�������
int index2 = -1;
int index3 = -1;
int index4 = -1;
int col1 = -1;
int col2 = -1;
int col3 = -1;
int col4 = -1;

/*----------������Ʊ���----------*/
int advanceLine = 20;         //Ԥ����
int Line1 = 25;               //������
int Line2 = 35;
int Line3 = 45;

int curAver;
int devAver;
int averData[3] = {0};
int sumAverData;
int countAver;
int preAver;
        

/*
//���Ʊ���(���)
int line1;                  //��������
int line2;
int line3;
int s;                      //��ǰ���
int preS;                   //�ϴ����
int ctrLine = 35;           
float deviation = 0;        //��������Ĳ�
*/

/*----------------------------------------------------------------------*/





