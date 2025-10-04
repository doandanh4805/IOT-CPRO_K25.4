#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "config.h"
#include "spws_controller.h"
#include "hal_buttons.h"

SystemState_t sysState;
SystemSettings_t sysSettings;
SensorData_t sensorData;

void System_Init() {
    sysSettings.minMoistureThreshold = 30.0f;
    sysSettings.maxMoistureThreshold = 70.0f;
    sysSettings.maxWateringDuration_s = 10;
    sysSettings.sensorReadInterval_s = 2;
    sysSettings.manualWateringDuration_s = 5;

    sysState.currentMode = MODE_AUTO;
    sysState.pumpState = PUMP_OFF;
    sysState.ledState = LED_NORMAL;
    sysState.wateringTimeCounter = 0;
    sysState.sensorCheckCounter = 0;

    printf("[INIT] System Initialized. Mode=AUTO\n");
}

int main() {
    System_Init();

    while (1) {
        if (IsModeButtonPressed()) {
            sysState.currentMode = (sysState.currentMode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
            printf("[EVENT] Mode changed to %s\n", sysState.currentMode == MODE_AUTO ? "AUTO" : "MANUAL");
            TurnPumpOff(&sysState);
        }

        if (sysState.currentMode == MODE_AUTO)
            SPWS_RunAutoMode(&sysState, &sysSettings, &sensorData);
        else
            SPWS_RunManualMode(&sysState, &sysSettings);

        SPWS_UpdateLED(&sysState);
        SPWS_PrintStatus(&sysState, &sensorData);

        sleep(sysSettings.sensorReadInterval_s);
    }

    return 0;
}
