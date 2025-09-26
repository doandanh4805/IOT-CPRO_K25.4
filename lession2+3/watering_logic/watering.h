#ifndef WATERING_LOGIC_H
#define WATERING_LOGIC_H

#include "types.h"

/* Khởi tạo logic */
void watering_logic_init(SystemConfig_t *cfg);

/* Cập nhật logic: gọi định kỳ theo chu kỳ sensor_cycle_seconds.
   current is latest sensor sample. now_sec: current timestamp (seconds). */
void watering_logic_step(const SensorData_t *current, time_t now_sec);

/* Hàm này gửi status định kỳ */
void watering_logic_periodic_report(time_t now_sec);

#endif /* WATERING_LOGIC_H */
