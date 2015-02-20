all: maze read_maze

read_maze: obj/read_maze.o

maze: obj/maze.o
	gcc -g obj/maze.o -o bin/maze 

obj/read_maze.o: src/read_maze.c src/read_maze.h
	gcc -g -c src/read_maze.c -o obj/read_maze.o

obj/maze.o: src/maze.c src/maze.h
	gcc -g -c src/maze.c -o obj/maze.o

clean:
	rm obj/* bin/*
