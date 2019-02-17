FLAGS = -ggdb -Wall -Wextra -pedantic -std=c11
LINKS = -lpthread -lncurses 

OPTIMIZATIONS = -O3
OBJECTS = main.o animations.o
EXECUTABLE = -o camagachi

main: main.o animations.o
	gcc $(EXECUTABLE) $(OBJECTS) $(FLAGS) $(LINKS)
main.o: main.c
	gcc -c main.c $(FLAGS)
main.c:

animations.o: animations.c
	gcc -c animations.c $(FLAGS)
clean:
	rm *.o camagachi

