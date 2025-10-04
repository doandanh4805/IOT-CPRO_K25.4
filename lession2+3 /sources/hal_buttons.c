#include <stdio.h>
#include <stdlib.h>
#include "hal_buttons.h"

bool IsModeButtonPressed(void) {
    return rand() % 1000 == 0; /*Returns true with a 1/1000 probability (0.1%) to mimic a rare press*/
}

bool IsManualWateringPressed(void) {
    return rand() % 500 == 0;  /*Returns true with a 1/500 probability (0.2%) to mimic a button press*/
}
