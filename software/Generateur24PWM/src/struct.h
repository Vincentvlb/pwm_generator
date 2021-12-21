#ifndef __STRUCT__
#define __STRUCT__

#include <stdlib.h>
#include <unistd.h>
#include <system.h>
#include <io.h>
#include <altera_avalon_pio_regs.h>
#include <priv/alt_iic_isr_register.h>
#include <altera_avalon_timer_regs.h>
#include <stdio.h>
#include <stdbool.h>

#include "params.h"

typedef struct pwmData{
    int id;
    bool status;
    int t_on;
} PWMDataType;

typedef struct lcdData{
    int ctrl_blinker;
    int blink;
} LCDDataType;

typedef struct mainData{
    int btn[3];
    int pwm_selected;
    LCDDataType* lcdData;
    PWMDataType* all_pwm;
    int setting;
    int delay;
} MainDataType;

LCDDataType* lcd_data_init();
MainDataType* main_data_init();
MainDataType* init();

#endif
