#include "maze.h"
#include "solvers.h"
#include <errno.h>

void setup()
{  
  
  Serial.begin(9600);
  
  Maze *maze = create_maze();
  
  flood_explore(maze);
  
  free_maze(maze);
}

void loop(){

}

