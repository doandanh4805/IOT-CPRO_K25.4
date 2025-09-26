#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "config.h"
#include "types.h"
#include "sensors.h"
#include "actuators.h"
#include "buttons.h"
#include "watering_logic.h"

/* Global system config (static to this file) */
static SystemConfig_t sys_config = {
    .min_moisture_percent = DEFAULT_MIN_MOISTURE_PERCENT,
    .max_moisture_percent = DEFAULT_MAX_MOISTURE_PERCENT,
    .watering_seconds_max = DEFAULT_WATERING_SECONDS,
    .sensor_cycle_seconds = DEFAULT_SENSOR_CYCLE_SECONDS,
    .mode = MODE_AUTO
};

/* Forward declarations for button callbacks (defined here) */
void user_pressed_toggle_mode(void);
void user_pressed_manual_water(void);

/* Also used by watering logic when mode changed */
void on_mode_changed(SystemMode_t new_mode) {
    /* Ensure pump off when switching to manual */
    if (new_mode == MODE_MANUAL) {
        if (actuators_get_pump_state() == PUMP_ON) {
            turn_pump_off();
        }
    }
    /* send notify */
    char buf[128];
    snprintf(buf, sizeof(buf), "Mode changed -> %s",
             (new_mode==MODE_AUTO) ? "AUTO" : "MANUAL");
    notify_status(buf);
}

/* Button callbacks */
void user_pressed_toggle_mode(void) {
    sys_config.mode = (sys_config.mode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
    printf("[MAIN] Mode toggled by user: %s\n", (sys_config.mode==MODE_AUTO) ? "AUTO" : "MANUAL");
    on_mode_changed(sys_config.mode);
}

void user_pressed_manual_water(void) {
    if (sys_config.mode != MODE_MANUAL) {
        notify_status("Manual water ignored: system not in MANUAL mode");
        return;
    }
    /* start pump for DEFAULT_MANUAL_WATER_SECONDS */
    notify_status("Manual watering started");
    turn_pump_on();
    sleep(DEFAULT_MANUAL_WATER_SECONDS);
    turn_pump_off();
    notify_status("Manual watering finished");
}

/* main loop */
int main(void) {
    printf("=== SPWS (Smart Plant Watering System) Simulation ===\n");

    /* init modules */
    actuators_init();
    sensors_init();
    buttons_init();
    watering_logic_init(&sys_config);

    /* Set up extern used in buttons.c (already weakly declared) */
    /* main loop variables */
    time_t last_sensor_time = 0;
    int quit = 0;

    while (!quit) {
        time_t now = time(NULL);

        /* poll buttons (non-blocking). returns 1 if quit requested */
        quit = buttons_poll_and_process();
        if (quit) break;

        /* sensor cycle */
        if ((now - last_sensor_time) >= sys_config.sensor_cycle_seconds) {
            SensorData_t sd;
            sensors_read(&sd);

            /* step logic */
            watering_logic_step(&sd, now);
            last_sensor_time = now;
        }

        /* small sleep to avoid busy loop (0.2s) */
        usleep(200000);
    }

    printf("Exiting SPWS simulation. Goodbye.\n");
    return 0;
}
