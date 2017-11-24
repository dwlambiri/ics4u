#include <iostream>
#include <apmatrix.h>
#include <fstream>
#include <string>
#include "apmatrix.h"
#include <ctype.h>
#include "Maze.hpp"
#include "GraphicsEngine.hpp"


int main(int argc, char* argv[]){
	std::string filename;

	if (argc < 2) {
		std::cout <<"What is the name of your maze textfile?" << std::endl;
		std::cin >> filename;
	} else {
		filename = argv[1];
	} //end-of-if


	Maze mymaze(filename);
	if(!mymaze.readIn()){
		std::cout << filename << " does not exist" << std::endl;
		return 1;
	}

	if(!mymaze.findstart()){
		return 1;
	}

	mymaze.printMaze();


	GraphicsEngine ge(mymaze);
	const int w_c = 1200;
	const int h_c = 800;
		 /* The following line calls a method in the GraphicsEngine class,
			initAllegro, which initializes all of the allegro primitives.
			The method will return false if an allegro initialization has an error
			and thus the program will run in terminal mode which only accepts input
			and delivers output from the terminal.
		 */
		bool initok = ge.initAllegro("RPN Calculator", w_c, h_c);


		/*
		 * The following method will return false and subsequently destroy the
		   thread if the the user presses the "close window" button.
		   The method will return with true if the variable quit is
		   set to true.
		 */
		ge.allegroEventLoop();
		ge.cleanUp();




	return 0;
}
