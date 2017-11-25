#include <iostream>
#include <apmatrix.h>
#include <fstream>
#include <string>
#include "apmatrix.h"
#include <ctype.h>
#include "Maze.hpp"


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




		mymaze.callFP();
		std::cout << std::endl << "solved maze" << std::endl;
		mymaze.printMaze();
		mymaze.closeWindow();


	return 0;
}
