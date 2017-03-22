#include "include.h"

GPIO_InitTypeDef pta_IIC;

void LPLD_IIC_Init(void)
{
  /********�û����޸�ֵ ��ʼ***********/
  pta_IIC.GPIO_PTx = PTA;
  pta_IIC.GPIO_Pins = GPIO_Pin12 | GPIO_Pin13;
  /********�û����޸�ֵ ����***********/
  pta_IIC.GPIO_Dir = DIR_OUTPUT;
  pta_IIC.GPIO_Output = OUTPUT_H;
  pta_IIC.GPIO_PinControl = NULL;
  LPLD_GPIO_Init(pta_IIC);
}


/**************************************
��ʱ5΢��(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺�����ע��ʱ�ӹ���ʱ��Ҫ�޸�
������1T��MCUʱ,���������ʱ����
**************************************/
//void Delay5us()
//{
//   for(int i =0;i<1;i++)
//       for(int j = 0;j < 25;j++)
//     {;}
//}

void Delay5us()
{
  for(int i =0;i<1;i++)
    for(int j = 0;j < 15;j++)
    {;}
}

/**************************************
��ʼ�ź�
**************************************/
void IIC_Start(void)

{
        SCL_Out;
        SDA_Out;                        //���
        //dwt_delay_us(1000);
	SDA=1;
        //dwt_delay_us(1000);
        SCL=1;
	Delay5us();
	SDA=0;
	Delay5us();
	SCL=0;
	//Delay5us();
	//SCL=0;
        //dwt_delay_us(2000);
}

/**************************************
ֹͣ�ź�
**************************************/
void IIC_Stop(void)
//��ֹͣλ SDA=0->1
{
	SDA_Out;
	SCL_Out;
	//dwt_delay_us(1000);
	SDA=0; //���ͽ��������������ź�
	//dwt_delay_us(1000);
	SCL=1; //���ͽ���������ʱ���ź�
	Delay5us();
	SDA=1; //����I2C���߽����ź�
	Delay5us();      
        SCL=0;//***
  
  
  /*SDA_Out;                        //���
	SCL=0;
	Delay5us();
	SDA=0;
	Delay5us();
	SCL=1;
	Delay5us();
	SDA=1;
	Delay5us();
	SCL=0;*/
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void L3G4200D_SendACK(BYTE a)
{    
    SDA_Out;
	SCL_Out;
	//dwt_delay_us(1000);
	if(a==0) SDA=0; //�ڴ˷���Ӧ����Ӧ���ź�
	else SDA=1;
	Delay5us();
	SCL=1;
	Delay5us();
	SCL=0; //��ʱ���ߣ�ǯסI2C�����Ա��������
	//dwt_delay_us(2000);
  
  
  
  
  /*if(ack_main)GY_SDA=0;
    else GY_SDA = 1;             //дӦ���ź�
    Delay5us();                

    GY_SCL = 1;                    //����ʱ����
    Delay5us();               //��ʱ
    GY_SCL = 0;       //����ʱ����   */              
}

/**************************************
����Ӧ���ź�
**************************************/
/*uchar L3G4200D_RecvACK()
{
    GY_SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    GY_CY = SDA;                   //��Ӧ���ź�
    GY_SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ

    return CY;
}
*/
/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
unsigned char Send_Byte(unsigned char c)
//�ֽڷ��ͳ���
{
	
	unsigned char BitCnt;
        //unsigned char a;
	SCL_Out;
	SDA_Out;	
//	asm("nop");


	for(BitCnt=0;BitCnt<8;BitCnt++) //Ҫ���͵����ݳ���Ϊ8λ
	{
		SCL=0;
		if(c&0x80) SDA=1; //�жϷ���λ
		else SDA=0;
		c<<=1;
		Delay5us();
		SCL=1; //��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ
		Delay5us();
		SCL=0;
	}
	Delay5us();
	SDA=1; //8λ��������ͷ������ߣ�׼������Ӧ��λ
	Delay5us();
	SCL=1;
	//SDA_In;
	Delay5us();
	/*if(SDA_Read==1) a=ack;
	else a=no_ack; //�ж��Ƿ���յ�Ӧ���ź�*/
	SCL=0;
	return ack;
  
  /*unsigned char i; 
	SDA_Out;
	for(i=0;i<8;i++)
	{
		SCL=0;
		if((SendChar<<i)&0x80)
		  SDA=1;                        //�жϷ���λ
		else 
		  SDA=0;
		Delay5us();
		SCL=1;
		Delay5us();
		SCL=0;
	}
	Delay5us();
	SDA=1;                            //������8bit���ͷ�����׼������Ӧ��λ
	Delay5us();
	SCL=1;
	Delay5us();
	SCL=0; */
}
/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
unsigned char Read_Byte(void)
//�ֽڽ��ճ���
{
  unsigned char retc;
	unsigned char BitCnt;
	retc=0;
	SDA_Out;
	Delay5us();
	SDA=1; //��������Ϊ���뷽ʽ
	SDA_In;
	Delay5us();
	for(BitCnt=0;BitCnt<8;BitCnt++)
	{
		//dwt_delay_us(1000);
		SCL=0; //��ʱ����Ϊ�ͣ�׼����������λ
		Delay5us();
		SCL=1; //��ʱ����Ϊ��ʹ��������������Ч
		Delay5us();
		
		retc=retc<<1;
		if(SDA_Read==1) retc=retc+1; //������λ,���յ�����λ����retc��
		Delay5us();
		
	}
	SCL=0;
	Delay5us();
	return(retc);
  
  
  /*unsigned char i;
  unsigned char ReadChar;
	ReadChar=0;
	SCL=0;
	Delay5us();
	SDA_Out;
	SDA=1;                            //��������Ϊ���뷽ʽ
	SDA_In;                       
	for(i=0;i<8;i++)
	{
		Delay5us();
		SCL=0;                          //��ʱ����Ϊ�ͣ�׼����������λ
		Delay5us();
		SCL=1;                          //��ʱ����Ϊ�ߣ�ʹ��������������Ч
		Delay5us();
		ReadChar<<=1;
		if(SDA_Read)
		ReadChar+=1;                    //������λ�������յ����ݴ�c
	}
	SDA_Out;
	SCL=0;
	return ReadChar;*/
}
//���ֽ�д��*******************************************

void GY_WriteByte(unsigned char Address, unsigned char Thedata)
//д��
{
	IIC_Start();		                  //����
	Send_Byte(SlaveAddress);	                //д���豸ID��д�ź�
	Send_Byte(Address);	              //X��ַ
	Send_Byte(Thedata);	              //д���豸ID������
	IIC_Stop();
}

//���ֽڶ�ȡ*****************************************
unsigned char GY_ReadByte(unsigned char Address)

{
       unsigned char Ret;
	IIC_Start();		                  //����
	Send_Byte(SlaveAddress);	                //д���豸ID��д�ź�
	Send_Byte(Address);	              //X��ַ
	IIC_Start();		                  //���·��Ϳ�ʼ
	Send_Byte(SlaveAddress+1);	                //д���豸ID������
	Ret=Read_Byte();	                //��ȡһ�ֽ�
	IIC_Stop();
	return Ret;
}

