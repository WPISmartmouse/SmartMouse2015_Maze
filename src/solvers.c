/** solvers.h
	@author Peter Mitrano
*/
#include "solvers.h"

#define min(a, b) ((a) < (b) ? (a) : (b))

//starts at 0,0 and explores the whole maze
//kmaze is the known maze, and should only be used to call sense()
void flood_explore(Maze *kmaze){
	Mouse *mouse = create_mouse();

	Maze* no_wall_maze = create_maze(); //this maze is initially no walls, and walls are filled out every time the mouse moves
	Maze* all_wall_maze = create_maze(); //this maze is initially no walls, and walls are filled out every time the mouse moves
	int i,j;
	for (i=0;i<MAZE_SIZE;i++){
		for (j=0;j<MAZE_SIZE;j++){
			get_node(no_wall_maze,i,j)->neighbors[N] = get_node(no_wall_maze, i-1, j);
			get_node(no_wall_maze,i,j)->neighbors[E] = get_node(no_wall_maze, i, j+1);
			get_node(no_wall_maze,i,j)->neighbors[S] = get_node(no_wall_maze, i+1, j);
			get_node(no_wall_maze,i,j)->neighbors[W] = get_node(no_wall_maze, i, j-1);
		}
	}

	Node *start;
	Node *goal;

	char *no_wall_path;
	char *all_wall_path;

	//mouse starts at 0,0
	do {
		//check left right and front sides
		//eventually this will return values from sensors
		bool *walls = sense(kmaze,mouse);
		printf("sensed N=%i E=%i S=%i W=%i\n",walls[0],walls[1],walls[2],walls[3]);

		//update the mazes to match the sensor readings
		Node *no_wall_node = get_node(no_wall_maze,mouse->row,mouse->col);
		Node *all_wall_node = get_node(all_wall_maze,mouse->row,mouse->col);
		int i;

		//check each direction around the mouse for walls
		for (i=0;i<4;i++){

			int r = mouse->row;
			int c = mouse->col;
			update_pos(i, &r, &c);

			//if no wall exists in that direction
			if (walls[i]){
				no_wall_node->neighbors[i] = NULL;
			}
			else {
				all_wall_node->neighbors[i] = get_node(all_wall_maze, r,c);	
				
			}
		}

		
		//print_pointer_maze(kmaze);
		//print_pointer_maze(all_wall_maze);
		print_pointer_maze(no_wall_maze);

		//solve flood fill on the two mazes
		no_wall_path = flood_fill(no_wall_maze);
		all_wall_path = flood_fill(all_wall_maze);//segfault occurs solving all_wall_maze
	}
	while (no_wall_path != all_wall_path);



}

//This method will take a maze and perform a traditional flood fill
//the fill starts from 0,0
char *flood_fill(Maze *maze){

	Node *n = get_node(maze,0,0);
	Node *root = get_node(maze,0,0);
	Node *center = get_node(maze,7,7);

	//explore all neighbors of the current node starting  with a weight of 1
	//return 1 means path to center was found
	bool success = false;
	explore_neighbors(n, center, 0, &success);

	print_weight_maze(maze);

	if (!success){
		printf("maze not solved :(\n");
		return;
	}
	else {
		printf("maze solved!\n");
	}
	
	n = center;
	char *path = malloc(sizeof(char)*MAZE_SIZE*MAZE_SIZE); //must free later
	while (n != root){
		Node *min_node = n;
		Direction min_dir = N;

		int i;
		for (i=0;i<4;i++){
			if (n->neighbors[i] != NULL){
				if (n->neighbors[i]->weight < min_node->weight){
					min_node = n->neighbors[i];
					min_dir = i;
				}
			}
		}

		n = min_node;

		*(path++) = dir_to_char(min_dir);
		*(path++) = ' ';
	}
	*path = '\0';

	printf("path = %s\n",maze->fastest_route);

}


void explore_neighbors(Node *node, Node *goal, int weight, bool *success){
	if (node != NULL){//handles dead-end nodes

		if (!node->known){
			node->weight = weight;
			node->known = true;
			//check if path to goal node was found
			if (node == goal){
				*success = true;
			}
			int i;
			//recursive call to explore each neighbors
			for (i=0;i<4;i++){
				explore_neighbors(node->neighbors[i], goal, weight+1, success);
			}
		}
	}
}


void left_hand_follow(Maze *maze){
	int i=0,j=0;
	maze->nodes[0][0]->known=true;
	Mouse *mouse = create_mouse();

	//run till you find the center
	int step=0;
	while (!atCenter(mouse)){
		Direction dir = (mouse->dir-1)%4; //check left first
		bool valid_turn;
		while (blocked_in_dir(mouse->row,mouse->col,dir,maze)){
			dir=(dir+1)%4;
		}

		if (dir != mouse->dir){
			maze->fastest_route[step] = dir_to_char(mouse->dir);
			step++;
		}

		mouse->dir = dir;
		
		forward(mouse);
		mark_position(mouse,maze);

		printf("{%d,%d} \n",mouse->row,mouse->col);
	}
	maze->fastest_route[step]=0;
	printf("solved! %s\n",maze->fastest_route);

}

void mark_position(Mouse *mouse, Maze *maze){
	maze->nodes[mouse->row][mouse->col]->known = true;
}

bool blocked(Mouse *mouse, Maze *maze){
	blocked_in_dir(mouse->row,mouse->col,mouse->dir,maze);
}

bool blocked_in_dir(int row, int col, Direction dir, Maze *maze){
	return !maze->nodes[row][col]->neighbors[dir];
}

bool atCenter(Mouse *mouse){
	return isCenter(mouse->row, mouse->col);
}

bool isCenter(int row, int col){
	return (row == MAZE_SIZE/2 || row == MAZE_SIZE/2-1) && (col == MAZE_SIZE/2 || col == MAZE_SIZE/2-1);
}