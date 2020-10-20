OBJS = uart_tasks.o uart_console.o

uart_console: $(OBJS)
	g++ -o uart_console -lpthread $(OBJS) -I include

%.o : src/%.c
	g++ -o $@ -c $< -I include


.PHONY: clean

clean:
	rm *.o uart_console
