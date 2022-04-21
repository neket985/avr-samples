#define F_CPU 8000000UL

#include <avr/io.h>

#define __DELAY_BACKWARD_COMPATIBLE__

#include <util/delay.h>
#include <stdio.h>

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
    LCD_clear();
    LCD_sendString("1234");

    _delay_ms(500);

    uint8_t i = 0;
    char buff[10];
    while (1) {
        sprintf(buff, "%03d", i++);
        LCD_setPosition(5, 1);
        LCD_sendString(buff);
        _delay_ms(1000);
    }
}
