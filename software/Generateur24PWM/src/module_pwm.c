#include "module_pwm.h"

void apply_t_on_on_all(int t_on){
	IOWR(MODMULTIPWMDRIVER_0_BASE,MODMULTIPWMDRIVER_0_BASE_TON_REG,t_on);
	IOWR(MODMULTIPWMDRIVER_0_BASE,MODMULTIPWMDRIVER_0_BASE_NLATCH_REG,0x00000000);
	IOWR(MODMULTIPWMDRIVER_0_BASE,MODMULTIPWMDRIVER_0_BASE_NLATCH_REG,0xFFFFFFFF);
}

void apply_t_on_on_channel(int t_on,int channel){
	IOWR(MODMULTIPWMDRIVER_0_BASE,MODMULTIPWMDRIVER_0_BASE_TON_REG,t_on);
	IOWR(MODMULTIPWMDRIVER_0_BASE,MODMULTIPWMDRIVER_0_BASE_NLATCH_REG,~(0xFFFFFFFF & 0b1<<channel));
	IOWR(MODMULTIPWMDRIVER_0_BASE,MODMULTIPWMDRIVER_0_BASE_NLATCH_REG,0xFFFFFFFF);
}

void enable_pwm_channel(MainDataType* mainData,int channel){
	//IOWR(MODMULTIPWMDRIVER_0_BASE,MODMULTIPWMDRIVER_0_BASE_OE_REG,(0b1<<23)+(0b1<<22));
	unsigned long int data=0;
	for(int index =0; index < PWM_NUMBER; index++){
		if(channel == index){
			data += 0b1<<index;
			mainData->all_pwm[channel].status = true;
		}else if(mainData->all_pwm[index].status){
			data += 0b1<<index;
		}
	}
	IOWR(MODMULTIPWMDRIVER_0_BASE,MODMULTIPWMDRIVER_0_BASE_OE_REG,data);
}

void disable_pwm_channel(MainDataType* mainData,int channel){
	unsigned long int data;
	for(int index; index < PWM_NUMBER; index++){
		if(channel == index){
			mainData->all_pwm[channel].status = false;
		}else if(mainData->all_pwm[index].status){
			data += 0b1<<index;
		}
	}
	IOWR(MODMULTIPWMDRIVER_0_BASE,MODMULTIPWMDRIVER_0_BASE_OE_REG,data);
}

void disable_all_pwm_channel(MainDataType* mainData){
	IOWR(MODMULTIPWMDRIVER_0_BASE,MODMULTIPWMDRIVER_0_BASE_OE_REG,0);
}
