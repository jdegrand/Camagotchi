FLAGS = -ggdb -Wall -Wextra -pedantic -std=c11
LINKS = -lpthread -lncurses 

OPTIMIZATIONS = -O3
OBJECTS = main.o sprites.o
EXECUTABLE = -o camagachi

main: main.o sprites.o
	gcc $(EXECUTABLE) $(OBJECTS) $(FLAGS) $(LINKS)
main.o: main.c
	gcc -c main.c $(FLAGS)
main.c:

sprites.o: sprites.c
	gcc -c sprites.c $(FLAGS)
clean:
	rm *.o camagachi

