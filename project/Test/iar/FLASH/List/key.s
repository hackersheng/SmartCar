///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.30.3.8024/W32 for ARM       12/Jul/2016  22:23:46
// Copyright 1999-2014 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  C:\Users\whstarlit\Desktop\Smart_Car\lib\LPLD\DEV\key.c
//    Command line =  
//        C:\Users\whstarlit\Desktop\Smart_Car\lib\LPLD\DEV\key.c -D LPLD_K60
//        -D USE_K60D10 -lCN
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\FLASH\List\ -lB
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\FLASH\List\ -o
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\FLASH\Obj\
//        --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_clustering --no_scheduling --debug --endian=little
//        --cpu=Cortex-M4 -e --fpu=None --dlib_config
//        D:\IAR\arm\INC\c\DLib_Config_Normal.h -I
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\..\app\ -I
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\..\..\..\lib\CPU\
//        -I
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\..\..\..\lib\common\
//        -I
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\..\..\..\lib\LPLD\
//        -I
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\..\..\..\lib\LPLD\HW\
//        -I
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\..\..\..\lib\LPLD\DEV\
//        -I
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\..\..\..\lib\LPLD\FUNC\
//        -I
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\..\..\..\lib\uCOS-II\Ports\
//        -I
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\..\..\..\lib\uCOS-II\Source\
//        -I
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\..\..\..\lib\FatFs\
//        -I
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\..\..\..\lib\FatFs\option\
//        -I
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\..\..\..\lib\USB\common\
//        -I
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\..\..\..\lib\USB\driver\
//        -I
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\..\..\..\lib\USB\descriptor\
//        -I
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\..\..\..\lib\USB\class\
//        -I C:\Users\whstarlit\Desktop\Smart_Car\lib\ -Ol -I
//        D:\IAR\arm\CMSIS\Include\ -D ARM_MATH_CM4
//    List file    =  
//        C:\Users\whstarlit\Desktop\Smart_Car\project\Test\iar\FLASH\List\key.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN LPLD_GPIO_Init
        EXTERN LPLD_GPIO_Input_b
        EXTERN LPLD_GPIO_Output_b
        EXTERN __aeabi_memcpy4

        PUBLIC InitGPIOKEY1
        PUBLIC InitGPIOKEY2
        PUBLIC InitGPIOkey_I
        PUBLIC InitGPIOkey_O
        PUBLIC Keyboard_init
        PUBLIC key_scan

// C:\Users\whstarlit\Desktop\Smart_Car\lib\LPLD\DEV\key.c
//    1 #include "key.h"
//    2 
//    3 
//    4 /*************************************************************************
//    5 *                           �θ�ѧԺ���ܳ���
//    6 *
//    7 *  �������ƣ�key_init
//    8 *  ����˵������ʼ��key�˿ڣ�������Ϊ�������Ϊ��������
//    9 *  ����˵������
//   10 *  �������أ���
//   11 *  �޸�ʱ�䣺2015-10-2   �Ѳ���
//   12 *  ��    ע��
//   13 *************************************************************************/
//   14 
//   15 
//   16 

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   17   GPIO_InitTypeDef InitGPIOKEY1; 
InitGPIOKEY1:
        DS8 20

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   18   GPIO_InitTypeDef InitGPIOKEY2;
InitGPIOKEY2:
        DS8 20
//   19 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   20 void Keyboard_init()                                               // KEY��ʼ�� ����
//   21 {
Keyboard_init:
        PUSH     {R7,LR}
//   22      InitGPIOkey_O();
        BL       InitGPIOkey_O
//   23      InitGPIOkey_I();
        BL       InitGPIOkey_I
//   24 } 
        POP      {R0,PC}          ;; return
//   25 
//   26 
//   27 /*************************************************************************
//   28 *                             �θ�ѧԺ���ܳ���
//   29 *
//   30 *  �������ƣ�key_scan
//   31 *  ����˵��:ɨ�谴�������
//   32 *  ����˵������
//   33 *  �������أ������µİ�����ֵ,��֧������ͬʱ����
//   34 *  �޸�ʱ�䣺2015-10-2   �Ѳ���
//   35 *  ��    ע��
//   36 *************************************************************************/

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   37 uint8 key_scan()
//   38 {
key_scan:
        PUSH     {R3-R5,LR}
//   39 
//   40     uint8 KeyValue =0;//Ĭ��û�а�������
        MOVS     R4,#+0
//   41     int i = 0;//��ʼɨ��Ķ˿�
        MOVS     R5,#+0
//   42 //    for(i=11;i<=13;i++)
//   43 //    {
//   44 //      LPLD_GPIO_Output_b(PTC, i, 1);//��������ߵ�ƽ
//   45 //      
//   46 //      if(LPLD_GPIO_Input_b(PTC, 14)==1)//��ʾ��һ���а�������
//   47 //      {
//   48 //        keyValue = 1+(i-11)*3;
//   49 //       while(LPLD_GPIO_Input_b(PTC, 14)==1);//�ȴ������ſ�
//   50 //      }
//   51 //      
//   52 //      else if(LPLD_GPIO_Input_b(PTC, 15)==1)//��ʾ�ڶ����а�������
//   53 //      {
//   54 //        keyValue = 2+(i-11)*3;
//   55 //        while(LPLD_GPIO_Input_b(PTC, 15)==1);//�ȴ������ſ�
//   56 //      }
//   57 //      
//   58 //      else if(LPLD_GPIO_Input_b(PTC, 16)==1)//��ʾ�������а�������
//   59 //      {
//   60 //        keyValue = 3+(i-11)*3;
//   61 //        while(LPLD_GPIO_Input_b(PTC, 16)==1);//�ȴ������ſ�
//   62 //      } 
//   63 //     LPLD_GPIO_Output_b(PTC, i, 0);//�ָ��͵�ƽ
//   64 //    }//����ɨ��
//   65     
//   66     for(i = 3;i <= 5;i++)
        MOVS     R5,#+3
        B.N      ??key_scan_0
//   67     {
//   68       LPLD_GPIO_Output_b(PTC, i, 1);//��������ߵ�ƽ
//   69       
//   70       if(LPLD_GPIO_Input_b(PTC, 6) == 1)//��ʾ��һ���а�������
//   71       {
//   72         KeyValue = 1 + (i - 3) * 3;
//   73         while(LPLD_GPIO_Input_b(PTC, 6) == 1);//�ȴ������ſ�
//   74       }
//   75       
//   76       else if(LPLD_GPIO_Input_b(PTC, 7) == 1)//��ʾ�ڶ����а�������
//   77       {
//   78         KeyValue = 2 + (i - 3) * 3;
//   79         while(LPLD_GPIO_Input_b(PTC, 7) == 1);//�ȴ������ſ�
//   80       }
//   81       
//   82       else if(LPLD_GPIO_Input_b(PTC, 8) == 1)//��ʾ�������а�������
??key_scan_1:
        MOVS     R1,#+8
        LDR.N    R0,??DataTable2  ;; 0x400ff080
        BL       LPLD_GPIO_Input_b
        CMP      R0,#+1
        BNE.N    ??key_scan_2
//   83       {
//   84         KeyValue = 3 + (i - 3) * 3;
        MOVS     R0,#+3
        MUL      R0,R0,R5
        SUBS     R4,R0,#+6
//   85         while(LPLD_GPIO_Input_b(PTC, 8) == 1);//�ȴ������ſ�
??key_scan_3:
        MOVS     R1,#+8
        LDR.N    R0,??DataTable2  ;; 0x400ff080
        BL       LPLD_GPIO_Input_b
        CMP      R0,#+1
        BEQ.N    ??key_scan_3
//   86       }
//   87       LPLD_GPIO_Output_b(PTC, i, 0);//�ָ��͵�ƽ
??key_scan_2:
        MOVS     R2,#+0
        MOVS     R1,R5
        LDR.N    R0,??DataTable2  ;; 0x400ff080
        BL       LPLD_GPIO_Output_b
        ADDS     R5,R5,#+1
??key_scan_0:
        CMP      R5,#+6
        BGE.N    ??key_scan_4
        MOVS     R2,#+1
        MOVS     R1,R5
        LDR.N    R0,??DataTable2  ;; 0x400ff080
        BL       LPLD_GPIO_Output_b
        MOVS     R1,#+6
        LDR.N    R0,??DataTable2  ;; 0x400ff080
        BL       LPLD_GPIO_Input_b
        CMP      R0,#+1
        BNE.N    ??key_scan_5
        MOVS     R0,#+3
        MUL      R0,R0,R5
        SUBS     R4,R0,#+8
??key_scan_6:
        MOVS     R1,#+6
        LDR.N    R0,??DataTable2  ;; 0x400ff080
        BL       LPLD_GPIO_Input_b
        CMP      R0,#+1
        BNE.N    ??key_scan_2
        B.N      ??key_scan_6
??key_scan_5:
        MOVS     R1,#+7
        LDR.N    R0,??DataTable2  ;; 0x400ff080
        BL       LPLD_GPIO_Input_b
        CMP      R0,#+1
        BNE.N    ??key_scan_1
        MOVS     R0,#+3
        MUL      R0,R0,R5
        SUBS     R4,R0,#+7
??key_scan_7:
        MOVS     R1,#+7
        LDR.N    R0,??DataTable2  ;; 0x400ff080
        BL       LPLD_GPIO_Input_b
        CMP      R0,#+1
        BNE.N    ??key_scan_2
        B.N      ??key_scan_7
//   88     }//����ɨ��
//   89     return KeyValue;
??key_scan_4:
        MOVS     R0,R4
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        POP      {R1,R4,R5,PC}    ;; return
//   90 }
//   91 
//   92 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   93 void InitGPIOkey_O()
//   94 {
InitGPIOkey_O:
        PUSH     {R7,LR}
//   95   /*���ýṹ���GPIO_PTx������ѡ��ʹ��PTD���PTE����
//   96    *���ýṹ���GPIO_Pins������ѡ��ʹ�ñ��ΪE0 -- E6������
//   97    *���ýṹ���GPIO_Dir����������PTD��������ŷ���Ϊ���
//   98    *���ýṹ���GPIO_Output����������PTD��������ų�ʼ�����Ϊ�ߵ�ƽ
//   99    *���ýṹ���GPIO_PinControl���������ö˿ڵĿ���ģʽΪ��ֹ�ж�
//  100    *����GPIO��ʼ���Ŀ⺯����������ʼ���ṹ������������У���ɳ�ʼ��*/
//  101 
//  102 //  InitGPIOKEY1.GPIO_PTx = PTC;
//  103 //  InitGPIOKEY1.GPIO_Pins = GPIO_Pin11 | GPIO_Pin12 | GPIO_Pin13;
//  104 //  InitGPIOKEY1.GPIO_Dir = DIR_OUTPUT;
//  105 //  InitGPIOKEY1.GPIO_Output = OUTPUT_L;
//  106 //  InitGPIOKEY1.GPIO_PinControl = IRQC_DIS;
//  107 //  LPLD_GPIO_Init(InitGPIOKEY1);
//  108   
//  109   
//  110   InitGPIOKEY1.GPIO_PTx = PTC;
        LDR.N    R0,??DataTable2  ;; 0x400ff080
        LDR.N    R1,??DataTable2_1
        STR      R0,[R1, #+0]
//  111   InitGPIOKEY1.GPIO_Pins = GPIO_Pin3 | GPIO_Pin4 | GPIO_Pin5;
        MOVS     R0,#+56
        LDR.N    R1,??DataTable2_1
        STR      R0,[R1, #+4]
//  112   InitGPIOKEY1.GPIO_Dir = DIR_OUTPUT;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable2_1
        STRB     R0,[R1, #+12]
//  113   InitGPIOKEY1.GPIO_Output = OUTPUT_L;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable2_1
        STRB     R0,[R1, #+13]
//  114   InitGPIOKEY1.GPIO_PinControl = IRQC_DIS;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable2_1
        STR      R0,[R1, #+8]
//  115   LPLD_GPIO_Init(InitGPIOKEY1);
        LDR.N    R1,??DataTable2_1
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//  116 }
        POP      {R0,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  117 void InitGPIOkey_I()
//  118 {
InitGPIOkey_I:
        PUSH     {R7,LR}
//  119   /*���ýṹ���GPIO_PTx������ѡ��ʹ��PTD���PTE����
//  120    *���ýṹ���GPIO_Pins������ѡ��ʹ�ñ��ΪE0 -- E6������
//  121    *���ýṹ���GPIO_Dir����������PTD��������ŷ���Ϊ����
//  122    *���ýṹ���GPIO_PinControl���������ö˿ڵĿ���ģʽΪ��ֹ�ж�
//  123    *����GPIO��ʼ���Ŀ⺯����������ʼ���ṹ������������У���ɳ�ʼ��*/
//  124 //  InitGPIOKEY2.GPIO_PTx = PTC;
//  125 //  InitGPIOKEY2.GPIO_Pins =GPIO_Pin14 | GPIO_Pin15 | GPIO_Pin16;
//  126 //  InitGPIOKEY2.GPIO_Dir = DIR_INPUT;
//  127 //  InitGPIOKEY2.GPIO_PinControl = INPUT_PULL_DOWN;
//  128 //  LPLD_GPIO_Init(InitGPIOKEY2);
//  129   
//  130   InitGPIOKEY2.GPIO_PTx = PTC;
        LDR.N    R0,??DataTable2  ;; 0x400ff080
        LDR.N    R1,??DataTable2_2
        STR      R0,[R1, #+0]
//  131   InitGPIOKEY2.GPIO_Pins =GPIO_Pin6 | GPIO_Pin7 | GPIO_Pin8;
        MOV      R0,#+448
        LDR.N    R1,??DataTable2_2
        STR      R0,[R1, #+4]
//  132   
//  133   InitGPIOKEY2.GPIO_Dir = DIR_INPUT;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable2_2
        STRB     R0,[R1, #+12]
//  134   InitGPIOKEY2.GPIO_PinControl = INPUT_PULL_DOWN;
        MOVS     R0,#+2
        LDR.N    R1,??DataTable2_2
        STR      R0,[R1, #+8]
//  135   LPLD_GPIO_Init(InitGPIOKEY2);
        LDR.N    R1,??DataTable2_2
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//  136 }
        POP      {R0,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2:
        DC32     0x400ff080

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_1:
        DC32     InitGPIOKEY1

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_2:
        DC32     InitGPIOKEY2

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
//  137 
// 
//  40 bytes in section .bss
// 268 bytes in section .text
// 
// 268 bytes of CODE memory
//  40 bytes of DATA memory
//
//Errors: none
//Warnings: none
