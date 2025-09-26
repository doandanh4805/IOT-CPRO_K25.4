#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "types.h"

/* Khởi tạo GPIO (mô phỏng) */
void actuators_init(void);

/* Bật/tắt bơm */
void turn_pump_on(void);
void turn_pump_off(void);
PumpState_t actuators_get_pump_state(void);

/* Cập nhật LED (mô phỏng) */
void set_led_state(LedState_t st);
LedState_t actuators_get_led_state(void);

/* Gửi thông báo (mô phỏng giao tiếp) */
void notify_status(const char *msg);

#endif /* ACTUATORS_H */
