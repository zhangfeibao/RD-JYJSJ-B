#ifndef output_h
#define output_h
uint8 BuzCountTotal;        //����������ܴ�����
uint8 BuzOnTotal;           //���������ʱ��������
uint8 BuzOffTotal;          //������ͣ��ʱ��������
uint8 BuzOnTime;            //���������ʱ
uint8 BuzOffTime;           //������ֹͣ��ʱ��
uint8 SmCount;              //ˮ������������
uint16 CxTime;              //��ϴʱ���ʱ��
uint16 HiSwitchCheckT;      //��ѹ���ؼ��ʱ�䡣
uint16 HiSwitchCheckT2;     //��ѹ���ؼ��ʱ�䡣
uint16 XieYiaTime;          //йѹʱ�䡣
uint16 ZjTime;              //�Լ��ʱ��

void BeepDeal(void);
void OutputDeal(void);
void BeepSet(uint8 total,uint16 ontotal,uint8 offtotal);

extern BYTE flag0;
extern BYTE flag1;
extern BYTE flag4;
extern uint8 ZjMode;            //�Լ�ģʽ�Ĵ�����
extern uint8 DisPowCount;       //�ϵ�����������

#endif


