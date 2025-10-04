#include <stdio.h>
#include "hal_actuators.h"

void TurnPumpOn(SystemState_t *state) {
    if (state->pumpState == PUMP_OFF) {
        printf("[ACTUATOR] Pump ON\n");
        state->pumpState = PUMP_ON;
        state->wateringTimeCounter = 0;
    }
}

void TurnPumpOff(SystemState_t *state) {
    if (state->pumpState == PUMP_ON) {
        printf("[ACTUATOR] Pump OFF\n");
        state->pumpState = PUMP_OFF;
    }
}

void UpdateLED(LedState_t ledState) {
    switch (ledState) {
        case LED_NORMAL: printf("[LED] GREEN - NORMAL\n"); break;
        case LED_WATERING: printf("[LED] YELLOW - WATERING\n"); break;
        case LED_LOW_MOISTURE_ALERT: printf("[LED] RED BLINK - LOW MOISTURE\n"); break;
        case LED_ERROR: printf("[LED] RED - ERROR\n"); break;
    }
}