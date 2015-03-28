/** maze.c implements the functions used to create, free, and manipulate maze
	@author Peter Mitrano
*/
#include "maze.h"

Maze *create_maze(){
	Maze *maze = malloc(sizeof(Maze));
	maze->solved = false;
	maze->fastest_route = malloc(PATH_SIZE*sizeof(char)); //assume really bad route--visits all squares.
	int i,j;
	for (i=0;i<MAZE_SIZE;i++){
		for (j=0;j<MAZE_SIZE;j++){
			maze->nodes[i][j] = create_node();
		}
	}
	return maze;
}

Node *create_node(){
	Node *node = malloc(sizeof(Node));
	node->known = false;
	node->weight = -1;
	node->neighbors[N]=NULL;
	node->neighbors[S]=NULL;
	node->neighbors[E]=NULL;
	node->neighbors[W]=NULL;
	return node;
}

Node *get_node(Maze *maze, int row, int col){
	if (col < 0 || col >= MAZE_SIZE || row < 0 || row >= MAZE_SIZE){
		return NULL;
	}
	return maze->nodes[row][col];
}

bool visited(int row, int col, Direction dir, Maze *maze){
	return maze->nodes[row][col]->neighbors[dir]->known;
}

bool free_maze(Maze *maze){
	free(maze->fastest_route);
	int i,j;
	for (i=0;i<MAZE_SIZE;i++){
		for (j=0;j<MAZE_SIZE;j++){
			free(maze->nodes[i][j]);
		}
	}
	free(maze);
	return true;
}

//nothing fancy here, just convenient. might remove if it never gets more complicated
bool free_node(Node *node){
	free(node);	
	return true;
}
