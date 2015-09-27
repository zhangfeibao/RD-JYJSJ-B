#include "def.h"
#include "STM8S103F3P.h"
#include "eeprom.h"

/*
* �������ܣ����ڲ�EE���ȡһ���ֽ�
* �����������
* �����������
* ����ֵ����
*/
uint8 ReadEeprom(uint8 radd)
{
    uint8 rm1;
    uint8 *prom;
    prom=(uint8 *)(0x4001+radd);
    rm1=*prom;
    return rm1;
}

void delay(uint16 i)
{
    uint16 m,n;
    for(n=0;n<i;n++)
    {
        for(m=0;m<10;m++)
        {

        PA_ODR ^= BIT3;//PA_ODR &= ~BIT3;
        }

    }
}

/*
* �������ܣ�д��һ���ֽڵ��ڲ�EE
* �����������
* �����������
* ����ֵ����
*/
void WriteEeprom(uint8 wadd,uint8 wdata)
{
    uint8 *prom;
    uint8 wr1,wr2,wr3;

//  _asm("sim");
//  FLASH_CR2 |= BIT4;  //���ٿ���ʹ��
    prom=(uint8 *)(0x4001+wadd);
    if((FLASH_IAPSR&0x08)==0x00)
    {
        FLASH_DUKR=0xae;
        FLASH_DUKR=0x56;
    }
//  FLASH_CR2 |= BIT4;  //���ٿ���ʹ��
//  FLASH_NCR2 |= BIT4; //���ٿ���ʹ��
//  while((FLASH_IAPSR&0x08)==0x00)
    {
        ;
    }


    *prom=wdata;
//  while((FLASH_IAPSR&0x04)==0x00)
    {
        ;
    }

    DisplayDrive();

    FLASH_IAPSR&=~0x08;
//  _asm("rim");
}

/*
* �������ܣ��ֲ�д��һ���ֽڵ��ڲ�EE
* �����������
* �����������
* ����ֵ��0��ʾ��ǰEE����û��д�꣬1��ʾ��ǰEE�Ѿ�д���ˡ�
*/
uint8 WriteEepromStep(uint8 wadd,uint8 wdata)
{
    uint8 *prom,res;
    uint8 wr1,wr2,wr3;

    res = 0;
    prom=(uint8 *)(0x4033+wadd);
    if(WriteEEStep == 0)
    {   //��һ����װ���ַ���ݡ�
        if((FLASH_IAPSR&0x08)==0x00)
        {
            FLASH_DUKR=0xae;
            FLASH_DUKR=0x56;
        }
        WriteEEStep ++;
    }
    else if(WriteEEStep == 1)
    {   //�ڶ������ж�д���������û��д�꣬���ûд�꣬�������ߣ�д���ˣ������ߡ�
        if((FLASH_IAPSR&0x08)!=0x00)
        {
            WriteEEStep ++;
        }
    }
    else if(WriteEEStep == 2)
    {   //��������װ���д����
        PA_ODR |= BIT3;
        *prom=wdata;
        PA_ODR &= ~BIT3;
        WriteEEStep ++;
    }
    else if(WriteEEStep == 3)
    {   //�ж�������û��д��:
        if((FLASH_IAPSR&0x04)!=0x00)
        {
            WriteEEStep ++;
            FLASH_IAPSR&=~0x08;
            res = 1;
        }
    }
    else
    {
        res = 1;
    }
    return res;
}

/*
* �������ܣ���ȡ��о��������
* �����������
* �����������
* ����ֵ����
*/
void ReadFilterData(void)
{
    uint8 i;
    uint16 data1,data2;
    for(i=0;i<LIFE_DATA_AMOUNT;i++)
    {
        data1 = ReadEeprom(C_EEPROM_ADDR+i*2);
        data2 = ReadEeprom(C_EEPROM_ADDR+i*2+1);
        data1 += data2<<8;
        life[i] = data1;
    }

    if(PP1filterTime >= C_PP1filter_life)
    {
        PP1filterTime = C_PP1filter_life;
        f_PP1_life_over = 1;
    }

    if(C1filterTime >= C_C1filter_life)
    {
        C1filterTime = C_C1filter_life;
        f_C1_life_over = 1;
    }

    if(PP2filterTime >= C_PP2filter_life)
    {
        PP2filterTime = C_PP2filter_life;
        f_PP2_life_over = 1;
    }

    if(ROfilterTime >= C_ROfilter_life)
    {
        ROfilterTime = C_ROfilter_life;
        f_RO_life_over = 1;
    }

    if(CUFfilterTime >= C_CUFfilter_life)
    {
        CUFfilterTime = C_CUFfilter_life;
        f_CUF_life_over = 1;
    }
}

/*
* �������ܣ�д����о��������
* �����������
* �����������
* ����ֵ����
*/
void WriteFilterData(void)
{
    uint8 i,data;
    for(i=0;i<LIFE_DATA_AMOUNT;i++)
    {
        data = life[i]&0xff;
        WriteEeprom(C_EEPROM_ADDR+i*2,data);
        data = (life[i]>>8)&0xff;
        WriteEeprom(C_EEPROM_ADDR+i*2+1,data);
    }
}

/*
* �������ܣ�������Ҫд���ڲ�EE�����ݡ�
* �����������
* �����������
* ����ֵ����
*/
void SetWriteData(void)
{
    uint8 i;
    if(f_need_write)
    {
        return;
    }
    for(i=0;i<LIFE_DATA_AMOUNT;i++)
    {
        WriteToEEData[i*2] = life[i]&0xff;
        WriteToEEData[i*2+1] = (life[i]>>8)&0xff;
    }
    WriteCurAddr = 0;
    WriteFlashDelay = C_FLASH_DELAY;//50;       //дflash֮ǰ��ʱ100ms
    f_need_write = 1;
    DisTime = C_DIS_Write;
}


