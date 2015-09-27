/*timer.h*/
#ifndef __TIMER_H__
#define __TIMER_H__

uint8 Time10Ms;     //10ms计时。
uint8 Time20Ms;     //20ms计时。
uint8 Time500Ms;    //500ms计时。
uint8 TimePower;    //上电10s计时。

uint16 life[LIFE_DATA_AMOUNT];
uint16 lifehour;    //小时计数。
uint16 ZsContiTimer;    //制水连续计时。
uint16 WriteFlashDelay; //写flash延时。
void delayus(uint8 dus);
void TIM4_Init(void);
void TimeCenter(void);
void TimeUpData(void);

extern uint8 ZjMode;            //自检模式寄存器。
extern BYTE flag0;
extern BYTE flag1;

extern void BeepSet(uint8 total,uint16 ontotal,uint8 offtotal);
extern void WriteFilterData(void);
extern void SetWriteData(void);
#endif

