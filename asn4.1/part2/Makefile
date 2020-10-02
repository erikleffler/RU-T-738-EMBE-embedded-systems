vpath %.h ../include

INC=-I./include/
LIB=-lpthread

OBJ=main.o increment_task.o decrement_task.o

default: main

main: $(OBJ)
	g++  $(LIB) $(INC) $(OBJ) -o main
	rm *.o

main.o: tasks.h
	g++  $(LIB) $(INC) -c src/main.cpp

increment_task.o: tasks.h
	g++  $(LIB) $(INC) -c src/increment_task.cpp

decrement_task.o: tasks.h
	g++  $(LIB) $(INC) -c src/decrement_task.cpp

tasks.h:

.PHONY: clean
clean:
	rm main
