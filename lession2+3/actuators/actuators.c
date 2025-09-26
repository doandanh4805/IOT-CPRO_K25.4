#include "actuators.h"
#include <stdio.h>
#include <time.h>

/* Internal state (module scope) */
static PumpState_t pump_state = PUMP_OFF;
static LedState_t led_state = LED_NORMAL;

/* This variable is used by sensor simulation to know pump state */
int hardware_pump_state_for_sensor_sim = 0;

void actuators_init(void) {
    pump_state = PUMP_OFF;
    led_state = LED_NORMAL;
    hardware_pump_state_for_sensor_sim = 0;
    printf("[ACT] Actuators initialized: pump OFF, LED NORMAL\n");
}

void turn_pump_on(void) {
    if (pump_state == PUMP_ON) return;
    pump_state = PUMP_ON;
    hardware_pump_state_for_sensor_sim = 1;
    printf("[ACT] PUMP -> ON (starting). Time=%ld\n", time(NULL));
}

void turn_pump_off(void) {
    if (pump_state == PUMP_OFF) return;
    pump_state = PUMP_OFF;
    hardware_pump_state_for_sensor_sim = 0;
    printf("[ACT] PUMP -> OFF (stopped). Time=%ld\n", time(NULL));
}

PumpState_t actuators_get_pump_state(void) {
    return pump_state;
}

void set_led_state(LedState_t st) {
    if (led_state == st) return;
    led_state = st;
    const char *s = "UNKNOWN";
    switch (st) {
        case LED_NORMAL: s = "NORMAL (Green)"; break;
        case LED_WATERING: s = "WATERING (Yellow)"; break;
        case LED_LOW_MOISTURE_ALERT: s = "LOW_MOISTURE_ALERT (Blink Red)"; break;
        case LED_ERROR: s = "ERROR (Red)"; break;
    }
    printf("[ACT] LED set -> %s\n", s);
}

LedState_t actuators_get_led_state(void) {
    return led_state;
}

void notify_status(const char *msg) {
    /* Mô phỏng gửi thông báo: in ra console */
    printf("[NOTIFY] %s\n", msg);
}
