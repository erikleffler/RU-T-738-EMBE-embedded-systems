vpath %.h ../include

INC=-I./include/
LIB=-lpthread

CC=g++
CFLAGS=$(INC) $(LIB)

OBJ=main.o increment_task.o decrement_task.o fifo.o

default: main

main: $(OBJ)
	g++  $(LIB) $(INC) $(OBJ) -o main
	rm *.o

main.o: tasks.h fifo.h
	g++  $(LIB) $(INC) -c src/main.cpp

increment_task.o: tasks.h fifo.h
	g++  $(LIB) $(INC) -c src/increment_task.cpp

decrement_task.o: tasks.h fifo.h
	g++  $(LIB) $(INC) -c src/decrement_task.cpp

fifo.o: fifo.h
	g++  $(LIB) $(INC) -c src/fifo.cpp

tasks.h:

fifo.h:

.PHONY: clean
clean:
	rm main
