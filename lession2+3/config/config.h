#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

/* Cấu hình mặc định */
#define DEFAULT_MIN_MOISTURE_PERCENT   30    /* tưới khi <= 30% */
#define DEFAULT_MAX_MOISTURE_PERCENT   60    /* dừng khi >= 60% */
#define DEFAULT_WATERING_SECONDS       20    /* thời gian tưới tối đa (giây) */
#define DEFAULT_SENSOR_CYCLE_SECONDS   10    /* chu kỳ kiểm tra cảm biến (giây) */
#define DEFAULT_MANUAL_WATER_SECONDS   10    /* tưới thủ công mặc định (giây) */
#define STATUS_REPORT_INTERVAL_SEC     30    /* gửi báo cáo định kỳ (giây) */

#endif /* CONFIG_H */
