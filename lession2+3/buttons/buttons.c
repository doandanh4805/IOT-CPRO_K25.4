#define _POSIX_C_SOURCE 200809L
#include "buttons.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>

/* Non-blocking stdin setup */
static struct termios orig_termios;
static int term_setup = 0;

static void restore_terminal(void) {
    if (term_setup) {
        tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
        term_setup = 0;
    }
}

void buttons_init(void) {
    /* set stdin to non-canonical no-echo */
    if (tcgetattr(STDIN_FILENO, &orig_termios) == 0) {
        struct termios t = orig_termios;
        t.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
        term_setup = 1;
        atexit(restore_terminal);
    }
    /* set non-blocking */
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    printf("[BUTTON] Buttons init. Press 't' = toggle AUTO/MANUAL, 'w' = manual water, 'q' = quit\n");
}

/* Weak default callbacks (can be defined elsewhere) */
void user_pressed_toggle_mode(void) {
    /* default empty */
}
void user_pressed_manual_water(void) {
    /* default empty */
}

int buttons_poll_and_process(void) {
    fd_set set;
    struct timeval tv;
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    int rv = select(STDIN_FILENO + 1, &set, NULL, NULL, &tv);
    if (rv > 0 && FD_ISSET(STDIN_FILENO, &set)) {
        char c = 0;
        ssize_t r = read(STDIN_FILENO, &c, 1);
        if (r > 0) {
            if (c == 't' || c == 'T') {
                printf("[BUTTON] Toggle button pressed\n");
                user_pressed_toggle_mode();
            } else if (c == 'w' || c == 'W') {
                printf("[BUTTON] Manual water button pressed\n");
                user_pressed_manual_water();
            } else if (c == 'q' || c == 'Q') {
                printf("[BUTTON] Quit requested\n");
                return 1;
            } else {
                /* ignore other keys */
            }
        }
    }
    return 0;
}
