#include "control_led.h"
#include "struct.h"

void enable_led(int channel){
	unsigned int actual_led_enable = IORD_ALTERA_AVALON_PIO_DATA(LEDS_BASE);
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, (actual_led_enable | 1<<channel));
}
void disable_led(int channel){
	unsigned int actual_led_enable = IORD_ALTERA_AVALON_PIO_DATA(LEDS_BASE);
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, (actual_led_enable & (~(1<<channel))));
}
void disable_all_led(){
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, 0);
}
void enable_all_led(){
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,~(1<<BYTES_BUS_NUMBER+1));
}
