#ifndef __MODULE_PWM__
#define __MODULE_PWM__

#include "struct.h"

void apply_t_on_on_all(int t_on);
void apply_t_on_on_channel(int t_on,int channel);
void enable_pwm_channel(MainDataType* mainData,int channel);
void disable_pwm_channel(MainDataType* mainData,int channel);
void disable_all_pwm_channel(MainDataType* mainData);

#endif
