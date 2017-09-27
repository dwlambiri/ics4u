//includes
#include <iostream>
#include <fstream>
#include <allegro5/allegro.h>
#include "apclasses/apmatrix.h"

using namespace std;
//Constant vaiables
const int matrixCols_c = 480;
const int matrixRows_c = 480;
const char fileName_c[] = "Colorado_480x480.dat";


//function that reads in data from a file
bool MapDataDrawer(apmatrix<int> &map){
    ifstream file;

	file.open(fileName_c);

	if ( ! file.is_open()) {
        cerr << "ERROR FILE NOT OPEN" << endl;
        return false;
    }
	// todo: check if file opens successfully


	for (int y = 0; y < matrixRows_c; y++){
        for (int x = 0; x < matrixCols_c; x++){
            file >>  map[y][x];
            //cout << map[y][x] << " ";
        }
        //cout << endl;
    }

	file.close();
	return true;
}//END OF MapDataDrawer


//finds the smallest peak of the set of heights
int findMin(apmatrix<int> &map){
    int lowest = map[0][0];

    for (int y = 0; y < matrixRows_c; y++){
        for (int x = 0; x < matrixCols_c; x++){
            if (lowest > map[y][x]){
                lowest = map[y][x];
            }
        }
    }
    return lowest;
}// END OF findMin



//finds the largest peak of the set of heights
int findMax(apmatrix<int> &map){
    int largest = map[0][0];

    for (int y = 0; y < matrixRows_c; y++){
        for (int x = 0; x < matrixCols_c; x++){
            if (largest < map[y][x]){
                largest = map[y][x];
            }
        }
    }
    return largest;
}// END OF findMin


void drawMap(apmatrix<int> &map){

}

//MAIN FUNCTION
int main(int argc, char **argv) {
	//we need full main declaration in osx

    apmatrix<int> mountainMat(matrixCols_c, matrixRows_c, 0);

    MapDataDrawer(mountainMat);

    int largestSize = findMax(mountainMat);
    int smallestSize = findMin(mountainMat);

    cout << "The largest size is: " << largestSize << endl << "And the smallest size is: " << smallestSize << endl;

	return 0;
}//RETURN OF MAIN IF EVERTHING GOES WELL
