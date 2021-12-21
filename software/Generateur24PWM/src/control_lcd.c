#include "control_lcd.h"

void clear_lcd(){
    printf("\x1B[2J");
}