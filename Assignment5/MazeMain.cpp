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
	std::string filename = "";

	srand(time(0));
	int row = 30;
	int fill = 6;

	switch (argc) {
		case 1:
			std::cout << "will auto generate maze" << std::endl;
			break;
		case 2:
			filename = argv[1];
			break;
		case 3:
			row = atoi(argv[1]);
			fill = atoi(argv[2]);
			break;
		default:
			break;
	} //end-switch(argc)

	Maze mymaze(filename, row, row, fill);

	if(mymaze.callFP() == true) {
		std::cout << std::endl << "success: solved maze" << std::endl;
	}
	else {
		std::cout << std::endl << "error: could not solved maze" << std::endl;
	}
	return 0;
}
