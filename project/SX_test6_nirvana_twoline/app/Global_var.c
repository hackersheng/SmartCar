#include "include.h"

uint8 device_id = 0;
uint8 Pix_Data[600];       //�ɼ�60�� 80�е�ͼ������
uint8 Pix_Data_prev[600];       //�ɼ�60�� 80�е�ͼ������



uint8 Img[60][80];           //��ѹ�������
uint8 Img_prve[60][80];     //��һ֡
uint8 Img_current[60][80]; //��ǰ֡
uint8 camera_flag = 0;         //0��ʾ���ɲɼ���1��ʾ���Բɼ�
uint8 show_img_flag = 0;       //0��ʾ������ʾ��1��ʾ������ʾ
int pixchange_flag=0;

int pixel_left;
int pixel_right;
float steering_err = 0;
float steering_errprev=0;
float steering_p = 20;
float steering_d = 20;

int steering_middle = 775
;
int steering_left = 565;
int steering_right = 955;
float steering_out = 775;



int Left_Line[60];
int Right_Line[60];
int Center_Line[60];



uint8 turn_right=0;
uint8 turn_left=0;
uint8 prev_mid=40;

