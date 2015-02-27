#ifndef MAZE_H
#define MAZE_H

#define MAZE_SIZE (16)

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

enum _DIRECTION{N,E,S,W};

typedef enum _DIRECTION Direction;

/** holds its location & neighbors, as well as a bool for indicating if it has been discovered */
struct _NODE{
	bool known;
	int weight; //used for flood-fill
	//if you want to iterate over neighbors, just increment the pointer to north
	struct _NODE *neighbors[4];
};

typedef struct _NODE Node;

/** the maze is graph of nodes, stored internally as an matrix.

*/
struct _MAZE{
	bool solved; //boolean for if we know the fastest rout
	Node *nodes[MAZE_SIZE][MAZE_SIZE]; // array of node pointers
	char *fastest_route; //a char array like NSEWNENNSNE, which means North, South, East...
};

typedef struct _MAZE Maze;

/** allocates a maze of the given size and sets all links in graph to be null. Naturally, it's column major.
  * @param size the size of the maze
*/
Maze *create_maze();

/** allocates a node setting all nighbors to null. Function does NOT allocate for neighbors.*/
Node *create_node();

/** get node by its position*/
Node *get_node(Maze *maze, int x, int y);

/** check if a node in a direciton is visited*/
bool visited(int row, int col,  Direction dir, Maze *maze);

/** free's the maze and all nodes
	* @param return false on failure
*/
bool free_maze(Maze *maze);

/** free's a node 
	* @param return false on failure
*/
bool free_node(Node *node);

#endif