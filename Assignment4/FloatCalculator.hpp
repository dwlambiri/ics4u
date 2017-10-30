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

#ifndef ASSIGNMENT4_FLOATCALCULATOR_HPP_
#define ASSIGNMENT4_FLOATCALCULATOR_HPP_

#include "FloatStack.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>

/**
 ---------------------------------------------------------------------------
 @author     dwlambiri
 @date       Oct 26, 2017
 @classname  FloatCalculator
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

	/**
	 ---------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 26, 2017
	 @mname   add
	 @details
	 \n
	 --------------------------------------------------------------------------
	 */
	bool add();

	/**
	 ---------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 26, 2017
	 @mname   subtract
	 @details
	 \n
	 --------------------------------------------------------------------------
	 */
	bool subtract();

	/**
	 ---------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 26, 2017
	 @mname   multiply
	 @details
	 \n
	 --------------------------------------------------------------------------
	 */
	bool multiply();

	/**
	 ---------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 26, 2017
	 @mname   divide
	 @details
	 \n
	 --------------------------------------------------------------------------
	 */
	bool divide();

	/**
	 ---------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 26, 2017
	 @mname   Commands
	 @details
	 \n
	 --------------------------------------------------------------------------
	 */
	bool compute(char term[]);

	/**
	 ---------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 28, 2017
	 @mname   thename
	 @details
	 This function parses a string which is entered by the user and then
	 operates upon the data provided by accessing FloatStack \n.
	 --------------------------------------------------------------------------
	 */
	bool parse(std::string& array);

	/**
	 ---------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 28, 2017
	 @mname   swap
	 @details
	 \n
	 --------------------------------------------------------------------------
	 */
	bool swap();

	/**
	 ---------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 28, 2017
	 @mname   exponent
	 @details
	 \n
	 --------------------------------------------------------------------------
	 */
	bool power();

	/**
	 ---------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 28, 2017
	 @mname   series
	 @details
	 \n
	 --------------------------------------------------------------------------
	 */
	bool series();

	/**
	 ---------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 28, 2017
	 @mname   sum
	 @details
	 \n
	 --------------------------------------------------------------------------
	 */
	bool sum();

	/**
	 ---------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 28, 2017
	 @mname   product
	 @details
	 \n
	 --------------------------------------------------------------------------
	 */
	bool product();

	/**
	 ---------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 28, 2017
	 @mname   exponent
	 @details
	 \n
	 --------------------------------------------------------------------------
	 */
	bool exponential();

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
	bool sqrt();

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
	bool log();
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
	bool cos();
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
	bool sin();

	/**
	 -------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 29, 2017
	 @name    FloatCalculator::popOp
	 @param   paramlist: none
	 @return  bool
	 @details
	 \n
	 -------------------------------------------------------------------------
	 */
	bool popOp();
	/**
	 -------------------------------------------------------------------------
	 @author  dwlambiri
	 @date    Oct 29, 2017
	 @name    FloatCalculator::getTopOfStack
	 @param   std::vector<float>& f
	 @return  void
	 @details
	 \n
	 -------------------------------------------------------------------------
	 */
	void getTopOfStack(std::vector<float>& f, unsigned int num) {
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

private:
	//--------------------------------------------------
	// Data Members
	//--------------------------------------------------
	/*
	 * @author   dwlambiri
	 * @date     Oct 29, 2017
	 *  I am using the "using" pattern because
	 *  it makes the code more readable.
	 *  FCMPF is a pointer to a member method of the
	 *  class FloatCalculator.
	 *  We will use this to access the operation functions
	 *  	(such as: sum, prod, add, subtract, etc.).
	 *  CmdMap is a shorthand for a map that has as a key,
	 *  a string representing the textual description of the
	 *  operation and as a value a pointer to the actual
	 *  member method that executes the operation.
	 */

	using FCMPF = bool (FloatCalculator::*)(void);
	using CmdMap = std::map<std::string, FCMPF>;

	/*
	 * @author   dwlambiri
	 * @date     Oct 29, 2017
	 *  cmdmap is a member variable that stores all
	 *  command strings and the actual pointers to
	 *  members.
	 *
	 *  I picked a map because according to Bjarne Stroustrup
	 *  (chapter 31 of c++ Programming Language [4th Edition])
	 *  this data structure has O(log(n)) search performance.
	 *  This means that the calculator will perform very close
	 *  to constant time when evaluating the expressions irrespective
	 *  of the number of functions that are being added.
	 */

	CmdMap cmdmap;

private:
	//--------------------------------------------------
	// Private Methods
	//--------------------------------------------------
	void initMap();

};
//end-of-class FloatCalculator

#endif /* ASSIGNMENT4_FLOATSTACK_HPP_ */
