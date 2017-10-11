#include <iostream>
#include <ctime>
#include <cstdlib>
#include "apclasses/apvector.h"

const int daysInAYear_c = 365;
const int peopleInClass_c = 20;

bool randomDates(apvector<int> &daysOfYear, int &day) {
	for (int i = 0; i < peopleInClass_c; i++) {
		daysOfYear[(rand() % daysInAYear_c + 1)]++;
	}
	for (int i = 0; i < daysInAYear_c; i++) {
		if (daysOfYear[i] >= 2) {
			day = i;
			return true;
		}
	}
	return false;
}

int main() {
	srand(time(0));

	int counter = 0;


	for (int i = 0; i < 10000; i++) {
		apvector<int> daysOfYear((daysInAYear_c + 1), 0);
		int day = -1;
		if (randomDates(daysOfYear, day)) {
			std::cout << "2 Birthdays are the same!! Day #: " << day
					<< std::endl;
			counter++;
		}
		//else std::cout << "No similar Birthdays" << std::endl;
	}
	std::cout << std::endl << "Number of times at least 2 birthdays were the same was " << counter
			<< "/10000" << std::endl;
	return 0;
}
