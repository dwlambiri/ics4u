/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   TestFloatCalculator.cpp
 *	Course: ICS4U
 *	Date:   Oct 28, 2017
 *
 *	Purpose: This program is used to test the FloatCalculator class
 *
 *	Usage:
 *
 *	Revision History:
 *
 *	Known Issues:
 *
 *****************************************************************************/

#include <iostream>
#include <string.h>
#include <string>

#include "FloatCalculator.hpp"
/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 28, 2017
   @name    main
   @param   argc number of command line arguments
   @param   argv command line arguments
   @return  the return code
   @details
	The main function of the program.
	\n
  --------------------------------------------------------------------------
 */
int
main(int argc, char **argv) {
	FloatCalculator test;
	std::string array;

	while(true) {
		std::cout << "#";
		std::getline(std::cin,array);
		if(strcmp("quit",array.c_str())== 0) {
			return 0;
		}
		if(test.parse(array) == true) {
			float* t = test.top();
			if(t) {
				std::cout <<"result =  "<< *t << std::endl;
			}
			else {
				std::cerr << "error: no result on stack" << std::endl;
			}
		}
	}
	return 0;
}
