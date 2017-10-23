/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   StringStack.hpp
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

#ifndef ASSIGNMENT4_STRINGSTACK_HPP_
#define ASSIGNMENT4_STRINGSTACK_HPP_

#include <string>

/**
  ---------------------------------------------------------------------------
   @author     dwlambiri
   @date       Oct 23, 2017
   @classname  StringStack
   @brief
	 \n
   @details
	\n
  ---------------------------------------------------------------------------
 */
class StringStack {

public:
	//--------------------------------------------------
	// Public Methods (External Type Interface)
	//--------------------------------------------------
	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Oct 23, 2017
	   @name    StringStack::StringStack
	   @param   -
	   @return  -
	   @details
		Default constructor of Class StringStack \n
	  --------------------------------------------------------------------------
	 */
	StringStack();

	/**
	  -------------------------------------------------------------------------
	   @name  StringStack
	   @param  int
	   @return
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	 StringStack(unsigned int);

	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Oct 23, 2017
	   @name    StringStack::~StringStack
	   @param   -
	   @return  -
	   @details
		Default destructor of class StringStack \n
	  --------------------------------------------------------------------------
	 */
	~StringStack();

	/**
	  -------------------------------------------------------------------------
	   @name  getStackSize
	   @param
	   @return  int
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	int getStackSize() const { return mStackSize; }

	/**
	  -------------------------------------------------------------------------
	   @name  top
	   @param
	   @return  std::string&
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	std::string* top();

	/**
	  -------------------------------------------------------------------------
	   @name  push
	   @param  std::string&
	   @return  void
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	void push(std::string&);

	/**
	  -------------------------------------------------------------------------
	   @name  push
	   @param  const char*
	   @return  void
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	void push(const char*);


	/**
	  -------------------------------------------------------------------------
	   @name  pop
	   @param
	   @return  void
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	void pop();

	/**
	  -------------------------------------------------------------------------
	   @name  isEmpty
	   @param
	   @return  bool
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	bool isEmpty() const {return (mElementsInStack == 0);}

private:
	//--------------------------------------------------
	// Data Members
	//--------------------------------------------------
	std::string*    mStack;
	unsigned int    mStackSize;
	unsigned int    mElementsInStack;

private:
	//--------------------------------------------------
	// Private Methods
	//--------------------------------------------------

}; //end-of-class StringStack


#endif /* ASSIGNMENT4_STRINGSTACK_HPP_ */
