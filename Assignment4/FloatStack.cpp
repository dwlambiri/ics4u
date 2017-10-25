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

#include "FloatStack.hpp"

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
	mStack = new float[mStackSize];
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

StringStack::StringStack(StringStack& param) {

	mStackSize = param.mStackSize;
	mStack = new float[mStackSize];
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
	mStack = new float[mStackSize];
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
float*
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
	  \n
  --------------------------------------------------------------------------
 */
void
StringStack::push(float& param) {
	if (full()) {
		expand();
	} //end-of-if
	mStack[mElementsInStack++] = param;
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
	  \n
  --------------------------------------------------------------------------
 */
void
StringStack::expand() {
	mStackSize *= 2;
	float* tmp = new float[mStackSize];
	for (unsigned int i = 0; i < mElementsInStack; i++ ) {
		tmp[i] = mStack[i];
	} //end-of-for
	delete [] mStack;
	mStack = tmp;

} // end-of-method StringStack::expand



