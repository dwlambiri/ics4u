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

#ifndef ASSIGNMENT4_FLOATFLOATCALCULATOR_HPP_
#define ASSIGNMENT4_FLOATFLOATCALCULATOR_HPP_

#include "FloatStack.hpp"
//#include "FloatStack.cpp"
#include <iostream>

/**
 ---------------------------------------------------------------------------
 @author     dwlambiri
 @date       Oct 26, 2017
 @classname  Calculator
 @brief
 \n
 @details
 \n
 ---------------------------------------------------------------------------
 */
class FloatCalculator: public FloatStack {

public:
	//--------------------------------------------------
	// Public Methods (External Type Interface)
	//--------------------------------------------------
	/**
	 --------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 26, 2017
	 @name    Calculator::Calculator
	 @param   -
	 @return  -
	 @details
	 Default constructor of Class Calculator \n
	 --------------------------------------------------------------------------
	 */
	FloatCalculator();

	/**
	 --------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 26, 2017
	 @name    Calculator::~Calculator
	 @param   -
	 @return  -
	 @details
	 Default destructor of class Calculator \n
	 --------------------------------------------------------------------------
	 */
	~FloatCalculator();

	FloatCalculator(unsigned int);

	float add();

	float subtract();

	float multiply();

	float divide();

	/**
	 ---------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 26, 2017
	 @mname   Commands
	 @details
	 \n
	 --------------------------------------------------------------------------
	 */
	bool Commands(char term[]);

	//bool newExpression(char newE[]);

	bool parse(char array[]);

private:
	//--------------------------------------------------
	// Data Members
	//--------------------------------------------------
	//char* expression;
	//int exSize = 200;

private:
	//--------------------------------------------------
	// Private Methods
	//--------------------------------------------------

};
//end-of-class Calculator

#endif /* ASSIGNMENT4_FLOATSTACK_HPP_ */
