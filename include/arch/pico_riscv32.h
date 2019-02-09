/*********************************************************************
   PicoTCP. Copyright (c) 2012-2017 Altran Intelligent Systems. Some rights reserved.
   See COPYING, LICENSE.GPLv2 and LICENSE.GPLv3 for usage.

 *********************************************************************/
#define dbg printf
/* #define dbg printf */

/*************************/

/*** MACHINE CONFIGURATION ***/
/* Temporary (POSIX) stuff. */
#include <string.h>
#include <stdio.h>
#include <stdint.h>
//#include "pico_mm.h"

#pragma message "pico_riscv32.h included"

#define pico_zalloc(x) calloc(x, 1)
#define pico_free(x) free(x)


extern uint64_t platform_timer_read_sys( void ); // returns time in us

static inline unsigned long PICO_TIME(void)
{
    return (unsigned long) (platform_timer_read_sys() / 1000000L); 
    //register uint32_t tick = __avr_tick;
    //return tick / 1000;
}

static inline unsigned long PICO_TIME_MS(void)
{
    return (unsigned long) (platform_timer_read_sys() / 1000L); 
}

static inline void PICO_IDLE(void)
{
    //unsigned long tick_now = __avr_tick;
    //while(tick_now == __avr_tick) ;
}

