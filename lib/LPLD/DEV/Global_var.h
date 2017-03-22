#ifndef __GLOBAL_VAR_H__
#define __GLOBAL_VAR_H__


extern uint8 Pix_Data[MAX_ROW*MAX_COL/8];
extern uint8 Img[MAX_ROW][MAX_COL];

extern uint8 camera_flag;  
extern uint8 show_img_flag;
extern uint8 device_id;

/*--------------------ȫ�ֳ�ʼ����--------------------*/
extern uint8 keyValue;            //������̵�ֵ
extern float P;
extern float D;
extern int angle;                        //�����ʼ��ֵ
extern int leftMaxAngle;                 //�������
extern int rightMaxAngle;                //����Ҵ��
extern int midAngle;                     //����е�ֵ
extern int absMid;                       //����ʵ���е�ֵ
extern float CAR_SPEED_SET;              //Ԥ���ٶ�
extern float crossScale;                 //������
extern int SPEED;
 
/*-------------�ٶȿ��Ʊ���-------------*/
  
extern uint8 start;
extern int speedCount;
extern uint8 speedFlag;
extern float P_Speed;                                   //�ٶȿ���P   
extern float I_Speed;                                   //�ٶȿ���I  
extern float D_Speed;                                   //�ٶȿ���D  
extern float P_speed_out;                               //�ٶȿ�����P�������
extern float I_speed_out;                               //�ٶȿ�����I�������
extern float D_speed_out;                               //�ٶȿ�����D�������
extern float speed_control_integeral;                   //i�Ļ���
extern float speed_control_integeral_Max;               //i�Ļ������ֵ
extern float speed_control_integeral_Min;               //i�Ļ�����Сֵ
extern float dir_speed_radio;                           //΢���ٶȱ�
extern float Speed_Control_Max;                         //�ٶȿ������ֵ
extern float Speed_Control_Min;                         //�ٶȿ�����Сֵ
extern int   Speed_Control_Period;                      //���ٿ��Ƶ�������
extern float SPEED_CONTROL_PERIOD;  
extern float Speed_Car_Old;                             //���ٶ�(�ٶȿ���PID���õ�)
extern float Speed_Car_New;                             //���ٶ�(�ٶȿ���PID���õ�)
extern float Speed_Car;                                 //��ǰ�ٶ�
extern float Speed_Control_Out;                         //�ٶȿ�������ٶ�
extern float Speed_Car_err;             
extern float ref_speed;                                 //�Ӽ��� 
extern float last_ref_speed;                            //��ȥ�Ӽ���
extern float before_last_ref_speed;   
 
/*----------------------------------------------------------------------*/
 
 
 
/*-----------ɨ��ͼ��------------*/
//ͼ���ڸ��е����һ���׵�
extern int leftDot[MAX_ROW];          //��ߵ�λ��
extern int rightDot[MAX_ROW];         //�ұߵ�λ��
extern int midDot[MAX_ROW];           //�е�λ��
extern int countBlack[MAX_ROW];       //�ڵ����
extern int absMid;                    //ͼ����ֵ
extern int startLine;                 //��ʼ��
extern int endLine;                   //������
extern int Left;                      //�������߽�
extern int Right;                     //�������߽�
extern int lostSide;                  //�����ı߶���
 
 
/*------------ʮ���ж�------------*/
extern int vertical[MAX_COL];       //��ֱ�ѵ�
extern int runwayType;              //��������
extern int crossFlag;               //ʮ�ֱ�־
extern int advanceLineStart;        //ʮ���ж���ʼ��
extern int advanceLineEnd;          //������
 
extern int index1;                  //ͻ�������
extern int index2;
extern int index3;
extern int index4;
extern int col1;
extern int col2;
extern int col3;
extern int col4;
 
 
/*----------������Ʊ���----------*/
extern int advanceLine;         //Ԥ����
extern int Line1;               //������
extern int Line2;
extern int Line3;

extern int curAver;
extern int devAver;
extern int averData[3];
extern int sumAverData;
extern int countAver;
extern int preAver;


 
 //��Ͽ���
extern float a_x;
extern float b_x;
extern float c_x;
extern float xxl;
extern float a_x1;
extern float b_x1;
extern float c_x1;
extern float a_x2;
extern float b_x2;
extern float c_x2;
extern int index[MAX_ROW];         

//���Ʊ���(���)
/*
extern int line1;                  //��������
extern int line2;
extern int line3;
extern int s;                      //��ǰ���
extern int preS;                   //�ϴ����
extern int ctrLine = 35;           
extern float deviation = 0;        //��������Ĳ�
*/

/*----------------------------------------------------------------------*/



//ʮ�ִ���
typedef enum
{
    IMG_NOTINIT = 0,
    IMG_FINISH,                     //ͼ��ɼ����
    IMG_FAIL,                       //ͼ��ɼ�ʧ��(�ɼ���������)
    IMG_GATHER,                     //ͼ��ɼ���
    IMG_START,                      //��ʼ�ɼ�ͼ��
    IMG_STOP,                       //��ֹͼ��ɼ�
} IMG_STATUS_e;


#endif 