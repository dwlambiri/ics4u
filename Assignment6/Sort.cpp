/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   Maze.cpp
 *	Course: ICS4U
 *	Date:   Nov 24, 2017
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
   @mname   Maze::Maze
   @details
	  Standard maze constructor which requires a text file\n
  --------------------------------------------------------------------------
 */

Sort::Sort(int rows, int cols) {
	numRows = rows;
	numCols = cols;

	data.resize(numCols);

	generateVector();

} // end-of-method Maze::Maze




/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Maze::~Maze
   @details
	  Standard maze destructor that cleans up allegro\n
  --------------------------------------------------------------------------
 */
Sort::~Sort() {
	ge.cleanUp();
} // end-of-method Maze::~Maze




/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 24, 2017
   @mname   Maze::callFP
   @details
	  Calls the recursive algorithm for the first time by passing the
	  private data (startRow and startCol)\n
  --------------------------------------------------------------------------
 */
bool
Sort::callFP(char salgo) {

	float xr = (float)w_c/numCols;
	float yr = (float)h_c/numRows;
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

	if(!ge.initAllegro(title, r*numCols, r*numRows)) {
		return false;
	}

	printVector();

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

	if(!result) {
		std::string err = "could not sort";
		std::cout << "error: " << err << std::endl;
		ge.errorBox(err);
		ge.allegroEventLoop();
		return false;
	}
	printVector();
	std::string success = "data is sorted";
	ge.okBox(success);
	ge.allegroEventLoop();

	return true;

} // end-of-method Maze::callFP


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

	for (int i = 0; i < numRows-1; ++i) {
		int min = data[i];
		int minidx = i;
		for (int j = i; j < numRows; ++j) {
			ge.pauseOnDisplayFrame();
			if(data[j] < min) {
				minidx = j;
				min = data[j];
			}
			ge.drawVector(data,j);
		}//end-of-for
		int tmp = data[i];
		data[i] = min;
		data[minidx] = tmp;
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

	for (int i = 0; i < numRows-1; ++i) {
		for (int j = i; j < numRows; ++j) {
			ge.pauseOnDisplayFrame();
			if(data[j] < data[i]) {
				swap(data[i], data[j]);
			}
			ge.drawVector(data, j);
		}//end-of-for
	}//end-of-for

	return true;

} // end-of-method Sort::selectionSort


int
Sort::partition (int low, int high){
    int pivot = data[high];    //taking the last element as pivot
    int i = (low - 1);
    for (int j = low; j <= high- 1; j++)
    {
    	ge.pauseOnDisplayFrame();
        // If current element is smaller than or
        // equal to pivot
        if (data[j] <= pivot)
        {
            i++;
            swap(data[i], data[j]);
        }
        ge.drawVector(data, j);
    }
    swap(data[i + 1], data[high]);
    return (i + 1);
}

bool
Sort::quickSort(int low, int high) {
    if (low < high)
    {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
    return true;
}


void
Sort::swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}



bool
Sort::merge_sort(int low,int high){
	int mid;
	if(low<high){
		mid=(low+high)/2;
		merge_sort(low,mid);
		merge_sort(mid+1,high);
		merge(low,mid,high);
	}

	return true;
}

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
		ge.pauseOnDisplayFrame();
		data[k] = b[k];
		ge.drawVector(data, k);
	}
}


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Nov 26, 2017
   @mname   Maze::mazeGenerator
   @details
	  \n
  --------------------------------------------------------------------------
 */
void
Sort::generateVector() {

	for (int r = 0; r < numCols; r++){
			data[r] = rand()% numRows;
	}
} // end-of-method Maze::mazeGenerator


/**
  ---------------------------------------------------------------------------
   @author  elambiri
   @date    Jan 14, 2018
   @mname   Sort::printVector
   @details
	  \n
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

