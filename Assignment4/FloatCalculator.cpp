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
#include <cmath>
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

	initMap();
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
	initMap();

}

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 29, 2017
 @mname   FloatCalculator::initMap
 @details
 \n
 --------------------------------------------------------------------------
 */
void FloatCalculator::initMap() {

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
	cmdmap["exp"] = &FloatCalculator::exponential;
	cmdmap["log"] = &FloatCalculator::log;
	cmdmap["sqrt"] = &FloatCalculator::sqrt;
	cmdmap["cos"] = &FloatCalculator::cos;
	cmdmap["sin"] = &FloatCalculator::sin;
	cmdmap["pop"] = &FloatCalculator::popOp;
	cmdmap["e"] = &FloatCalculator::euler;
	cmdmap["pi"] = &FloatCalculator::pi;
	cmdmap["rand"] = &FloatCalculator::random;
} // end-of-method FloatCalculator::initMap

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 29, 2017
 @mname   FloatCalculator::getTopOfStack
 @details
 \n
 --------------------------------------------------------------------------
 */
void FloatCalculator::getTopOfStack(std::vector<float>& f, unsigned int num) {
	int retnum = (num < mElementsInStack) ? num : mElementsInStack;
	if(retnum) {
		f.resize(retnum+1);
		f[0] = mElementsInStack;
	}
	else {
		f.resize(0);
		return;
	}
	for (unsigned int i = 0; (i < num) && (mElementsInStack >= i + 1);
			i++) {
		f[i+1] = mStack[mElementsInStack - i - 1];
	} //end-of-for
}

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 31, 2017
   @mname   unary
   @details
	  \n
  --------------------------------------------------------------------------
 */
bool
FloatCalculator::unary(float& FirstInStack) {

	if (top()) {
		FirstInStack = *top();
		pop();
	} //end-of-if
	else {
		return false;
	}
	return true;
} // end-of-method unary


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 31, 2017
   @mname   binary
   @details
	  \n
  --------------------------------------------------------------------------
 */
bool
FloatCalculator::binary(float& FirstInStack, float& SecondInStack) {

	if (top()) {
			FirstInStack = *top();
			pop();
	} //end-of-if
	else {
		return false;
	}

	if (top()) {
		SecondInStack = *top();
		pop();
	} //end-of-if

	else {
		return false;
	}
	return true;
} // end-of-method unary

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
	float v1 = 0;
	float v2 = 0;

	if(binary(v1,v2) == false)
		return false;
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
	float v1 = 0;
	float v2 = 0;

	if(binary(v1,v2) == false)
			return false;
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
	float v1 = 0;
	float v2 = 0;

	if(binary(v1,v2) == false)
		return false;
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
	float v1 = 0;
	float v2 = 0;

	if(binary(v1,v2) == false)
		return false;

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
	float v1 = 0;
	float v2 = 0;

	if(binary(v1,v2) == false)
		return false;

	push(v1);
	push(v2);
	return true;
} // end-of-method FloatCalculator::swap

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
	if(!top()) return false;
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
	if(!top()) return false;
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
	float v1 = 0;
	float v2 = 0;

	if(binary(v1,v2) == false)
		return false;
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

	for (float i = firstNum; i <= lastNum; i += step) {
		push(i);
	} //end-of-for

	return true;
} // end-of-method FloatCalculator::series

/**
 -------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 29, 2017
 @name    FloatCalculator::sqrt
 @param   paramlist: none
 @return  type
 @details
 \n
 -------------------------------------------------------------------------
 */

bool FloatCalculator::sqrt() {
	float v1 = 0;
	if(unary(v1) == false)
		return false;
	push((float) ::sqrt(v1));

	return true;
}

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 30, 2017
   @mname   FloatCalculator::pi
   @details
	  \n
  --------------------------------------------------------------------------
 */
bool
FloatCalculator::pi() {

	push((float) M_PI);
	return true;
} // end-of-method FloatCalculator::pi



/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 30, 2017
   @mname   FloatCalculator::euler
   @details
	  \n
  --------------------------------------------------------------------------
 */
bool
FloatCalculator::euler() {

	push((float) std::exp(1.0));
	return true;
} // end-of-method FloatCalculator::euler



/**
 -------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 29, 2017
 @name    FloatCalculator::exp
 @param   paramlist: none
 @return  bool
 @details
 \n
 -------------------------------------------------------------------------
 */
bool FloatCalculator::exponential() {
	float v1 = 0;
	if(unary(v1) == false)
		return false;
	push((float) ::exp(v1));

	return true;
}

/**
 -------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 29, 2017
 @name    FloatCalculator::log
 @param   paramlist: none
 @return  bool
 @details
 \n
 -------------------------------------------------------------------------
 */
bool FloatCalculator::log() {
	float v1 = 0;
	if(unary(v1) == false)
		return false;
	push((float) ::log(v1));

	return true;
}
/**
 -------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 29, 2017
 @name    FloatCalculator::cos
 @param   paramlist: none
 @return  bool
 @details
 \n
 -------------------------------------------------------------------------
 */
bool FloatCalculator::cos() {
	float v1 = 0;
	if(unary(v1) == false)
		return false;
	push((float) ::cos(v1));

	return true;
}
/**
 -------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 29, 2017
 @name    FloatCalculator::sin
 @param   paramlist: none
 @return  bool
 @details
 \n
 -------------------------------------------------------------------------
 */
bool FloatCalculator::sin() {
	float v1 = 0;
	if(unary(v1) == false)
		return false;
	push((float) ::sin(v1));

	return true;
}

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 31, 2017
   @mname   FloatCalculator::random
   @details
	  \n
  --------------------------------------------------------------------------
 */
bool
FloatCalculator::random() {

	push(rand());
	return true;
} // end-of-method FloatCalculator::random


/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 29, 2017
 @mname   FloatCalculator::popOp
 @details
 \n
 --------------------------------------------------------------------------
 */
bool FloatCalculator::popOp() {

	if (top()) {
		pop();
	} //end-of-if
	else {
		return false;
	}
	return true;
} // end-of-method FloatCalculator::popOp

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
	/*
	 * @author   dwlambiri
	 * @date     Oct 29, 2017
	 *  The std::map data structure returns an iterator
	 *  as the result from a find.
	 *  I used the example from:
	 *  	 http://www.cplusplus.com/reference/map/map/find/
	 *  to write my compute function.
	 *  I first check that the string provided against the map.
	 *  If the string is part of the map then the string is an
	 *  operation. The program tries to execute the operation.
	 *  If the iterator points to cmdmap.end() it means that the
	 *  string is not a key in the map.
	 *
	 *  In that case we try to see if we can transform the string
	 *  into a float. we use strtod() function.
	 *  http://www.cplusplus.com/reference/cstdlib/strtod/?kw=strtod
	 *
	 */

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
		return true;
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
