/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   MazeMain.cpp
 *	Course: ICS4U
 *	Date:   Nov 24, 2017
 *
 *	Purpose: This is the main program which uses the GraphicsEngine class
 *				as well as the maze class.
 *			The user is also able to enter the textfile name either by writing
 *				it as a command line parameter or by manually typing it in at
 *				the start of the program.
 *
 *	Usage:
 *
 *	Revision History:
 *
 *	Known Issues: NONE
 *
 *****************************************************************************/


#include <iostream>
#include <apmatrix.h>
#include <fstream>
#include <string>
#include "apmatrix.h"
#include <ctype.h>
#include "Maze.hpp"
#include <math.h>


int main(int argc, char* argv[]){
	std::string filename;

	srand(time(0));

	if (argc < 2) {
		std::cout <<"What is the name of your maze textfile?" << std::endl;
		std::cin >> filename;
	} else {
		filename = argv[1];
	} //end-of-if


	Maze mymaze(filename);

	if(mymaze.callFP() == true) {
		std::cout << std::endl << "success: solved maze" << std::endl;
	}
	else {
		std::cout << std::endl << "error: could not solved maze" << std::endl;
	}
	return 0;
}
