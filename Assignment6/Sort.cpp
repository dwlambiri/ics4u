/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   Maze.cpp
 *	Course: ICS4U
 *	Date:   Jan 15, 2018
 *
 *	Purpose:
 *
 *	Usage: This file contains methods to read in and solve a maze from a text
 *			file
 *
 *	Revision History:
 *
 *	Known Issues: NONE
 *
 *****************************************************************************/


#include "Sort.hpp"

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Sort::Sort
   @details
	  \n
  --------------------------------------------------------------------------
 */

Sort::Sort(int indeces) {
	numVals = indeces;
	swapCounter = 0;
	compCounter = 0;
	data.resize(numVals);

	generateVector();

} // end-of-method Sort::Sort




/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Sort::~Sort
   @details
	  Standard destructor that cleans up allegro\n
  --------------------------------------------------------------------------
 */
Sort::~Sort() {
	ge.cleanUp();
} // end-of-method Sort::~Sort



/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Sort::callFP
   @details
   	  This method is the "central" method of the maze class.
   	  This reads checks the type of sort that is wanted and then uses a
   	  	  switch statement to call the according sorting method.
   	  There is also a swap, time, and comparison counter which allows the
   	  	  user to see how much time and how many computations each sort takes.
	  \n
  --------------------------------------------------------------------------
 */
bool
Sort::callFP(char salgo) {

	float xr = (float)w_c/numVals;
	float yr = (float)h_c/numVals;
	float r = (xr >yr)?yr:xr;
	//float r = 20;

	char* title = nullptr;
	bool result = false;


	switch(salgo) {
	case 'b':
		title = "Sorting Demo: Bubble Sort";
		break;
	case 's':
		title = "Sorting Demo: Selection Sort";
		break;
	case 'q':
		title = "Sorting Demo: QuickSort";
		break;
	case 'm':
		title = "Sorting Demo: MergeSort";
		break;
	default:
		title = "Sorting Demo: Bubble Sort";
		salgo = 'b';
		break;
	}

	if(!ge.initAllegro(title, r*numVals, r*numVals)) {
		return false;
	}

	printVector();
	std::cout << "FPS = " << ge.fps << std::endl;
	myTime.start();
    swapCounter = 0;
    compCounter = 0;

	switch(salgo) {
	case 'b':
		result = bubbleSort();
		break;
	case 's':
		result = selectionSort();
		break;
	case 'q':
		result = quickSort(0, data.length()-1);
		break;
	case 'm':
		result = merge_sort(0, data.length()-1);
		break;
	default:
		std::cout << "Unknown sorting algorithm" << std::endl;
		break;
	}

	ge.drawVector(data, -1);
	if(!result) {
		std::string err = "could not sort";
		std::cout << "error: " << err << std::endl;
		ge.errorBox(err);
		ge.allegroEventLoop();
		return false;
	}

	myTime.stop();
	printVector();
	std::cout <<"Number of Seconds " << myTime.elapsedSeconds() <<std::endl;
	std::cout <<"Number of swaps = " << swapCounter <<std::endl;
	std::cout <<"Number of Comparisons = " << compCounter <<std::endl;
	std::string success = "data is sorted";
	ge.okBox(success);
	ge.allegroEventLoop();

	return true;

} // end-of-method Sort::callFP


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Sort::selectionSort
   @details
	  Selection Sort\n
  --------------------------------------------------------------------------
 */
bool
Sort::selectionSort() {
	for (int i = 0; i < numVals-1; ++i) {
		int min = data[i];
		int minidx = i;
		for (int j = i; j < numVals; ++j) {
			ge.pauseOnDisplayFrame();
			compCounter++;
			if(data[j] < min) {
				minidx = j;
				min = data[j];
			}
			ge.drawVector(data,j);
		}//end-of-for
		swap(data[i], data[minidx]);
	}//end-of-for
	return true;

} // end-of-method Sort::selectionSort


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Sort::bubbleSort
   @details
	  bubble Sort\n
  --------------------------------------------------------------------------
 */
bool
Sort::bubbleSort() {
	for (int i = 0; i < numVals-1; ++i) {
		for (int j = i; j < numVals; ++j) {
			ge.pauseOnDisplayFrame();
			compCounter++;
			if(data[j] < data[i]) {
				swap(data[i], data[j]);
			}
			ge.drawVector(data, j);
		}//end-of-for
	}//end-of-for

//  This was my first attempt at writing bubble sort
	// inspired by the textbook. It has problems running
	// wiht my allegro method so i took it out.

//	bool disorder = true;
//	while (disorder) {
//		disorder = false;
//		for (int i = 1; i < numRows; i++) {
//			ge.pauseOnDisplayFrame();
//			compCounter++;
//			if (data[i] < data[i - 1]) {
//				swap(data[i], data[i - 1]);
//				disorder = true;
//			}
//			ge.drawVector(data, i);
//		}
//	}
	return true;

} // end-of-method Sort::selectionSort


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Jan 14, 2018
   @mname   Sort::partition
   @details
	  This method partitions the array and then gets called from quicksort\n
  --------------------------------------------------------------------------
 */
int
Sort::partition (int low, int high){
    int pivot = data[high];    //taking the last element as pivot
    int i = (low - 1);
    for (int j = low; j <= high- 1; j++){
    	ge.pauseOnDisplayFrame();
        // This checks if the current element is smaller than or equal to pivot
        compCounter++;
    	if (data[j] <= pivot){
            i++;
            swap(data[i], data[j]);
        }
        ge.drawVector(data, high);
    }
    swap(data[i + 1], data[high]);
    return (i + 1);
}

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Jan 14, 2018
   @mname   Sort::quicksort
   @details
	  recursively quicksorts the vector by partitioning and sorting it\n
  --------------------------------------------------------------------------
 */
bool
Sort::quickSort(int low, int high) {
    if (low < high){
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
    return true;
}

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Jan 14, 2018
   @mname   Sort::swap
   @details
	  standard swap function that swaps the values of their parameters
	  	  as well as incrementing the swap counter\n
  --------------------------------------------------------------------------
 */
void
Sort::swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
	swapCounter++;
}


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Jan 14, 2018
   @mname   Sort::merge_sort
   @details
	  Recursive merge sort.
	  Breaks the vector down into into subsections and sorts them
	  	  by merging them.
	  	  Inspired by pseudocode from Bjarne Stroustrup "Algorithms in C++"
  --------------------------------------------------------------------------
 */
bool
Sort::merge_sort(int low,int high){
	int mid;
	compCounter++;
	if(low<high){
		mid=(low+high)/2;
		merge_sort(low,mid);
		merge_sort(mid+1,high);
		merge(low,mid,high);
	}
	return true;
}

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Jan 14, 2018
   @mname   Sort::merge
   @details
	  This is called from the merge sort method. \n
  --------------------------------------------------------------------------
 */
void
Sort::merge(int low,int mid,int high){
	int h,i,j,k;
	apvector<int> b;

	b.resize(data.length());

	h=low;
	i=low;
	j=mid+1;

	while((h<=mid)&&(j<=high)){
		if(data[h]<=data[j]){
			b[i]=data[h];
			h++;
		}
		else{
			b[i]=data[j];
			j++;
		}
		i++;
	}
	if(h>mid){
		for(k=j;k<=high;k++){
			b[i]=data[k];
			i++;
		}
	}
	else{
		for(k=h;k<=mid;k++){
			b[i]=data[k];
			i++;
		}
	}
	for(k=low;k<=high;k++) {
		//Stops and redraws on allegro display
		ge.pauseOnDisplayFrame();
		data[k] = b[k];
		ge.drawVector(data, k);
	}
}


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 26, 2017
   @mname   Sort::generateVector
   @details
	  Fills the vector with random integers with the max number equal to
	  	  the vector size. \n
  --------------------------------------------------------------------------
 */
void
Sort::generateVector() {

	for (int r = 0; r < numVals; r++){
			data[r] = rand()% numVals + 1;
	}
} // end-of-method Sort::generateVector


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Jan 14, 2018
   @mname   Sort::printVector
   @details
	  This prints out into the terminal each element in the vector.\n
  --------------------------------------------------------------------------
 */
void
Sort::printVector() {

	std::cout << std::endl;
	for (int i = 0; i < data.length(); ++i) {
		std::cout << data[i] << " ";
	}//end-of-for
	std::cout << std::endl << std::endl;
} // end-of-method Sort::printVector

