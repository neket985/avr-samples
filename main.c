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
    char symbols[][8]={
            {
                0b00000001,
                0b00000010,
                0b00000100,
                0b00001000,
                0b00010000,
                0b00010000,
                0b00001000,
                0b00001100,
            }
    };
    LCD_clear();
    LCD_newChar(&symbols[0][0], 0);
    LCD_setPosition(0, 0);
    sendWriteByte(0);
//    char str[] = { 'a', 0, '\0'};
//    LCD_sendString(str);
//    LCD_sendString("hello");

    _delay_ms(500);

    uint8_t i = 0;
}
