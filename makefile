all: read_and_print

read_and_print: obj/read_and_print.o obj/maze_io.o obj/maze.o
	gcc -g obj/read_and_print.o obj/maze_io.o obj/maze.o -o bin/read_and_print


obj/read_and_print.o: src/read_and_print.c src/maze_io.h src/maze.h
	gcc -g -c src/read_and_print.c -o obj/read_and_print.o

obj/maze_io.o: src/maze_io.c src/maze_io.h
	gcc -g -c src/maze_io.c -o obj/maze_io.o

obj/maze.o: src/maze.c src/maze.h
	gcc -g -c src/maze.c -o obj/maze.o

clean:
	rm obj/* bin/*
