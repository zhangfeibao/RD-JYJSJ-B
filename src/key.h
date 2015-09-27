#ifndef key_h
#define key_h

uint8 keyMode;// ������ȡģʽ����Ч״̬���� 0���״ζ�ȡ���� 1����ʱ���� 2���ȴ������ſ��򳤰��� 3: ��������
uint8 keyValue;// ʵʱ����ֵ
uint8 KeyValueBefor;    //��ǰɨ��ǰһ������ֵ��
uint16 PressTime;       //�������¼�ʱ��
uint8 ReleaseTime;      //�����ɿ���ʱ��
uint8 LowPressTime;     //��ѹ���ذ��¼�ʱ��
uint8 LowReleasTime;    //��ѹ�����ɿ���ʱ��
uint8 HiPressTime;      //��ѹ���ذ��¼�ʱ��
uint8 HiReleasTime; //��ѹ�����ɿ���ʱ��
uint8 ZjMode;           //�Լ�ģʽ�Ĵ�����
uint8 SetMode;          //��о��λ����ģʽ��
uint16 SettingTime;     //��о����ʱ�䳬��10S��ȡˮ���ã�
uint8 SelfChekDis;      //�Լ�ǰȫ����ʾ1S��ʱ

const uint8 C_FilterReset[] = {0x1e,0x1d,0x1b,0x17,0x0f};

void FilterResetDeal(void);

extern uint8 DisPowCount;                   //�ϵ�����������
extern uint16 CxTime;   //��ϴʱ���ʱ��
extern uint16 life[LIFE_DATA_AMOUNT];
extern uint16 HiSwitchCheckT2;      //��ѹ���ؼ��ʱ�䡣
extern BYTE flag0;
extern BYTE flag1;
extern BYTE flag3;
extern void BeepSet(uint8 total,uint16 ontotal,uint8 offtotal);
extern void SetWriteData(void);
#endif


