#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

/* Chế độ hệ thống */
typedef enum {
    MODE_AUTO,
    MODE_MANUAL
} SystemMode_t;

/* Trạng thái bơm */
typedef enum {
    PUMP_OFF,
    PUMP_ON
} PumpState_t;

/* Trạng thái LED (biểu diễn bằng enum) */
typedef enum {
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} LedState_t;

/* Dữ liệu cảm biến */
typedef struct {
    float soil_moisture_percent; /* 0.0 - 100.0 */
    float temperature_celsius;
} SensorData_t;

/* Cấu hình có thể thay đổi runtime */
typedef struct {
    uint8_t min_moisture_percent;
    uint8_t max_moisture_percent;
    uint32_t watering_seconds_max;
    uint32_t sensor_cycle_seconds;
    SystemMode_t mode;
} SystemConfig_t;

#endif /* TYPES_H */
