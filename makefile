all: read_and_print explore

explore: obj/explore.o obj/solvers.o obj/maze_io.o obj/maze.o obj/mouse.o
	gcc -g obj/explore.o obj/solvers.o obj/maze_io.o obj/maze.o obj/mouse.o -o bin/explore

read_and_print: obj/read_and_print.o obj/maze_io.o obj/maze.o
	gcc -g obj/read_and_print.o obj/maze_io.o obj/maze.o -o bin/read_and_print

obj/mouse.o: src/mouse.c src/mouse.h
	gcc -g -c src/mouse.c -o obj/mouse.o

obj/explore.o: src/explore.c
	gcc -g -c src/explore.c -o obj/explore.o

obj/solvers.o: src/solvers.c src/solvers.h
	gcc -g -c src/solvers.c -o obj/solvers.o

obj/read_and_print.o: src/read_and_print.c
	gcc -g -c src/read_and_print.c -o obj/read_and_print.o

obj/maze_io.o: src/maze_io.c src/maze_io.h
	gcc -g -c src/maze_io.c -o obj/maze_io.o

obj/maze.o: src/maze.c src/maze.h
	gcc -g -c src/maze.c -o obj/maze.o

clean:
	rm obj/* bin/*
