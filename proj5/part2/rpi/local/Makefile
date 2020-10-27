OBJS = main.o modbus.o

all: command

# We use -l to specify libraries containing the library functions that we have used
command: $(OBJS)
	g++ -o command $(OBJS)

%.o : src/%.c
	g++ -o $@ -c $< -I include
