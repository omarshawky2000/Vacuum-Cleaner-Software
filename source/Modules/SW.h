#ifndef __SW_H__
#define __SW_H__

#include "../Main/main.h"

typedef enum
{
    SW_PLUS,
    SW_MINUS,
    SW_DUST
}tSW;

typedef enum
{
    SW_RELEASED,
    SW_PRE_PRESSED,
    SW_PRESSED,
    SW_PRE_RELEASED
}tSW_State;

void SW_Init(void);
tSW_State SW_GetState(tSW sw);
void SW_Update(void);
tWord SW_GetPressedTime(tSW sw);

#endif // __SW_H__
