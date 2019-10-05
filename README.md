# STM8S TIM4 Periodic Timer

## What is it?

It is a programmable interval timer implementation for STM8S using TIM4 as an interrupt source.

## Why the implementation is so specific? No hardware abstraction?

The whole project is the hardware abstraction for STM8S.
I could create the same thing for AVR, MCS-51, etc.
And each of them will be easily interchanged based on an underlying CPU.

This library promotes composablity over genericity.

## Why TIM4?

TIM4 is the least powerful timer of STM8 that fits the bill. I could create a similar project using another timer if a situation arises.
But, for now, TIM4 should be good for most of the cases.

## Source code dependencies

* [STM8S header](https://github.com/the-cave/stm8s-header)

## How to use this?

Just include the header to your project.
~~~c
#include "tim4_periodic_timer.h"
~~~
Declaring what to do when the timer tick.
~~~c
// For example toggle pin B5
uint8_t count = 0;
void ms_handler() {
  count++;
  if (count)
    return;
  ChgBit(GPIOB->ODR, 5);
}
~~~
And setup the timer
~~~c
CONST Tim4PeriodicTimer_Config ms_timer_config = {
    // tick every 1 ms if the CPU runs at 2MHz
    .prescaler = TIM4_PRESCALER_16,
    .reload_value = (0x100 - 125),
    // point to the function we declared earlier
    .ticked = &ms_handler,
};

int main() {
  // most of the functions here has been defined in "stm8s.h"
  // (in STM8S header library)
  disableInterrupts();
  SetBit(GPIOB->DDR, 5);
  SetBit(GPIOB->ODR, 5);
  tim4_periodic_timer__setup(&ms_timer_config);
  enableInterrupts();
  for (;;) {
    wfi();
  }
}
~~~

## Build recommendations

The opinionated way to build this library is by using the [Universal STM8 Builder](https://github.com/midnight-wonderer/universal-stm8-builder).
You can have it your way if you are also opinionated yourself.

## License

STM8S TIM4 Periodic Timer is released under the [BSD 3-Clause License](LICENSE.md). :tada:
