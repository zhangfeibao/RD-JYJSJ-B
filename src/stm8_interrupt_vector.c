





                           #include "def.h"
#include "STM8S103F3P.h"
#include "stm8_interrupt_vector.h"

/*  BASIC INTERRUPT VECTOR TABLE FOR STM8 devices
 *  Copyright (c) 2007 STMicroelectronics
 */

typedef void @far (*interrupt_handler_t)(void);

struct interrupt_vector {
    unsigned char interrupt_instruction;
    interrupt_handler_t interrupt_handler;
};

@far @interrupt void TIM4IRQ (void)         // 125us中断一次
{
    TIM4_SR = 0x00;
    Timer1msCount ++;
//  if(Timer1msCount >=16)
//  if(Timer1msCount >=4)
//  if(Timer1msCount >=40)
//  if(Timer1msCount >=32)
/// if(Timer1msCount >=36)
//  if(Timer1msCount >=34)
    if(Timer1msCount >= DisTime)
    {
    // 1ms 计数。
        Timer1msCount = 0;
        f_DisDrive = 1;
    //  DisplayDrive();
    }

    Timer2msCount ++;

    //蜂鸣器:
    if(f_beep_on)
    {
        if(++BuzBeepTime >= 2)
        {
            BuzBeepTime = 0;
            PA_ODR ^= BIT3;
        }
    }
    else
    {
        PA_ODR &= ~BIT3;
    }
}

@far @interrupt void NonHandledInterrupt (void)
{
    /* in order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction
    */
    return;
}

extern void _stext();     /* startup routine */

struct interrupt_vector const _vectab[] = {
    {0x82, (interrupt_handler_t)_stext}, /* reset */
    {0x82, NonHandledInterrupt}, /* trap  */
    {0x82, NonHandledInterrupt}, /* irq0  */
    {0x82, NonHandledInterrupt}, /* irq1  */
    {0x82, NonHandledInterrupt}, /* irq2  */
    {0x82, NonHandledInterrupt}, /* irq3  */
    {0x82, NonHandledInterrupt}, /* irq4  */
    {0x82, NonHandledInterrupt}, /* irq5  */
    {0x82, NonHandledInterrupt}, /* irq6  */
    {0x82, NonHandledInterrupt}, /* irq7  */
    {0x82, NonHandledInterrupt}, /* irq8  */
    {0x82, NonHandledInterrupt}, /* irq9  */
    {0x82, NonHandledInterrupt}, /* irq10 */
    {0x82, NonHandledInterrupt}, /* irq11 */
    {0x82, NonHandledInterrupt}, /* irq12 */
    {0x82, NonHandledInterrupt}, /* irq13 */
    {0x82, NonHandledInterrupt}, /* irq14 */
    {0x82, NonHandledInterrupt}, /* irq15 */
    {0x82, NonHandledInterrupt}, /* irq16 */
    {0x82, NonHandledInterrupt}, /* irq17 */
    {0x82, NonHandledInterrupt}, /* irq18 */
    {0x82, NonHandledInterrupt}, /* irq19 */
    {0x82, NonHandledInterrupt}, /* irq20 */
    {0x82, NonHandledInterrupt}, /* irq21 */
    {0x82, NonHandledInterrupt}, /* irq22 */
    {0x82, TIM4IRQ}, /* irq23 */
    {0x82, NonHandledInterrupt}, /* irq24 */
    {0x82, NonHandledInterrupt}, /* irq25 */
    {0x82, NonHandledInterrupt}, /* irq26 */
    {0x82, NonHandledInterrupt}, /* irq27 */
    {0x82, NonHandledInterrupt}, /* irq28 */
    {0x82, NonHandledInterrupt}, /* irq29 */
};

