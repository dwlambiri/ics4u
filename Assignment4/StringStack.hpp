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
	  -------------------------------------------------------------------------
	   @name  StringStack
	   @param  StringStack&
	   @return
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	 StringStack(StringStack&);

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


	/*
	 * @author   dwlambiri
	 * @date     Oct 23, 2017
	 *  mStack is dynamically allocated when the object is constructed,
	 *  and deleted when the object is destroyed.
	 *  It stores the strings passed to the object.
	 */
	std::string*    mStack;

	/*
	 * @author   dwlambiri
	 * @date     Oct 23, 2017
	 *  mStackSize remembers the maximum number of elements that mStack can store.
	 */
	unsigned int    mStackSize;

	/*
	 * @author   dwlambiri
	 * @date     Oct 23, 2017
	 *   mElementsInStack represents the number of elements in the stack.
	 *   The index of the top of the stack is mElementsInStack - 1, if
	 *     mElementsInStack > 0.
	 */
	unsigned int    mElementsInStack;

private:
	//--------------------------------------------------
	// Private Methods
	//--------------------------------------------------

}; //end-of-class StringStack


#endif /* ASSIGNMENT4_STRINGSTACK_HPP_ */
