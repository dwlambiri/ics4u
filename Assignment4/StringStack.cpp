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
	  \n
  --------------------------------------------------------------------------
 */

StringStack::StringStack(unsigned int stackSize) {

	mStackSize = stackSize;
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
StringStack::top() {
	if (mElementsInStack == 0) {
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
	  \n
  --------------------------------------------------------------------------
 */
void
StringStack::push(std::string& param) {
	if (mElementsInStack >= mStackSize) {
		return;
	} else {
		mStack[mElementsInStack++] = param;
	} //end-of-if
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

	if (mElementsInStack >= mStackSize) {
		return;
	} else {
		mStack[mElementsInStack++] = std::string(param);
	} //end-of-if
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

	if (mElementsInStack == 0) {
		return;
	} else {
		mElementsInStack--;
	} //end-of-if
} // end-of-method StringStack::pop






