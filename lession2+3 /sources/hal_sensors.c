#include <stdio.h>
#include "hal_sensors.h"

void ReadSensors(SensorData_t *data) {
    /*simulate sensor values*/
    data->soilMoisturePercent = (rand() % 101);   // 0–100%
    data->airTemperatureCelsius = 25 + (rand() % 5); // 25–30°C
}