#include "Maze.hpp"

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Maze::Maze
   @details
	  \n
  --------------------------------------------------------------------------
 */

Maze::Maze(std::string& filename) : maze(1,1) {
	numRows = 0;
	numCols = 0;
	startRow = -1;
	startCol = -1;
	this->filename = filename;


} // end-of-method Maze::Maze


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   readIn
   @details
	  \n
  --------------------------------------------------------------------------
 */
bool
Maze::readIn() {

	std::ifstream file(filename);

	if (file.is_open()) {
		//gets the dimensions of the maze
		file >> numRows;
		file >> numCols;
		maze.resize(numRows, numCols);

		for (int r = 0; r < numRows; r++){
			for(int c = 0; c < numCols; c++){
				file >> maze[r][c];
			}
		}
		file.close();
		 /* The following line calls a method in the GraphicsEngine class,
			initAllegro, which initializes all of the allegro primitives.
			The method will return false if an allegro initialization has an error
			and thus the program will run in terminal mode which only accepts input
			and delivers output from the terminal.
		 */
	    return ge.initAllegro("Maze Solver", w_c, h_c);
	}
	else {
		std::cout << "file " << filename << " does not exist" << std::endl;
		return false;
	} //end-of-if

	return false;
} // end-of-method readIn


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Maze::~Maze
   @details
	  \n
  --------------------------------------------------------------------------
 */
Maze::~Maze() {
	ge.cleanUp();
} // end-of-method Maze::~Maze



/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Maze::findstart
   @details
	  \n
  --------------------------------------------------------------------------
 */
bool
Maze::findstart() {

	bool foundStart = false;

	    for (int r = 0; r < maze.numrows(); r++)
	        for (int c = 0; c < maze.numcols(); c++){
	            if (toupper(maze[r][c]) == 'S'){
	                foundStart = true;
	                startRow = r;
	                startCol = c;
	            }
	        }
	std::cout << "starting point is (" << startRow << "," << startCol << ")" << std::endl;
	 return foundStart;
} // end-of-method Maze::findstart

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Maze::printMaze
   @details
	  \n
  --------------------------------------------------------------------------
 */
void
Maze::printMaze() {
	for (int i = 0; i < numRows; i++){
		for (int j = 0; j < numCols; j++){
			if (maze[i][j] == 'v')
				std::cout<< '.';
			else{
				std::cout << maze[i][j];
			}
		}
		std::cout << std::endl;
	}
} // end-of-method Maze::printMaze


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Maze::callFP
   @details
	  \n
  --------------------------------------------------------------------------
 */
void
Maze::callFP() {
	findPath(startRow, startCol);
	maze[startRow][startCol] = 'S';
} // end-of-method Maze::callFP


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Maze::findPath
   @details
	  \n    
  --------------------------------------------------------------------------
 */
bool
Maze::findPath(int curR, int curC) {
	/*
	 * @author   dwlambiri
	 * @date     Nov 24, 2017
	 *  I am pausing the computation for 1/60 of a second.
	 *  After the pause I am drawing the maze, and I continue with the
	 *  	recursive function.
	 */

	ge.pause();
	ge.drawMaze(maze);
	//Check for exceeding the bounds of the maze
	if (curR <= -1 || curC <= -1 || curR >= maze.numrows() || curC >= maze.numcols())
		return false;
	//Checks if it is at the maze exit
	else if (toupper(maze[curR][curC]) == 'G')
		return true;
	//Checks if the maze location is a wall
	else if (maze[curR][curC] == '#')
		return false;
	//Checks if the location in the path is already marked
	else if (maze[curR][curC] == '+')
		return false;
	else if (maze[curR][curC] == 'v')
		return false;

	//Marks the path as visited with a + sign
	if(maze[curR][curC] != 'S')
		maze[curR][curC] = '+';
	
	//NORTH
	if(findPath(curR-1, curC))
		return true;
	
	//WEST
	if(findPath(curR, curC-1))
		return true;
	//EAST
	
	if(findPath(curR, curC+1))
		return true;
	
	//SOUTH
	if(findPath(curR+1, curC))
		return true;
	if(maze[curR][curC] != 'S')
		maze[curR][curC] = 'v';
	return false;
	
} // end-of-method Maze::findPath



