//
// Created by Никита Смирнов on 20.03.2022.
//

#define MAX_PARALLEL_SIZE 20

//при большом размере массива (200) перестает работать. не помещается в память
uint8_t REAL_PARALLEL_SIZE = 0;
uint16_t PARALLEL_MAX_DELAY = 0;
uint8_t PARALLEL_TO_EXECUTES[MAX_PARALLEL_SIZE];
uint16_t PARALLEL_INIT_DELAYS[MAX_PARALLEL_SIZE];
uint16_t PARALLEL_DELAYS[MAX_PARALLEL_SIZE];

void (*PARALLEL_EXECS[MAX_PARALLEL_SIZE])(uint8_t);


void addParallelProcess(
        uint8_t toExecute,
        uint16_t initDelayMs,
        uint16_t delayMs,
        void (*exec)(uint8_t)
) {
    PARALLEL_TO_EXECUTES[REAL_PARALLEL_SIZE] = toExecute;
    PARALLEL_INIT_DELAYS[REAL_PARALLEL_SIZE] = initDelayMs;
    PARALLEL_DELAYS[REAL_PARALLEL_SIZE] = delayMs;
    PARALLEL_EXECS[REAL_PARALLEL_SIZE] = exec;
    if (delayMs > PARALLEL_MAX_DELAY) {
        PARALLEL_MAX_DELAY = delayMs;
    }

    ++REAL_PARALLEL_SIZE;
}


_Noreturn void runParallelProcesses() {
    uint16_t currentTime = 0; // may be at range from 0 to {PARALLEL_MAX_DELAY}

    while (TRUE) {
        uint16_t delay = PARALLEL_MAX_DELAY;

        for (uint8_t i = 0; i < REAL_PARALLEL_SIZE; ++i) {
            if (PARALLEL_TO_EXECUTES[i]) {
                PARALLEL_EXECS[i](i);
                PARALLEL_TO_EXECUTES[i] = FALSE;
            }

            uint16_t delayForOp = PARALLEL_DELAYS[i] - ((currentTime + PARALLEL_INIT_DELAYS[i]) % PARALLEL_DELAYS[i]);
            if (delay == delayForOp) {
                PARALLEL_TO_EXECUTES[i] = TRUE;
            } else if (delay > delayForOp) {
                delay = delayForOp;
                for (uint8_t disI = 0; disI < i; ++disI) { //disable executes for all previous elements
                    PARALLEL_TO_EXECUTES[disI] = FALSE;
                }
                PARALLEL_TO_EXECUTES[i] = TRUE;
            }
        }
        currentTime = (currentTime + delay) % PARALLEL_MAX_DELAY;
        _delay_ms(delay);
    }
}