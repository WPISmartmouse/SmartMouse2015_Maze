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


	char *no_wall_path;
	no_wall_path = calloc(PATH_SIZE,sizeof(char));
	char *all_wall_path;
	all_wall_path = calloc(PATH_SIZE,sizeof(char));

	//mouse starts at 0,0
	do {
		//check left right and front sides
		//eventually this will return values from sensors
		bool *walls = sense(kmaze,mouse);

		//update the mazes to match the sensor readings
		Node *no_wall_node = get_node(no_wall_maze,mouse->row,mouse->col);
		Node *all_wall_node = get_node(all_wall_maze,mouse->row,mouse->col);
		int i;

		//check each direction around the mouse for walls and update our mazes
		for (i=0;i<4;i++){

			int r = mouse->row;
			int c = mouse->col;
			update_pos(i, &r, &c);

			Direction opposite_direction = (i + 2) % 4;

			//if a wall exists in that direction, add a wall to no_wall_maze
			if (walls[i]){
				//making the neighbor null represents adding a wall
				//make sure to update both the node and the node it no longer connects to!
				if (no_wall_node->neighbors[i] != NULL){
					no_wall_node->neighbors[i]->neighbors[opposite_direction] = NULL;
				}
				no_wall_node->neighbors[i] = NULL;
			}
			//if no wall exists in that direction remove a wall from all_wall_maze
			else {
				//getting the previously unconnected neighbor represents adding a wall
				//make sure to update both the node and the node it now connects to
				all_wall_node->neighbors[i] = get_node(all_wall_maze, r,c);
				if (get_node(all_wall_maze,r,c) != NULL){
					get_node(all_wall_maze, r,c)->neighbors[opposite_direction] = all_wall_node;
				}
			}
		}

		//solve flood fill on the two mazes
		flood_fill_custom(no_wall_maze,no_wall_path,mouse->row,mouse->col);
		
		flood_fill_custom(all_wall_maze,all_wall_path,mouse->row,mouse->col);

		printf("no wall path  = %s\n",no_wall_path);
		printf("all wall path = %s\n",all_wall_path);


		//execute the first instruction of the path!
		execute_command(mouse,*no_wall_path);
		printf("mouse position (%i:%i)\n",mouse->row,mouse->col);
	}
	while (no_wall_path != all_wall_path);


	free(all_wall_path);
	free(no_wall_path);
}

void flood_fill(Maze *maze, char *path){
	flood_fill_custom(maze,path,0,0);
}

//This method will take a maze and perform a traditional flood fill
//the fill starts from r0,c0
void flood_fill_custom(Maze *maze, char *path, int r0, int c0){
	Node *n = get_node(maze,r0,c0);
	Node *root = get_node(maze,r0,c0);
	Node *center = get_node(maze,7,7);

	//incase the maze has already been solved, reset all weight and known values
	int i,j;
	for (i=0;i<MAZE_SIZE;i++){
		for (j=0;j<MAZE_SIZE;j++){
			maze->nodes[i][j]->weight = -1;
			maze->nodes[i][j]->known = false;
		}
	}

	//explore all neighbors of the current node starting  with a weight of 1
	//return 1 means path to center was found
	bool success = false;
	explore_neighbors(n, center, 0, &success);

#ifdef DEBUG
//	print_weight_maze(maze);
//	print_maze(maze);
#endif

	if (!success){
		return;
	}
	
	//start at the center 
	n = center;

	//if we solved the maze, traverse from goal back to root and record what direction is shortest
	char *r_path = malloc(PATH_SIZE*sizeof(char));
	char *r_p = r_path;
	while (n != root){
		Node *min_node = n;
		Direction min_dir = N;

		//find the neighbor with the lowest weight and go there, that is the fastest route
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

		*(r_p++) = dir_to_char(min_dir);
	}
	*r_p = '\0';
	r_p = r_path;
	
	//the create path is from goal to start, so now we "reverse" it
	char* p = path;
	while ((*r_p) != '\0'){
		char c;
		switch(*r_p){
			case 'N':c='S';break;
			case 'E':c='W';break;
			case 'S':c='N';break;
			case 'W':c='E';break;
		}
		*(p++) = c;
		r_p++;
	}
}


void explore_neighbors(Node *node, Node *goal, int weight, bool *success){
	if (node != NULL){
		//check all nodes that are unvisited, or would be given a lower weight
		if (!node->known || weight < node->weight){ 
			//don't visiti it again unless you find a shorter path
			node->known = true;
			
			//check if path to goal node was found
			if (node == goal){
				*success = true;
			}
			
			//update weight
			node->weight = weight;
			
			//recursive call to explore each neighbors
			int i;
			for (i=0;i<4;i++){
				if (node->neighbors[i] != NULL){
					explore_neighbors(node->neighbors[i], goal, weight+1, success);	
				}
			}
		}
	}
}


void left_hand_follow(Maze *maze){
	
	maze->nodes[0][0]->known=true;
	Mouse *mouse = create_mouse();

	//run till you find the center
	int step=0;
	while (!atCenter(mouse)){
		Direction dir = (mouse->dir-1)%4; //check left first
		
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
	return blocked_in_dir(mouse->row,mouse->col,mouse->dir,maze);
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
