#include "../Main/main.h"
#include "../Modules/Timer.h"
#include "../Modules/SW.h"
#include "../Modules/Display.h"
#include "../Modules/Motor.h"
#include "../Modules/Led.h"
#include "../Port/Port.h"
#include "stm32f4xx_ll_tim.h"
#include "stm32f4xx.h"


// For debugging only (For logic analyzer)
volatile uint32_t tick = 0;
extern uint32_t Set_Angle;
extern unsigned char Pressed_Sw_Flag ;
unsigned char Period_Flag = DOWN;
LL_TIM_InitTypeDef TIMER2;



// Initializing the systick timer
void TMR_Init(void)
{
   // System clock frequency = 16 MHz
   // Tick Period = 10 ms
   SysTick_Config(16*TMR_TICK_MS*1000);
   TMR_Stop();
}

// Initializing timer 2 (Note: didn't work due to simulation limitations)
void TMRA_Init(void)
{  
	 
	 RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;  // Enable Timer 2 clock
	 TIMER2.Prescaler          =  (uint16_t)0x0000;
   TIMER2.CounterMode        =   LL_TIM_COUNTERMODE_UP;
   TIMER2.Autoreload         =   0x0000ffffU;
   TIMER2.ClockDivision      =   LL_TIM_CLOCKDIVISION_DIV1;
   TIMER2.RepetitionCounter  =   (uint8_t)0x00;
   LL_TIM_Init(TIMER_PORT, &TIMER2 );
	 LL_TIM_EnableCounter(TIMER_PORT);
	 LL_TIM_EnableARRPreload(TIMER_PORT);
	 LL_TIM_SetUpdateSource(TIMER_PORT , LL_TIM_UPDATESOURCE_COUNTER);
	 TIM2->EGR |= (1<<0);
   NVIC_EnableIRQ(TIM2_IRQn);

}
// starting systick timer
void TMR_Start(void)
{
   SysTick->CTRL |= (0x03);
}

// stoping systick timer
void TMR_Stop(void)
{
   SysTick->CTRL &= ~(0x03);
}

//Systick ISR Handler
void SysTick_Handler(void)
{
	
	 /*Defining two static variables that will be used to keep track of different states*/
	 static uint32_t Current_Degree = 0 ;
	 static uint16_t Debouncer_Counter = 0 ;
	
	 Current_Degree ++;
	
	/*Lowering the Period flag at the start of new cycle*/
	 if(Period_Flag == RAISED){ Period_Flag = DOWN;}
	
	/*ensuring that the motor GPIO pin is kept at low*/
	 Motor_idle();
	
	/*Firing Motor GPIO Pin when the current Degree equals to the Set_Angle*/
	 if(Current_Degree == Set_Angle)
		{
			Motor_Fire();
	  }
	
	/*Raising the period flag and reseting the degrees counter at full period*/
	 if(Current_Degree == Full_Period)
		 {
			 Period_Flag = RAISED;
			 Current_Degree = 0;
		 }

	 /* Debouncer counter for the Switches*/
	if(Pressed_Sw_Flag == RAISED)
		{
			if(Debouncer_Counter == Debounce_Time)
			{
			Pressed_Sw_Flag = DOWN; Debouncer_Counter = 0; 
			}
			Debouncer_Counter ++;
		}

}

