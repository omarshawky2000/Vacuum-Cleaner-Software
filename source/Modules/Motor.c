#include "../Main/main.h"
#include "../Port/Port.h"
#include "../Modules/Timer.h"
#include "../Modules/SW.h"
#include "../Modules/Motor.h"
#include "stm32f4xx_ll_gpio.h"




/* Angle variables */
uint32_t Set_Angle;
uint32_t Target_Angle;
uint32_t Current_Angle;
unsigned char State;											// state indicating on which mode the motor is currently operating
unsigned char Motor_state = REST ;				// Variable that represent the firing of the GPIO PI

/* Initializing Motor parameters */
void  Motor_Init(void){
	 /* Enable peripheral clock */
   MOTOR_ENABLE_CLOCK;
   

   LL_GPIO_InitTypeDef Motor_GPIO;
   Motor_GPIO.Pin        = MOTOR_PIN;
   Motor_GPIO.Mode       = LL_GPIO_MODE_INPUT;
   Motor_GPIO.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
   Motor_GPIO.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
   Motor_GPIO.Pull       = LL_GPIO_PULL_NO;
   Motor_GPIO.Alternate  = LL_GPIO_AF_0;
   LL_GPIO_Init(MOTOR_PORT,&Motor_GPIO);
	 LL_GPIO_ResetOutputPin(MOTOR_PORT,MOTOR_PIN);
	
	 /* setting the default conditions of the motor at startup */
   State = Soft_Switching_Mode;
	 Set_Angle = Starting_Speed;
	 Target_Angle = Medium_Speed;
}

/* Function to fire the motor GPIO PIN */
void Motor_Fire(void)
	{
		LL_GPIO_SetOutputPin(MOTOR_PORT,MOTOR_PIN);
		Motor_state = FIRED;
  }

/* Function to reset the motor GPIO PIN */
void Motor_idle(void)
	{
		LL_GPIO_ResetOutputPin(MOTOR_PORT,MOTOR_PIN);
		Motor_state = REST;
  }
	
/* Function to set the motor firing angle */
void Motor_SetAngle(uint32_t Angle){
	Target_Angle = Angle;
}

/* Updating the values of the motor parameters according to the operating mode */
void Motor_Update(void)
	{
		/* Defining a Simple Toggler to switch between adding and subtracting the offset for harmonic reduction */
		static unsigned char toggler = 0;
		State = Check_State();
		/* Updating in Harmonic reduction mode */
		if(State == Harmonic_Reduction_Mode)
			{
				if(toggler % 2 == 0){Set_Angle = Target_Angle + Margin_Set_Angle; }
				else{ Set_Angle = Target_Angle - Margin_Set_Angle;}
				toggler ++;
				if(toggler == 2){toggler=0;} 
		  }
		/* Updating in soft switching mode */
		if(State == Soft_Switching_Mode)
			{
				if(Set_Angle < Target_Angle){Set_Angle ++; }
				else{ Set_Angle --;}
				Current_Angle = Set_Angle;
		  }
}

/* Function that return the expectedd operating mode given a certain set angle */
 unsigned char Check_State(void)
	{
		if(Current_Angle == Target_Angle)
				{
				return Harmonic_Reduction_Mode;
			}
			else
				{
			return Soft_Switching_Mode;
			}
	}
	