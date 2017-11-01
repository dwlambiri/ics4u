/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   StringStack.cpp
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

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 23, 2017
   @mname   StringStack::StringStack
   @details
	  \n
  --------------------------------------------------------------------------
 */

StringStack::StringStack() {
	mStackSize = 50;
	mStack = new std::string[mStackSize];
	mElementsInStack = 0;

} // end-of-method StringStack::StringStack


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 23, 2017
   @mname   StringStack::~StringStack
   @details
	  \n
  --------------------------------------------------------------------------
 */

StringStack::~StringStack() {

	if (mStackSize > 0) {
		delete [] mStack;
	} //end-of-if

} // end-of-method StringStack::~StringStack

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 23, 2017
   @mname   StringStack::StringStack
   @details
	  The efficiency of the algorithm is: n
  --------------------------------------------------------------------------
 */

StringStack::StringStack(StringStack& param) {

	mStackSize = param.mStackSize;
	mStack = new std::string[mStackSize];
	mElementsInStack = param.mElementsInStack;
	for (unsigned int i = 0; i < mElementsInStack; i++ ) {
		mStack[i] = param.mStack[i];
	} //end-of-for
} // end-of-method StringStack::StringStack



/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 23, 2017
   @mname   StringStack::StringStack
   @details
	  \n
  --------------------------------------------------------------------------
 */

StringStack::StringStack(unsigned int stackSize) {

	if (stackSize == 0) {
		mStackSize = 1;
	} else {
		mStackSize = stackSize;
	} //end-of-if
	mStack = new std::string[mStackSize];
	mElementsInStack = 0;
} // end-of-method StringStack::StringStack


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 23, 2017
   @mname   StringStack::top
   @details
	  \n
  --------------------------------------------------------------------------
 */
std::string*
StringStack::top() const{
	if (empty()) {
		return nullptr;
	} //end-of-if
	return &(mStack[mElementsInStack - 1]);
} // end-of-method StringStack::top

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 23, 2017
   @mname   StringStack::push
   @details
	  The normal computational complexity for pushing an element to the stack
	  is 1. However if the stack is full, and the user attempts to push in a
	  new element the stack will increase in size. The two loops present in
	  the expand() function make the computational complexity of this step
	  2n+1.
  --------------------------------------------------------------------------
 */
void
StringStack::push(std::string& param) {
	if (full()) {
		expand();
	} //end-of-if
	mStack[mElementsInStack++] = param;
} // end-of-method StringStack::push

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 23, 2017
   @mname   StringStack::push
   @details
	  \n
  --------------------------------------------------------------------------
 */
void
StringStack::push(const char* param) {
	std::string s(param);
	push(s);
} // end-of-method StringStack::push



/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 23, 2017
   @mname   StringStack::pop
   @details
	  \n
  --------------------------------------------------------------------------
 */
void
StringStack::pop() {

	if (empty()) {
		return;
	} else {
		mElementsInStack--;
	} //end-of-if
} // end-of-method StringStack::pop


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 23, 2017
   @mname   StringStack::expand
   @details
	  The efficiency of this algorithm is 2n (with n representing the number
        of elements in the stack.
      There are n steps in the first loop, which copies the contents of the
        first stack, iterates through each element of the stack and copies
        it into a temporary array.
      The second loop is implicit and occurs with the use of the '=' sign
        to copy the contents of the temporary array back into the stack array
  --------------------------------------------------------------------------
 */
void
StringStack::expand() {
	mStackSize *= 2;
	std::string* tmp = new std::string[mStackSize];
	for (unsigned int i = 0; i < mElementsInStack; i++ ) {
		tmp[i] = mStack[i];
	} //end-of-for
	delete [] mStack;
	mStack = tmp;

} // end-of-method StringStack::expand



