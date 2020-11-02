OBJS = main.o modbus.o crc.o
LIBS = -lpthread

all: command

command: $(OBJS)
	g++ $(LIBS) -o command $(OBJS)

%.o : src/%.c
	g++ -o $@ -c $< -I include
