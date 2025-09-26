#ifndef SENSORS_H
#define SENSORS_H

#include "types.h"

/* Khởi tạo mô-đun cảm biến (mô phỏng). */
void sensors_init(void);

/* Đọc cảm biến và ghi vào sensor_out */
void sensors_read(SensorData_t *sensor_out);

/* Lấy giá trị đã đọc gần nhất (non-null) */
const SensorData_t* sensors_get_latest(void);

#endif /* SENSORS_H */
