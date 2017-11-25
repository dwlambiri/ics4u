/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   Maze.cpp
 *	Course: ICS4U
 *	Date:   Nov 24, 2017
 *
 *	Purpose:
 *
 *	Usage: This file contains methods to read in and solve a maze from a text
 *			file
 *
 *	Revision History:
 *
 *	Known Issues: NONE
 *
 *****************************************************************************/


#include "Maze.hpp"

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Maze::Maze
   @details
	  Standard maze constructor which requires a text file\n
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
	  Reads in the contents of the maze from a textfile\n
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
	  Standard maze destructor that cleans up allegro\n
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
	  Finds the start of the maze\n
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
			if (maze[i][j] == 'a')
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
	  Calls the recursive algorithm for the first time by passing the
	  private data\n
  --------------------------------------------------------------------------
 */
void
Maze::callFP() {
	findPath(startRow, startCol, 'v');
	maze[startRow][startCol] = 'S';
} // end-of-method Maze::callFP


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Maze::findPath
   @details
	  This algorithm recursively solves the maze by checking possible
	  paths and either marking them as not useful(does not lead to the
	  termination) or with an arrow character which tells the user from
	  where the path moved.\n
  --------------------------------------------------------------------------
 */
bool
Maze::findPath(int curR, int curC, char dir) {
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
	else if (maze[curR][curC] == 'G')
		return true;
	//Checks if the maze location is a wall
	else if (maze[curR][curC] == '#')
		return false;
	//Checks if the location in the path is already marked
	else if((maze[curR][curC] == 'v')||
			(maze[curR][curC] == '^')||
			(maze[curR][curC] == '<')||
			(maze[curR][curC] == '>'))
		return false;
	else if (maze[curR][curC] == 'a')
		return false;

	//Marks the path as visited with a direction sign
	if(maze[curR][curC] != 'S')
		maze[curR][curC] = dir;
	
	if(dir == '^') {
		//NORTH
		if(findPath(curR-1, curC, '^'))
			return true;
		//SOUTH
		if(findPath(curR+1, curC, 'v'))
			return true;
		//WEST
		if(findPath(curR, curC-1, '<'))
			return true;
		//EAST
		if(findPath(curR, curC+1, '>'))
			return true;
	}
	else if(dir == 'v') {
		//SOUTH
		if(findPath(curR+1, curC, 'v'))
			return true;
		//NORTH
		if(findPath(curR-1, curC, '^'))
			return true;
		//WEST
		if(findPath(curR, curC-1, '<'))
			return true;
		//EAST
		if(findPath(curR, curC+1, '>'))
			return true;

	} 	else if(dir == '<') {
		//WEST
		if(findPath(curR, curC-1, '<'))
			return true;
		//EAST
		if(findPath(curR, curC+1, '>'))
			return true;
		//NORTH
		if(findPath(curR-1, curC, '^'))
			return true;
		//SOUTH
		if(findPath(curR+1, curC, 'v'))
			return true;
	}	else if(dir == '>') {
		//EAST
		if(findPath(curR, curC+1, '>'))
			return true;
		//WEST
		if(findPath(curR, curC-1, '<'))
			return true;
		//NORTH
		if(findPath(curR-1, curC, '^'))
			return true;
		//SOUTH
		if(findPath(curR+1, curC, 'v'))
			return true;
	}
	

	if(maze[curR][curC] != 'S')
		maze[curR][curC] = 'a';

	return false;
	
} // end-of-method Maze::findPath



