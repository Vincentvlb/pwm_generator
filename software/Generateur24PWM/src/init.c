#include "struct.h"
#include "interrupt.h"
#include "control_lcd.h"
#include "control_led.h"

PWMDataType* pwm_data_init(){
    PWMDataType* pwmData = malloc(PWM_NUMBER * sizeof(PWMDataType));
    for(int index=0; index < PWM_NUMBER; index++){
        pwmData[index].id = index+1;
        pwmData[index].status = false;
        pwmData[index].t_on = 512;
    }
    return pwmData;
}

LCDDataType* lcd_data_init(){
    LCDDataType *lcdData = (LCDDataType*)malloc(sizeof(LCDDataType));
    lcdData->ctrl_blinker = NONE_BLINKS;
    lcdData->blink = 1;
    return lcdData;
}

MainDataType* main_data_init(){
    MainDataType *mainData = (MainDataType*)malloc(sizeof(MainDataType));
	mainData->btn[0] = PENDING_BUTTON;
	mainData->btn[1] = PENDING_BUTTON;
	mainData->btn[2] = PENDING_BUTTON;
	mainData->pwm_selected = 0;
	mainData->lcdData = lcd_data_init();
    mainData->all_pwm = pwm_data_init();
    mainData->setting = IORD_ALTERA_AVALON_PIO_DATA(SWITCH_REGLAGE_BASE);
    mainData->delay =0;
    return mainData;
}

MainDataType* init(){
    MainDataType *mainData = main_data_init();

	//setup interruption btn
	alt_iic_isr_register(BUTTONS_COMMANDE_IRQ_INTERRUPT_CONTROLLER_ID,BUTTONS_COMMANDE_IRQ,&button_interrupt,mainData,NULL);
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTONS_COMMANDE_BASE,0b111);

	//setup interruption lcd
	alt_iic_isr_register(LCD_REFRESH_TIMER_IRQ_INTERRUPT_CONTROLLER_ID,LCD_REFRESH_TIMER_IRQ,&lcd_refresh_interrupt,mainData,NULL);
	IOWR_ALTERA_AVALON_TIMER_CONTROL(LCD_REFRESH_TIMER_BASE,0x0007);

	//setup interruption settings
	alt_iic_isr_register(SWITCH_REGLAGE_IRQ_INTERRUPT_CONTROLLER_ID,SWITCH_REGLAGE_IRQ,&switch_settings_interrupt,mainData,NULL);
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(SWITCH_REGLAGE_BASE,0b1);

	//setup interruption adding t_on
	alt_iic_isr_register(ADDER_TIMER_IRQ_INTERRUPT_CONTROLLER_ID,ADDER_TIMER_IRQ,&adding_interrupt,mainData,NULL);
	IOWR_ALTERA_AVALON_TIMER_CONTROL(ADDER_TIMER_BASE,0x0003);

	disable_all_pwm_channel();
	apply_t_on_on_all(512);
	disable_all_led();
	clear_lcd();

	return mainData;
}
