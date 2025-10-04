#include <stdio.h>
#include "spws_controller.h"
#include "hal_actuators.h"
#include "hal_sensors.h"
#include "hal_buttons.h"

void SPWS_RunAutoMode(SystemState_t *state, SystemSettings_t *settings, SensorData_t *data) {
    ReadSensors(data);

    if (data->soilMoisturePercent < settings->minMoistureThreshold) {
        TurnPumpOn(state);
        state->ledState = LED_WATERING;
    }

    if (state->pumpState == PUMP_ON) {
        state->wateringTimeCounter++;

        if (data->soilMoisturePercent > settings->maxMoistureThreshold ||
            state->wateringTimeCounter > settings->maxWateringDuration_s) {
            TurnPumpOff(state);
        }
    }
}

void SPWS_RunManualMode(SystemState_t *state, SystemSettings_t *settings) {
    if (IsManualWateringPressed()) {
        printf("[INFO] Manual watering started.\n");
        TurnPumpOn(state);
        state->ledState = LED_WATERING;
        for (unsigned int t = 0; t < settings->manualWateringDuration_s; t++) {
            /* Watering simulator*/
        }
        TurnPumpOff(state);
    }
}

void SPWS_UpdateLED(SystemState_t *state) {
    UpdateLED(state->ledState);
}

void SPWS_PrintStatus(SystemState_t *state, SensorData_t *data) {
    printf("[STATUS] Mode: %s | Pump: %s | Soil: %.1f%% | Temp: %.1f°C\n",
           state->currentMode == MODE_AUTO ? "AUTO" : "MANUAL",
           state->pumpState == PUMP_ON ? "ON" : "OFF",
           data->soilMoisturePercent,
           data->airTemperatureCelsius);
}
