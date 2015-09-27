#include "def.h"
#include "STM8S103F3P.h"
#include "Key.h"

/*
* 函数介绍：开关类信号读取程序 10MS执行一次
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void ReadSwKey(void)
{
//  if(PA_IDR & (BIT2))     //低压开关
    if(PA_IDR & (BIT1))     //低压开关
    {
        LowPressTime = 0;
        LowReleasTime ++;
        if(LowReleasTime >= 8)
        {
            LowReleasTime = 0;
            f_lo_vol = 1;
        }
    }
    else//高压开关状态为闭合
    {
        LowPressTime ++;
        LowReleasTime = 0;
        if(LowPressTime >= 8)
        {
            LowPressTime = 0;
            f_lo_vol = 0;
        }
    }

//  if(PA_IDR & (BIT1))
    if(PA_IDR & (BIT2))
    {       HiPressTime = 0;
        HiReleasTime ++;
        if(HiReleasTime >= 8)
        {
            HiReleasTime = 0;
            f_hi_vol = 1;
        }
    }
    else
    {
        HiPressTime = 0;
        HiReleasTime ++;
        if(HiReleasTime >= 8)
        {
            HiReleasTime = 0;
            f_hi_vol = 0;
        }
    }
}
/*
* 函数介绍：按键扫描程序 10MS执行一次
* 输入参数：无
* 输出参数：按键值
* 返回值：无
*/
void KeyScan(void)
{
    uint8 temp;
    keyValue = 0;
    temp = 0;
    temp = PB_IDR & (BIT4|BIT5);
    temp ^= 0xff;
    temp &= (BIT4|BIT5);

    switch (keyMode)
    {
        case 0:// 等待按键按下
            if (temp != 0)
            {
                ReleaseTime = 0;
                if(KeyValueBefor != temp)
                {
                    PressTime = 0;
                }
                else
                {
                    ReleaseTime = 0;
                    PressTime ++;
                }

                KeyValueBefor = temp;
                //if(PressTime >= C_KEY_PCS)
                if(PressTime >= 4)
                {
                    PressTime = 0;
                    keyMode++;
                }
            }
            else
            {
                ReleaseTime ++;
                if(ReleaseTime >= C_KEY_PCS)
                {
                    ReleaseTime = 0;
                    f_key_pres = 0;
                    f_filter_reset_Ok = 0;
                }
            }
            break;
        case 1:// 消抖 短按键（按键按下响应）
            if (KeyValueBefor == temp)
            {
                keyMode++;
                ReleaseTime = 0;
                switch (temp)
                {
                    case C_CXKEY:           //冲洗
                        keyValue = C_CX_PRE;
                        break;
                    case C_LXKEY:
                        keyValue = C_LX_PRE;
                        break;
                    default:
                        break;
                }
                if(f_key_pres)
                {
                    keyValue = 0;
                }
                f_key_pres = 1;
            }
            else
            {
                ReleaseTime ++;
                //if(ReleaseTime > C_KEY_PCS)
                if(ReleaseTime > 4)
                {
                    ReleaseTime = 0;
                    f_key_pres = 0;
                    keyMode = 0;
                }
            }
            break;
        case 2:// 长按键 短按键（按键放开响应）
            if (KeyValueBefor == temp)
            {
                ReleaseTime = 0;
                switch (temp)
                {
                    case C_CXKEY:
                        if (++PressTime >= C_KEY_3S)
                        {
                            PressTime = 0;
                            keyValue = C_CX_L_PRE;
                            keyMode++;
                            f_key_pres = 1;
                        }
                        break;
                    case C_LXKEY:
                        if (++PressTime >= C_KEY_3S)
                        {
                            PressTime = 0;
                            keyValue = C_LX_L_PRE;
                            keyMode++;
                            f_key_pres = 1;
                        }
                        break;
                    default:
                        break;
                }
            }
            else
            {
                ReleaseTime ++;
                if(ReleaseTime > C_KEY_PCS)
                {
                    ReleaseTime = 0;
                    f_key_pres = 0;
                    keyMode = 0;
                }
                switch (KeyValueBefor)
                {
                    case C_CXKEY:
                        keyValue = C_CX_L_O;
                        f_key_pres = 1;
                        break;
                    case C_LXKEY:
                        keyValue = C_LX_L_O;
                        f_key_pres = 1;
                        break;
                    default:
                        break;
                }
            }
            break;
        case 3:// 连续按键并等待按键放开
            if (KeyValueBefor == temp)
            {
                ReleaseTime = 0;
                switch (KeyValueBefor)
                {
                    case C_CXKEY:
                        if (++PressTime >= C_KEY_2S)
                        {
                            PressTime = 0;
                            keyValue = C_CX_LL_PRE;     //5S长按
                            keyMode ++;
                            f_key_pres = 1;
                        }
                        break;
                    case C_LXKEY:
                        if (++PressTime >= C_KEY_2S)
                        {
                            PressTime = 0;
                            keyValue = C_LX_LL_PRE;     //5S长按
                            keyMode ++;
                            f_key_pres = 1;
                        }
                        break;
                    default:
                        break;
                }
            }
            else
            {
                ReleaseTime ++;
                if(ReleaseTime >= C_KEY_PCS)
                {
                    ReleaseTime = 0;
                    keyMode = 0;
                    f_key_pres = 0;
                }
            }
            break;
        default:
            if(temp == 0)
            {
                ReleaseTime ++;
                if(ReleaseTime > C_KEY_PCS)
                {
                    ReleaseTime = 0;
                    f_key_pres = 0;
                    keyMode = 0;
                }
            }
            else
            {
                ReleaseTime = 0;
            }
            break;
    }
}

/*
* 函数介绍：按键处理程序 10MS调用一次
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void Key(void)
{
    if(f_zs_err)
    {   //制水故障，整机失效。
        return;
    }
    if(ZjMode != 0)
    {       if(keyValue == C_LX_L_PRE)
        {
        //  BeepSet(1,100,0);
            FilterResetDeal();
        }
        return;
    }
    switch(keyValue)
    {
        case C_CX_PRE:
            //if(!f_first_10s)
            if(DisPowCount < 3)
            {   //上电前10s按
                break;
            }
            //SetWriteData();
            BeepSet(1,20,0);
            if(SetMode)
            {
                life[SetMode-1] = 0;    //将当前滤芯时间清零。
                switch(SetMode)         //将相应滤芯寿命到标志清零。
                {
                    case 1:
                        f_PP1_life_over = 0;
                        break;
                    case 2:
                        f_C1_life_over = 0;
                        break;
                    case 3:
                        f_PP2_life_over = 0;
                        break;
                    case 4:
                        f_RO_life_over = 0;
                        break;
                    case 5:
                        f_CUF_life_over = 0;
                        break;
                    default:
                        break;
                }
                SetMode ++;
                if(SetMode >= 6)
                {
                    SetMode = 0;                }
                SettingTime = 0;
                SetWriteData();
                break;
            }
            if(f_cx_auto&&CxTime)
            {   //当前为自动冲洗，
                f_cx_auto = 0;
                CxTime = C_CX_MANU_T;
            }
            else if(CxTime)
            {
                CxTime = 0;
                if(HiSwitchCheckT2 >= 250)      //自动冲洗时间清零时，再一次检测看开关有没有闭合5S.
                {
                    f_zs_on = 1;
                }
                HiSwitchCheckT2 = 0;
            }
            else
            {
                CxTime = C_CX_MANU_T;
            }
            f_cx_auto = 0;
            break;

        /*
        case C_CX_L_O:
            if(f_first_10s)
            {   //上电10s后长按松开后无效。
                break;          }

            BeepSet(1,20,0);
            if(f_cx_auto&&CxTime)
            {   //当前为自动冲洗，
                f_cx_auto = 0;
                CxTime = C_CX_MANU_T;
            }
            else if(CxTime)
            {
                CxTime = 0;
            }
            else
            {
                CxTime = C_CX_MANU_T;
            }
            f_cx_auto = 0;
            break;
        */

        case C_CX_L_PRE:
            if(f_first_10s)
            {
                break;          }
            BeepSet(1,20,0);
            ZjMode = 0x01;          //进入快检模式。
            SelfChekDis = 50;       //快检前全屏显示1S
            DisPowCount = 4;        //取消上电前的闪动显示。
            break;

        case C_LX_PRE:
            if(SetMode)
            {
                BeepSet(1,20,0);
                SetMode ++;
                if(SetMode >= 6)
                {
                    SetMode = 0;
                    SettingTime = 0;
                }
            }
            else
            {
                    BeepSet(1,20,0);
            }
            break;

        case C_LX_L_PRE:
            if(!f_first_10s)
            {                       //上电前10秒长按滤芯无效。
                break;
            }
            FilterResetDeal();
            break;

        case C_LX_LL_PRE:
            if(!f_first_10s)
            {                       //上电前10秒长按滤芯无效。
                break;
            }
            if(f_filter_reset_Ok)
            {                       //当前长按5秒是由前面的长按3S且滤芯已全部复位而来，不处理，
                break;
            }
            if(SetMode == 0)
            {
                BeepSet(1,20,0);
                SetMode = 1;
                SettingTime = 0;
            }
            break;
        default:
            break;
    }

    if(++SettingTime >= 1000)
    {
        SettingTime = 0;        SetMode = 0;
    }
}

/*
* 函数介绍：长按滤芯键3S，所有滤芯复位子程序:
* 输入参数：无
* 输出参数：无
* 返回值：无
*/
void FilterResetDeal(void)
{
//  if(flag3&LIFE_OVER_VALUE)
    if(f_PP1_life_over||f_C1_life_over||f_PP2_life_over||f_RO_life_over||f_CUF_life_over)
    {   //任意一级滤芯寿命到期，复位寿命。
        PP1filterTime = 0;
        C1filterTime = 0;
        PP2filterTime = 0;
        ROfilterTime = 0;
        CUFfilterTime = 0;
        f_filter_reset_Ok = 1;
        BeepSet(1,20,0);
        f_PP1_life_over = 0;
        f_C1_life_over = 0;
        f_PP2_life_over = 0;
        f_RO_life_over = 0;
        f_CUF_life_over = 0;

    //  if(ZjMode == 0)
        {
            SetWriteData();
        }
    }
}

