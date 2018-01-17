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
    //bool algorithmGo = false;

	char salgo = 'b';

	switch (argc) {
		case 3:
			row = atoi(argv[1]);
			salgo = argv[2][0];
			break;
		case 2:
			row = atoi(argv[1]);
			std::cout << "Would you like 'b'ubble,'m'erge, 's'election, or 'q'uick sort" << std::endl;
			std::cin >> salgo;
			break;
		case 1:
		    std::cout << "Would you like 'b'ubble,'m'erge, 's'election, or 'q'uick sort" << std::endl;
			std::cin >> salgo;
			break;
		default:
			break;
	} //end-switch(argc)

	std::cout << "will auto generate vector to sort" << std::endl;
    std::cout << "1/100 FPS" << std::endl;


	Sort mysort(row, row);

	if(mysort.callFP(salgo) == true) {
        //algorithmGo = true;
		std::cout << std::endl << "success: vector is sorted" << std::endl;
	}
	else {
		std::cout << std::endl << "error: could not sort the vector" << std::endl;
	}

	return 0;
}
