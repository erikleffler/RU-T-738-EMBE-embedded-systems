/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014-2018, Erik Moqvist
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * This file is part of the Simba project.
 */

#include "simba.h"
#include "../../avr_lib/include/digital_out.h"
#include "./led_blink_task.h"
#include "./button_check_task.h"

THRD_STACK(led_stack, 255);
THRD_STACK(button_stack, 255);

int main()
{

	sys_start();

	struct uart_driver_t uart;

	uart_module_init();
    uart_init(&uart, &uart_device[0], 9600, NULL, 0);
    uart_start(&uart);

    /* Set standard output to the UART. */
    sys_set_stdout(&uart.chout);

	thrd_module_init();

	struct sem_t button_sem;
	sem_init(&button_sem, 0, 1);

	struct thread_shared_variables {
		sem_t button_sem;
		bool should_toggle;
	};

	struct thread_shared_variables args = {
		button_sem,
		false
	};

	thrd_t* led_thrd = thrd_spawn(
		led_blink_task, 
		(void*)&args,
		81,
		led_stack,
		sizeof(led_stack)
	);

	thrd_t* button_thrd = thrd_spawn(
		button_check_task, 
		(void*)&args,
		50,
		button_stack,
		sizeof(button_stack)
	);

	thrd_suspend(NULL);


	return 0;
}
