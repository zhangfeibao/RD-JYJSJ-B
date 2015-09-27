#include "def.h"
#include "STM8S103F3P.h"
#include "display.h"

/*
* 函数介绍：显示驱动程序2MS调用一次
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void DisplayDrive(void)
{
    uint8 temp;
    //先设置需要发送的数据:
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

    //先关闭所有的显示:
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

    //再轮流显示:
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
* 函数介绍：显示自检程序 检测显示是否正常
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void DisplayZJ(void)
{
    ;
}
/*
* 函数介绍：显示处理程序 20MS调用一次
* 输入参数：无
* 输出参数：无
* 返回值：无
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
            {   //当前需要写LFASH,则刷屏频率减慢
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

    //亮电源指示灯:
    PWR_LED_ON;

    //显示产品型号:
    //LOG_CHAR_ON;

    //动态显示"净水改变生活"
    DisLogFlash ++;
    LOG_RED_ON;
    LOG_GREEN_ON;
    LOG_B_G_ON;

    //冲洗，缺水灯显示:
    if(CxTime||XieYiaTime)
    {
        CX_LED_ON;
    }
    else if(f_zs_on)
    {
        ZS_LED_ON;
    }

    //自检指示灯显示:
    if(f_zs_err)
    {
        if(!f_flash_on)
        {
            ZJ_LED_ON;
        }
    }

    //滤芯 显示:
    if(SetMode)
    {   //在设置模式下，闪动当前需要设置的滤芯
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
        DisPP1Filter();             //PP1滤芯显示
        DisC1Filter();              //C1滤芯显示
        DisPP2Filter();             //PP2滤芯显示
        DisROFilter();              //RO滤芯显示
        DisCUFFilter();             //CUF滤芯显示
    }
}

/*
* 函数介绍：写入一个字节到595里
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void WriteAByteTo595(uint8 indata)  //往 74HC595里写入一个数据。
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
* 函数介绍：将595里的数据输出到锁存器里。
* 输入参数：无
* 输出参数：无
* 返回值：无
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
* 函数介绍：PP1滤芯寿命显示.
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void DisPP1Filter(void)             //PP1滤芯显示
{
    PP1_PPF_ON;
    if(PP1filterTime<C_PP1_life_1_3)
    {   // 1/3的寿命都还没到，全显.
        PP1_LED1_ON;
        PP1_LED2_ON;
        PP1_LED3_ON;
    }
    else if(PP1filterTime<C_PP1_life_2_3)
    {   // 2/3的寿命都还没到，
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
        {   //在滤芯复位模式时，不闪动
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
        {   //在滤芯复位模式时，不闪动
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
* 函数介绍：C1滤芯寿命显示.
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void DisC1Filter(void)              //PP1滤芯显示
{
    C1_C1_ON;
    if(C1filterTime<C_C1_life_1_3)
    {   // 1/3的寿命都还没到，全显.
        C1_LED1_ON;
        C1_LED2_ON;
        C1_LED3_ON;
    }
    else if(C1filterTime<C_C1_life_2_3)
    {   // 2/3的寿命都还没到，
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
        {   //在滤芯复位模式时，不闪动
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
        {   //在滤芯复位模式时，不闪动
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
* 函数介绍：PP1滤芯寿命显示.
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void DisPP2Filter(void)             //PP1滤芯显示
{
    PP2_PP_ON;
    if(PP2filterTime<C_PP2_life_1_3)
    {   // 1/3的寿命都还没到，全显.
        PP2_LED1_ON;
        PP2_LED2_ON;
        PP2_LED3_ON;
    }
    else if(PP2filterTime<C_PP2_life_2_3)
    {   // 2/3的寿命都还没到，
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
        {   //在滤芯复位模式时，不闪动
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
* 函数介绍：PP1滤芯寿命显示.
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void DisROFilter(void)              //PP1滤芯显示
{
    RO_RO_ON;
    if(ROfilterTime<C_RO_life_1_3)
    {   // 1/3的寿命都还没到，全显.
        RO_LED1_ON;
        RO_LED2_ON;
        RO_LED3_ON;
    }
    else if(ROfilterTime<C_RO_life_2_3)
    {   // 2/3的寿命都还没到，
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
        {   //在滤芯复位模式时，不闪动
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
        {   //在滤芯复位模式时，不闪动
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
* 函数介绍：PP1滤芯寿命显示.
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void DisCUFFilter(void)             //PP1滤芯显示
{
    CUF_CUF_ON;
    if(CUFfilterTime<C_CUF_life_1_3)
    {   // 1/3的寿命都还没到，全显.
        CUF_LED1_ON;
        CUF_LED2_ON;
        CUF_LED3_ON;
    }
    else if(CUFfilterTime<C_CUF_life_2_3)
    {   // 2/3的寿命都还没到，
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
        {   //在滤芯复位模式时，不闪动
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
        {   //在滤芯复位模式时，不闪动
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

