#include "./button_check_task.h"

void* button_check_task(void* arg_p) {

	sem_t button_sem = *(sem_t *) (arg_p);

	DigitalIn button;

    /* Initialize the LED pin as output. */
	button.init(4);
    

	bool state = false;
    while (1) {
		bool is_pressed = button.read();	
	
		std_printf(FSTR("==========\n"));
		std_printf(FSTR("%d\n"), button_sem.count);
		std_printf(FSTR("%d\n"), is_pressed);
		std_printf(FSTR("%d\n"), state);

		if(state != is_pressed) {
			sem_give(&button_sem, 5);
			state = is_pressed;
			std_printf(FSTR("--------------\n"));
			std_printf(FSTR("%d\n"), button_sem.count);
			std_printf(FSTR("%d\n"), is_pressed);
			std_printf(FSTR("%d\n"), state);
		}

		thrd_sleep_ms(50);
    }

    return (0);
}
