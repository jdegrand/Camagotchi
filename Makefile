FLAGS = -ggdb -Wall -Wextra -pedantic -std=c11
LINKS = -lpthread -lncurses 

OPTIMIZATIONS = -O3
OBJECTS = main.o
EXECUTABLE = -o camagachi

main: main.o
	gcc $(EXECUTABLE) $(OBJECTS) $(FLAGS) $(LINKS)
main.o: main.c
	gcc -c main.c $(FLAGS)
main.c:

clean:
	rm *.o camagachi

