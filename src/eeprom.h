#ifndef _EEPROM_H
#define _EEPROM_H

uint8 WriteEEStep;      //写入EE的操作步骤。
uint8 ReadEeprom(uint8 radd);
void WriteEeprom(uint8 wadd,uint8 wdata);

void ReadFilterData(void);
void WriteFilterData(void);
void SetWriteData(void);

extern BYTE flag0;
extern BYTE flag1;
extern uint8 disMode;
extern uint8 WriteToEEData[10];         //需要往内部ee写的数据。
extern uint8 WriteCurAddr;              //当前要写的ee地址偏移。
extern uint8 DisTime;                   //用于控制显示刷屏的时间间隔
extern uint16 WriteFlashDelay;          //写flash延时。
extern void SetWriteData(void);
extern void DisplayDrive(void);
extern uint16 life[LIFE_DATA_AMOUNT];

#endif

