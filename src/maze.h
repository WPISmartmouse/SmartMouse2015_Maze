#ifndef MAZE_H
#define MAZE_H

#include <stdlib.h>
#include <stdio.h>
#include <Boolean.h>

/** holds its location & neighbors, as well as a bool for indicating if it has been discovered */
struct _NODE{
	bool known;
	//if you want to iterate over neighbors, just increment the pointer to north
	Node* north;
	Node* west;
	Node* east;
	Node* south;
};

typedef _NODE Node;

/** the maze is graph of nodes, stored internally as an matrix.

*/
struct _MAZE{
	int size; //the size, assumed to be square
	bool solved; //boolean for if we know the fastest rout
	Node **base_node; // array of node pointers
	char *fastest_route; //a char array like NSEWNENNSNE, which means North, South, East...
};

typedef _MAZE Maze;

/** allocates a maze of the given size and sets all links in graph to be null. Naturally, it's column major.
  * @param size the size of the maze
*/
*Maze create_maze(int size);

/** allocates a node setting all nighbors to null. Function does NOT allocate for neighbors.*/
*Node create_node();

/** get node by its position*/
*Node get_node(Maze *maze, int x, int y);

/** free's the maze and all nodes
	* @param return false on failure
*/
bool free_maze(Maze *maze);

/** free's a node 
	* @param return false on failure
*/
bool free_node(Node *node);

#endif