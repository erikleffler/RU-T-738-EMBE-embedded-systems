#include "./button_check_task.h"

void* button_check_task(void* arg_p) {

	sem_t button_sem = *(sem_t *) (arg_p);
	bool *should_toggle = (bool *) (((sem_t *) (arg_p)) + 1);

	DigitalIn button;

    /* Initialize the LED pin as output. */
	button.init(4);

	bool state = false;
    while (1) {
		bool is_pressed = button.read();	

		if(state != is_pressed) {

			sem_take(&button_sem, NULL);
			*should_toggle = true;
			sem_give(&button_sem, 1);

			state = is_pressed;
		}

		thrd_sleep_ms(50);
    }

    return (0);
}
