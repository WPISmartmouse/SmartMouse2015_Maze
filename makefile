all: maze

maze: obj/maze.o
	gcc -g obj/maze.o -o bin/maze 

obj/maze.o: src/maze.c src/maze.h
	gcc -g -c src/maze.c -o obj/maze.o