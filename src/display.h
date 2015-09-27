#ifndef display_h
#define display_h

#define DISPLAY_OFF             P2 |= BIT1|BIT2, P2 &= ~(BIT3|BIT4|BIT5), P3 &= ~BIT0
#define SEG                     P2
#define COM0_ON                 P21 = 0
#define COM1_ON                 P22 = 0

//#define COM_AMOUNT                5// 定义显示位数

#define PWR_LED_ON              displayBuff[1] |= BIT4  // 定义电源指示灯
#define ZJ_LED_ON               displayBuff[2] |= BIT4  // 定义自检指示灯
#define CX_LED_ON               displayBuff[3] |= BIT4  // 定义冲洗指示灯
#define ZS_LED_ON               displayBuff[4] |= BIT4  // 定义自检指示灯
#define LOG_RED_ON              displayBuff[3] |= BIT3  // 定义LOG红色灯
#define LOG_GREEN_ON            displayBuff[2] |= BIT3  // 定义LOG绿色灯
#define LOG_BLUE_ON             displayBuff[1] |= BIT3  // 定义LOG蓝色灯
#define LOG_B_G_ON              displayBuff[1] |= BIT3,displayBuff[2] |= BIT3   // 定义LOG蓝同绿色灯
#define LOG_CHAR_ON             displayBuff[4] |= BIT3  // 定义LOG型号灯

#define PP1_PPF_ON              displayBuff[1] |= BIT2  //PP1滤芯灯PPF标志。
#define PP1_PPF_OFF             displayBuff[1] &= ~BIT2 //PP1滤芯灯PPF标志。
#define PP1_LED1_ON             displayBuff[2] |= BIT2  //PP1滤芯灯最下面一个LED
#define PP1_LED2_ON             displayBuff[3] |= BIT2  //PP1滤芯灯最下面第二个LED
#define PP1_LED3_ON             displayBuff[4] |= BIT2  //PP1滤芯灯最下面第三桓鯨ED

#define C1_C1_ON                displayBuff[1] |= BIT1  //PP1滤芯灯PPF标志。
#define C1_C1_OFF               displayBuff[1] &= ~BIT1 //PP1滤芯灯PPF标志。
#define C1_LED1_ON              displayBuff[2] |= BIT1  //PP1滤芯灯最下面一个LED
#define C1_LED2_ON              displayBuff[3] |= BIT1  //PP1滤芯灯最下面第二个LED
#define C1_LED3_ON              displayBuff[4] |= BIT1  //PP1滤芯灯最下面第三桓鯨ED

#define PP2_PP_ON               displayBuff[1] |= BIT6  //PP1滤芯灯PPF标志。
#define PP2_PP_OFF              displayBuff[1] &= ~BIT6 //PP1滤芯灯PPF标志。
#define PP2_LED1_ON             displayBuff[2] |= BIT6  //PP1滤芯灯最下面一个LED
#define PP2_LED2_ON             displayBuff[3] |= BIT6  //PP1滤芯灯最下面第二个LED
#define PP2_LED3_ON             displayBuff[4] |= BIT6  //PP1滤芯灯最下面第三桓鯨ED

#define RO_RO_ON                displayBuff[1] |= BIT5  //PP1滤芯灯PPF标志。
#define RO_RO_OFF               displayBuff[1] &= ~BIT5 //PP1滤芯灯PPF标志。
#define RO_LED1_ON              displayBuff[2] |= BIT5  //PP1滤芯灯最下面一个LED
#define RO_LED2_ON              displayBuff[3] |= BIT5  //PP1滤芯灯最下面第二个LED
#define RO_LED3_ON              displayBuff[4] |= BIT5  //PP1滤芯灯最下面第三桓鯨ED

#define CUF_CUF_ON              displayBuff[1] |= BIT7  //PP1滤芯灯PPF标志。
#define CUF_CUF_OFF             displayBuff[1] &= ~BIT7 //PP1滤芯灯PPF标志。
#define CUF_LED1_ON             displayBuff[2] |= BIT7  //PP1滤芯灯最下面一个LED
#define CUF_LED2_ON             displayBuff[3] |= BIT7  //PP1滤芯灯最下面第二个LED
#define CUF_LED3_ON             displayBuff[4] |= BIT7  //PP1滤芯灯最下面第三桓鯨ED

uint8 WriteFlashDelay2;
uint8 displayBuff[COM_AMOUNT];      // 显示寄存器 bit0,SEG4(P30)，bit3,SEG1，bit4,SEG2,bit5,SEG3
uint8 displayBuf;                       // 显示寄存器
uint8 disMode;
uint8 DisFlashTime;                 //用于闪动的计时。
uint8 DisPowCount;                  //上电闪动次数。
uint8 DisLogFlash;                  //动态显示"净水改变生活"
const uint8 C_ScanCom[] = {0x1e,0x1d,0x1b,0x17,0x0f};

void DisplayDrive(void);
void WriteAByteTo595(uint8 indata); //往 74HC595里写入一个数据。
void SetByteOut595(void);           //将 74HC595里的数据送到输出锁存器里。
void DisPP1Filter(void);                //PP1滤芯显示
void DisC1Filter(void);             //C1滤芯显示
void DisPP2Filter(void);                //PP2滤芯显示
void DisROFilter(void);             //RO滤芯显示
void DisCUFFilter(void);                //CUF滤芯显示

extern uint8 SetMode;           //滤芯复位设置模式。
extern uint8 SelfChekDis;       //自检前全屏显示1S计时
extern uint8 DisTime;               //用于控制显示刷屏的时间间隔
extern uint16 CxTime;               //冲洗时间计时。
extern uint16 life[LIFE_DATA_AMOUNT];
extern uint16 XieYiaTime;           //泄压时间。
extern uint16 WriteFlashDelay;  //写flash延时。
extern BYTE flag1;
extern void delayus(uint8);
#endif


