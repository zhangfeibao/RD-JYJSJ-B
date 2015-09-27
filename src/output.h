#ifndef output_h
#define output_h
uint8 BuzCountTotal;        //蜂鸣器响的总次数。
uint8 BuzOnTotal;           //蜂鸣器响的时间总数。
uint8 BuzOffTotal;          //蜂鸣器停的时间总数。
uint8 BuzOnTime;            //蜂鸣器响计时
uint8 BuzOffTime;           //蜂鸣器停止计时。
uint8 SmCount;              //水满次数计数。
uint16 CxTime;              //冲洗时间计时。
uint16 HiSwitchCheckT;      //高压开关检测时间。
uint16 HiSwitchCheckT2;     //高压开关检测时间。
uint16 XieYiaTime;          //泄压时间。
uint16 ZjTime;              //自检计时。

void BeepDeal(void);
void OutputDeal(void);
void BeepSet(uint8 total,uint16 ontotal,uint8 offtotal);

extern BYTE flag0;
extern BYTE flag1;
extern BYTE flag4;
extern uint8 ZjMode;            //自检模式寄存器。
extern uint8 DisPowCount;       //上电闪动次数。

#endif


