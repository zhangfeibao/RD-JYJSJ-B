/*stm8_interrupt_vector.h*/
#ifndef __STM8_INTERRUPT_VECTOR_H__
#define __STM8_INTERRUPT_VECTOR_H__

uint8 Timer1msCount;
uint8 Timer2msCount;        // 2MS��ʱ��
uint8 DisTime;              //���ڿ�����ʾˢ����ʱ����
uint8 BuzBeepTime;          //���������ʱ��

extern BYTE flag0;
extern BYTE flag1;

extern void DisplayDrive(void);

#endif


