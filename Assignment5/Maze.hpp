/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   Maze.hpp
 *	Course: ICS4U
 *	Date:   Nov 24, 2017
 *
 *	Purpose: This is a Maze class declaration
 *
 *	Usage:
 *
 *	Revision History:
 *
 *	Known Issues: NONE
 *
 *****************************************************************************/


#ifndef MAZE_H_
#define MAZE_H_
#include <iostream>
#include <fstream>
#include <string>
#include "apmatrix.h"
#include <ctype.h>
#include "GraphicsEngine.hpp"
/**
  ---------------------------------------------------------------------------
   @author     dwlambiri
   @date       Nov 24, 2017
   @classname  Maze
   @brief
	 \n
   @details
	\n
  ---------------------------------------------------------------------------
 */
class Maze {

public:
	//--------------------------------------------------
	// Public Methods (External Type Interface)
	//--------------------------------------------------
	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 24, 2017
	   @name    Maze::Maze
	   @param   -
	   @return  -
	   @details
		Default constructor of Class Maze \n
	  --------------------------------------------------------------------------
	 */
	Maze(std::string& filename);

	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 24, 2017
	   @name    Maze::~Maze
	   @param   -
	   @return  -
	   @details
		Default destructor of class Maze \n
	  --------------------------------------------------------------------------
	 */
	~Maze();

	/**
	  -------------------------------------------------------------------------
	   @name  callFP
	   @param
	   @return  void
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	bool callFP();

private:
	//--------------------------------------------------
	// Data Members
	//--------------------------------------------------


private:
	int numRows;
	int numCols;
	int startRow;
	int startCol;
	std::string filename;
	apmatrix<char> maze;
	static const int w_c = 1200;
	static const int h_c = 800;

	static const char visited_c = 'a';
	static const char exit_c = 'G';
	static const char start_c = 'S';
	static const char wall_c = '#';
	static const char down_c = 'v';
	static const char up_c = '^';
	static const char left_c = '<';
	static const char right_c = '>';
	static const char open_c = '.';

	GraphicsEngine ge;

	//--------------------------------------------------
	// Private Methods
	//--------------------------------------------------
	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 24, 2017
	   @name    Maze::Maze
	   @param   -
	   @return  -
	   @details
		Default constructor of Class Maze \n
	  --------------------------------------------------------------------------
	 */
	Maze();

	struct Move {
		int x;
		int y;
		char dir;
	};

	/**
	  -------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 24, 2017
	   @name    Maze::findPath
	   @param
	   @return  bool
	   @details
		  This method was made private because it only needs to be called
		  from the callFC method which uses the private data to be passed
		  as parameters. \n
	  -------------------------------------------------------------------------
	 */
	bool findPath(int, int, char);

	/**
	  -------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 24, 2017
	   @name    Maze::findstart
	   @param   void
	   @return  bool
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	bool findStart(void);

	/**
	  -------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 24, 2017
	   @name    Maze::readIn
	   @param   std::string filename
	   @return  bool
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	bool readIn();

	/**
	  -------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 24, 2017
	   @name    Maze::printMaze
	   @param
	   @return  void
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	void printMaze();



}; //end-of-class Maze

#endif
