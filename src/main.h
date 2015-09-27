/*timer.h*/
#ifndef __MAIN_H__
#define __MAIN_H__

BYTE flag0;
BYTE flag1;
BYTE flag3;
BYTE flag4;

uint8 WriteToEEData[10];            //需要往内部ee写的数据。
uint8 WriteCurAddr;                 //当前要写的ee地址偏移。
uint16 JustForTest;
extern uint8 Timer1msCount;
extern uint8 WriteEEStep;       //写入EE的操作步骤。
extern uint8 displayBuff[];     // 显示寄存器 bit0,SEG4(P30)，bit3,SEG1，bit4,SEG2,bit5,SEG3
extern uint8 disMode;
extern uint8 Timer2msCount;     // 2MS计时。
extern uint8 DisTime;               //用于控制显示刷屏的时间间隔
extern uint16 WriteFlashDelay;  //写flash延时。
extern uint16 CxTime;           //冲洗时间计时。

extern void delayus(uint8 dus);
extern void TIM4_Init(void);
extern void DisplayDrive(void);
extern void ReadSwKey(void);
extern void Key(void);
extern void KeyScan(void);
extern void TimeCenter(void);
extern void Display(void);
extern void BeepDeal(void);
extern void OutputDeal(void);
extern void BeepSet(uint8 total,uint16 ontotal,uint8 offtotal);
extern void ReadFilterData(void);
extern void WriteEeprom(uint8 wadd,uint8 wdata);
extern uint8 WriteEepromStep(uint8 wadd,uint8 wdata);

#endif

