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
#include <sstream>
#include <string.h>
#include <string>

#include "FloatCalculator.hpp"
#include "GraphicsEngine.hpp"

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
	GraphicsEngine ge;

	const int w_c = 1200;
	const int h_c = 800;

	ge.initAllegro("RPN Calculator", w_c, h_c);
	ge.initCalculator();
	ge.drawCalculator();

	while(true) {
		std::ostringstream out;
		std::ostringstream  error;
		std::vector<float>  topofstack(10);

		std::cout << "#";
		std::getline(std::cin,array);
		if(strcmp("quit",array.c_str())== 0) {
			return 0;
		}
		if(test.parse(array) == false) {
			error << "error: bad expression" << std::endl;
			ge.setErrorString(error.str());
		}
		else {
			test.getTopOfStack(topofstack, 10);
			ge.setVector(topofstack);
			ge.setErrorString(error.str());
		}
		ge.drawCalculator();

	}
	return 0;
}
