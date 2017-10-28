#include "FloatFloatCalculator.hpp"

#include <stdlib.h>
#include <string.h>

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 28, 2017
   @mname   FloatClalculator()
   @details
	  This constructor does not take any parameters. It simply calls the
	  basic constructor from the FloatStack class.
  --------------------------------------------------------------------------
 */
FloatCalculator::FloatCalculator() {
	FloatStack();
}

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 28, 2017
   @mname   ~FloatClalculator()
   @details
	  This constructor calls the destructor of the FloatStack class.
  --------------------------------------------------------------------------
 */
FloatCalculator::~FloatCalculator() {
	~FloatStack();
}

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 28, 2017
   @mname   FloatClalculator(unsigned int)
   @details
	  This constructor takes an unsigned integer as a parameter to
	  initialize the size of the FloatStack by calling a specific
	  constructor and passing in the size as a parameter.
  --------------------------------------------------------------------------
 */
FloatCalculator::FloatCalculator(unsigned int sizeOfStack) {
	FloatStack(sizeOfStack);
}

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 28, 2017
   @mname   add
   @details
	  This pops the top two elements in the stack and adds them together
	  and pushes the result back onto the stack.
  --------------------------------------------------------------------------
 */
float FloatCalculator::add() {
	float value1 = *top();
	pop();
	float value2 = *top();
	pop();
	push(value2 + value1);
	return *top();
}

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 28, 2017
   @mname   subtract
   @details
	  This pops the top two elements in the stack and subtracts the top one
	  from the one underneath it.
  --------------------------------------------------------------------------
 */
float FloatCalculator::subtract() {
	float value1 = *top();
	pop();
	float value2 = *top();
	pop();
	push(value2 - value1);
	return *top();
}

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 28, 2017
   @mname   add
   @details
	  This pops the top two elements in the stack and multiplies one by the
	  other and pushes the result back onto the stack.
  --------------------------------------------------------------------------
 */
float FloatCalculator::multiply() {
	float value1 = *top();
	pop();
	float value2 = *top();
	pop();
	push(value2 * value1);
	return *top();
}


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 28, 2017
   @mname   subtract
   @details
	  This pops the top two elements in the stack and divides the lower
	  the lower element by the top one.
  --------------------------------------------------------------------------
 */
float FloatCalculator::divide() {
	float value1 = *top();
	pop();
	float value2 = *top();
	pop();
	//This is error checker for divide by zero
	if (value1 == 0) {
		return 0;
	}
	push(value2 / value1);
	return *top();
}

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 26, 2017
 @mname   Calculator::Commands
 @details
 \n
 --------------------------------------------------------------------------
 */
bool FloatCalculator::Commands(char term[]) {

	if (term[0] <= '0' && term[0] >= '9') {
		push(atof(term));
	} else if (term[0] != NULL && term[1] == NULL) {
		switch (term[0]) {
		case '+':
			add();
			break;
		case '-':
			subtract();
			break;
		case '*':
			multiply();
			break;
		case '/':
			divide();
			break;
		default:
			return false;
		}
		return true;
	}
	return false;
} // end-of-method Calculator::Commands

bool FloatCalculator::parse(char array[]) {

	if (array[0] == NULL) {
		return false;
	}
	char * pch = NULL;
	pch = strtok(array, " ");

	Commands(pch);

	while (pch != NULL) {
		pch = strtok(NULL, " ");
		Commands(pch);
	}

	return true;
}

