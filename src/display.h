#ifndef display_h
#define display_h

#define DISPLAY_OFF             P2 |= BIT1|BIT2, P2 &= ~(BIT3|BIT4|BIT5), P3 &= ~BIT0
#define SEG                     P2
#define COM0_ON                 P21 = 0
#define COM1_ON                 P22 = 0

//#define COM_AMOUNT                5// ������ʾλ��

#define PWR_LED_ON              displayBuff[1] |= BIT4  // �����Դָʾ��
#define ZJ_LED_ON               displayBuff[2] |= BIT4  // �����Լ�ָʾ��
#define CX_LED_ON               displayBuff[3] |= BIT4  // �����ϴָʾ��
#define ZS_LED_ON               displayBuff[4] |= BIT4  // �����Լ�ָʾ��
#define LOG_RED_ON              displayBuff[3] |= BIT3  // ����LOG��ɫ��
#define LOG_GREEN_ON            displayBuff[2] |= BIT3  // ����LOG��ɫ��
#define LOG_BLUE_ON             displayBuff[1] |= BIT3  // ����LOG��ɫ��
#define LOG_B_G_ON              displayBuff[1] |= BIT3,displayBuff[2] |= BIT3   // ����LOG��ͬ��ɫ��
#define LOG_CHAR_ON             displayBuff[4] |= BIT3  // ����LOG�ͺŵ�

#define PP1_PPF_ON              displayBuff[1] |= BIT2  //PP1��о��PPF��־��
#define PP1_PPF_OFF             displayBuff[1] &= ~BIT2 //PP1��о��PPF��־��
#define PP1_LED1_ON             displayBuff[2] |= BIT2  //PP1��о��������һ��LED
#define PP1_LED2_ON             displayBuff[3] |= BIT2  //PP1��о��������ڶ���LED
#define PP1_LED3_ON             displayBuff[4] |= BIT2  //PP1��о��������������LED

#define C1_C1_ON                displayBuff[1] |= BIT1  //PP1��о��PPF��־��
#define C1_C1_OFF               displayBuff[1] &= ~BIT1 //PP1��о��PPF��־��
#define C1_LED1_ON              displayBuff[2] |= BIT1  //PP1��о��������һ��LED
#define C1_LED2_ON              displayBuff[3] |= BIT1  //PP1��о��������ڶ���LED
#define C1_LED3_ON              displayBuff[4] |= BIT1  //PP1��о��������������LED

#define PP2_PP_ON               displayBuff[1] |= BIT6  //PP1��о��PPF��־��
#define PP2_PP_OFF              displayBuff[1] &= ~BIT6 //PP1��о��PPF��־��
#define PP2_LED1_ON             displayBuff[2] |= BIT6  //PP1��о��������һ��LED
#define PP2_LED2_ON             displayBuff[3] |= BIT6  //PP1��о��������ڶ���LED
#define PP2_LED3_ON             displayBuff[4] |= BIT6  //PP1��о��������������LED

#define RO_RO_ON                displayBuff[1] |= BIT5  //PP1��о��PPF��־��
#define RO_RO_OFF               displayBuff[1] &= ~BIT5 //PP1��о��PPF��־��
#define RO_LED1_ON              displayBuff[2] |= BIT5  //PP1��о��������һ��LED
#define RO_LED2_ON              displayBuff[3] |= BIT5  //PP1��о��������ڶ���LED
#define RO_LED3_ON              displayBuff[4] |= BIT5  //PP1��о��������������LED

#define CUF_CUF_ON              displayBuff[1] |= BIT7  //PP1��о��PPF��־��
#define CUF_CUF_OFF             displayBuff[1] &= ~BIT7 //PP1��о��PPF��־��
#define CUF_LED1_ON             displayBuff[2] |= BIT7  //PP1��о��������һ��LED
#define CUF_LED2_ON             displayBuff[3] |= BIT7  //PP1��о��������ڶ���LED
#define CUF_LED3_ON             displayBuff[4] |= BIT7  //PP1��о��������������LED

uint8 WriteFlashDelay2;
uint8 displayBuff[COM_AMOUNT];      // ��ʾ�Ĵ��� bit0,SEG4(P30)��bit3,SEG1��bit4,SEG2,bit5,SEG3
uint8 displayBuf;                       // ��ʾ�Ĵ���
uint8 disMode;
uint8 DisFlashTime;                 //���������ļ�ʱ��
uint8 DisPowCount;                  //�ϵ�����������
uint8 DisLogFlash;                  //��̬��ʾ"��ˮ�ı�����"
const uint8 C_ScanCom[] = {0x1e,0x1d,0x1b,0x17,0x0f};

void DisplayDrive(void);
void WriteAByteTo595(uint8 indata); //�� 74HC595��д��һ�����ݡ�
void SetByteOut595(void);           //�� 74HC595��������͵�����������
void DisPP1Filter(void);                //PP1��о��ʾ
void DisC1Filter(void);             //C1��о��ʾ
void DisPP2Filter(void);                //PP2��о��ʾ
void DisROFilter(void);             //RO��о��ʾ
void DisCUFFilter(void);                //CUF��о��ʾ

extern uint8 SetMode;           //��о��λ����ģʽ��
extern uint8 SelfChekDis;       //�Լ�ǰȫ����ʾ1S��ʱ
extern uint8 DisTime;               //���ڿ�����ʾˢ����ʱ����
extern uint16 CxTime;               //��ϴʱ���ʱ��
extern uint16 life[LIFE_DATA_AMOUNT];
extern uint16 XieYiaTime;           //йѹʱ�䡣
extern uint16 WriteFlashDelay;  //дflash��ʱ��
extern BYTE flag1;
extern void delayus(uint8);
#endif


