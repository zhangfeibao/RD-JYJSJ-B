/* MAIN.C file
 *
 * Copyright (c) 2002-2005 STMicroelectronics
 */
//#include "STM8S103F3P.h"
#include "STM8S003F3.h"
#include "def.h"
#include "main.h"


main()
{
    uint8 i;
    //ʱ��ѡ��:
//  CLK_ECKR = 0x01;                //ѡ���ⲿʱ��Դ
//  while((CLK_ECKR&BIT1) == 0);    //�ȴ��ⲿʱ��Դ����
//  CLK_CMSR = 0xb4;                //���ⲿʱ��Դ����Ϊ��ʱ��Դ��
//  CLK_SWR = 0xb4;

//  CLK_CSSR = 0x01;                //ʱ�Ӱ�ȫϵͳ��
//  CLK_ICKR = 0;                   //�ر��ڲ�RC

//  CLK_CMSR = 0xb4;                //���ⲿʱ��Դ����Ϊ��ʱ��Դ��
//  CLK_SWR = 0xb4;
//  CLK_SWCR |= BIT1;               //ʹ��ʱ�ӵ��л���

//  CLK_ICKR = 0;                   //�ر��ڲ�RC

    CLK_CKDIVR = 0x00;      // fmaster=fcpu=16M
    delayus(250);
//  CLK_PCKENR1 = 0x38;
//  CLK_PCKENR2 = 0x08;     // adc
    CFG_GCR |= 0x01;        // disable swim

    //�˿ڳ�ʼ��:
    //PA3 --> BUZ, ������
    PA_ODR = 0x00;
    PA_DDR = 0x08;          // 0000 1000
    PA_CR1 = 0x0f;          //
    PA_CR2 = 0x00;          //�����������
    PA_ODR = 0x00;

    //PB0~PB3 ��, PB4->K2, PB5->K1, PB6,PB7��
    PB_DDR=0x00;            //
    PB_CR1=0x30;            //
    PB_CR2=0x00;            //��������

    //PC0~PC2->��, PC3->ZY/JS, PC4->��, PC5->SEG6, PC6->SEG7
    PC_ODR = 0x00;
    PC_DDR = 0xE8;          // 0000 0100
    PC_CR1 = 0xEf;          //
    PC_CR2 = 0x00;          //�����������

    //PD0->��, PD1->SWIM(������), PD2->ST_CP, PD3->SH_CP, PD4->SEG2, PD5->SEG1, PD6->CX_OUT
    PD_ODR = 0x00;
    PD_DDR = 0x7e;          // 0000 0100
    PD_CR1 = 0x7e;          //
    PD_CR2 = 0x00;          //�����������

//  FLASH_NCR2 &= ~BIT4;    //���ٿ���ʹ��
//  FLASH_CR1 &= ~BIT1; //���ٿ���ʹ��
//  FLASH_CR1 |= BIT0;  //���ٿ���ʹ��

//  FLASH_CR1 |= BIT4+BIT6; //���ٿ���ʹ��
    //��ȡ�洢��EEPROM����о��������:
//  FLASH_CR2 |= BIT4;  //���ٿ���ʹ��
    FLASH_CR2 |= BIT7;  //���ٿ���ʹ��
    FLASH_NCR2 &= ~BIT7;    //���ٿ���ʹ��
//  FLASH_NCR2 |= BIT4; //���ٿ���ʹ��
//  FLASH_NCR2 &= ~BIT0;    //���ٿ���ʹ��

    CLK_PCKENR1 = 0;
    CLK_PCKENR2 = 0;

//  FLASH_CR2 |= BIT6;
//  FLASH_NCR2 &= ~BIT6;

    FLASH_CR1 &= ~ BIT1;
    TIM4_Init();
    _asm("rim");
//  BeepSet(1,50,0);
    BeepSet(1,20,0);
    ReadFilterData();
    WriteEEStep = C_WriteEEStepOver;
    DisTime = C_DIS_NOR;

//  for(i=0;i<COM_AMOUNT;i++)
//  {
//      displayBuff[i] = 0xff;
//  }

    DisplayDrive();
    CxTime = 1500;      //�ϵ��ϴ30S
    f_stand_on = 0;
    f_cx_auto = 1;
    while (1)
    {
        if (f_DisDrive)
        {
            f_DisDrive = 0;
            DisplayDrive();

            if(++JustForTest >= 25)
            {
                JustForTest = 25;
            }

            if(f_need_write&&(JustForTest>=25)&&(!WriteFlashDelay))
            {
                JustForTest = 0;
                WriteEeprom(WriteCurAddr,WriteToEEData[WriteCurAddr]);
                WriteCurAddr ++;
                if(WriteCurAddr >= LIFE_DATA_AMOUNT*2)
                {
                    WriteCurAddr = 0;
                    f_need_write = 0;
                    WriteFlashDelay = C_FLASH_DELAY;
                }
            }
        }
        else if(f_10ms)
        {

            f_10ms = 0;
            KeyScan();
            BeepDeal();
            ReadSwKey();
            Key();
        }
        else if(f_20ms)
        {
            f_20ms = 0;
            Display();
            BeepDeal();
            OutputDeal();
        }
        else
        {
            if(Timer2msCount >= 16)
            {
                Timer2msCount -= 16;

                TimeCenter();
            }
        }
    }
}

