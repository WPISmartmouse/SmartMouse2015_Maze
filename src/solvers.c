#include "solvers.h"

//solves with a star between two positions
void A_star(Maze *maze, int x0, int y0, int x1, int y1){

	Node *start = get_node(maze,x0,y0);
	Node *goal = get_node(maze,x1,y1);
	Node *n;
	while (!goal->known){
		n = closest_unknown(maze);
		n->known = true;
		update_neighbors(n);
	}
}

Node *closest_unknown(Maze *maze){

}

void update_neighbors(Node *node){

}

//This method will take a maze and perform a traditional flood fill
//the fill starts from 0,0
void flood_fill(Maze *maze){

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
	char *path = maze->fastest_route;
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