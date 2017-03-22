#ifndef _LQ12864_H_
#define _LQ12864_H_

#define byte unsigned char  //�Լ��ӵ�   �ǵó�ȥ����
#define word unsigned int   //�Լ��ӵ�

/*
4��SPIʹ��˵����
VBT ���ڲ�DC-DC��ѹ��3.3~4.3V�����ʹ��5V��ѹ��Ϊ���������һ��100~500ŷ�ĵ���
VCC ���ڲ��߼���ѹ 1.8~6V   
GND ��

BS0 �͵�ƽ
BS1 �͵�ƽ
BS2 �͵�ƽ

CS  Ƭѡ�ܽ�
DC  ��������ѡ��ܽ�
RES ģ�鸴λ�ܽ� 
D0��SCLK�� ��ʱ�ӽţ���MCU����
D1��MOSI�� ����������������ݽţ���MCU����

D2 ����      
D3-D7 �� �͵�ƽ �� Ҳ�����գ��������Ϊ�͵�ƽ
RD  �͵�ƽ ��Ҳ�����գ��������Ϊ�͵�ƽ
RW  �͵�ƽ ��Ҳ�����գ��������Ϊ�͵�ƽ
RD  �͵�ƽ ��Ҳ�����գ��������Ϊ�͵�ƽ   
*/
#define LCD_SCL PTA14_O  /*D0*///K60�Ĺܽ����� PTE3�����
#define LCD_SDA	PTA16_O  /*D1*/
#define LCD_RST PTB21_O  /*RST*/ 
#define LCD_DC  PTB20_O  /*DC*/ 

#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel		((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		  64
#define	Brightness	0xCF 

#define Dot_Size 3                  // С�������λ

#define X_WIDTH 128
#define Y_WIDTH 64

extern byte LIBLOGO60x58[480];

extern unsigned char str1[6];
extern unsigned char str2[6];
extern unsigned char str3[8];

extern unsigned char str4[6];
extern unsigned char str5[6];
extern unsigned char str6[8];

void init_gpio_OLED();
int Dly_ms(int ms);
void LCD_WrDat(byte data);     //д����
void LCD_WrCmd(byte cmd);     //д����
void LCD_Set_Pos(byte x, byte y);     //������ʼλ��
void LCD_Fill(byte dat);     //�����ĻΪ�ڻ��
void LCD_CLS(void);     //����

void LCD_Init(void);     //��ʼ��
void LCD_Fill(byte bmp_data);     //���������Ļ�׻��
void LCD_PutPixel(byte x,byte y);     //����һ����
void LCD_Rectangle(byte x1,byte y1,byte x2,byte y2,byte gif);     //����һ������
void LCD_P6x8Str(byte x,byte y,byte ch[]);       //��ʾ�����С6x8������
void LCD_P6x8Str2(byte x,byte y,byte ch[]);      //��ʾ�����С6x8������ ǰ����������
void LCD_P8x16Str(byte x,byte y,byte ch[]);      //��ʾ�����С8x16������
void LCD_P8x16Str2(byte x,byte y,byte ch[]);     //��ʾ�����С8x16������
void LCD_P14x16Str(byte x,byte y,byte ch[]);     //��ʾ�����С14x16������
void LCD_P14x16Str2(byte x,byte y,byte ch[]);    //��ʾ�����С14x16������ ��ת����
void LCD_Print(byte x, byte y, byte ch[]);
void Draw_BMP(byte x0,byte y0,byte x1,byte y1,byte bmp[]);      //����BMPͼ��
void Draw_LQLogo(void);     //�����LOGO
void Draw_LibLogo(void);     //lib��LOGO
void LED_PrintImage(unsigned char *pucTable,unsigned short usRowNum, unsigned short usColumnNum);     //����ͼ��
void LED_PrintImag2(unsigned char *pucTable,unsigned short usRowNum, unsigned short usColumnNum);       //�Ƿ���
void floatToInt(float fl,byte n,byte s);     //����ת����
void floatToInt2(float fl,byte n,byte s);     //����ת����2

void Paint_Angle(float Angle);     //ˢ�½Ƕȣ������߷�ʽ����
void LCD_Fill_Line(byte line,byte bmp_data);  //�Լ�  ���һ��Ϊ�ڻ��
void LCD_PaintTSL1401_Line(byte data[],float avange);    //������
void LCD_PaintTSL1401_Bulk(byte y1,byte y2,byte data[]);     //��״��
extern void LCD_Write_Float(unsigned char x,unsigned char y,float Number);    //������ ע�����ͬ���ļ������
void LCD_Write_Float_Dot(unsigned char x,unsigned char y,float Number,int dotNumber);     //��������ʾ������С����λ��
void LCD_Write_Float_Dot_Chinese(unsigned char x,unsigned char y,float Number,int dotNumber);     //��������ʾ������С����λ��

#endif

