#include "./led_blink_task.h"

void* led_blink_task(void* arg_p) {

	DigitalOut led;

    /* Initialize the LED pin as output. */
	led.init(5);
    
    while (1) {
        /* Wait for a seconds. */
        thrd_sleep_ms(500);
        
        /* Toggle the LED on/off. */
		led.toggle();
		
    }

    return (0);
}
