#include "./led_blink_task.h"

void* led_blink_task(void* arg_p) {

	sem_t button_sem = *(sem_t *) (arg_p);
	bool *should_toggle = (bool *) (((sem_t *) (arg_p)) + 1);

	DigitalOut led;

    /* Initialize the LED pin as output. */
	led.init(5);

    while (1) {
        /* Wait for a seconds. */
		std_printf(FSTR("LE %d\n"), button_sem.count);

		sem_take(&button_sem, NULL);
		if(*should_toggle) {
			led.toggle();
			*should_toggle = false;
		}
		sem_give(&button_sem, 1);
		
    }

    return (0);
}
