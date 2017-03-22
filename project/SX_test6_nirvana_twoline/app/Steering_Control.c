#include "include.h"
/*�����ӵı���*/
#define white 255
#define black 0


#define ROW_MAX 60
#define COL_MAX 80

/* 80*60
*/


uint8 Left_Valid[ROW_MAX];
uint8 Right_Valid[ROW_MAX];

uint8 Left_turnmax=0;
uint8 Right_turnmax=0;

uint8 straight_cross=0;

uint8 Left_flag=0,Right_flag=0;
int turn=0;
int turn1=0;
int turn2=0;
int last_turn=0;
int D_value=0;
int D_value_old=0;

FTM_InitTypeDef steering_init_struct;
uint8 m_abs(int m);
void  search_line(void);

void steering_init()
{
  steering_init_struct.FTM_Ftmx = FTM2;	
  steering_init_struct.FTM_Mode = FTM_MODE_PWM;	
  steering_init_struct.FTM_PwmFreq = 50;
  
  LPLD_FTM_Init(steering_init_struct);
  
  LPLD_FTM_PWM_Enable(FTM2, 
                      FTM_Ch1, 
                      steering_middle,  
                      PTB19, 
                      ALIGN_LEFT       
                        );  
}


void steering_control(void)
{
  search_line();
  
  
  last_turn=turn;
  turn1=Center_Line[39]-40;
  turn2=Center_Line[30]-40;
  turn=(turn1*8+turn2*2)/10;
  
  D_value=(-turn);
  
  if(turn_left&&turn_right)
  steering_out=steering_middle-(D_value*(steering_p+20));//+(D_value-D_value_old*steering_d));
  
  else
     steering_out=steering_middle-(D_value*(steering_p));//+(D_value-D_value_old*steering_d));
  
  
   if(steering_out<=steering_left)
  {steering_out = steering_left;}
  if(steering_out>=steering_right)
  {steering_out = steering_right;}
   LCD_Write_Float_Dot(85,0,turn,2);
   
   
 LCD_Write_Float_Dot(108,2,Right_Line[30],0);
 LCD_Write_Float_Dot(85,2,Left_Line[30],0);
 
    LCD_Write_Float_Dot(108,3,Right_Line[39],0);
  LCD_Write_Float_Dot(85,3,Left_Line[39],0);
  
//  for(uint8 i=59;i>19;i--)
//  {
//    LCD_PutPixel(i,Center_Line[i]); 
//    LCD_PutPixel(i,Left_Line[i]); 
//    LCD_PutPixel(i,Right_Line[i]); 
//  }
   //   steering_err=40-(right[8]+left[8])/2;
  LPLD_FTM_PWM_ChangeDuty(FTM2, FTM_Ch1, (int)steering_out);
  
  
  turn_right=0;
  turn_left=0;
straight_cross=0;
}
void  search_line(void)
{

  uint8 max_row=0;
  uint8 cross_flag=0;

  
  for(uint8 y=59;y>19;y--)
  {
    
    Left_flag=0;
    Right_flag=0;
    
    Left_Line[y]=1;//��ʼ�������Ϊ1
    Right_Line[y]=78;//��ʼ���Һ���Ϊ1
    //��
    for(uint8 xl=40;xl>1;xl--)
    {
      if(Img[y][xl]==white&&Img[y][xl-2]==black)
      {
        Left_Line[y]=xl+2;
        Left_flag=1;
        break;
      }
    
    }
    

    //��
    for(uint8 xr=40;xr<78;xr++)
    {
      if(Img[y][xr]==white&&Img[y][xr+2]==black)
      {
        Right_Line[y]=xr-2;
        Right_flag=1;
        break;
      }
    }
    
    if(y>56)
    {
      if(!Right_flag&&!Left_flag)
        cross_flag=1;
    }
    
   if(Right_flag&&Left_flag)
     Center_Line[y]=(Right_Line[y]+Left_Line[y])/2;
    
      // else if(!Right_flag&&!Left_flag)//ֱ��ʮ��
    else if(Right_Line[y]-Left_Line[y]>60)
   {
     straight_cross++;
   }
    
   else if(!Left_flag&&Right_flag&&!straight_cross)//��ת
   {
     Center_Line[y]=Right_Line[y]-(Right_Line[y+1]-Center_Line[y+1]);
     turn_left=1;
   }
   else if(Left_flag&&!Right_flag&&!straight_cross)//��ת
   {
     Center_Line[y]=Left_Line[y]+(Center_Line[y+1]-Left_Line[y+1]);
     turn_right=1;
   }

   
   
   

  }
  
  
  if(straight_cross>3)
  {
     uint8 x1=0,y1=0;
     uint8 x2=0,y2=0;
     uint8 x3=0,y3=0;
     uint8 x4=0,y4=0;
     uint8 fLeft_Flag=0;
     uint8 fRight_Flag=0;
     uint8 mid=0;
     
     float k1,k2;
     for(uint8 i=59;i>19;i=i-5)
     {
       if((m_abs(Left_Line[i+1]-Left_Line[i]))>5)
       {
         x1=Left_Line[i+1];
         y1=i;
         fLeft_Flag=1;
       }
       
       else if((Right_Line[i]-Right_Line[i+1])>15)
       {
         x2=Right_Line[i+1];
         y2=i;
         fRight_Flag=1;
       }
       else if(fLeft_Flag&&fRight_Flag)
        break;       
     }
     
     fLeft_Flag=0;     
     fRight_Flag=0;
     
     if(y1>=y2)//���µ�y1�����µ�y2 �� 
     {
       mid=(Right_Line[y1]+Left_Line[y1])/2;

     }
     
      else    if(y1<y2)//���µ�y1�����µ�y2 ��
     {
       mid=(Right_Line[y2]+Left_Line[y2])/2;
     }
     
            
       
       for(uint8 i=y1;i>19;i--)
       {
         if((Left_Line[i]-Left_Line[i+1])>15)
         {
           y3=i;
           x3=Left_Line[i];
           break;
         }
       }
       for(uint8 i=y2;i>19;i--)
       {
         if((Right_Line[i+1]-Right_Line[i])>15)
         {
           y4=i;
           x4=Right_Line[i];
           break;
         }
       }
     
     k1=(y1-y3)/(x1-x3);
     k2=(y2-y4)/(x2-x4);
     
     for(uint8 i=y3;y3<y1;y3++)
     {
       Left_Line[i]=Left_Line[i-1]+(int)k1;
     }
     
     
    // Center_Line[y]=(Right_Line[y]+Left_Line[y])/2;
  }
}

 

/*
void  search_line(void)
{
  uint8 Left_End=0;//��Ч������
  uint8 Right_End=0;
  
  uint8 Left_Valid_Count=0;//Ĭ���������Ч��������ֵΪ0
  uint8 Right_Valid_Count=0;//Ĭ���ұ�����Ч��������ֵΪ0
  
  uint8 Left_Invalid_Count=0;//Ĭ���������Ч��������ֵΪ0
  uint8 Right_Invalid_Count=0;//Ĭ���ұ�����Ч��������ֵΪ0
  
  uint8 Left_Turn_Count=0;//���������쳣��������
  uint8 Right_Turn_Count=0;
  
  uint8 Left_Break=0;
  uint8 Right_Break=0;
  
  uint8 Cross_Flag=0;//Ĭ����ʮ��
  Left_flag=0;
  Right_flag=0;

  //ǰ3��
  for(uint8 i=59;i>56;i--)
  {
    Left_Line[i]=1;//��ʼ�������Ϊ1
    Right_Line[i]=78;//��ʼ���Һ���Ϊ78
    Left_Valid[i]=0;//Ĭ�����δ�ҵ�����
    Right_Valid[i]=0;//Ĭ���ұ�δ�ҵ�����
    Center_Line[i]=40;//Ĭ������Ϊͼ���м�
    //���м䵽��
    for(uint8 j=40;j>0;j--)
    {
      if(Img[i][j]==white&&Img[i][j-2]==black)
      {
        Left_Line[i]=j;//����λ��
        Left_Valid[i]=1;//�����������Чλ��1
        Left_Valid_Count++;//������Ч��+1
        Left_Invalid_Count=0;
        break;
      }
    }
    
    if(Left_Valid[i]==0)
    {
      Left_Valid_Count=0;
      Left_Invalid_Count++;
    }
    
    //���м䵽�ұ�
    for(uint8 k=40;k<80;k++)
    {
      if(Img[i][k]==white&&Img[i][k+2]==black)
      {
        Right_Line[i]=k;
        Right_Valid[i]=1;
        Right_Valid_Count++;
        Right_Invalid_Count=0;
        break;
      }
    }
    if(Right_Valid[i]==0)
    {
      Right_Valid_Count=0;
      Right_Invalid_Count++;
    }
    
    
    
    Center_Line[i]=(Right_Line[i]+Left_Line[i])/2;
  }
  
  
  if(Left_Valid_Count==3&&Right_Valid_Count==3)
  {
    for(uint8 i=56;i>29;i--)
    {
      uint8 col;
      
      //�м�����
      Left_Line[i]=1;//��ʼ��Ϊ1
      Left_Valid[i]=0;//��ʼ��ÿ����Ч
      
      col=Left_Line[i+1]+6;//������ֵ�������������
      Left_End=Left_Line[i+1]-6;
      
    //  for(;col>Left_End;col--)     
      for(uint8 m=40;m>0;m--)
      {
        if(Img[i][col]==white&&Img[i][col-2]==black)
        {
          Left_Line[i]=col;//����λ��
            Left_flag=1;
          Left_Invalid_Count=0;//����������Чֵ����
          if(Left_Line[i]<Left_Line[i+1])//���������쳣����������
          {
            Left_Turn_Count++;//�������������쳣��������+1
            Left_Valid[i]=1;//��ʱ��Ǵ����������Чλ��1
            break;
          }
          else//����������������
          {
            Left_Turn_Count=0;//�������������쳣��������ֵ����
            Left_Valid[i]=1;//�����������Чλ��1
            break;
          }
        }
        else 
          Left_Line[m]=0;
      }
      if(Left_Valid[i]==0)//����û���ҵ������
        Left_Invalid_Count++;
      if(Left_Turn_Count==3)//��������������쳣��һ���ж��Ƿ�Ϊб��ʮ��
      {
        //�����ж�ʮ��
      }
      if(Left_Invalid_Count==3)
      {
        Left_Break=i+3;//��ߺ��߶ϵ��м�¼
        break;//������ѭ����ֹͣ����
      }
      
      
      
      Right_Line[i]=78;
      Right_Valid[i]=0;
      
      col=Right_Line[i+1]-6;
      Right_End=Right_Line[i+1]+6;
      
     // for(;col<Right_End;col++)
      for(uint8 n=40;n<78;n++)
      {
        if(Img[i][col]==white&&Img[i][col+2]==black)
        {
          Right_Line[i]=col;
           Right_flag=1;
          Right_Invalid_Count=0;
          if(Right_Line[i]>Right_Line[i+1])
          {
            Right_Turn_Count++;
            Right_Valid[i]=1;
            break;
          }
          else
          {
            Right_Turn_Count=0;
            Right_Valid[i]=1;
            break;
          }
        }
        else
          Right_Line[n]=79;
      }
      if(Right_Valid[i]==0)
        Right_Invalid_Count++;
      if(Right_Turn_Count==3)
      {
        //�����ж�ʮ��
      }
      if(Right_Invalid_Count==3)
      {
        Right_Break=i+3;
        break;
      }
      if(Right_flag&&Left_flag)
        Center_Line[i]=(Right_Line[i]+Left_Line[i])/2;
      else if(!Left_flag&&Right_flag)//��ת
        Center_Line[i]=Right_Line[i]-(Right_Line[i+1]-Center_Line[i+1]);
      else if(Left_flag&&!Right_flag)//��ת
        Center_Line[i]=Left_Line[i]+(Center_Line[i+1]-Left_Line[i+1]);
    }
    
  }
}
*/
            
            
            
 uint8 m_abs(int m)
 {
   if(m>0)
     return m;
   else 
     return (-m);
 }