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

	ge.initAllegro("RPN Calculator", 800, 600);
	ge.initCalculator();
	ge.drawCalculator();
	ge.moveBitmapToDisplay();

	while(true) {
		std::ostringstream out;
		std::ostringstream  err;

		std::cout << "#";
		std::getline(std::cin,array);
		if(strcmp("quit",array.c_str())== 0) {
			return 0;
		}
		if(test.parse(array) == true) {
			float* t = test.top();
			if(t) {
				out <<"result =  "<< *t << std::endl;
			}
			else {
				out <<"result =  null" << std::endl;
			}
			ge.drawCalculator();
			ge.displayMessage(100, 100, whitePixel_c, out.str().c_str());
			ge.moveBitmapToDisplay();
		}
		else {
			err << "error: stack is empty" << std::endl;
			ge.drawCalculator();
			ge.displayMessage(100, 200, whitePixel_c, err.str().c_str());
			ge.moveBitmapToDisplay();
		}
	}
	return 0;
}
