#include "./led_blink_task.h"

void* led_blink_task(void* arg_p) {

	sem_t button_sem = *(sem_t *) (arg_p);

	DigitalOut led;

    /* Initialize the LED pin as output. */
	led.init(5);

	time_t wait_forever = time_t{999999999, 0};
    
    while (1) {
        /* Wait for a seconds. */
		sem_take(&button_sem, &wait_forever);
		std_printf(FSTR("LEDLEDLED\n"));
		std_printf(FSTR("LEDLEDLED\n"));
		std_printf(FSTR("LEDLEDLED\n"));
		std_printf(FSTR("LEDLEDLED\n"));
		std_printf(FSTR("LEDLEDLED\n"));
		led.toggle();
		
    }

    return (0);
}
