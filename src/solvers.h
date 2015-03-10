/** functions for exploring and solving mazes */
#ifndef SOLVERS_H
#define SOLVERS_H

#include "maze.h"
#include "mouse.h"
#include <stdbool.h>

/** set starting point 0,0 & S. depth-first search of all nodes in the grid, adding 1 each time.
* once all nodes are discovered, the path is solved by going backwards from the center to the lowest neighbor each time
* @param maze maze to solve
*/
void flood_fill(Maze *maze);

/**this assigns n->weight+1 to each neighbor, and recursively calls it on all valid neighbors
* @param node the node to explore the neighbors of
* @param goal the node you want to find a path to
* @param weight the weight to set the node to
* @param success should be false to start, and will be set to true if path to goal is found
*/
void explore_neighbors(Node *node,Node *goal, int weight, bool *success);

/** set starting point to 0,0. follow left hand wall
* @param maze maze to solve
*/
void left_hand_follow(Maze *maze);

/** marks the mouses given position as known
* @param mouse the mouse
* @param maze the maze
*/
void mark_position(Mouse *mouse, Maze *maze);

/** checks the mouses direction, and compares it to the mazes walls. For example, if the mouse is facing north, and the node it's on has a null north pointer, then there's a wall
* @param mouse the mouse
* @param maze the maze
*/
bool blocked(Mouse *mouse, Maze *maze);

/** checks a direction, and compares it to the mazes walls. For example, if the mouse is facing north, and the node it's on has a null north pointer, then there's a wall
* @param mouse the mouse
* @param maze the maze
*/
bool blocked_in_dir(int row, int col, Direction dir, Maze *maze);

/** chooses a direction. If possible, it picks an unvisited node, otherwise it picks a random one it's been too already
* @param mouse the mouse
*/
void choose_direction(Mouse *mouse, Maze *maze);

/** checks if the mouse is int the center 4 squares of the maze
* @param mouse the mouse
*/
bool atCenter(Mouse *mouse);

/** checks if the row col is at center
* @param mouse the mouse
*/
bool isCenter(int row, int col);

#endif