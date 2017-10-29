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
	bool exponent();

	/**
	  ---------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Oct 28, 2017
	   @mname   series
	   @details
		  \n
	  --------------------------------------------------------------------------
	 */
	void series(int firstNum, int lastNum, int step);

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



private:
	//--------------------------------------------------
	// Data Members
	//--------------------------------------------------
	using FCMPF = bool (FloatCalculator::*)(void);
	using CmdMap = std::map<std::string, FCMPF>;

	CmdMap cmdmap;

private:
	//--------------------------------------------------
	// Private Methods
	//--------------------------------------------------

};
//end-of-class FloatCalculator

#endif /* ASSIGNMENT4_FLOATSTACK_HPP_ */
