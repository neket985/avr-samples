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

uint16_t max(uint16_t (*arr)[], uint8_t arrSize) {
    uint16_t result = 0;
    for (uint8_t i = 0; i < arrSize; ++i) {
        if ((*arr)[i] > result) {
            result = (*arr)[i];
        }
    }
    return result;
}

_Noreturn void parallelProcess(
        uint8_t operationsCount,
        uint8_t (*toExecutes)[],
        uint16_t (*initDelaysMs)[],
        uint16_t (*delaysMs)[],
        void (*exec)(uint8_t)
) {
    const uint16_t maxDelay = max(delaysMs, operationsCount);

    uint16_t currentTime = 0; // may be at range from 0 to {maxDelay}

    while (TRUE) {
        uint16_t delay = maxDelay;

        for (uint8_t i = 0; i < operationsCount; ++i) {
            if ((*toExecutes)[i]) {
                exec(i);
                (*toExecutes)[i] = FALSE;
            }

            uint16_t delayForOp = (*delaysMs)[i] - ((currentTime + (*initDelaysMs)[i]) % (*delaysMs)[i]);
            if (delay == delayForOp) {
                (*toExecutes)[i] = TRUE;
            }
            if (delay > delayForOp) {
                delay = delayForOp;
                for (uint8_t disI = 0; disI < i; ++disI) { //disable executes for all previous elements
                    (*toExecutes)[disI] = FALSE;
                }
                (*toExecutes)[i] = TRUE;
            }
        }
        currentTime = (currentTime + delay) % maxDelay;
        _delay_ms(delay);
    }
}
