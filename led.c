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

void ledParallel() {
    const uint8_t delay = 200;

    DDRA = 0xff; // set pin as output
    const uint8_t size = sizeof(pins)/sizeof(uint8_t);

    for (uint8_t i = 0; i < size; ++i) {
        addParallelProcess(FALSE, i * delay, size * delay, togglePinOnPortA);
    }
}
