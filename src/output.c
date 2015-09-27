



                 #include "STM8S103F3P.h"
#include "def.h"
#include "Output.h"

/*
* 函数介绍：蜂鸣器设置子程序，10MS一次。
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void BeepSet(uint8 total,uint16 ontotal,uint8 offtotal)
{
    if(total == 0)
    {
        return;
    }
    BuzCountTotal = total*2 - 1;
    BuzOnTotal = ontotal;
    BuzOffTotal = offtotal;
    BuzOnTime = 0;
    BuzOffTime = 0;
}
/*
* 函数介绍：蜂鸣器控制子程序，10MS一次。
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void BeepDeal(void)
{
    if(BuzCountTotal)
    {
        if(BuzCountTotal&BIT0)
        {
            f_beep_on = 1;
            BuzOffTime = 0;
            BuzOnTime ++;
            if(BuzOnTime >= BuzOnTotal)
            {

                BuzOnTime = 0;
                BuzCountTotal --;
            }

        }
        else
        {
            f_beep_on = 0;
            BuzOnTime = 0;
            BuzOffTime ++;
            if(BuzOffTime >= BuzOffTotal)
            {
                BuzOffTime = 0;
                BuzCountTotal --;
            }
        }
    }
    else
    {
        BuzOnTime = 0;
        BuzOffTime = 0;
        f_beep_on = 0;
//      PA_ODR &= ~BIT3;
    }
}

/*
* 函数介绍：制水控制程序 20ms一次。
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void OutputDeal(void)
{
    uint16 x;
    if(ZjMode)
    {
        ZjTime ++;
        if(ZjTime >= 900)
        {
            ZjTime = 900;
            P_ZY_JS_ON;
            P_CX_OFF;
            f_zs_on = 1;    //亮制水灯
            CxTime = 0;     //亮冲洗灯
        }
        else
        {
            P_CX_ON;
            P_ZY_JS_ON;
            CxTime = 1;     //亮冲洗灯
        }
        return;
    }

    if(f_zs_err)
    {
        f_zs_on = 0;
        CxTime = 0;
        HiSwitchCheckT = 0;
        P_CX_OFF;
        P_ZY_JS_OFF;
        return;
    }

    if(DisPowCount < 3)
    {   //还没显示完，不动作
        P_CX_OFF;
        P_ZY_JS_OFF;
        return;
    }

    if(CxTime)
    {
        CxTime --;

        //冲洗过程中检测高压开关是否断开:
        if(f_hi_vol)
        {
            HiSwitchCheckT2 = 0;
            HiSwitchCheckT ++;
            if(HiSwitchCheckT >= 250)
            {   //连续5秒检测高压开关断开。
                HiSwitchCheckT = 250;
                //CxTime = C_CX_AUTO_T;
                //f_cx_auto = 1;
                f_zs_on = 0;
            }
        }
        else
        {
            HiSwitchCheckT = 0;
            HiSwitchCheckT2 ++;
            if(HiSwitchCheckT2 >= 250)
            {
                HiSwitchCheckT2 = 250;
                //if(!f_zs_on)
                //{
                //  CxTime = C_CX_AUTO_10s;
                //}
                //f_zs_on = 1;
            }
        }

        //进入泄压条件:1,自动冲洗,2,冲洗完成，3,完后是待机,4,高压开关断开时间大于等于5S:
        if(f_cx_auto && !f_zs_on && (CxTime == 0) && (HiSwitchCheckT >= 250))
        {
            HiSwitchCheckT = 250;
            XieYiaTime = 100;       //泄压两秒。
        }

        //在冲洗过程中，检测到高压开关闭合5秒，接着冲洗10秒进入制水：
        if((HiSwitchCheckT2 >= 250)&&(CxTime == 0)&&!f_zs_on)
        {
            CxTime = C_CX_AUTO_10s;
            f_zs_on = 1;
        }

        //
        if(!f_stand_on)
        {
            if((HiSwitchCheckT >= 250)&&(CxTime == 0))
            {
                CxTime = C_CX_AUTO_T;
                f_stand_on = 1;

                SmCount ++;     //水满计数加1
                if(SmCount >= 100)
                {
                    SmCount = 100;
                }
            }
        }
    //  if(f_zs_on&&)
    //  f_zs_on = 0;
        if(CxTime == 0)
        {
            f_cx_auto = 0;  //清自动冲洗标志。
        }
        P_CX_ON;
        P_ZY_JS_ON;
        return;
    }

    if(XieYiaTime)
    {
        XieYiaTime --;
        P_CX_ON;        //开冲洗
        P_ZY_JS_OFF;    //关增压和进水阀
        return;
    }

    //制水状态检测
    if(f_zs_on)
    {
        f_stand_on = 0;
        if(f_hi_vol)
        {
            HiSwitchCheckT ++;
            //if(HiSwitchCheckT >= 250)
            if(HiSwitchCheckT >= 1500)
            {   //连续5秒检测高压开关断开。
                HiSwitchCheckT = 0;
                CxTime = C_CX_AUTO_T;
                f_cx_auto = 1;
                f_stand_on = 1;         //进入待机状态
                f_zs_on = 0;
                SmCount ++;     //水满计数加1
                if(SmCount >= 100)
                {
                    SmCount = 100;
                }
            }
        }
        else
        {
            HiSwitchCheckT = 0;
        }
    }
    else
    {
        f_stand_on = 1;
        if(f_hi_vol)
        {
            HiSwitchCheckT = 0;
        }
        else
        {
            if(SmCount >= 1)
            {   //非第一次水满连续闭合30s进入到冲洗状态。
                x = 1500;
            }
            else
            {   //第一次水满则连续闭合5S进入到冲洗状态。
                x = 250;
            }
            HiSwitchCheckT ++;
            if(HiSwitchCheckT >= x)
            {   //待机状态下，检测到高压开关连续闭合30秒，则进入冲洗状态。
                HiSwitchCheckT = 0;
                CxTime = 500;
                f_cx_auto = 1;
                f_zs_on = 1;
                f_stand_on = 0;         //取消待机状态。
            }
        }
    }

    //制水输出:
    if(f_zs_on)
    {
        P_CX_OFF;
        P_ZY_JS_ON;
    }
    else
    {
        P_CX_OFF;
        P_ZY_JS_OFF;
    }
}

