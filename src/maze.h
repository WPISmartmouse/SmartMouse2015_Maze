/** maze.h
 * \brief Contains functions for creating and using the Maze and Node structs
 */
#ifndef MAZE_H
#define MAZE_H

#define MAZE_SIZE (16)
#define PATH_SIZE (100)

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

enum _DIRECTION{N,E,S,W};

typedef enum _DIRECTION Direction;

/**
 * \brief holds its location & neighbors, as well as a bool for indicating if it has been discovered
 * you don't need to free nodes in a maze, just use free_maze however, be sure to free nodes allocated not in mazes
 */
struct _NODE{
	bool known;
	int weight; //used for flood-fill
	int distance; //used for a star
	//if you want to iterate over neighbors, just increment the pointer to north
	struct _NODE *neighbors[4];
};

typedef struct _NODE Node;

/**
 * \brief the maze is graph of nodes, stored internally as an matrix.
 * don't forget to call free_maze(maze) after a maze is done being used
 */
struct _MAZE{
	bool solved; //boolean for if we know the fastest rout
	Node *nodes[MAZE_SIZE][MAZE_SIZE]; // array of node pointers
	char *fastest_route; //a char array like NSEWNENNSNE, which means North, South, East...
};

typedef struct _MAZE Maze;

/** \brief allocates and initializes a node
 * allocates a maze of the given size and sets all links in graph to be null. Naturally, it's column major.
 */
Maze *create_maze();

/** \brief allocates and intializes a node
 * 	allocates a node setting all nighbors to null. Function does NOT allocate for neighbors.
 */
Node *create_node();

/** \brief get node by its position
 * this is equlvelant to maze->nodes[x][y]
 */
Node *get_node(Maze *maze, int x, int y);

/** \brief check if a node in a direction is visited
 * looks up (row,col) in maze and checks its neighbors[dir] and returns if that neighbor is known
 */
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