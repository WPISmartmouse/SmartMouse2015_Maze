/** maze.c implements the functions used to create, free, and manipulate maze
*/

#include "maze.c"

*Maze create_maze(int size){
	Maze *maze = malloc(sizeof(Maze));
	maze->size = size;
	maze->solved = false;
	maze->fastestRoute = malloc(size*size*sizeof(char)); //assume reall bad route--visits all squares.
	maze->base_node = create_node();
	int i,j;
	for (i=0;i<size;i++){
		for (j=0;j<size;j++){	
			*(base_node++) = create_node();
		}
	}

}

*Node create_node(){
	Node* node = malloc(sizeof(Node));
	node->known = false;
	node->north=NULL;
	node->south=NULL;
	node->east=NULL;
	node->west=NULL;
}

*Node get_node(int x, int y){

}

bool free_maze(Maze *maze){

}

bool free_node(Node *node){

}
