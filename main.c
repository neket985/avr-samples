#define F_CPU 8000000UL

#include <avr/io.h>

#define __DELAY_BACKWARD_COMPATIBLE__

#include <util/delay.h>

//#include "helper/helper.c"
//#include "helper/parallel.c"

//#include "servo.c"
//#include "led.c"
#include "twi.c"
#include "lcd.c"

int main(void) {
//    servoSimple();
//    ledParallel();
//    servoParallel();

//    runParallelProcesses();

    TWI_Init();
    _delay_ms(50);  //wait after power on
    LCD_Init();

    _delay_ms(500);
    LCD_clear();
    LCD_sendString("hui");
}
