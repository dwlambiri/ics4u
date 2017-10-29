/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   FloatFloatCalculator.hpp
 *	Course: ICS4U
 *	Date:   Oct 28, 2017
 *
 *	Purpose: This class does calculations on floats stored into a stack.
 *				When an operation method such as add() gets called it pops
 *				the top two terms and pushes back in the result.
 *
 *	Usage:
 *
 *	Revision History:
 *
 *	Known Issues:
 *
 *****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <map>
#include <string>
#include <math.h>
#include "FloatCalculator.hpp"

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
FloatCalculator::FloatCalculator() :
		FloatStack() {

	cmdmap["+"] = &FloatCalculator::add;
	cmdmap["-"] = &FloatCalculator::subtract;
	cmdmap["*"] = &FloatCalculator::multiply;
	cmdmap["/"] = &FloatCalculator::divide;
	cmdmap["sum"] = &FloatCalculator::sum;
	cmdmap["prod"] = &FloatCalculator::product;
	cmdmap["series"] = &FloatCalculator::series;
	cmdmap["^"] = &FloatCalculator::power;
	cmdmap["pow"] = &FloatCalculator::power;
	cmdmap["swap"] = &FloatCalculator::swap;
	cmdmap["print"] = &FloatCalculator::printStack;
	cmdmap["clear"] = &FloatCalculator::clearStack;

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
FloatCalculator::FloatCalculator(unsigned int sizeOfStack) :
		FloatStack(sizeOfStack) {
	cmdmap["+"] = &FloatCalculator::add;
	cmdmap["-"] = &FloatCalculator::subtract;
	cmdmap["*"] = &FloatCalculator::multiply;
	cmdmap["/"] = &FloatCalculator::divide;
	cmdmap["sum"] = &FloatCalculator::sum;
	cmdmap["prod"] = &FloatCalculator::product;
	cmdmap["series"] = &FloatCalculator::series;
	cmdmap["^"] = &FloatCalculator::power;
	cmdmap["pow"] = &FloatCalculator::power;
	cmdmap["swap"] = &FloatCalculator::swap;
	cmdmap["print"] = &FloatCalculator::printStack;
	cmdmap["clear"] = &FloatCalculator::clearStack;

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
bool FloatCalculator::add() {
	float v1;
	float v2;

	if (top()) {
		v1 = *top();
		pop();
	} //end-of-if
	else {
		return false;
	}

	if (top()) {
		v2 = *top();
		pop();
	} //end-of-if

	else {
		return false;
	}
	push(v2 + v1);
	return true;
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
bool FloatCalculator::subtract() {
	float v1;
	float v2;

	if (top()) {
		v1 = *top();
		pop();
	} //end-of-if
	else {
		return false;
	}

	if (top()) {
		v2 = *top();
		pop();
	} //end-of-if
	else {
		return false;
	}
	push(v2 - v1);
	return true;
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
bool FloatCalculator::multiply() {
	float v1;
	float v2;

	if (top()) {
		v1 = *top();
		pop();
	} //end-of-if
	else {
		return false;

	}
	if (top()) {
		v2 = *top();
		pop();
	} //end-of-if
	else {
		return false;
	}
	push(v2 * v1);
	return true;
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
bool FloatCalculator::divide() {
	float v1;
	float v2;

	if (top()) {
		v1 = *top();
		pop();
	} //end-of-if
	else {
		return false;
	}

	if (top()) {
		v2 = *top();
		pop();
	} //end-of-if

	else {
		return false;
	}

	if (v1 == 0) {
		return false;
	}
	push(v2 / v1);
	return true;
}

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 28, 2017
 @mname   FloatCalculator::swap
 @details
 Swaps the top two characters in the stack\n
 --------------------------------------------------------------------------
 */
bool FloatCalculator::swap() {
	float v1;
	float v2;

	if (top()) {
		v1 = *top();
		pop();
	} //end-of-if
	else {
		return false;
	}

	if (top()) {
		v2 = *top();
		pop();
	} //end-of-if

	else {
		return false;
	}

	push(v1);
	push(v2);
	return true;
} // end-of-method FloatCalculator::swap

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 28, 2017
 @mname   exponent
 @details
 \n
 --------------------------------------------------------------------------
 */
bool FloatCalculator::exponent() {
	float v1;
	float v2;

	if (top()) {
		v1 = *top();
		pop();
	} //end-of-if
	else {
		return false;
	}

	if (top()) {
		v2 = *top();
		pop();
	} //end-of-if

	else {
		return false;
	}
	push(pow(v2, v1));
	return true;
}

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 28, 2017
 @mname   FloatCalculator::sum
 @details
 \n
 --------------------------------------------------------------------------
 */
bool FloatCalculator::sum() {
	float sumation = 0;
	while (top()) {
		sumation += *top();
		pop();
	}
	push(sumation);
	return true;
} // end-of-method FloatCalculator::sum

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 28, 2017
 @mname   FloatCalculator::product
 @details
 \n
 --------------------------------------------------------------------------
 */
bool FloatCalculator::product() {
	float totalProduct = 1;
	while (top()) {
		totalProduct *= *top();
		pop();
	}
	push(totalProduct);
	return true;
} // end-of-method FloatCalculator::sum


/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 28, 2017
 @mname   exponent
 @details
 \n
 --------------------------------------------------------------------------
 */
bool FloatCalculator::power() {
	float v1;
	float v2;

	if (top()) {
		v1 = *top();
		pop();
	} //end-of-if
	else {
		return false;
	}

	if (top()) {
		v2 = *top();
		pop();
	} //end-of-if

	else {
		return false;
	}
	push(pow(v2, v1));
	return true;
}

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 28, 2017
 @mname   FloatCalculator::series
 @details
 \n
 --------------------------------------------------------------------------
 */
bool FloatCalculator::series() {

	float firstNum;
	float lastNum;
	float step;

	if (top()) {
		step = *top();
		pop();
	} //end-of-if
	else {
		return false;
	}

	if (top()) {
		lastNum = *top();
		pop();
	} //end-of-if

	else {
		return false;
	}
	if (top()) {
		firstNum = *top();
		pop();
	} //end-of-if

	else {
		return false;
	}
	for (float i = firstNum; i <= lastNum; i+= step ) {
		push(i);
	} //end-of-for

	return true;
} // end-of-method FloatCalculator::series



/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 26, 2017
 @mname   FloatCalculator::compute
 @details
 \n
 --------------------------------------------------------------------------
 */
bool FloatCalculator::compute(char term[]) {
	bool noError = true;
	CmdMap::iterator it = cmdmap.find(std::string(term));
	if (it != cmdmap.end()) {
		FCMPF cpf = it->second;
		if ((this->*cpf)() == false) {
			noError = false;
		}
	} else {
		char* pEnd;
		float f = (float) strtod(term, &pEnd);
		if (pEnd != term) {
			push(f);
		} else {
			noError = false;
		}
	}
	return noError;
} // end-of-method Calculator::Commands

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 28, 2017
 @mname   parse
 @details
 \n
 --------------------------------------------------------------------------
 */
bool FloatCalculator::parse(std::string& array) {
	bool noError = true;

	static const int localArraySize_c = 1000;
	static char local[localArraySize_c];

	if (array[0] == '\0') {
		return false;
	}

	char * pch = nullptr;
	strncpy(local, array.c_str(), localArraySize_c - 1);

	pch = strtok(local, " \t\r\n");
	while (pch != nullptr) {

		if (compute(pch) == false) {
			noError = false;
			break;
		}
		pch = strtok(nullptr, " \t\r\n");
	}

	return noError;
}
