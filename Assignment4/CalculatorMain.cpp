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
#include <thread>

#include "FloatCalculator.hpp"
#include "GraphicsEngine.hpp"

static std::string cmdLine;
static bool ready = false;
static bool quit = false;

void foo() {
	while (true) {
		while (ready == true)
			;
		std::cout << "#";
		std::getline(std::cin, cmdLine);
		if (strstr(cmdLine.c_str(), "quit") != nullptr) {
			quit = true;
			return;
		}
		ready = true;
	}
}

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

	FloatCalculator calculator;

	const int w_c = 1200;
	const int h_c = 800;
	GraphicsEngine ge;

	std::cout << "Welcome to the RPN calculator" << std::endl;
	std::cout << "Type quit to exit the calculator" << std::endl;

	bool initok = ge.initAllegro("RPN Calculator", w_c, h_c);
	if (initok) {
		ge.initCalculator();
		ge.drawCalculator();
		std::thread pthread(foo);
		ge.allegroEventLoop(calculator, &cmdLine, &ready, &quit);
		pthread.join();
		ge.cleanUp();
	} else {
		std::cerr << "error: could not init allegro. running in terminal mode"
				<< std::endl;
		while (true) {
			std::ostringstream out;
			std::ostringstream error;
			const int topNum_c = 11;
			std::vector<float> topofstack(topNum_c);

			std::cout << "#";
			std::getline(std::cin, cmdLine);
			if (strstr(cmdLine.c_str(), "quit") != nullptr) {
				return 0;
			}
			if (calculator.parse(cmdLine) == false) {
				error << "error: bad expression";
			}
			std::cerr << error.str() << std::endl;
			calculator.getTopOfStack(topofstack, topNum_c);
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
	}
	return 0;
}
