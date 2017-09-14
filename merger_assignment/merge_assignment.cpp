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

//opens file and reads in its content into an array
int openFile(char filename[], int numberList[]){
	ifstream file;
	 file.open(filename);
	 // todo: check if file opens successfully

	 int counter = 0;

	 while (!file.eof()) {
		 file >> numberList[counter++];
	 }
	 for (int i = 0; i < counter; i++){
			cout << numberList[i] <<endl;
	 }
	 cout << '\n';
	 file.close();
	 return counter;
}




int merger(int listA[], int listB[], int outlist[], int sizeArray1, int sizeArray2){
	int counter1 = 0;
	int counter2 = 0;
	int output_counter = 0;
	while (counter1 < sizeArray1 && counter2 < sizeArray2 ){
    	if (listA[counter1] < listB[counter2]){
        	outlist[output_counter] = listA[counter1];
        	counter1++;
    	}
    	else {
        	outlist[output_counter] = listB[counter2];
        	counter2++;
    	}
    	output_counter++;
	}
	if (counter1 != sizeArray1){
		output_counter = input_remaining(sizeArray1, counter1, listA, outlist, output_counter);
	}
	else{
		output_counter = input_remaining(sizeArray2, counter2, listB, outlist, output_counter);
	}
	return output_counter;
}


int input_remaining(int arraysize, int counter, int list[], int outlist[], int output_counter){
	while (counter < arraysize){
		outlist[output_counter] = list[counter];
		counter++;
		output_counter++;
	}
	return output_counter;
}

bool print_list(int list[],int listSize){
	for (int i = 0; i < listSize; i++){
		cout << list[i] << endl;
	}
	return true;
}

bool writeToTextFile(int outputArray[], int arraySize, char filename[]){
	ofstream fout(filename);
	/*
	if ( ! filename.is_open()) {
		cerr << "ERROR: OUTPUT FILE CANNOT BE OPENED" <<endl;
		return false;
	}
	 */
	 for (int i = 0; i < arraySize; i++) {
		 fout << outputArray[i] << endl;
	 }
	 cout << "successfulyl wrote to textfile" << endl;
	 return true;
}

//main function
int main() {
	char filename1[100] = "data1.dat";
	char filename2[100] = "data2.dat";
	char output_file[100] = "merged_data.txt";
	int list1[200] = {0};
	int list2[200] = {0};
	int outputList[400] = {0};
	int arraySize1 = openFile(filename1, list1);
	int arraySize2 = openFile(filename2, list2);

	int outputSize = merger(list1, list2, outputList, arraySize1, arraySize2);

	print_list(outputList,outputSize);
	writeToTextFile(outputList, outputSize, output_file);


    return 0;
}

