#ifndef _EEPROM_H
#define _EEPROM_H

uint8 WriteEEStep;      //д��EE�Ĳ������衣
uint8 ReadEeprom(uint8 radd);
void WriteEeprom(uint8 wadd,uint8 wdata);

void ReadFilterData(void);
void WriteFilterData(void);
void SetWriteData(void);

extern BYTE flag0;
extern BYTE flag1;
extern uint8 disMode;
extern uint8 WriteToEEData[10];         //��Ҫ���ڲ�eeд�����ݡ�
extern uint8 WriteCurAddr;              //��ǰҪд��ee��ַƫ�ơ�
extern uint8 DisTime;                   //���ڿ�����ʾˢ����ʱ����
extern uint16 WriteFlashDelay;          //дflash��ʱ��
extern void SetWriteData(void);
extern void DisplayDrive(void);
extern uint16 life[LIFE_DATA_AMOUNT];

#endif

