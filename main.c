#define F_CPU 8000000UL

#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

#include "helper/helper.c"
#include "helper/parallel.c"

#include "servo.c"
#include "led.c"

int main(void)
{
//    servoSimple();
    ledParallel();
    servoParallel();

    runParallelProcesses();
}
