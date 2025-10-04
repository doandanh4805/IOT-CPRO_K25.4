#ifndef HAL_ACTUATORS_H
#define HAL_ACTUATORS_H
#include "config.h"
void TurnPumpOn(SystemState_t *state);
void TurnPumpOff(SystemState_t *state);
void UpdateLED(LedState_t ledState);
#endif