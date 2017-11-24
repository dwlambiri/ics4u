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
		return true;
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
		for (int j = 0; j < numCols; j++)
			std::cout << maze[i][j];
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

	//Marks the path as visited with a + sign
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

	maze[curR][curC] = '.';
	return false;
	
} // end-of-method Maze::findPath



