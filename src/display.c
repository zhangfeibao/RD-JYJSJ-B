#include "def.h"
#include "STM8S103F3P.h"
#include "display.h"

/*
* �������ܣ���ʾ��������2MS����һ��
* �����������
* �����������
* ����ֵ����
*/
void DisplayDrive(void)
{
    uint8 temp;
    //��������Ҫ���͵�����:
    displayBuf = 0x1f;
    switch(disMode)
    {
        case 0:
            break;
        case 1:
            displayBuf &= C_ScanCom[disMode];
            if(displayBuff[0])
            {
                displayBuf &= C_ScanCom[0];
            }
            displayBuf |= (displayBuff[disMode])&(BIT5|BIT6|BIT7);
            break;
        case 2:
        case 3:
        case 4:
            displayBuf &= C_ScanCom[disMode];
            displayBuf |= (displayBuff[disMode])&(BIT5|BIT6|BIT7);
            break;
        default:
            break;

    }

    P_CLR_SEG1;
    P_CLR_SEG2;
    P_CLR_SEG6;
    P_CLR_SEG7;

    //�ȹر����е���ʾ:
    WriteAByteTo595(0x1f);
    SetByteOut595();
//  P_CLR_SEG1;
//  P_CLR_SEG2;
//  P_CLR_SEG6;
//  P_CLR_SEG7;

//  temp = displayBuff[disMode]&(BIT1|BIT2);
//  temp <<= 3;
//  PD_ODR |= temp;

//  temp = displayBuff[disMode]&(BIT3|BIT4);
//  temp <<= 2;
//  PC_ODR |= temp;

    //��������ʾ:
    WriteAByteTo595(displayBuf);
    SetByteOut595();
    CLR_SDATA;


    temp = displayBuff[disMode]&(BIT1|BIT2);
    temp <<= 3;
    PD_ODR |= temp;

    temp = displayBuff[disMode]&(BIT3|BIT4);
    temp <<= 2;
    PC_ODR |= temp;

    disMode ++;
    if(disMode >= 5)
    {
        disMode = 1;
    }
}
/*
* �������ܣ���ʾ�Լ���� �����ʾ�Ƿ�����
* �����������
* �����������
* ����ֵ����
*/
void DisplayZJ(void)
{
    ;
}
/*
* �������ܣ���ʾ������� 20MS����һ��
* �����������
* �����������
* ����ֵ����
*/
void Display(void)
{
    uint8 i;
    if(WriteFlashDelay)
    {
        WriteFlashDelay --;
        WriteFlashDelay2 ++;
        if(WriteFlashDelay2 >= 4)
        {

            WriteFlashDelay2 = 0;
            if(f_need_write)
            {   //��ǰ��ҪдLFASH,��ˢ��Ƶ�ʼ���
                if(DisTime <= C_DIS_Write)
                {
                    DisTime ++;
                }
                else
                {
                    DisTime = C_DIS_Write;
                }
            }
            else
            {
                if(DisTime > C_DIS_NOR)
                {
                    DisTime --;
                }
                else
                {
                    DisTime = C_DIS_NOR;
                }
            }
        }
    }

    for(i=0;i<COM_AMOUNT;i++)
    {
        displayBuff[i] = 0;
    }
    DisFlashTime ++;
    if(DisFlashTime >= 25)
    {
        DisFlashTime = 0;
        f_flash_on ^= 1;
        if(f_flash_on)
        {
            DisPowCount ++;
            if(DisPowCount > 3)
            {
                DisPowCount = 4;

            }
        }
    }

    if(DisPowCount < 3)
    {
        if(!f_flash_on)
        {
            for(i=0;i<COM_AMOUNT;i++)
            {
                displayBuff[i] = 0xff;
            }
        }
        return;
    }

    if(SelfChekDis)
    {
        SelfChekDis --;
        for(i=0;i<COM_AMOUNT;i++)
        {
            displayBuff[i] = 0xff;
        }
        return;
    }

    //����Դָʾ��:
    PWR_LED_ON;

    //��ʾ��Ʒ�ͺ�:
    //LOG_CHAR_ON;

    //��̬��ʾ"��ˮ�ı�����"
    DisLogFlash ++;
    LOG_RED_ON;
    LOG_GREEN_ON;
    LOG_B_G_ON;

    //��ϴ��ȱˮ����ʾ:
    if(CxTime||XieYiaTime)
    {
        CX_LED_ON;
    }
    else if(f_zs_on)
    {
        ZS_LED_ON;
    }

    //�Լ�ָʾ����ʾ:
    if(f_zs_err)
    {
        if(!f_flash_on)
        {
            ZJ_LED_ON;
        }
    }

    //��о ��ʾ:
    if(SetMode)
    {   //������ģʽ�£�������ǰ��Ҫ���õ���о
        switch(SetMode)
        {
            case 1:
                if(!f_flash_on)
                {
                    DisPP1Filter();
                }
                break;
            case 2:
                if(!f_flash_on)
                {
                    DisC1Filter();
                }
                break;
            case 3:
                if(!f_flash_on)
                {
                    DisPP2Filter();
                }
                break;
            case 4:
                if(!f_flash_on)
                {
                    DisROFilter();
                }
                break;
            case 5:
                if(!f_flash_on)
                {
                    DisCUFFilter();
                }
                break;
            default:
                break;
        }
        //return;
    }
    else
    {
        DisPP1Filter();             //PP1��о��ʾ
        DisC1Filter();              //C1��о��ʾ
        DisPP2Filter();             //PP2��о��ʾ
        DisROFilter();              //RO��о��ʾ
        DisCUFFilter();             //CUF��о��ʾ
    }
}

/*
* �������ܣ�д��һ���ֽڵ�595��
* �����������
* �����������
* ����ֵ����
*/
void WriteAByteTo595(uint8 indata)  //�� 74HC595��д��һ�����ݡ�
{
    uint8 i,data;
    data = indata;
    for(i=0;i<8;i++)
    {
        CLR_SHCLK;
        if(data&0x80)
        {
            SET_SDATA;

        }
        else
        {
            CLR_SDATA;

        }
        data <<= 1;
        delayus(2);
//      delayus(200);
        SET_SHCLK;
        delayus(2);
//      delayus(200);
        CLR_SHCLK;
    }
}

/*
* �������ܣ���595�������������������
* �����������
* �����������
* ����ֵ����
*/
void SetByteOut595(void)
{
    CLR_STCLK;
    delayus(2);
//  delayus(200);
    SET_STCLK;
    delayus(2);
//  delayus(200);
    CLR_STCLK;
}

/*
* �������ܣ�PP1��о������ʾ.
* �����������
* �����������
* ����ֵ����
*/
void DisPP1Filter(void)             //PP1��о��ʾ
{
    PP1_PPF_ON;
    if(PP1filterTime<C_PP1_life_1_3)
    {   // 1/3����������û����ȫ��.
        PP1_LED1_ON;
        PP1_LED2_ON;
        PP1_LED3_ON;
    }
    else if(PP1filterTime<C_PP1_life_2_3)
    {   // 2/3����������û����
        PP1_LED1_ON;
        PP1_LED2_ON;
    }
    else if(PP1filterTime<C_PP1_life_2_3_2)
    {
        PP1_LED1_ON;
    }
    else if(PP1filterTime<C_PP1filter_life)
    {
        if(SetMode)
        {   //����о��λģʽʱ��������
            PP1_LED1_ON;
        }
        else
        {
            if(!f_flash_on)
            {
                PP1_LED1_ON;
            }
        }
    }
    else
    {
        if(SetMode)
        {   //����о��λģʽʱ��������
            PP1_LED1_ON;
        }
        else if(!f_flash_on)
        {
            PP1_PPF_ON;
        }
        else
        {
            PP1_PPF_OFF;
        }
    }
}

/*
* �������ܣ�C1��о������ʾ.
* �����������
* �����������
* ����ֵ����
*/
void DisC1Filter(void)              //PP1��о��ʾ
{
    C1_C1_ON;
    if(C1filterTime<C_C1_life_1_3)
    {   // 1/3����������û����ȫ��.
        C1_LED1_ON;
        C1_LED2_ON;
        C1_LED3_ON;
    }
    else if(C1filterTime<C_C1_life_2_3)
    {   // 2/3����������û����
        C1_LED1_ON;
        C1_LED2_ON;
    }
    else if(C1filterTime<C_C1_life_2_3_2)
    {
        C1_LED1_ON;
    }
    else if(C1filterTime<C_C1filter_life)
    {
        if(SetMode)
        {   //����о��λģʽʱ��������
            C1_LED1_ON;
        }
        else
        {
            if(!f_flash_on)
            {
                C1_LED1_ON;
            }
        }
    }
    else
    {
        if(SetMode)
        {   //����о��λģʽʱ��������
            C1_C1_ON;
        }
        else if(!f_flash_on)
        {
            C1_C1_ON;
        }
        else
        {
            C1_C1_OFF;
        }
    }
}

/*
* �������ܣ�PP1��о������ʾ.
* �����������
* �����������
* ����ֵ����
*/
void DisPP2Filter(void)             //PP1��о��ʾ
{
    PP2_PP_ON;
    if(PP2filterTime<C_PP2_life_1_3)
    {   // 1/3����������û����ȫ��.
        PP2_LED1_ON;
        PP2_LED2_ON;
        PP2_LED3_ON;
    }
    else if(PP2filterTime<C_PP2_life_2_3)
    {   // 2/3����������û����
        PP2_LED1_ON;
        PP2_LED2_ON;
    }
    else if(PP2filterTime<C_PP2_life_2_3_2)
    {
        PP2_LED1_ON;
    }
    else if(PP2filterTime<C_PP2filter_life)
    {
        if(SetMode)
        {   //����о��λģʽʱ��������
            PP2_LED1_ON;
        }
        else
        {
            if(!f_flash_on)
            {
                PP2_LED1_ON;
            }
        }
    }
    else
    {
        if(!f_flash_on)
        {
            PP2_PP_ON;
        }
        else
        {
            PP2_PP_OFF;
        }
    }
}

/*
* �������ܣ�PP1��о������ʾ.
* �����������
* �����������
* ����ֵ����
*/
void DisROFilter(void)              //PP1��о��ʾ
{
    RO_RO_ON;
    if(ROfilterTime<C_RO_life_1_3)
    {   // 1/3����������û����ȫ��.
        RO_LED1_ON;
        RO_LED2_ON;
        RO_LED3_ON;
    }
    else if(ROfilterTime<C_RO_life_2_3)
    {   // 2/3����������û����
        RO_LED1_ON;
        RO_LED2_ON;
    }
    else if(ROfilterTime<C_RO_life_2_3_2)
    {
        RO_LED1_ON;
    }
    else if(ROfilterTime<C_ROfilter_life)
    {
        if(SetMode)
        {   //����о��λģʽʱ��������
            RO_LED1_ON;
        }
        else
        {
            if(!f_flash_on)
            {
                RO_LED1_ON;
            }
        }
    }
    else
    {
        if(SetMode)
        {   //����о��λģʽʱ��������
            RO_RO_ON;
        }
        else if(!f_flash_on)
        {
            RO_RO_ON;
        }
        else
        {
            RO_RO_OFF;
        }
    }
}

/*
* �������ܣ�PP1��о������ʾ.
* �����������
* �����������
* ����ֵ����
*/
void DisCUFFilter(void)             //PP1��о��ʾ
{
    CUF_CUF_ON;
    if(CUFfilterTime<C_CUF_life_1_3)
    {   // 1/3����������û����ȫ��.
        CUF_LED1_ON;
        CUF_LED2_ON;
        CUF_LED3_ON;
    }
    else if(CUFfilterTime<C_CUF_life_2_3)
    {   // 2/3����������û����
        CUF_LED1_ON;
        CUF_LED2_ON;
    }
    else if(CUFfilterTime<C_CUF_life_2_3_2)
    {
        CUF_LED1_ON;
    }
    else if(CUFfilterTime<C_CUFfilter_life)
    {
        if(SetMode)
        {   //����о��λģʽʱ��������
            CUF_LED1_ON;
        }
        else
        {
            if(!f_flash_on)
            {
                CUF_LED1_ON;
            }
        }
    }
    else
    {
        if(SetMode)
        {   //����о��λģʽʱ��������
            CUF_CUF_ON;
        }
        else if(!f_flash_on)
        {
            CUF_CUF_ON;
        }
        else
        {
            CUF_CUF_OFF;
        }
    }
}

