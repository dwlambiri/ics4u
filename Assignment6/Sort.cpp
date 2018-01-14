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


#include "Sort.hpp"

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Maze::Maze
   @details
	  Standard maze constructor which requires a text file\n
  --------------------------------------------------------------------------
 */

Sort::Sort(int rows, int cols) {
	numRows = rows;
	numCols = cols;

	data.resize(numCols);

	generateVector();

} // end-of-method Maze::Maze




/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Maze::~Maze
   @details
	  Standard maze destructor that cleans up allegro\n
  --------------------------------------------------------------------------
 */
Sort::~Sort() {
	ge.cleanUp();
} // end-of-method Maze::~Maze




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
Sort::callFP() {

	float xr = (float)w_c/numCols;
	float yr = (float)h_c/numRows;
	float r = (xr >yr)?yr:xr;
	//float r = 20;

	if(!ge.initAllegro("Sorting Demo", r*numCols, r*numRows)) {
		return false;
	}

	if(!insertionSort()) {
		std::string err = "could not sort";
		std::cout << "error: " << err << std::endl;
		ge.errorBox(err);
		ge.allegroEventLoop();
		return false;
	}
	std::string success = "data is sorted";
	ge.okBox(success);
	std::cout << "success: " << success << std::endl;
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
Sort::insertionSort() {
	/*
	 * @author   dwlambiri
	 * @date     Nov 24, 2017
	 *  I am pausing the computation for 1/60 of a second.
	 *  After the pause I am drawing the maze, and I continue with the
	 *  	recursive function.
	 */


	for (int i = 0; i < numRows-1; ++i) {
		for (int j = i; j < numRows; ++j) {
			ge.pauseOnDisplayFrame();
			if(data[j] < data[i]) {
				int temp = data[j];
				data[j] = data[i];
				data[i] = temp;
			}
			ge.drawVector(data);
		}//end-of-for
	}//end-of-for

	return true;

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
Sort::generateVector() {

	for (int r = 0; r < numCols; r++){
			data[r] = rand()% numRows;
	}
} // end-of-method Maze::mazeGenerator




