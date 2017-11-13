/*****************************************************************************
 *	Name:                                                                    *
 *	Course:                                                                  *
 *	Date:                                                                    *
 *	                                                                         *
 *	Purpose:                                                                 *
 *	                                                                         *
 *	Usage:                                                                   *
 *	                                                                         *
 *	Revision History:                                                        *
 *	                                                                         *
 *	Known Issues:                                                            *
 *	                                                                         *
 *****************************************************************************/

// CityList.CPP
// Maintain an ordered list of cities using a linked list
// Modified from Menu.cpp Author: Bill Wares
#include <iostream>
#include <iomanip>
#include <cctype>                 // Declares toupper(ch)
using namespace std;
#include "apstring.cpp"
#include "List.h"
#include "List.cpp"

int main() {
	char cmd;
	apstring city;
	apstring filename;
	List Cities;

	cout << endl << "    ICS4U Linked List Assignment" << endl;
	cout << "      List of Cities System " << endl;

	while (true) {  // Repeat (until break)

		// Show the menu and prompt:

		cout << "\n";  // Output a blank line

		cout << "\t (L)oad list of cities\n";      // '\t' is tab
		cout << "\t (A)dd city\n";
		cout << "\t (R)emove city\n";
		cout << "\t (D)isplay cities\n";
		cout << "\t (S)ave cities";
		cout << "\t (Q)uit\n";
		cout << endl;
		cout << "Next command ==> ";

		// Accept command:

		cin >> cmd;             // Read one char.
		cin.ignore(80, '\n');   // Skip remaining input (up to 80
								//   chars) to the end of the line.
		cmd = toupper(cmd);     // Convert letter to upper case
								//   to allow lower case input
								//   for commands (for convenience).

		// Quit if 'Q'

		if (cmd == 'Q')
			break;                  // Quit processing commands

		cout << "\n\n****************************************\n";

		// Process command:

		switch (cmd) {

		case 'A':           // Add City

			cout << "City Name: ";
			getline(cin, city);     // allow for names with spaces.
			Cities.insert(city);

			break;

		case 'R':           // remove City

			cout << "City Name: ";
			getline(cin, city);     // allow for names with spaces.
			Cities.remove(city);

			break;

		case 'L':           // Load cities from file

			cout << "File Name: ";
			cin >> filename;
			if (Cities.load(filename))
				Cities.show();
			break;

		case 'D':          //  List Cities
			Cities.show();
			break;

		case 'S':          //  List Cities
			Cities.save(filename);
			Cities.show();
			break;

		}

		cout << "****************************************\n";
	}
	return 0;
}

