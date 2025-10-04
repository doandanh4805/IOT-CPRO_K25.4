#ifndef SPWS_CONTROLLER_H
#define SPWS_CONTROLLER_H
#include "config.h"

void SPWS_RunAutoMode(SystemState_t *state, SystemSettings_t *settings, SensorData_t *data);
void SPWS_RunManualMode(SystemState_t *state, SystemSettings_t *settings);
void SPWS_UpdateLED(SystemState_t *state);
void SPWS_PrintStatus(SystemState_t *state, SensorData_t *data);

#endif
