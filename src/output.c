



                 #include "STM8S103F3P.h"
#include "def.h"
#include "Output.h"

/*
* �������ܣ������������ӳ���10MSһ�Ρ�
* �����������
* �����������
* ����ֵ����
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
* �������ܣ������������ӳ���10MSһ�Ρ�
* �����������
* �����������
* ����ֵ����
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
* �������ܣ���ˮ���Ƴ��� 20msһ�Ρ�
* �����������
* �����������
* ����ֵ����
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
            f_zs_on = 1;    //����ˮ��
            CxTime = 0;     //����ϴ��
        }
        else
        {
            P_CX_ON;
            P_ZY_JS_ON;
            CxTime = 1;     //����ϴ��
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
    {   //��û��ʾ�꣬������
        P_CX_OFF;
        P_ZY_JS_OFF;
        return;
    }

    if(CxTime)
    {
        CxTime --;

        //��ϴ�����м���ѹ�����Ƿ�Ͽ�:
        if(f_hi_vol)
        {
            HiSwitchCheckT2 = 0;
            HiSwitchCheckT ++;
            if(HiSwitchCheckT >= 250)
            {   //����5�����ѹ���ضϿ���
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

        //����йѹ����:1,�Զ���ϴ,2,��ϴ��ɣ�3,����Ǵ���,4,��ѹ���ضϿ�ʱ����ڵ���5S:
        if(f_cx_auto && !f_zs_on && (CxTime == 0) && (HiSwitchCheckT >= 250))
        {
            HiSwitchCheckT = 250;
            XieYiaTime = 100;       //йѹ���롣
        }

        //�ڳ�ϴ�����У���⵽��ѹ���رպ�5�룬���ų�ϴ10�������ˮ��
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

                SmCount ++;     //ˮ��������1
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
            f_cx_auto = 0;  //���Զ���ϴ��־��
        }
        P_CX_ON;
        P_ZY_JS_ON;
        return;
    }

    if(XieYiaTime)
    {
        XieYiaTime --;
        P_CX_ON;        //����ϴ
        P_ZY_JS_OFF;    //����ѹ�ͽ�ˮ��
        return;
    }

    //��ˮ״̬���
    if(f_zs_on)
    {
        f_stand_on = 0;
        if(f_hi_vol)
        {
            HiSwitchCheckT ++;
            //if(HiSwitchCheckT >= 250)
            if(HiSwitchCheckT >= 1500)
            {   //����5�����ѹ���ضϿ���
                HiSwitchCheckT = 0;
                CxTime = C_CX_AUTO_T;
                f_cx_auto = 1;
                f_stand_on = 1;         //�������״̬
                f_zs_on = 0;
                SmCount ++;     //ˮ��������1
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
            {   //�ǵ�һ��ˮ�������պ�30s���뵽��ϴ״̬��
                x = 1500;
            }
            else
            {   //��һ��ˮ���������պ�5S���뵽��ϴ״̬��
                x = 250;
            }
            HiSwitchCheckT ++;
            if(HiSwitchCheckT >= x)
            {   //����״̬�£���⵽��ѹ���������պ�30�룬������ϴ״̬��
                HiSwitchCheckT = 0;
                CxTime = 500;
                f_cx_auto = 1;
                f_zs_on = 1;
                f_stand_on = 0;         //ȡ������״̬��
            }
        }
    }

    //��ˮ���:
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

