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
int main(int argc, char **argv) {

	FloatCalculator test;
	std::string array;

	const int w_c = 1200;
	const int h_c = 800;
	GraphicsEngine ge;

	bool initok = ge.initAllegro("RPN Calculator", w_c, h_c);
	if (initok) {
		ge.initCalculator();
		ge.drawCalculator();
	} else {
		std::cerr << "error: could not init allegro. running in terminal mode"
				<< std::endl;
	}

	std::cout << "Welcome to the RPN calculator" << std::endl;
	std::cout << "Type quit to exit the calculator" << std::endl;
//	if(initok) {
//		ge.allegroEventLoop();
//	}
	while (true) {
		std::ostringstream out;
		std::ostringstream error;
		const int topNum_c = 11;
		std::vector<float> topofstack(topNum_c);

		std::cout << "#";
		std::getline(std::cin, array);
		if (strstr(array.c_str(), "quit") != nullptr) {
			return 0;
		}
		if (test.parse(array) == false) {
			error << "error: bad expression" << std::endl;

			if (initok) {
				ge.setErrorString(error.str());
			} else {
				std::cerr << error.str() << std::endl;
			}
		}
		test.getTopOfStack(topofstack, topNum_c);
		if (initok) {
			ge.setVector(topofstack);
			ge.setErrorString(error.str());
		} else {
			if (topofstack.size() == 0) {
				std::cout << "empty stack" << std::endl;
			} else {
				std::cout << "stack contains " << topofstack[0] << " elements"
						<< std::endl;
				for (int i = 1; i < topofstack.size(); i++) {
					std::cout << topofstack[i];
					if (i == 1) {
						std::cout << "    [Top of stack]" << std::endl;
					} else {
						std::cout << std::endl;
					}
				} //end-of-for
			}
		}
		if (initok) {
			ge.drawCalculator();
		}

	}
	return 0;
}
