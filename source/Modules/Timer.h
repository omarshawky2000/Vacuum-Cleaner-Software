#ifndef __TIMER_H__
#define __TIMER_H__

#include "../Main/main.h"
#include "../Modules/Uart.h"

#define TMR_TICK_MS				(0.055)   // Period That Equates to one Degree of firing angles
#define PERIOD_TICK_MS		 (10)
#define RAISED             (1)
#define DOWN               (0)
#define Debounce_Time     (3000)

void TMR_Init(void);
void TMRA_Init(void);
void TMR_Start(void);
void TMR_Stop(void);
void SysTick_Handler(void);

#endif // __TIMER_H__
