#ifndef __DEF__
#define __DEF__
#define uint8 unsigned char
#define uint16 unsigned int

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80
#define BIT8 0x0100
#define BIT9 0x0200
#define BIT10 0x0400
#define BIT11 0x0800
#define BIT12 0x1000
#define BIT13 0x2000
#define BIT14 0x4000
#define BIT15 0x8000
#define BIT16 0x010000
#define BIT17 0x020000
#define BIT18 0x040000
#define BIT19 0x080000
#define BIT20 0x100000
#define BIT21 0x200000
#define BIT22 0x400000
#define BIT23 0x800000
#define BIT24 0x01000000
#define BIT25 0x02000000
#define BIT26 0x04000000
#define BIT27 0x08000000
#define BIT28 0x10000000
#define BIT29 0x20000000
#define BIT30 0x40000000
#define BIT31 0x80000000

#define FALSE 0
#define TRUE 1

#define key     (PC_IDR&0x40)
//#define zbrst0    PC_ODR&=~0x80
//#define zbrst1    PC_ODR|=0x80

typedef union byte_type_t
{
    uint8 byte;
    struct p8_bit
        {
            uint8 bit0:1    ; // 0
            uint8 bit1:1    ; // 1
            uint8 bit2:1    ; // 2
            uint8 bit3:1    ; // 3
            uint8 bit4:1    ; // 4
            uint8 bit5:1    ; // 5
            uint8 bit6:1    ; // 6
            uint8 bit7:1    ; // 7
        }bits;
}BYTE;

//BYTE flag0;
#define f_DisDrive  flag0.bits.bit0     //ˢ����־����
#define f_10ms      flag0.bits.bit1
#define f_20ms      flag0.bits.bit2
#define f_500ms     flag0.bits.bit3
#define f_key_pres  flag0.bits.bit4     //�������±�־��
#define f_first_10s flag0.bits.bit5     //�ϵ�10S��־��
#define f_lo_vol    flag0.bits.bit6     //��ѹ���ص�ƽ״̬��
#define f_hi_vol    flag0.bits.bit7     //��ѹ���ص�ƽ״̬��

//BYTE flag1;
#define f_beep_on   flag1.bits.bit0     //���������־��
#define f_cx_auto   flag1.bits.bit1     //�Զ���ϴ��־��
#define f_filter_reset_Ok   flag1.bits.bit2 //��о��λOK��־����������ǰ��������3S���ſ����ﵽ5S��������
#define f_flash_on  flag1.bits.bit3     //������־��
#define f_zs_on     flag1.bits.bit4     //��ˮ����־��
#define f_zs_err    flag1.bits.bit5     //��ˮ�����־��
#define f_need_write    flag1.bits.bit6 //��Ҫ���ڲ�EEд�����ݵı�־��1��ʾ��Ҫд��д�����0
#define f_first_cx      flag1.bits.bit7 //
//#define f_first_sm    flag1.bits.bit7     //��һ��ˮ����־��

//BYTE flag4;
#define f_stand_on  flag4.bits.bit0     //����״̬��־��1��ʾ������

//==============
//display.h:
//==============
#define SET_SDATA   PC_ODR|=BIT7
#define CLR_SDATA   PC_ODR&=~BIT7
#define SET_SHCLK   PD_ODR|=BIT3
#define CLR_SHCLK   PD_ODR&=~BIT3   //��λʱ��
#define SET_STCLK   PD_ODR|=BIT2
#define CLR_STCLK   PD_ODR&=~BIT2   //����ʱ��

#define P_SET_SEG1  PD_ODR|=BIT4
#define P_SET_SEG2  PD_ODR|=BIT5
#define P_SET_SEG6  PC_ODR|=BIT5
#define P_SET_SEG7  PC_ODR|=BIT6
#define P_CLR_SEG1  PD_ODR&=~BIT4
#define P_CLR_SEG2  PD_ODR&=~BIT5
#define P_CLR_SEG6  PC_ODR&=~BIT5
#define P_CLR_SEG7  PC_ODR&=~BIT6

#define COM_AMOUNT              5// ������ʾλ��
//==============
//eeprom.h:
//==============
#define C_EEPROM_ADDR   0           //��о�����洢���ڲ�EE�Ŀ�ʼ��ַ��
#define C_WriteEEStepOver   4       //д���������Ҫ�Ĳ�����
//==============
//key.h:
//==============
#define C_KEY_PCS   8           //�������»��ɿ��Ļ���ʱ�䣬20*4 = 80ms
#define C_KEY_3S    300//750            //
#define C_KEY_200MS 50
#define C_KEY_2S    200//500            //
#define C_CXKEY     BIT4        //��ϴ��
#define C_LXKEY     BIT5        //��о��
#define C_CX_PRE    1           //��ϴ�����¼�ֵ��
#define C_LX_PRE    2           //��о�����¼�ֵ��
#define C_CX_L_PRE  3           //��ϴ������
#define C_LX_L_PRE  4           //��ϴ������
#define C_CX_LL_PRE 5           //��ϴ������
#define C_LX_LL_PRE 6           //��ϴ������
#define C_CX_L_O    7           //��ϴ������
#define C_LX_L_O    8           //��ϴ������
#define C_CX_RUN_PRE 9          //

//==============
//main.h:
//==============
//CLK_CKDIVR
#define HSI_DIV0 0x00
#define HSI_DIV2 0x01<<3
#define HSI_DIV4 0x02<<3
#define HSI_DIV8 0x03<<3
#define C_DIS_NOR   16//35//32          //����ʱˢ����Ƶ��Ϊ4ms��
//#define C_DIS_Write   36          //дflashʱˢ����Ƶ��
#define C_DIS_Write 40//35          //дflashʱˢ����Ƶ��
#define C_FLASH_DELAY   120//50//25     //дFLASH��ʱʱ�䡣

//==============
//output.h:
//==============
#define C_CX_MANU_T 3000        //�ֶ���ϴʱ��:3000*20MS/1000 = 60S
#define C_CX_AUTO_T 1500        //�Զ���ϴʱ��:500*20MS/1000 = 10S
#define C_CX_AUTO_10s   500     //�Զ���ϴʱ��:500*20MS/1000 = 10S

#define P_CX_ON     PD_ODR |= BIT6  //��ϴ��
#define P_CX_OFF    PD_ODR &= ~BIT6 //��ϴ��
#define P_ZY_JS_ON  PC_ODR |= BIT3  //��ѹ����ˮ��
#define P_ZY_JS_OFF PC_ODR &= ~BIT3 //��ѹ����ˮ��

//==============
//Timer.h:
//==============
extern BYTE flag3;
#define lifeOver            flag3.byte
#define LIFE_OVER_VALUE     0x1f
#define f_PP1_life_over     flag3.bits.bit0// PP1
#define f_C1_life_over      flag3.bits.bit1// C1
#define f_PP2_life_over     flag3.bits.bit2// PP2
#define f_RO_life_over      flag3.bits.bit3// RO��͸����������־
#define f_CUF_life_over     flag3.bits.bit4// C2�ڸе���������־

#define LIFE_DATA_AMOUNT        5
#define PP1filterTime       life[0]// ��һ��PP����������ʱ��
#define C1filterTime        life[1]// C1����720Сʱ30�����
#define PP2filterTime       life[2]// �ڶ���PP����720Сʱ30�����
#define ROfilterTime        life[3]// RO��͸720Сʱ30�����
#define CUFfilterTime       life[4]// C2�ڸ�720Сʱ30�����

#define C_PP1filter_life    4320
#define C_C1filter_life     8640
#define C_PP2filter_life    4320
#define C_ROfilter_life     25920
#define C_CUFfilter_life    8640

#define C_PP1_life_1_3      1440    //��һ��PP����1/3����
#define C_PP1_life_2_3      2880    //��һ��PP����2/3����
#define C_PP1_life_2_3_2    4152    //��һ��PP����2/3����~���һ��

#define C_C1_life_1_3       2880    //C1���� 1/3����
#define C_C1_life_2_3       5730    //C1���� 2/3����
#define C_C1_life_2_3_2     8472    //C1���� 2/3����~���һ��

#define C_PP2_life_1_3      1440    //PP2���� 1/3����
#define C_PP2_life_2_3      2880    //PP2���� 2/3����
#define C_PP2_life_2_3_2    4152    //PP2���� 2/3����~���һ��

#define C_RO_life_1_3       8640    //RO���� 1/3����
#define C_RO_life_2_3       17280   //RO���� 2/3����
#define C_RO_life_2_3_2     25752   //RO���� 2/3����~���һ��

#define C_CUF_life_1_3      2880    //CUF���� 1/3����
#define C_CUF_life_2_3      5730    //CUF���� 2/3����
#define C_CUF_life_2_3_2    8472    //CUF���� 2/3����~���һ��

#define C_ZsContiTimer      57600   //������ˮ8Сʱ����8*3600*2 = 57600*0.5s

#define C_DEBUG             0       // 1,������ʱ���ԣ� 0,����ģʽ

#endif


