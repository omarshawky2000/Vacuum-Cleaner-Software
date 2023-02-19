/**
 * Author : - Omar Shawky Mohamed
						- Omar Mohamed Atfi
						- Mohamed Ayman Mohamed
						
	* Vaccum Cleaner Software that have the following features:-
		1) Soft switching.
		2) Harmonic reduction.
		3) Safety feature using the dust sensor.
							
	* Part of the Swift Act Training Program. (Embedded SW Design).
 **/


#include "../Main/main.h"
#include "../Modules/SW.h"
#include "../Modules/Timer.h"
#include "../Modules/Display.h"
#include "../Modules/Led.h"
#include "../Modules/VC.h"
#include "../Modules/Motor.h"
#include "stdio.h"

///Oscilloscope should monitor C6 and C7 channels

extern char Period_Flag;		//Global Flag that mark the 10 ms timestamp

int main(void)
{   
    /* Initialization */
    printf("Vacuum Cleaner is starting ...\n");
    SW_Init();
    DISP_Init();
    VC_Init();
    Motor_Init();
	
    //Initialize the timer and start it
    TMR_Init();
    TMRA_Init();
    TMR_Start();
	  
    while (1)
    {		
			/* - Updating the values for every module
			   - Motor Update is called first since it has the highest priority to begin without any shifting
				 - VC_Update is called last since it is the least determentistic as it include the debouncing coditioning
			*/
			if(Period_Flag == RAISED)
			{
			Motor_Update();		
			SW_Update();
      DISP_Update();
			VC_Update();
			}
      // Sleep
      __WFI();
    }

    return 0;
}

