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
	sendByte(0b00101000, 0); // Data 4bit, Line 2, Font 5x8
    _delay_ms(1);
    sendByte(0b00001110, 0); //Display ON, Cursor ON, Blink ON
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
    LCD_E_CLR; // Disable E
    _delay_us(50);

}

void sendByte(unsigned char c, unsigned char mode) {
    if (mode == 0) TWI_TransmitByAddr(state_lcd &= ~0x01, I2C_WADDR);
    else TWI_TransmitByAddr(state_lcd |= 0x01, I2C_WADDR);
    unsigned char hc = 0;
    hc = c >> 4;
    sendHalfByte(hc);
    sendHalfByte(c);
}

void LCD_sendString(char s[]) {
    int n;
    for (n = 0; s[n] != '\0'; n++)
        sendByte(s[n], 1);
}

void LCD_setPosition(unsigned char x, unsigned char y) {
    switch (y) {
        case 0:
            sendByte(x | 0x80, 0);
            break;
        case 1:
            sendByte((0x40 + x) | 0x80, 0);
            break;
        case 2:
            sendByte((0x10 + x) | 0x80, 0);
            break;
        case 3:
            sendByte((0x50 + x) | 0x80, 0);
            break;
    }
}

void LCD_clear(void) {
    sendByte(0x01, 0);
    _delay_ms(5);
}