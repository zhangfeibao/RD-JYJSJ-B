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
#define f_DisDrive  flag0.bits.bit0     //刷屏标志到。
#define f_10ms      flag0.bits.bit1
#define f_20ms      flag0.bits.bit2
#define f_500ms     flag0.bits.bit3
#define f_key_pres  flag0.bits.bit4     //按键按下标志。
#define f_first_10s flag0.bits.bit5     //上电10S标志。
#define f_lo_vol    flag0.bits.bit6     //低压开关电平状态。
#define f_hi_vol    flag0.bits.bit7     //高压开关电平状态。

//BYTE flag1;
#define f_beep_on   flag1.bits.bit0     //蜂鸣器响标志。
#define f_cx_auto   flag1.bits.bit1     //自动冲洗标志。
#define f_filter_reset_Ok   flag1.bits.bit2 //滤芯复位OK标志，用于区别当前按键按下3S不放开而达到5S的误动作。
#define f_flash_on  flag1.bits.bit3     //闪动标志。
#define f_zs_on     flag1.bits.bit4     //制水开标志。
#define f_zs_err    flag1.bits.bit5     //制水错误标志。
#define f_need_write    flag1.bits.bit6 //需要向内部EE写入数据的标志，1表示需要写，写完后清0
#define f_first_cx      flag1.bits.bit7 //
//#define f_first_sm    flag1.bits.bit7     //第一次水满标志。

//BYTE flag4;
#define f_stand_on  flag4.bits.bit0     //待机状态标志，1表示待机。

//==============
//display.h:
//==============
#define SET_SDATA   PC_ODR|=BIT7
#define CLR_SDATA   PC_ODR&=~BIT7
#define SET_SHCLK   PD_ODR|=BIT3
#define CLR_SHCLK   PD_ODR&=~BIT3   //移位时钟
#define SET_STCLK   PD_ODR|=BIT2
#define CLR_STCLK   PD_ODR&=~BIT2   //锁存时钟

#define P_SET_SEG1  PD_ODR|=BIT4
#define P_SET_SEG2  PD_ODR|=BIT5
#define P_SET_SEG6  PC_ODR|=BIT5
#define P_SET_SEG7  PC_ODR|=BIT6
#define P_CLR_SEG1  PD_ODR&=~BIT4
#define P_CLR_SEG2  PD_ODR&=~BIT5
#define P_CLR_SEG6  PC_ODR&=~BIT5
#define P_CLR_SEG7  PC_ODR&=~BIT6

#define COM_AMOUNT              5// 定义显示位数
//==============
//eeprom.h:
//==============
#define C_EEPROM_ADDR   0           //滤芯寿命存储在内部EE的开始地址。
#define C_WriteEEStepOver   4       //写入完成所需要的步数。
//==============
//key.h:
//==============
#define C_KEY_PCS   8           //按键按下或松开的基本时间，20*4 = 80ms
#define C_KEY_3S    300//750            //
#define C_KEY_200MS 50
#define C_KEY_2S    200//500            //
#define C_CXKEY     BIT4        //冲洗键
#define C_LXKEY     BIT5        //滤芯键
#define C_CX_PRE    1           //冲洗键按下键值。
#define C_LX_PRE    2           //滤芯键按下键值。
#define C_CX_L_PRE  3           //冲洗长按键
#define C_LX_L_PRE  4           //冲洗长按键
#define C_CX_LL_PRE 5           //冲洗长按键
#define C_LX_LL_PRE 6           //冲洗长按键
#define C_CX_L_O    7           //冲洗长按键
#define C_LX_L_O    8           //冲洗长按键
#define C_CX_RUN_PRE 9          //

//==============
//main.h:
//==============
//CLK_CKDIVR
#define HSI_DIV0 0x00
#define HSI_DIV2 0x01<<3
#define HSI_DIV4 0x02<<3
#define HSI_DIV8 0x03<<3
#define C_DIS_NOR   16//35//32          //正常时刷屏的频率为4ms，
//#define C_DIS_Write   36          //写flash时刷屏的频率
#define C_DIS_Write 40//35          //写flash时刷屏的频率
#define C_FLASH_DELAY   120//50//25     //写FLASH延时时间。

//==============
//output.h:
//==============
#define C_CX_MANU_T 3000        //手动冲洗时间:3000*20MS/1000 = 60S
#define C_CX_AUTO_T 1500        //自动冲洗时间:500*20MS/1000 = 10S
#define C_CX_AUTO_10s   500     //自动冲洗时间:500*20MS/1000 = 10S

#define P_CX_ON     PD_ODR |= BIT6  //冲洗开
#define P_CX_OFF    PD_ODR &= ~BIT6 //冲洗关
#define P_ZY_JS_ON  PC_ODR |= BIT3  //增压，进水开
#define P_ZY_JS_OFF PC_ODR &= ~BIT3 //增压，进水开

//==============
//Timer.h:
//==============
extern BYTE flag3;
#define lifeOver            flag3.byte
#define LIFE_OVER_VALUE     0x1f
#define f_PP1_life_over     flag3.bits.bit0// PP1
#define f_C1_life_over      flag3.bits.bit1// C1
#define f_PP2_life_over     flag3.bits.bit2// PP2
#define f_RO_life_over      flag3.bits.bit3// RO渗透到达寿命标志
#define f_CUF_life_over     flag3.bits.bit4// C2口感到达寿命标志

#define LIFE_DATA_AMOUNT        5
#define PP1filterTime       life[0]// 第一级PP初滤寿命计时。
#define C1filterTime        life[1]// C1吸附720小时30天计数
#define PP2filterTime       life[2]// 第二级PP初滤720小时30天计数
#define ROfilterTime        life[3]// RO渗透720小时30天计数
#define CUFfilterTime       life[4]// C2口感720小时30天计数

#define C_PP1filter_life    4320
#define C_C1filter_life     8640
#define C_PP2filter_life    4320
#define C_ROfilter_life     25920
#define C_CUFfilter_life    8640

#define C_PP1_life_1_3      1440    //第一级PP初滤1/3寿命
#define C_PP1_life_2_3      2880    //第一级PP初滤2/3寿命
#define C_PP1_life_2_3_2    4152    //第一级PP初滤2/3寿命~最后一周

#define C_C1_life_1_3       2880    //C1吸附 1/3寿命
#define C_C1_life_2_3       5730    //C1吸附 2/3寿命
#define C_C1_life_2_3_2     8472    //C1吸附 2/3寿命~最后一周

#define C_PP2_life_1_3      1440    //PP2吸附 1/3寿命
#define C_PP2_life_2_3      2880    //PP2吸附 2/3寿命
#define C_PP2_life_2_3_2    4152    //PP2吸附 2/3寿命~最后一周

#define C_RO_life_1_3       8640    //RO吸附 1/3寿命
#define C_RO_life_2_3       17280   //RO吸附 2/3寿命
#define C_RO_life_2_3_2     25752   //RO吸附 2/3寿命~最后一周

#define C_CUF_life_1_3      2880    //CUF吸附 1/3寿命
#define C_CUF_life_2_3      5730    //CUF吸附 2/3寿命
#define C_CUF_life_2_3_2    8472    //CUF吸附 2/3寿命~最后一周

#define C_ZsContiTimer      57600   //连续制水8小时，即8*3600*2 = 57600*0.5s

#define C_DEBUG             0       // 1,用于缩时测试， 0,正常模式

#endif


