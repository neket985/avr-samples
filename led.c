_Noreturn void led(void) {
    DDRA = 0xff; // set pin as output
    while (1) {
        togglePins(&PORTA);
        _delay_ms(1000); // busy wait, 500ms
    }
}


const uint8_t pins[] = {PIN0, PIN1, PIN2, PIN3, PIN3, PIN2, PIN1, PIN0};

void togglePinOnPortA(uint8_t i) {
    togglePin(&PORTA, pins[i]);
}

_Noreturn void unsinkLed(void) {
    const uint8_t delay = 200;

    DDRA = 0xff; // set pin as output
    uint8_t toExecutes[] = {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE};
    const uint8_t size = sizeof(toExecutes);
    uint16_t initDelaysMs[] = {0 * delay, 1 * delay, 2 * delay, 3 * delay, 4 * delay, 5 * delay, 6 * delay, 7 * delay};
    uint16_t delaysMs[] = {size * delay, size * delay, size * delay, size * delay, size * delay, size * delay,
                           size * delay, size * delay};

    parallelProcess(
            size,
            &toExecutes,
            &initDelaysMs,
            &delaysMs,
            togglePinOnPortA
    );
}

