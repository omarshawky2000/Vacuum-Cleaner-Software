#include "../Main/main.h"

/* Motor_Update period */
#define Motor_PERIOD_MS   (10)
#define Margin_Set_Angle   (5)
#define Soft_Switching_Mode       (0)
#define Harmonic_Reduction_Mode   (1)
#define REST       (0)
#define FIRED   (1)
#define Starting_Speed   (170)
#define Low_Speed        (140)
#define Medium_Speed     (90)
#define High_Speed       (10)
#define Full_Period      (180)


void Motor_SetAngle(uint32_t Angle);
void Motor_Update(void) ;
void Motor_idle(void);
void Motor_Fire(void);
void Motor_Init(void);
unsigned char Check_State(void);