#include "def.h"
#include "STM8S103F3P.h"
#include "timer.h"

void delayus(uint8 dus)
{
    uint8 i;
    uint8 m;
    for(i=0;i<dus;i++)
    {
        ;
    }

}

void TIM4_Init(void)
{
    CLK_PCKENR1 |= 0x10;//timer4 clock enable
    TIM4_CR1=0x84;      // 1 000 0 1 00
    TIM4_IER=0x41;      //触发中断使能
    TIM4_SR=0x00;
    TIM4_EGR=0x01;
    TIM4_CNTR=0x00;     // 1ms
    TIM4_PSCR=0x04;     // 1/16---1us   分频后的频率1M，1US
    TIM4_ARR=124;//250;     // 0--250 ==  250us
    TIM4_CR1|=0x01;     // enable counter
}

/*
* 函数介绍：时间中心，每2MS执行一次。
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void TimeCenter(void)
{
    Time10Ms ++;
    if(Time10Ms >= 5)
    {
        Time10Ms = 0;
        f_10ms = 1;
    }
    if(++Time20Ms >= 10)
    {
        Time20Ms = 0;
        f_20ms = 1;
    }
    if(++Time500Ms >= 250)
    {   //5ms时间点到:
        Time500Ms = 0;
        TimeUpData();
    }

/*
    if(WriteFlashDelay)
    {
        WriteFlashDelay --;
        if(f_need_write)
        {

        }
    }
*/
}

/*
* 函数介绍：时间更新 500MS执行一次。
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void TimeUpData(void)
{
    uint8 i;
    if(!f_first_10s)
    {
        TimePower ++;
        if(TimePower >= 20)
        {
            f_first_10s = 1;
        }
    }

    //滤芯计时:
    lifehour ++;
    if(ZjMode)
    {
        PP1filterTime += 180;
        if(PP1filterTime >= C_PP1filter_life)
        {
            PP1filterTime = C_PP1filter_life;
            f_PP1_life_over = 1;
        }

        C1filterTime += 180;
        if(C1filterTime >= C_C1filter_life)
        {
            C1filterTime = C_C1filter_life;
            f_C1_life_over = 1;
        }

        PP2filterTime += 180;
        if(PP2filterTime >= C_PP2filter_life)
        {
            PP2filterTime = C_PP2filter_life;
            f_PP2_life_over = 1;
        }

        ROfilterTime += 180;
        if(ROfilterTime >= C_ROfilter_life)
        {
            ROfilterTime = C_ROfilter_life;
            f_RO_life_over = 1;
        }

        CUFfilterTime += 180;
        if(CUFfilterTime >= C_CUFfilter_life)
        {
            CUFfilterTime = C_CUFfilter_life;
            f_CUF_life_over = 1;
        }

        //将滤芯时间存储起来:
        //WriteFilterData();
        //SetWriteData();
    }
    else
    {
#if C_DEBUG
        if(lifehour >= 1)
        {

            i = 1;
            lifehour = 0;
            PP1filterTime ++;
            if(PP1filterTime == C_PP1_life_1_3)
            {
                SetWriteData();
            }
            else if(PP1filterTime == C_PP1_life_2_3)
            {
                SetWriteData();
            }
            else if(PP1filterTime == C_PP1_life_2_3_2)
            {
                SetWriteData();
            }
            else if(PP1filterTime == C_PP1filter_life)
            {
                SetWriteData();
            }
            if(PP1filterTime >= C_PP1filter_life)
            {
                PP1filterTime = C_PP1filter_life +1;
                f_PP1_life_over = 1;
            }

            C1filterTime ++;
            if(C1filterTime == C_C1_life_1_3)
            {
                SetWriteData();
            }
            else if(C1filterTime == C_C1_life_2_3)
            {
                SetWriteData();
            }
            else if(C1filterTime == C_C1_life_2_3_2)
            {
                SetWriteData();
            }
            else if(C1filterTime == C_C1filter_life)
            {
                SetWriteData();
            }
            if(C1filterTime >= C_C1filter_life)
            {
                C1filterTime = C_C1filter_life +1;
                f_C1_life_over = 1;
            }

            PP2filterTime ++;
            if(PP2filterTime == C_PP2_life_1_3)
            {
                SetWriteData();
            }
            else if(PP2filterTime == C_PP2_life_2_3)
            {
                SetWriteData();
            }
            else if(PP2filterTime == C_PP2_life_2_3_2)
            {
                SetWriteData();
            }
            else if(PP2filterTime == C_PP2filter_life)
            {
                SetWriteData();
            }
            if(PP2filterTime >= C_PP2filter_life)
            {
                PP2filterTime = C_PP2filter_life +1;
                f_PP2_life_over = 1;
            }

            ROfilterTime ++;
            if(ROfilterTime == C_RO_life_1_3)
            {
                SetWriteData();
            }
            else if(ROfilterTime == C_RO_life_2_3)
            {
                SetWriteData();
            }
            else if(ROfilterTime == C_RO_life_2_3_2)
            {
                SetWriteData();
            }
            else if(ROfilterTime == C_ROfilter_life)
            {
                SetWriteData();
            }
            if(ROfilterTime >= C_ROfilter_life)
            {
                ROfilterTime = C_ROfilter_life +1;
                f_RO_life_over = 1;
            }

            CUFfilterTime ++;
            if(CUFfilterTime == C_CUF_life_1_3)
            {
                SetWriteData();
            }
            else if(CUFfilterTime == C_CUF_life_2_3)
            {
                SetWriteData();
            }
            else if(CUFfilterTime == C_CUF_life_2_3_2)
            {
                SetWriteData();
            }
            else if(CUFfilterTime == C_CUFfilter_life)
            {
                SetWriteData();
            }
            if(CUFfilterTime >= C_CUFfilter_life)
            {
                CUFfilterTime = C_CUFfilter_life +1;
                f_CUF_life_over = 1;
            }
        }

#else
        if(lifehour >= 7200)
        {

            lifehour = 0;
            PP1filterTime ++;
            if(PP1filterTime >= C_PP1filter_life)
            {
                PP1filterTime = C_PP1filter_life;
                f_PP1_life_over = 1;
            }

            C1filterTime ++;
            if(C1filterTime >= C_C1filter_life)
            {
                C1filterTime = C_C1filter_life;
                f_C1_life_over = 1;
            }

            PP2filterTime ++;
            if(PP2filterTime >= C_PP2filter_life)
            {
                PP2filterTime = C_PP2filter_life;
                f_PP2_life_over = 1;
            }

            ROfilterTime ++;
            if(ROfilterTime >= C_ROfilter_life)
            {
                ROfilterTime = C_ROfilter_life;
                f_RO_life_over = 1;
            }

            CUFfilterTime ++;
            if(CUFfilterTime >= C_CUFfilter_life)
            {
                CUFfilterTime = C_CUFfilter_life;
                f_CUF_life_over = 1;
            }

            //将滤芯时间存储起来:
            //WriteFilterData();
            SetWriteData();
        }

#endif
    }

    //连续制水计时:
    if(f_zs_on)
    {
        ZsContiTimer ++;
        if(ZsContiTimer >= C_ZsContiTimer)
        {
            ZsContiTimer = 0;
            f_zs_err = 1;
            BeepSet(30,25,25);      //报警30下，
        }
    }
    else
    {
        ZsContiTimer = 0;
    }
}

