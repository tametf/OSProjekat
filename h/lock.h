#ifndef _lock_h_
#define _lock_h_
#include "timer.h"


extern volatile unsigned int lockFlag;

#define lock {asm pushf;asm cli;}
#define unlock asm popf
//#define lock lockFlag = 0;
//#define unlock lockFlag = 1;

#endif
