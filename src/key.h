#ifndef key_h
#define key_h

uint8 keyMode;// 按键读取模式（有效状态机） 0：首次读取按键 1：延时消抖 2：等待按键放开或长按键 3: 连续按键
uint8 keyValue;// 实时按键值
uint8 KeyValueBefor;    //当前扫描前一个按键值。
uint16 PressTime;       //按键按下计时。
uint8 ReleaseTime;      //按键松开计时。
uint8 LowPressTime;     //低压开关按下计时。
uint8 LowReleasTime;    //低压开关松开计时。
uint8 HiPressTime;      //高压开关按下计时。
uint8 HiReleasTime; //高压开关松开计时。
uint8 ZjMode;           //自检模式寄存器。
uint8 SetMode;          //滤芯复位设置模式。
uint16 SettingTime;     //滤芯设置时间超过10S即取水设置，
uint8 SelfChekDis;      //自检前全屏显示1S计时

const uint8 C_FilterReset[] = {0x1e,0x1d,0x1b,0x17,0x0f};

void FilterResetDeal(void);

extern uint8 DisPowCount;                   //上电闪动次数。
extern uint16 CxTime;   //冲洗时间计时。
extern uint16 life[LIFE_DATA_AMOUNT];
extern uint16 HiSwitchCheckT2;      //高压开关检测时间。
extern BYTE flag0;
extern BYTE flag1;
extern BYTE flag3;
extern void BeepSet(uint8 total,uint16 ontotal,uint8 offtotal);
extern void SetWriteData(void);
#endif


