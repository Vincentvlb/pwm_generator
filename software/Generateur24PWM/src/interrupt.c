#include "interrupt.h"
#include "control_lcd.h"
#include "control_led.h"

void button_interrupt(void* isr_context){
	MainDataType *mainDataType = isr_context;
	switch(IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_COMMANDE_BASE)){
		case 4:
			if(mainDataType->btn[0]==PENDING_BUTTON || mainDataType->btn[0]==RISING_BUTTON){
				//fprintf(stderr,"Button 1 is push.\n");
				mainDataType->btn[0]=FALLING_BUTTON;
				if(mainDataType->lcdData->ctrl_blinker == T_ON_BLINKS){
					mainDataType->btn[0]=PENDING_RISING_BUTTON;
					if(mainDataType->all_pwm[mainDataType->pwm_selected].t_on > 0)
					mainDataType->all_pwm[mainDataType->pwm_selected].t_on -= 1;
					else mainDataType->all_pwm[mainDataType->pwm_selected].t_on = MAX_T_ON;
					apply_t_on_on_channel(mainDataType->all_pwm[mainDataType->pwm_selected].t_on,mainDataType->pwm_selected);
					IOWR_ALTERA_AVALON_TIMER_CONTROL(ADDER_TIMER_BASE,0x0007);
				}
			}
			else if(mainDataType->btn[0]==FALLING_BUTTON || mainDataType->btn[0]==PENDING_RISING_BUTTON){
				//fprintf(stderr,"Button 1 is release.\n");
				mainDataType->btn[0]=RISING_BUTTON;
				if(mainDataType->lcdData->ctrl_blinker == T_ON_BLINKS){
					/*if(mainDataType->all_pwm[mainDataType->pwm_selected].t_on > 0)
					mainDataType->all_pwm[mainDataType->pwm_selected].t_on -= 1;
					else mainDataType->all_pwm[mainDataType->pwm_selected].t_on = MAX_T_ON;*/
					IOWR_ALTERA_AVALON_TIMER_CONTROL(ADDER_TIMER_BASE,0x000B);
					mainDataType->delay =0;
					mainDataType->btn[0]=PENDING_BUTTON;
				}
				if(mainDataType->lcdData->ctrl_blinker == ON_OFF_BLINKS){
					mainDataType->all_pwm[mainDataType->pwm_selected].status =! mainDataType->all_pwm[mainDataType->pwm_selected].status ;
					if(mainDataType->all_pwm[mainDataType->pwm_selected].status){
						enable_led(mainDataType->pwm_selected);
						enable_pwm_channel(mainDataType,mainDataType->pwm_selected);
					}
					else{
						disable_led(mainDataType->pwm_selected);
						disable_pwm_channel(mainDataType,mainDataType->pwm_selected);
					}
					mainDataType->btn[0]=PENDING_BUTTON;
				}
				if(!mainDataType->setting){
					if(mainDataType->pwm_selected>0)mainDataType->pwm_selected -= 1;
					else mainDataType->pwm_selected = PWM_NUMBER-1;
					mainDataType->btn[0] = PENDING_BUTTON;
				}
			}

		break;
		case 2:
			if(mainDataType->btn[1]==PENDING_BUTTON || mainDataType->btn[1]==RISING_BUTTON){
				//fprintf(stderr,"Button 2 is push.\n");
				mainDataType->btn[1]=FALLING_BUTTON;
				if(mainDataType->lcdData->ctrl_blinker == T_ON_BLINKS){
					mainDataType->btn[1]=PENDING_RISING_BUTTON;
					if(mainDataType->all_pwm[mainDataType->pwm_selected].t_on < MAX_T_ON)
					mainDataType->all_pwm[mainDataType->pwm_selected].t_on += 1;
					else mainDataType->all_pwm[mainDataType->pwm_selected].t_on = 0;
					apply_t_on_on_channel(mainDataType->all_pwm[mainDataType->pwm_selected].t_on,mainDataType->pwm_selected);
					IOWR_ALTERA_AVALON_TIMER_CONTROL(ADDER_TIMER_BASE,0x0007);
				}
			}
			else if(mainDataType->btn[1]==FALLING_BUTTON || mainDataType->btn[1]==PENDING_RISING_BUTTON){
				//fprintf(stderr,"Button 2 is release.\n");
				mainDataType->btn[1]=RISING_BUTTON;
				if(mainDataType->lcdData->ctrl_blinker == T_ON_BLINKS){
					/*if(mainDataType->all_pwm[mainDataType->pwm_selected].t_on < MAX_T_ON)
					mainDataType->all_pwm[mainDataType->pwm_selected].t_on += 1;
					else mainDataType->all_pwm[mainDataType->pwm_selected].t_on = 0;*/
					IOWR_ALTERA_AVALON_TIMER_CONTROL(ADDER_TIMER_BASE,0x000B);
					mainDataType->delay =0;
					mainDataType->btn[0]=PENDING_BUTTON;
				}
				if(mainDataType->lcdData->ctrl_blinker == ON_OFF_BLINKS){
					mainDataType->all_pwm[mainDataType->pwm_selected].status =! mainDataType->all_pwm[mainDataType->pwm_selected].status;
					if(mainDataType->all_pwm[mainDataType->pwm_selected].status){
						enable_led(mainDataType->pwm_selected);
						enable_pwm_channel(mainDataType,mainDataType->pwm_selected);
					}
					else{
						disable_led(mainDataType->pwm_selected);
						disable_pwm_channel(mainDataType,mainDataType->pwm_selected);
					}
					mainDataType->btn[1]=PENDING_BUTTON;
				}
				if(!mainDataType->setting){
					if(mainDataType->pwm_selected<PWM_NUMBER-1)mainDataType->pwm_selected += 1;
					else mainDataType->pwm_selected = 0;
					mainDataType->btn[1] = PENDING_BUTTON;
				}
			}
		break;
		case 1:
			if(mainDataType->btn[2]==PENDING_BUTTON || mainDataType->btn[2]==RISING_BUTTON){
				//fprintf(stderr,"Button 3 is push.\n");
				mainDataType->btn[2]=FALLING_BUTTON;
			}
			else if(mainDataType->btn[2]==FALLING_BUTTON || mainDataType->btn[1]==PENDING_RISING_BUTTON){
				//fprintf(stderr,"Button 3 is release.\n");
				mainDataType->btn[2]=RISING_BUTTON;
				if (mainDataType->setting){
					if(mainDataType->lcdData->ctrl_blinker == ON_OFF_BLINKS){
						mainDataType->lcdData->ctrl_blinker = T_ON_BLINKS;
					}
					else {
						mainDataType->lcdData->ctrl_blinker = ON_OFF_BLINKS;
					}
					mainDataType->btn[2]=PENDING_BUTTON;
				}
			}
		break;
		default:
		break;
	}
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_COMMANDE_BASE,BUTTONS_COMMANDE_RESET_VALUE);
}

void lcd_refresh_interrupt(void* isr_context){
	MainDataType *mainDataType = isr_context;

	clear_lcd();

	if(mainDataType->all_pwm[mainDataType->pwm_selected].id<10) printf("PWM  %d : ",mainDataType->all_pwm[mainDataType->pwm_selected].id);
	else printf("PWM %d : ",mainDataType->all_pwm[mainDataType->pwm_selected].id);

	if((mainDataType->lcdData->ctrl_blinker==ON_OFF_BLINKS && mainDataType->lcdData->blink<DIVIDE_FREQ_FOR_BLINKS) || mainDataType->lcdData->ctrl_blinker!=ON_OFF_BLINKS){
		if(mainDataType->all_pwm[mainDataType->pwm_selected].status) printf("ON");
		else printf("OFF");
	}

	if((mainDataType->lcdData->ctrl_blinker==T_ON_BLINKS && mainDataType->lcdData->blink<DIVIDE_FREQ_FOR_BLINKS) || mainDataType->lcdData->ctrl_blinker!=T_ON_BLINKS){
		printf("\nTon : %d",mainDataType->all_pwm[mainDataType->pwm_selected].t_on);
	}else printf("\nTon :");


	if(mainDataType->lcdData->ctrl_blinker!=NONE_BLINKS){
		if(mainDataType->lcdData->blink<DIVIDE_FREQ_FOR_BLINKS*2) mainDataType->lcdData->blink += 1;
		else mainDataType->lcdData->blink = 0;
	}
	IOWR_ALTERA_AVALON_TIMER_STATUS(LCD_REFRESH_TIMER_BASE,0x0000);
}

void switch_settings_interrupt(void* isr_context){
	MainDataType *mainDataType = isr_context;
	mainDataType->setting = IORD_ALTERA_AVALON_PIO_DATA(SWITCH_REGLAGE_BASE);
	if(mainDataType->setting){
		mainDataType->lcdData->ctrl_blinker = ON_OFF_BLINKS;
	}
	else{
		mainDataType->lcdData->ctrl_blinker = NONE_BLINKS;
	}
	//fprintf(stderr,"%d", IORD_ALTERA_AVALON_PIO_DATA(SWITCH_REGLAGE_BASE));
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH_REGLAGE_BASE,SWITCH_REGLAGE_RESET_VALUE);
}

void adding_interrupt(void* isr_context){
	MainDataType *mainDataType = isr_context;
	if(mainDataType->lcdData->ctrl_blinker == T_ON_BLINKS && mainDataType->delay > 20){
		if(mainDataType->btn[0]==FALLING_BUTTON || mainDataType->btn[0]==PENDING_RISING_BUTTON){
			mainDataType->btn[0]=PENDING_RISING_BUTTON;
			if(mainDataType->all_pwm[mainDataType->pwm_selected].t_on >= 10)
			mainDataType->all_pwm[mainDataType->pwm_selected].t_on -= 10;
			else mainDataType->all_pwm[mainDataType->pwm_selected].t_on = MAX_T_ON;
			apply_t_on_on_channel(mainDataType->all_pwm[mainDataType->pwm_selected].t_on,mainDataType->pwm_selected);
		}else if(mainDataType->btn[1]==FALLING_BUTTON || mainDataType->btn[1]==PENDING_RISING_BUTTON){
			mainDataType->btn[1]=PENDING_RISING_BUTTON;
			if(mainDataType->all_pwm[mainDataType->pwm_selected].t_on <= MAX_T_ON-10)
			mainDataType->all_pwm[mainDataType->pwm_selected].t_on += 10;
			else mainDataType->all_pwm[mainDataType->pwm_selected].t_on = 0;
			apply_t_on_on_channel(mainDataType->all_pwm[mainDataType->pwm_selected].t_on,mainDataType->pwm_selected);
		}
	}
	else if(mainDataType->lcdData->ctrl_blinker == T_ON_BLINKS && mainDataType->delay >5){
		if(mainDataType->btn[0]==FALLING_BUTTON || mainDataType->btn[0]==PENDING_RISING_BUTTON){
			mainDataType->btn[0]=PENDING_RISING_BUTTON;
			if(mainDataType->all_pwm[mainDataType->pwm_selected].t_on > 0)
			mainDataType->all_pwm[mainDataType->pwm_selected].t_on -= 1;
			else mainDataType->all_pwm[mainDataType->pwm_selected].t_on = MAX_T_ON;
			apply_t_on_on_channel(mainDataType->all_pwm[mainDataType->pwm_selected].t_on,mainDataType->pwm_selected);
		}else if(mainDataType->btn[1]==FALLING_BUTTON || mainDataType->btn[1]==PENDING_RISING_BUTTON){
			mainDataType->btn[1]=PENDING_RISING_BUTTON;
			if(mainDataType->all_pwm[mainDataType->pwm_selected].t_on < MAX_T_ON)
			mainDataType->all_pwm[mainDataType->pwm_selected].t_on += 1;
			else mainDataType->all_pwm[mainDataType->pwm_selected].t_on = 0;
			apply_t_on_on_channel(mainDataType->all_pwm[mainDataType->pwm_selected].t_on,mainDataType->pwm_selected);
		}
		mainDataType->delay +=1;
	}
	else {
		mainDataType->delay +=1;
	}
	IOWR_ALTERA_AVALON_TIMER_STATUS(ADDER_TIMER_BASE,0x0000);
}
