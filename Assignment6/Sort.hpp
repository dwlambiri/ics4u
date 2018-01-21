/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   Sort.hpp
 *	Course: ICS4U
 *	Date:   Jan 15, 2018
 *
 *	Purpose: This is a Sort class declaration
 *
 *	Usage:
 *
 *	Revision History:
 *
 *	Known Issues: NONE
 *
 *****************************************************************************/


#ifndef SORT_HPP_
#define SORT_HPP_
#include <iostream>
#include <fstream>
#include <string>
#include "apvector.h"
#include <ctype.h>
#include "GraphicsEngine.hpp"
#include "Timer.cpp"
/**
  ---------------------------------------------------------------------------
   @author     dwlambiri
   @date       Nov 24, 2017
   @classname  Sort
   @brief
	 \n
   @details
	\n
  ---------------------------------------------------------------------------
 */
class Sort {

public:
	//--------------------------------------------------
	// Public Methods (External Type Interface)
	//--------------------------------------------------
	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 24, 2017
	   @name    Sort::Sort
	   @param   -
	   @return  -
	   @details
		Default constructor of Class Sort \n
	  --------------------------------------------------------------------------
	 */
	Sort(int indeces);

	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 24, 2017
	   @name    Sort::~Sort
	   @param   -
	   @return  -
	   @details
		Default destructor of class Sort \n
	  --------------------------------------------------------------------------
	 */
	~Sort();

	/**
	  -------------------------------------------------------------------------
	   @name  callFP
	   @param
	   @return  void
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	bool callFP(char salgo);

private:
	//--------------------------------------------------
	// Data Members
	//--------------------------------------------------


private:
	int numVals;
	apvector<int> data;
	static const int w_c = 600;
	static const int h_c = 600;
	int swapCounter;
	int compCounter;
	Timer myTime;

	GraphicsEngine ge;

	//--------------------------------------------------
	// Private Methods
	//--------------------------------------------------
	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 24, 2017
	   @name    Sort::Sort
	   @param   -
	   @return  -
	   @details
		Default constructor of Class Sort \n
	  --------------------------------------------------------------------------
	 */
	Sort();


	/**
	  -------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 24, 2017
	   @details
		  These methods were made private because it only needs to be called
		  from the callFC method which uses the private data to be passed
		  as parameters. \n
	  -------------------------------------------------------------------------
	 */
	bool selectionSort();

	bool bubbleSort();

	int partition (int low, int high);

	bool quickSort(int low, int high);

	void swap(int& a, int& b);

	void merge(int,int,int);

	bool merge_sort(int low,int high);


	/**
	  -------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 26, 2017
	   @name    Sort::generateVector
	   @param
	   @return  void
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	void generateVector();

	/**
	  -------------------------------------------------------------------------
	   @author  elambiri
	   @date    Jan 14, 2018
	   @name    Sort::printVector
	   @param
	   @return  void
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	void printVector();



}; //end-of-class Sort

#endif
