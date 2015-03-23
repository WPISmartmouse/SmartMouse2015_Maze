/*! \mainpage SmartMouse V3 Index Page
 *
 * \section intro_sec Introduction
 *
 * All function documentation is done in the header files. To see notes for each function, click on the header file it belongs to.

 * If there are any issues/bugs, use the issue tracker on the github repository. 
 * 	[Issue tracker] (https://github.com/WPISmartmouse/SmartMouse2015_Maze/issues)
 *
 * \section install_sec_linux Installation (Linux)
 *
 * \subsection step1_linux Clone the repository

 *      git clone https://github.com/WPISmartmouse/SmartMouse2015_Maze/
 *
 * \section install_sec_mac Installation (Mac)
 *
 * \subsection step1_mac Figure it out yourself
 *
 * \section install_sec_win Installation (Windows)
 *
 * \subsection step1_win No.
 *
 */

#include "maze.h"
#include "maze_io.h"
#include "solvers.h"

int main(){

	srand(time(NULL));

	FILE *f = fopen("mazes/16x16.mz","r");

	Maze *maze = read_from_file(f);

	flood_explore(maze);
	
	return EXIT_SUCCESS;
}