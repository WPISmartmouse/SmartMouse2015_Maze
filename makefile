all: obj/maze.o obj/maze_io.o

obj/maze_io.o: src/maze_io.c src/maze_io.h
	gcc -g -c src/maze_io.c -o obj/maze_io.o

obj/maze.o: src/maze.c src/maze.h
	gcc -g -c src/maze.c -o obj/maze.o

clean:
	rm obj/* bin/*
