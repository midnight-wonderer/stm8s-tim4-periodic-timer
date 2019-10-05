// Copyright (c) 2019 Sarun Rattanasiri
// under the 3-Clause BSD License
// https://opensource.org/licenses/BSD-3-Clause

#ifndef __TIM4_PERIODIC_TIMER_H
#define __TIM4_PERIODIC_TIMER_H

#include <stdint.h>
#include "stm8s.h"
#include "stm8s_itc.h"
#include "stm8s_tim4.h"

typedef struct _tim4_periodic_timer__config {
  TIM4_Prescaler_TypeDef prescaler;
  uint8_t reload_value;
  void (*ticked)(void);
} Tim4PeriodicTimer_Config;

// example config parameters for 2 MHz PSC
// prescaler = TIM4_PRESCALER_16
// reload_value = (0x100 - 125)

void tim4_periodic_timer__setup(Tim4PeriodicTimer_Config* config);
INTERRUPT_HANDLER(tim4_periodic_timer__tick, ITC_IRQ_TIM4_OVF);

#endif
