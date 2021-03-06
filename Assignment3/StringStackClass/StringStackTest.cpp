/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   StringStackTest.cpp
 *	Course: ICS4U
 *	Date:   Oct 23, 2017
 *
 *	Purpose:
 *
 *	Usage:
 *
 *	Revision History:
 *
 *	Known Issues:
 *
 *****************************************************************************/

#include "StringStack.hpp"
#include "StringStack.cpp"
#include <iostream>


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 23, 2017
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

	StringStack testStack(0);

	testStack.push("one");
	testStack.push("+");
	testStack.push("two");

	StringStack copyStack(testStack);

	std::cout << *testStack.top() << std::endl;
	testStack.pop();
	std::cout << *testStack.top() << std::endl;
	testStack.pop();
	std::cout << *testStack.top() << std::endl;
	testStack.pop();

	std::cout << *copyStack.top() << std::endl;
	copyStack.pop();
	std::cout << *copyStack.top() << std::endl;
	copyStack.pop();
	std::cout << *copyStack.top() << std::endl;
	copyStack.pop();


	return 0;
}
