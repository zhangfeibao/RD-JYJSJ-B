#include "def.h"
#include "STM8S103F3P.h"
#include "Key.h"

/*
* �������ܣ��������źŶ�ȡ���� 10MSִ��һ��
* �����������
* �����������
* ����ֵ����
*/
void ReadSwKey(void)
{
//  if(PA_IDR & (BIT2))     //��ѹ����
    if(PA_IDR & (BIT1))     //��ѹ����
    {
        LowPressTime = 0;
        LowReleasTime ++;
        if(LowReleasTime >= 8)
        {
            LowReleasTime = 0;
            f_lo_vol = 1;
        }
    }
    else//��ѹ����״̬Ϊ�պ�
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
* �������ܣ�����ɨ����� 10MSִ��һ��
* �����������
* �������������ֵ
* ����ֵ����
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
        case 0:// �ȴ���������
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
        case 1:// ���� �̰���������������Ӧ��
            if (KeyValueBefor == temp)
            {
                keyMode++;
                ReleaseTime = 0;
                switch (temp)
                {
                    case C_CXKEY:           //��ϴ
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
        case 2:// ������ �̰����������ſ���Ӧ��
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
        case 3:// �����������ȴ������ſ�
            if (KeyValueBefor == temp)
            {
                ReleaseTime = 0;
                switch (KeyValueBefor)
                {
                    case C_CXKEY:
                        if (++PressTime >= C_KEY_2S)
                        {
                            PressTime = 0;
                            keyValue = C_CX_LL_PRE;     //5S����
                            keyMode ++;
                            f_key_pres = 1;
                        }
                        break;
                    case C_LXKEY:
                        if (++PressTime >= C_KEY_2S)
                        {
                            PressTime = 0;
                            keyValue = C_LX_LL_PRE;     //5S����
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
* �������ܣ������������ 10MS����һ��
* �����������
* �����������
* ����ֵ����
*/
void Key(void)
{
    if(f_zs_err)
    {   //��ˮ���ϣ�����ʧЧ��
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
            {   //�ϵ�ǰ10s��
                break;
            }
            //SetWriteData();
            BeepSet(1,20,0);
            if(SetMode)
            {
                life[SetMode-1] = 0;    //����ǰ��оʱ�����㡣
                switch(SetMode)         //����Ӧ��о��������־���㡣
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
            {   //��ǰΪ�Զ���ϴ��
                f_cx_auto = 0;
                CxTime = C_CX_MANU_T;
            }
            else if(CxTime)
            {
                CxTime = 0;
                if(HiSwitchCheckT2 >= 250)      //�Զ���ϴʱ������ʱ����һ�μ�⿴������û�бպ�5S.
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
            {   //�ϵ�10s�󳤰��ɿ�����Ч��
                break;          }

            BeepSet(1,20,0);
            if(f_cx_auto&&CxTime)
            {   //��ǰΪ�Զ���ϴ��
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
            ZjMode = 0x01;          //������ģʽ��
            SelfChekDis = 50;       //���ǰȫ����ʾ1S
            DisPowCount = 4;        //ȡ���ϵ�ǰ��������ʾ��
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
            {                       //�ϵ�ǰ10�볤����о��Ч��
                break;
            }
            FilterResetDeal();
            break;

        case C_LX_LL_PRE:
            if(!f_first_10s)
            {                       //�ϵ�ǰ10�볤����о��Ч��
                break;
            }
            if(f_filter_reset_Ok)
            {                       //��ǰ����5������ǰ��ĳ���3S����о��ȫ����λ������������
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
* �������ܣ�������о��3S��������о��λ�ӳ���:
* �����������
* �����������
* ����ֵ����
*/
void FilterResetDeal(void)
{
//  if(flag3&LIFE_OVER_VALUE)
    if(f_PP1_life_over||f_C1_life_over||f_PP2_life_over||f_RO_life_over||f_CUF_life_over)
    {   //����һ����о�������ڣ���λ������
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

