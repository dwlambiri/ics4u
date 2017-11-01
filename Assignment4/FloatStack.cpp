/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   FloatStackStack.cpp
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
#include <iostream>

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 23, 2017
 @mname   FloatStack::FloatStack
 @details
 \n
 --------------------------------------------------------------------------
 */

FloatStack::FloatStack() {
	mStackSize = 50;
	mStack = new float[mStackSize];
	mElementsInStack = 0;
	v = 0;
} // end-of-method FloatStack::FloatStack

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 23, 2017
 @mname   FloatStack::~FloatStack
 @details
 \n
 --------------------------------------------------------------------------
 */

FloatStack::~FloatStack() {

	if (mStackSize > 0) {
		delete[] mStack;
	} //end-of-if

} // end-of-method FloatStack::~FloatStack

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 23, 2017
 @mname   FloatStack::FloatStack
 @details
 \n
 --------------------------------------------------------------------------
 */

FloatStack::FloatStack(FloatStack& param) {

	mStackSize = param.mStackSize;
	mStack = new float[mStackSize];
	mElementsInStack = param.mElementsInStack;
	for (unsigned int i = 0; i < mElementsInStack; i++) {
		mStack[i] = param.mStack[i];
	} //end-of-for
	v= 0;
} // end-of-method FloatStack::FloatStack

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 23, 2017
 @mname   FloatStack::FloatStack
 @details
 	 Constructor that allows you to declare the total number of elements
 	 that can be stored in the stack. \n
 --------------------------------------------------------------------------
 */

FloatStack::FloatStack(unsigned int stackSize) {

	if (stackSize == 0) {
		mStackSize = 1;
	} else {
		mStackSize = stackSize;
	} //end-of-if
	mStack = new float[mStackSize];
	mElementsInStack = 0;
	v= 0;
} // end-of-method FloatStack::FloatStack

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 23, 2017
 @mname   FloatStack::top
 @details
 	 This function returns the top element on the stack. \n
 --------------------------------------------------------------------------
 */
float*
FloatStack::top() {
	if (empty()) {
		return nullptr;
	} //end-of-if

	v = mStack[mElementsInStack - 1];
	return &v;
} // end-of-method FloatStack::top

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 23, 2017
 @mname   FloatStack::push
 @details
 	 Pushes an element into the stack. \n
 --------------------------------------------------------------------------
 */
void FloatStack::push(float param) {
	if (full()) {
		expand();
	} //end-of-if
	mStack[mElementsInStack++] = param;
} // end-of-method FloatStack::push

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 23, 2017
 @mname   FloatStack::pop
 @details
 	 Pop's the top element of the stack.\n
 --------------------------------------------------------------------------
 */
void FloatStack::pop() {

	if (empty()) {
		return;
	} else {
		mElementsInStack--;
	} //end-of-if
} // end-of-method FloatStack::pop

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 23, 2017
 @mname   FloatStack::expand
 @details
 	 This method is called when the stack is full and expands it if it is
 	 so. The computational complexity of this method is: n. \n
 --------------------------------------------------------------------------
 */
void FloatStack::expand() {
	mStackSize *= 2;
	float* tmp = new float[mStackSize];
	for (unsigned int i = 0; i < mElementsInStack; i++) {
		tmp[i] = mStack[i];
	} //end-of-for
	delete[] mStack;
	mStack = tmp;

} // end-of-method FloatStack::expand

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 28, 2017
   @mname   FloatStack::printStack
   @details
	  This function prints the contents of the stack from the bottom of the
	  stack to the top.
  --------------------------------------------------------------------------
 */
bool
FloatStack::printStack() {

	if (mElementsInStack == 0){
		std::cout << "The stack is empty" << std::endl;
		return false;
	}
	else {
		for (int i = mElementsInStack-1; i >=0 ; i--){
			std::cout << mStack[i] << std::endl;
		}
	}
	return true;
} // end-of-method FloatStack::printStack



