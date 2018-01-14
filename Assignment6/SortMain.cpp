/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   SortMain.cpp
 *	Course: ICS4U
 *	Date:   Jan 12, 2018
 *
 *	Purpose:
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
#include "Sort.hpp"
#include <math.h>


int main(int argc, char* argv[]){

	srand(time(0));
	int row = 30;

	switch (argc) {
		case 2:
			row = atoi(argv[1]);
			break;
		case 1:
			break;
		default:
			break;
	} //end-switch(argc)

	std::cout << "will auto generate vector to sort" << std::endl;

	Sort mysort(row, row);

	if(mysort.callFP() == true) {
		std::cout << std::endl << "success: solved maze" << std::endl;
	}
	else {
		std::cout << std::endl << "error: could not solved maze" << std::endl;
	}
	return 0;
}
