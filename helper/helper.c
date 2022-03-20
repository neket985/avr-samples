//
// Created by Никита Смирнов on 19.03.2022.
//

#define TRUE 1
#define FALSE 0

void togglePins(volatile uint8_t *port) {
    *port ^= 0xff; // toggles all pins
}

void togglePin(volatile uint8_t *port, uint8_t pin) {
    *port ^= (1 << pin); // toggles pin
}

void setPin(volatile uint8_t *port, uint8_t pin) {
    *port |= (1 << pin); // toggles pin
}

void unsetPin(volatile uint8_t *port, uint8_t pin) {
    *port &= ~(1 << pin); // toggles pin
}

uint8_t pinValue(const volatile uint8_t *port, uint8_t pin) {
    return (*port & (1 << pin)) >> pin;
}

uint16_t max(uint16_t (*arr)[], uint8_t arrSize) {
    uint16_t result = 0;
    for (uint8_t i = 0; i < arrSize; ++i) {
        if ((*arr)[i] > result) {
            result = (*arr)[i];
        }
    }
    return result;
}

void debug(uint8_t condition) {
    if (condition) {
        setPin(&PORTA, PIN1);
        _delay_ms(2000);
        unsetPin(&PORTA, PIN1);
    }
}