const uint16_t SERVO_MIN_US = 500;
const uint16_t SERVO_MAX_US = 2400;
const uint16_t SERVO_CYCLE_US = 20000;
const uint8_t SERVO_MAX_ANGLE = 180;
const uint16_t SERVO_ANGLE_STEP_US = (SERVO_MAX_US - SERVO_MIN_US) / SERVO_MAX_ANGLE;

uint16_t servoImpulseUs(int angle) {
    uint16_t result = SERVO_MIN_US + angle * SERVO_ANGLE_STEP_US;

    if(result > SERVO_MAX_US) return SERVO_MAX_US;
    if(result < SERVO_MIN_US) return SERVO_MIN_US;

    return result;
}

_Noreturn void servo() {
    DDRA = 0xff;

    uint8_t i = 0;
    uint8_t angle = 0;
    while (1) {
        ++i;

        uint16_t delayUs;
        if ((angle / SERVO_MAX_US) % 2 == 0) {
            delayUs = servoImpulseUs(angle);
        } else {
            delayUs = servoImpulseUs(SERVO_MAX_ANGLE - angle);
        }
        PORTA = 0xff; //hight
        _delay_us(delayUs);
        PORTA = 0x00; //low
        _delay_us(SERVO_CYCLE_US - delayUs);

        if (i % 10 == 1) {
            angle = (angle + 1) % SERVO_MAX_US;
        }
    }
}

_Noreturn void servoSimple() {
    DDRA = 0xff;

    while (1) {

        _delay_ms(1000);
        PORTA = 0xff; //hight
        _delay_us(SERVO_MAX_US);
        PORTA = 0x00; //low
        _delay_us(SERVO_CYCLE_US);

        _delay_ms(1000);
        PORTA = 0xff; //hight
        _delay_us(SERVO_MIN_US);
        PORTA = 0x00; //low
        _delay_us(SERVO_CYCLE_US);

    }
}


uint8_t lastInState = 0;
uint8_t angle = 0;

void servoExec(uint8_t i) {
    uint8_t inValue = pinValue(&PINA, PIN5);
    if (inValue != lastInState) {
        angle = (angle + 10) % 180;
        lastInState = inValue;
    }

    setPin(&PORTA, PIN4);
    _delay_us(servoImpulseUs(angle));
    unsetPin(&PORTA, PIN4);
}

void servoParallel() {
    DDRA = 0xff; // set pin as output
    unsetPin(&DDRA, PIN7);

    addParallelProcess(FALSE, 0, 50, servoExec);

}