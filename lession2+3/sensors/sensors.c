#include "sensors.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Internal state */
static SensorData_t latest = {50.0f, 25.0f}; /* khởi tạo trung bình */
static int inited = 0;

/* Simple random walk to simulate soil moisture changes */
static float randf_range(float a, float b) {
    return a + ((float)rand() / RAND_MAX) * (b - a);
}

void sensors_init(void) {
    srand((unsigned)time(NULL));
    latest.soil_moisture_percent = randf_range(40.0f, 60.0f);
    latest.temperature_celsius = randf_range(20.0f, 30.0f);
    inited = 1;
    printf("[SENSOR] Initialized: moisture=%.1f%%, temp=%.1fC\n",
           latest.soil_moisture_percent, latest.temperature_celsius);
}

/* Mô phỏng đọc: random walk + small noise; nếu bơm đang on, moisture tăng */
extern int hardware_pump_state_for_sensor_sim; /* được cung cấp từ actuators.c */

void sensors_read(SensorData_t *sensor_out) {
    if (!inited) sensors_init();

    /* Random drift */
    float drift = randf_range(-1.5f, 1.5f);

    /* Nếu bơm đang hoạt động, tăng  moisture nhanh */
    if (hardware_pump_state_for_sensor_sim) {
        drift += randf_range(1.5f, 4.0f);
    } else {
        /* khi không tưới, soil hơi giảm theo thời gian */
        drift += randf_range(-1.0f, 0.5f);
    }

    latest.soil_moisture_percent += drift;
    if (latest.soil_moisture_percent < 0.0f) latest.soil_moisture_percent = 0.0f;
    if (latest.soil_moisture_percent > 100.0f) latest.soil_moisture_percent = 100.0f;

    /* Nhiệt độ thay đổi chậm */
    latest.temperature_celsius += randf_range(-0.3f, 0.3f);
    if (latest.temperature_celsius < -10.0f) latest.temperature_celsius = -10.0f;
    if (latest.temperature_celsius > 60.0f) latest.temperature_celsius = 60.0f;

    /* Lưu và trả về */
    if (sensor_out) {
        *sensor_out = latest;
    }

    printf("[SENSOR] Read: moisture=%.1f%%, temp=%.1fC\n",
           latest.soil_moisture_percent, latest.temperature_celsius);
}

const SensorData_t* sensors_get_latest(void) {
    return &latest;
}
