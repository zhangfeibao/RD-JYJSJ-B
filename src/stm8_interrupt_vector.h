/*stm8_interrupt_vector.h*/
#ifndef __STM8_INTERRUPT_VECTOR_H__
#define __STM8_INTERRUPT_VECTOR_H__

uint8 Timer1msCount;
uint8 Timer2msCount;        // 2MS计时。
uint8 DisTime;              //用于控制显示刷屏的时间间隔
uint8 BuzBeepTime;          //蜂鸣器响计时。

extern BYTE flag0;
extern BYTE flag1;

extern void DisplayDrive(void);

#endif


