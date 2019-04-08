FLAGS = -ggdb -Wall -Wextra -pedantic -std=c11
LINKS = -lpthread -lncurses 

OPTIMIZATIONS = -O3
OBJECTS = main.o animations.o border.o modes.o camagotchi.o extras.o
EXECUTABLE = -o camagotchi

main: main.o animations.o border.o modes.o camagotchi.o extras.o
	gcc $(EXECUTABLE) $(OBJECTS) $(FLAGS) $(LINKS)

main.o: main.c
	gcc -c main.c $(FLAGS)

animations.o: animations.c
	gcc -c animations.c $(FLAGS)

border.o: border.c
	gcc -c border.c $(FLAGS)

camagotchi.o: camagotchi.c
	gcc -c camagotchi.c $(FLAGS)

modes.o: modes.c
	gcc -c modes.c $(FLAGS)

extras.o: extras.c
	gcc -c extras.c $(FLAGS)

clean:
	rm *.o camagotchi

