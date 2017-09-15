/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   merge_assignment.cpp
 *	Course: ICS4U
 *	Date:   Sep 14, 2017
 *
 *	Purpose: Merging two sorted lists of numbers
 *
 *	Usage:
 *
 *	Revision History:
 *
 *	Known Issues: none
 *
 *****************************************************************************/


#include <iostream>
#include <fstream>

//prototyping
int input_remaining(int arraysize, int counter, int list[], int outlist[], int output_counter);
//using namespace allows me to not have to add the namespace to each of my stream objects

using namespace std;

const int listSize_c = 10000;
int list[listSize_c+1];


//opens file and reads in its content into an array
int openFile(const char* filename, int numberList[], int size){
	ifstream file;
	 file.open(filename);
	 // todo: check if file opens successfully

	 int counter = 0;

	 while (!file.eof()) {
		 int temp = 0;
		 file >> temp;

		 if (temp <= size) {
			numberList[temp]++;
		} //end-of-if(temp <= size)

	 }
//	 for (int i = 0; i < counter; i++){
//			cout << numberList[i] <<endl;
//	 }
//	 cout << '\n';
	 file.close();
	 return counter;
}



bool print_list(int list[],int listSize){
	for (int i = 0; i <= listSize; i++){
		for (int j = 0; j < list[i]; j++ ) {
			cout << i << endl;
		} //end-of-for
	}
	return true;
}

bool writeToTextFile(int outputArray[], int listSize, const char* filename){
	ofstream fout(filename);
	/*
	if ( ! filename.is_open()) {
		cerr << "ERROR: OUTPUT FILE CANNOT BE OPENED" <<endl;
		return false;
	}
	 */
	for (int i = 0; i <= listSize; i++){
			for (int j = 0; j < list[i]; j++ ) {
				fout << i << endl;
			} //end-of-for
		}
	 return true;
}

//main function
int main() {
	const char* filename1 = "data1.dat";
	const char* filename2 = "data2.dat";
	const char* output_file = "merged_data.txt";

	int arraySize1 = openFile(filename1, list, listSize_c);
	int arraySize2 = openFile(filename2, list, listSize_c);


	print_list(list,listSize_c);
	writeToTextFile(list, listSize_c, output_file);


    return 0;
}

