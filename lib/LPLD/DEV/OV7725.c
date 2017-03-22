#include "include.h"

volatile IMG_STATUS_e      ov7725_eagle_img_flag = IMG_FINISH;   //ͼ��״̬

GPIO_InitTypeDef IO_init_struct;
GPIO_InitTypeDef VSY_init_struct;
GPIO_InitTypeDef PCLK_init_struct;
DMA_InitTypeDef DMA_init_struct;


//���жϺ���
void VSY_isr()
{ 
  uint8  n = 0;    //���ź�
  uint32 flag = (PORTC->ISFR);
  LPLD_GPIO_ClearIntFlag(PORTC);                  //���жϱ�־λ
  n = 17;
  //���ж�
  if(flag & (1 << n))  
  {
    //���ж���Ҫ�ж��ǳ��������ǳ���ʼ
    if(ov7725_eagle_img_flag == IMG_START)        //��Ҫ��ʼ�ɼ�ͼ��
    {
      ov7725_eagle_img_flag = IMG_GATHER;         //���ͼ��ɼ���
      disable_irq(PORTC_IRQn);
      
      PORTC->ISFR = 1 << 17;                      //���PCLK��־λ              
      LPLD_DMA_LoadDstAddr(DMA_CH0, Pix_Data);    //�ָ���ַ
      LPLD_DMA_EnableReq(DMA_CH0);                //ʹ��ͨ��CHn Ӳ������
      LPLD_DMA_EnableIrq(DMA_init_struct);        //��DMA�����ж�
    }
    else                                         //ͼ��ɼ�����
    {
      disable_irq(PORTC_IRQn);                    //�ر�PTA���ж�
      ov7725_eagle_img_flag = IMG_FAIL;           //���ͼ��ɼ�ʧ��
    }
  }
}


//DMA�����жϺ���
void DMA_isr()
{
  disable_irq(PORTC_IRQn);
  
  ov7725_eagle_img_flag = IMG_FINISH ;
  DMA0->INT |= 0x1u<<0;
  img_extract(*Img,(unsigned char*)Pix_Data,600);  //4800---320 * 240, 600 ---80 * 60
  
  enable_irq(PORTC_IRQn); 
  
  /*-----����Ϊִ�г���-----*/
  
  cameraScan();
  handleImg();          //����ͼ��
  directionControl();   //�������
  paint();

  /*-----����Ϊִ�г���-----*/
  //LPLD_GPIO_Toggle_b(PTC, 8);  //��ʱ��
}


//�ɼ�����
void get_img()
{
  ov7725_eagle_img_flag = IMG_START;               //��ʼ�ɼ�ͼ��
  LPLD_GPIO_ClearIntFlag(PORTC);                   //д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
  enable_irq(PORTC_IRQn);                          //����PTC���ж�
  while(ov7725_eagle_img_flag != IMG_FINISH)      //�ȴ�ͼ��ɼ����
  {
    if(ov7725_eagle_img_flag == IMG_FAIL)         //����ͼ��ɼ����������¿�ʼ�ɼ�
    {
      ov7725_eagle_img_flag = IMG_START;          //��ʼ�ɼ�ͼ��
      LPLD_GPIO_ClearIntFlag(PORTC);              //д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
      enable_irq(PORTC_IRQn);                     //����PTA���ж�
    }
  }
}


void IO_init()
{
  //OV���ݿڳ�ʼ����PTD0~PTD7
  IO_init_struct.GPIO_PTx = PTD;
  IO_init_struct.GPIO_Dir = DIR_INPUT;
  IO_init_struct.GPIO_Pins = GPIO_Pin0_7;
  IO_init_struct.GPIO_PinControl = IRQC_DIS | INPUT_PULL_DIS;
  LPLD_GPIO_Init(IO_init_struct);
  
//  IO_init_struct.GPIO_PTx = PTC;
//  IO_init_struct.GPIO_Dir = DIR_OUTPUT;
//  IO_init_struct.GPIO_Pins = GPIO_Pin8;
//  LPLD_GPIO_Init(IO_init_struct);
  
}

void VSY_init()
{
  VSY_init_struct.GPIO_PTx = PTC;
  VSY_init_struct.GPIO_Dir = DIR_INPUT;
  VSY_init_struct.GPIO_Pins = GPIO_Pin18;
  VSY_init_struct.GPIO_PinControl = IRQC_RI|INPUT_PULL_UP|INPUT_PF_EN;
  VSY_init_struct.GPIO_Isr = VSY_isr;
  LPLD_GPIO_Init(VSY_init_struct); 
}

void PCLK_init()
{
  PCLK_init_struct.GPIO_PTx = PTC;
  PCLK_init_struct.GPIO_Pins = GPIO_Pin17;
  PCLK_init_struct.GPIO_Dir = DIR_INPUT;
  PCLK_init_struct.GPIO_PinControl = IRQC_DMAFA | INPUT_PULL_UP;
  LPLD_GPIO_Init(PCLK_init_struct); 
}

void DMA_init()
{
  //DMA��������
  DMA_init_struct.DMA_CHx = DMA_CH0;        //CH0ͨ��
  DMA_init_struct.DMA_Req = PORTC_DMAREQ;   //PORTCΪ����Դ
  DMA_init_struct.DMA_MajorLoopCnt = 600;   //��ѭ������ֵ���ɼ���
  DMA_init_struct.DMA_MinorByteCnt = 1;     //��ѭ���ֽڼ�����ÿ�ζ���1�ֽ�
  DMA_init_struct.DMA_SourceAddr = (uint32_t)&PTD->PDIR;//Դ��ַ��PTD0~7
  DMA_init_struct.DMA_DestAddr = (uint32)Pix_Data;      //Ŀ�ĵ�ַ�����ͼ�������
  DMA_init_struct.DMA_DestAddrOffset = 1;   //Ŀ�ĵ�ַƫ�ƣ�ÿ�ζ�������1
  DMA_init_struct.DMA_MajorCompleteIntEnable = TRUE;
  DMA_init_struct.DMA_Isr = DMA_isr;
  DMA_init_struct.DMA_AutoDisableReq = TRUE;//�Զ���������
  //��ʼ��DMA
  LPLD_DMA_Init(DMA_init_struct);
}

//ov7725��ʼ������
void ov7725_init(void)
{
  SCCB_GPIO_init();
  delay(10);
  SCCB_WriteByte(OV7725_COM7,0x80);//��λ
  delay(10);
  SCCB_WriteByte(OV7725_COM4,0x81); //150֡:0xC1,112֡:0x81,75֡:0x41,50֡:0xC1
  SCCB_WriteByte(OV7725_CLKRC,0x00);//150֡:0x00,112֡:0x00,75֡:0x00,50֡:0x02
  SCCB_WriteByte(OV7725_COM2,0x03);
  SCCB_WriteByte(OV7725_COM3,0xD0);//50
  SCCB_WriteByte(OV7725_COM7,0x40);
  SCCB_WriteByte(OV7725_HSTART,0x3F);
  SCCB_WriteByte(OV7725_HSIZE,0x50);
  SCCB_WriteByte(OV7725_VSTRT,0x03);
  SCCB_WriteByte(OV7725_VSIZE,0x78);
  SCCB_WriteByte(OV7725_HREF,0x00);
  SCCB_WriteByte(OV7725_SCAL0,0x0A);
  SCCB_WriteByte(OV7725_AWB_Ctrl0,0xE0);
  SCCB_WriteByte(OV7725_DSPAuto,0xff);
  SCCB_WriteByte(OV7725_DSP_Ctrl2,0x0C);
  SCCB_WriteByte(OV7725_DSP_Ctrl3,0x00);
  SCCB_WriteByte(OV7725_DSP_Ctrl4,0x00);
  SCCB_WriteByte(OV7725_HOutSize,0x14);//80-14, 160-28, 240-3c, 320-50---��
  SCCB_WriteByte(OV7725_VOutSize,0x1e);//60-1e, 120-3c, 180-5a, 240-78---��
  SCCB_WriteByte(OV7725_EXHCH,0x00);
  SCCB_WriteByte(OV7725_GAM1,0x0c);
  SCCB_WriteByte(OV7725_GAM2,0x16);
  SCCB_WriteByte(OV7725_GAM3,0x2a);
  SCCB_WriteByte(OV7725_GAM4,0x4e);
  SCCB_WriteByte(OV7725_GAM5,0x61);
  SCCB_WriteByte(OV7725_GAM6,0x6f);
  SCCB_WriteByte(OV7725_GAM7,0x7b);
  SCCB_WriteByte(OV7725_GAM8,0x86);
  SCCB_WriteByte(OV7725_GAM9,0x8e);
  SCCB_WriteByte(OV7725_GAM10,0x97);
  SCCB_WriteByte(OV7725_GAM11,0xa4);
  SCCB_WriteByte(OV7725_GAM12,0xaf);
  SCCB_WriteByte(OV7725_GAM13,0xc5);
  SCCB_WriteByte(OV7725_GAM14,0xd7);
  SCCB_WriteByte(OV7725_GAM15,0xe8);
  SCCB_WriteByte(OV7725_SLOP,0x20);
  SCCB_WriteByte(OV7725_LC_RADI,0x00);
  SCCB_WriteByte(OV7725_LC_COEF,0x13);
  SCCB_WriteByte(OV7725_LC_XC,0x08);
  SCCB_WriteByte(OV7725_LC_COEFB,0x14);
  SCCB_WriteByte(OV7725_LC_COEFR,0x17);
  SCCB_WriteByte(OV7725_LC_CTR,0x05);
  SCCB_WriteByte(OV7725_BDBase,0x99);
  SCCB_WriteByte(OV7725_BDMStep,0x03);
  SCCB_WriteByte(OV7725_SDE,0x04);
  SCCB_WriteByte(OV7725_BRIGHT,0x8a); //����ֵ����
  SCCB_WriteByte(OV7725_CNST,0xA0);//��ֵ����(0~255)//0xA0
  SCCB_WriteByte(OV7725_SIGN,0x0E);//0x06  BRIGHTΪ��       0x0E    BRIGHTΪ��
  SCCB_WriteByte(OV7725_UVADJ0,0x11);
  SCCB_WriteByte(OV7725_UVADJ1,0x02);
}


/*!
 *  @brief      ��ֵ��ͼ���ѹ���ռ� �� ʱ�� ��ѹ��
 *  @param      dst             ͼ���ѹĿ�ĵ�ַ
 *  @param      src             ͼ���ѹԴ��ַ
 *  @param      srclen          ��ֵ��ͼ���ռ�ÿռ��С
 *  @since      v5.0            img_extract(img, imgbuff,CAMERA_SIZE);
 *  Sample usage:
 */
void img_extract(uint8 *dst, uint8 *src, uint32 srclen)
{
    uint8 colour[2] = {255, 0}; //0 �� 1 �ֱ��Ӧ����ɫ
    //ע�� 0 ��ʾ ��ɫ��1��ʾ ��ɫ
    uint8 tmpsrc;
    while(srclen --)
    {
        tmpsrc = *src++;
        *dst++ = colour[ (tmpsrc >> 7 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 6 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 5 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 4 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 3 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 2 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 1 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 0 ) & 0x01 ];
    }
}

/*
 * ��ʱһ��ʱ��
 */
void delay(uint8 t)
{
  uint16 i, n;
  for(i=0;i<20000;i++)
  {
    for(n=0;n<t;n++)
    {
      asm("nop");
    }
  }
}