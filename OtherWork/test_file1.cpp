#include "apclasses/apstring.h"
#include "apclasses/apstring.cpp"
#include <iostream>

int main(){

	apstring line;
	getline(std::cin, line);
	int result;
	line.math(result);
	std::cout << result << std::endl;
	return 0;
}
