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

Maze::Maze(std::string& filename, int rows, int cols, int fillv) : maze(rows,cols) {
	numRows = rows;
	numCols = cols;
	fill    = fillv;
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
	}
	else {
		std::cout << "file " << filename << " does not exist" << std::endl;
		std::cout << "will generate maze of size " << numRows << " x  " <<  numCols << " fill = " << fill << std::endl;
		maze.resize(numRows, numCols);
		mazeGenerator(numRows, numCols, fill);
	} //end-of-if

	float xr = (float)w_c/numCols;
	float yr = (float)h_c/numRows;
	float r = (xr >yr)?yr:xr;
	return ge.initAllegro("Recursive Maze Solver", r*numCols, r*numRows);

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
Maze::findStart() {

	bool foundStartPoint = false;

	for (int r = 0; r < maze.numrows(); r++)
		for (int c = 0; c < maze.numcols(); c++){
			if (maze[r][c] == 'S'){
				foundStartPoint = true;
				startRow = r;
				startCol = c;
			}
		}
	std::cout << "starting point is (" << startRow << "," << startCol << ")" << std::endl;
	return foundStartPoint;
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
	  private data (startRow and startCol)\n
  --------------------------------------------------------------------------
 */
bool
Maze::callFP() {
	if(!readIn()){
		std::cout << filename << " does not exist" << std::endl;
		return false;
	}


	if(!findStart()) {
		std::cout << "error: could not find a starting point" << std::endl;
		return false;
	}

	printMaze();
	if(!findPath(startRow, startCol, down_c)) {
		std::string err = "could not find an exit";
		std::cout << "error: " << err << std::endl;
		ge.errorBox(err);
		ge.allegroEventLoop();
		return false;
	}
	std::string success = "solved the maze";
	ge.okBox(success);
	std::cout << "success: " << success << std::endl;
	printMaze();
	ge.allegroEventLoop();

	return true;

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


	ge.pauseOnDisplayFrame();
	ge.drawMaze(maze);
	//Check for exceeding the bounds of the maze
	if (curR <= -1 || curC <= -1 || curR >= maze.numrows() || curC >= maze.numcols())
		return false;
	//Checks if it is at the maze exit or an invalid space
	else {
		switch (maze[curR][curC]) {
		case exit_c:
			return true;
		case wall_c:
		case down_c:
		case up_c:
		case left_c:
		case right_c:
		case visited_c:
			return false;
		default:
			break;
		} //end-switch(maze[curR][curC])
	}

	static const int noDir_c = 4;
	Maze::Move move[noDir_c];


	//Marks the path as visited with a direction sign
	if(maze[curR][curC] != start_c)
		maze[curR][curC] = dir;

	/*
	 * @author   dwlambiri
	 * @date     Nov 25, 2017
	 *	I implemented a heuristic that works as follows:
	 *	It tries to maintain direction.
	 *	If it cannot, it uses a coin toss to switch direction at
	 *		90 degrees.
	 *	The randomization makes the algorithm more fun to watch.
	 *	As well as providing "cleaner" paths.
	 *	If that is unsuccessful, it tries opposite direction.
	 *	This heuristic does not change the performance of the
	 *		algorithm which remains O(rows * cols).
	 */

	int r = rand()%2;
	if(dir == up_c) {
		move[0] = {curR-1, curC, up_c};
		move[1+r] = {curR, curC-1, left_c};
		move[2-r] = {curR, curC+1, right_c};
		move[3] = {curR+1, curC, down_c};

	}
	else if(dir == down_c) {
		move[3] = {curR-1, curC, up_c};
		move[2-r] = {curR, curC-1, left_c};
		move[0] = {curR+1, curC, down_c};
		move[1+r] = {curR, curC+1, right_c};
	}
	else if(dir == left_c) {
		move[2-r] = {curR-1, curC, up_c};
		move[0] = {curR, curC-1, left_c};
		move[1+r] = {curR+1, curC, down_c};
		move[3] = {curR, curC+1, right_c};
	}
	else if(dir == right_c) {
		move[1+r] = {curR-1, curC, up_c};
		move[3] = {curR, curC-1, left_c};
		move[2-r] = {curR+1, curC, down_c};
		move[0] = {curR, curC+1, right_c};
	}

	/*
	 * @author   dwlambiri
	 * @date     Nov 25, 2017
	 *  This calls the function recursively four times,
	 *  	one call is for each direction.
	 *  The order depends upon the previously explained heuristic.
	 */

	for (int i = 0; i < noDir_c; ++i) {
		if((move[i].dir != wall_c) && (findPath(move[i].x, move[i].y, move[i].dir) == true)) {
			return true;
		}
	}//end-of-for

	if(maze[curR][curC] != start_c)
		maze[curR][curC] = visited_c;

	return false;

} // end-of-method Maze::findPath

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 26, 2017
   @mname   Maze::mazeGenerator
   @details
	  \n
  --------------------------------------------------------------------------
 */
void
Maze::mazeGenerator(int rows, int cols, int fill) {

	for (int r = 0; r < rows; r++){
		for(int c = 0; c < cols; c++){
			maze[r][c] = (rand()% fill)?'.':'#';
		}
	}

	maze[rand()% rows][rand()% cols] = 'S';
	maze[rand()% rows][rand()% cols] = 'G';

} // end-of-method Maze::mazeGenerator




