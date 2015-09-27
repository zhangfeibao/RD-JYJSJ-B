/*timer.h*/
#ifndef __TIMER_H__
#define __TIMER_H__

uint8 Time10Ms;     //10ms��ʱ��
uint8 Time20Ms;     //20ms��ʱ��
uint8 Time500Ms;    //500ms��ʱ��
uint8 TimePower;    //�ϵ�10s��ʱ��

uint16 life[LIFE_DATA_AMOUNT];
uint16 lifehour;    //Сʱ������
uint16 ZsContiTimer;    //��ˮ������ʱ��
uint16 WriteFlashDelay; //дflash��ʱ��
void delayus(uint8 dus);
void TIM4_Init(void);
void TimeCenter(void);
void TimeUpData(void);

extern uint8 ZjMode;            //�Լ�ģʽ�Ĵ�����
extern BYTE flag0;
extern BYTE flag1;

extern void BeepSet(uint8 total,uint16 ontotal,uint8 offtotal);
extern void WriteFilterData(void);
extern void SetWriteData(void);
#endif

