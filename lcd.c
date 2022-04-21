#include "twi.h"
#include "lcd.h"

uint8_t state_lcd = 0; //состояние управляющих битов (P0-P3)
#define I2C_ADDR 0b0100111 //0x27
#define I2C_WADDR I2C_ADDR<<1 //битовый сдвиг влево 0x4e

#define LCD_RS_SET TWI_TransmitByAddr(state_lcd |= 0x01, I2C_WADDR)
#define LCD_RS_CLR TWI_TransmitByAddr(state_lcd &= ~0x01, I2C_WADDR)
#define LCD_RW_SET TWI_TransmitByAddr(state_lcd |= 0x02, I2C_WADDR)
#define LCD_RW_CLR TWI_TransmitByAddr(state_lcd &= ~0x02, I2C_WADDR)
#define LCD_E_SET TWI_TransmitByAddr(state_lcd |= 0x04, I2C_WADDR)
#define LCD_E_CLR TWI_TransmitByAddr(state_lcd &= ~0x04, I2C_WADDR)
#define LCD_BACKLIGHT_SET TWI_TransmitByAddr(state_lcd |= 0x08, I2C_WADDR)
#define LCD_BACKLIGHT_CLR TWI_TransmitByAddr(state_lcd &= ~0x08, I2C_WADDR)


void LCD_Init(void) {
    sendHalfByte(0b00000011);
    _delay_ms(5);
    sendHalfByte(0b00000011);
    _delay_us(100);
    sendHalfByte(0b00000011);
    _delay_ms(1);
    sendHalfByte(0b00000010);
	_delay_ms(1);
	sendReadByte(0b00101000); // Data 4bit, Line 2, Font 5x8
    _delay_ms(1);
    sendReadByte(0b00001111); //Display ON, Cursor ON, Blink ON
    _delay_ms(1);

    LCD_BACKLIGHT_SET;

	LCD_RW_CLR; //LCD Write ON
}

void sendHalfByte(unsigned char c) {
    c <<= 4;

    LCD_E_SET;
    _delay_us(50);
    state_lcd &= ~0xF0;
    TWI_TransmitByAddr(state_lcd |= c, I2C_WADDR);
    LCD_E_CLR;
    _delay_us(50);
}

void sendReadByte(unsigned char c) {
    LCD_RS_CLR;
    unsigned char hc = c >> 4;
    sendHalfByte(hc);
    sendHalfByte(c);
}

void sendWriteByte(unsigned char c) {
    LCD_RS_SET;
    unsigned char hc = c >> 4;
    sendHalfByte(hc);
    sendHalfByte(c);
}

void LCD_sendString(char s[]) {
    int n;
    for (n = 0; s[n] != '\0'; n++)
        sendWriteByte(s[n]);
}

void LCD_setPosition(unsigned char x, unsigned char y) {
    switch (y) {
        case 0:
            sendReadByte(x | 0x80);
            break;
        case 1:
            sendReadByte((0x40 + x) | 0x80);
            break;
        case 2:
            sendReadByte((0x10 + x) | 0x80);
            break;
        case 3:
            sendReadByte((0x50 + x) | 0x80);
            break;
    }
}

void LCD_clear(void) {
    sendReadByte(0x01);
    _delay_ms(5);
}