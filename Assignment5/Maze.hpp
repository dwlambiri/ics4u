#ifndef MazeClass
#define MazeClass
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
	   @name    Maze::findstart
	   @param   void
	   @return  bool
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	bool findstart(void);

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

	/**
	  -------------------------------------------------------------------------
	   @name  callFP
	   @param
	   @return  void
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	void callFP();

	/**
	  -------------------------------------------------------------------------
	   @name  getnumRows
	   @param
	   @return  int
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	int getNumRows() const {
		return numRows;
	}

	/**
	  -------------------------------------------------------------------------
	   @name  getnumCols
	   @param
	   @return  int
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	int getNumCols() const {
		return numCols;
	}

	/**
	  -------------------------------------------------------------------------
	   @name  getnumRows
	   @param
	   @return  apmatrix<char>
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	apmatrix<char>& getMaze() {
		return maze;
	}


	void closeWindow() {
		ge.allegroEventLoop();
	}

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

	/**
	  -------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 24, 2017
	   @name    Maze::findPath
	   @param
	   @return  bool
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	bool findPath(int, int);

}; //end-of-class Maze

#endif
