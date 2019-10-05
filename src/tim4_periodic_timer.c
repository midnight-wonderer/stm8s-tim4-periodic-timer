// Copyright (c) 2019 Sarun Rattanasiri
// under the 3-Clause BSD License
// https://opensource.org/licenses/BSD-3-Clause

#include "tim4_periodic_timer.h"

void (*tick_handler)();

void tim4_periodic_timer__setup(Tim4PeriodicTimer_Config* config) {
  TIM4->PSCR = config->prescaler;
  TIM4->ARR = config->reload_value;
  TIM4->CNTR = 0;
  tick_handler = config->ticked;
  if (!tick_handler) {
    return;
  }
  TIM4->IER = 0x01;
  TIM4->CR1 = 0x85;
}

INTERRUPT_HANDLER(tim4_periodic_timer__tick, ITC_IRQ_TIM4_OVF) {
  TIM4->SR1 &= ~1;
  tick_handler();
}
