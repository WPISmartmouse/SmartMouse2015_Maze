#include "solvers.h"

void flood_fill(Maze *maze){
	Mouse *mouse = create_mouse();

	Node *n = get_node(maze,mouse->row,mouse->col);

	Node *root = get_node(maze,0,0);

	print_pointer_maze(maze);

	//explore all neighbors of the current node starting  with a weight of 1
	explore_neighbors(root, n, 1);

	int i,j;
	for (i=0;i<MAZE_SIZE;i++){
		for (j=0;j<MAZE_SIZE;j++){
			int w = get_node(maze,i,j)->weight;
			if (w<10){
				printf(" %d ",w);
			}
			else {
				printf("%d ",w);
			}
		}
		printf("\n");
	}
}


void explore_neighbors(Node *root, Node *node,int weight){
	if (node != NULL){//handles dead-end nodes

		node->weight = weight;

		if (!node->known){
			node->known = true;
			int i;
			//recursive call to explore each neighbors
			for (i=0;i<4;i++){
				explore_neighbors(root, node->neighbors[i], weight+1);
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
	return (mouse->row == MAZE_SIZE/2 || mouse->row == MAZE_SIZE/2-1) && (mouse->col == MAZE_SIZE/2 || mouse->col == MAZE_SIZE/2-1);
}