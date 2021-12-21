#ifndef __INTERRUPT__
#define __INTERRUPT__

#include "struct.h"

void button_interrupt(void* isr_context);
void lcd_refresh_interrupt(void* isr_context);
void switch_settings_interrupt(void* isr_context);
void adding_interrupt(void* isr_context);

#endif
