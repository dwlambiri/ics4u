/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   SortMain.cpp
 *	Course: ICS4U
 *	Date:   Jan 12, 2018
 *
 *	Purpose:This is the file which contains the main function for the sorting
 *				program. It creates an object (Sort mysort) which contains
 *				all of the sorting methods. The user is able to ask for a
 *				specific sort and array size through the command line or through
 *				terminal input.
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
	int indeces = 200;
    //bool algorithmGo = false;

	char salgo = 'b';
	//determines type of sort needed from user input
	switch (argc) {
		case 3:
			indeces = atoi(argv[1]);
			salgo = argv[2][0];
			break;
		case 2:
			indeces = atoi(argv[1]);
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

	//Creates the sorting object with indeces number of elements
	Sort mysort(indeces);

	//Calls the callFP method which sorts the vector.
	//Any error will be caught and messaged accordingly
	if(mysort.callFP(salgo) == true) {
        //algorithmGo = true;
		std::cout << std::endl << "success: vector is sorted" << std::endl;
	}
	else {
		std::cout << std::endl << "error: could not sort the vector" << std::endl;
	}

	return 0;
}
