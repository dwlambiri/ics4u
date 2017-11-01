/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   CalculatorMain.cpp
 *	Course: ICS4U
 *	Date:   Oct 28, 2017
 *
 *	Purpose: Assigment4
 *
 *	Usage: The user inputs either an expression into the terminal, or
    may press buttons on an allegro display.
    The operands and numbers inputed will be stored into a stack. Any operators
    placed into the stack will be read in as "operands" (will be explained
    further in FloatCalculator.cpp) and functions of various arities can
    be performed on them.
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
#include <time.h>
#include "FloatCalculator.hpp"
#include "GraphicsEngine.hpp"

/*
 * The string, cmdLine reads in a line from std::cin which will be passed
 * to the FloatCalculator class, interpreted using the parse method and then
 * the output will be printed into an allegro display or send to std::cout
 *
 */
static std::string cmdLine;

/*
 * @author   dwlambiri
 * @date     Oct 31, 2017
 *  global variable ready is used to communicate between 2 threads:
 *    it is set to true when a command line is read from std::cin
 *    and set to false from GraphicsEngine::allegroEventLoop
 *    after the command has been processed
 */

static bool ready = false;

/*
 * @author   dwlambiri
 * @date     Oct 31, 2017
 *  the variable quit is set to true when the user types quit
 *  in the command line
 */

static bool quit = false;


/*
 * @author   dwlambiri
 * @date     Oct 31, 2017
 *  this function will be launched from the thread
 *  to read the user input in a terminal
 */

void foo() {
	while (true) {
		while (ready == true);
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
	srand(time(0));
	FloatCalculator calculator;

	const int w_c = 1200;
	const int h_c = 800;
	GraphicsEngine ge;

	std::cout << "Welcome to the RPN calculator" << std::endl;
	std::cout << "Type quit to exit the calculator" << std::endl;

	/*
	 * The following line calls a method in the GraphicsEngine class,
        initAllegro, which initializes all of the allegro primitives.
        The method will return false if an allegro initialization has an error
        and thus the program will run in terminal mode which only accepts input
        and delivers output from the terminal.
      */
	bool initok = ge.initAllegro("RPN Calculator", w_c, h_c);
	if (initok) {
		/*
		 * The following declares a thread which accesses a function that loops
		   infinitely in wait of user input in the terminal. While there is no
		   input the terminal, the second thread remains blocked.
		*/
		std::thread pthread(foo);
		/*
		 * The following method will return false and subsequently destroy the
		   thread if the the user presses the "close window" button.
		   The method will return with true if the variable quit is
		   set to true.
		 */
		if(ge.allegroEventLoop(calculator, &cmdLine, &ready, &quit) == false){
			pthread.~thread();
		}
		else {
			pthread.join();
		}
		ge.cleanUp();
	} else {
		/*
		 * @author   dwlambiri
		 * @date     Oct 31, 2017
		 *  if allegro cannot initialize, the program runs in command line
		 *  mode only. in this case the program has only one thread
		 */

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
