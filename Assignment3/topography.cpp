/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   topography.cpp
 *	Course: ICS4U
 *	Date:   Oct 6, 2017
 *
 *	Purpose: This program reads in data relating to a topographical map into a
 *			 matrix. It then draws the map and calculates routes to traverse the map
 *			 from east to west in order to travel a path with the least change in
 *			 elevation.
 *
 *	Usage:   Just run the program. The green line represents the optimal path
 *			 with the least change. Each red path represents every possible
 *			 east west path involving a minimal amount of height change.
 *
 *	Revision History:
 *
 *	Known Issues:
 *
 *****************************************************************************/


//includes
#include <iostream>
#include <fstream>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include "apclasses/apmatrix.h"
#include "apclasses/apmatrix.h"

using namespace std;

/**
  ---------------------------------------------------------------------------
   @author     dwlambiri
   @date       Sep 30, 2017
   @name       MapPixelColour
   @brief

  ---------------------------------------------------------------------------
 */
/*
the enum is used to select a colour of the line drawn in the findpath function*/
enum MapPixelColour {
	redPixel_c,
	greeenPixel_c,
	bluePixel_c
}; //end-of-enum MapPixelColour
//constants that determine the initial values of the variables
// initialize the allegro display
//Constant vaiables
const int matrixCols_c = 844;
const int matrixRows_c = 480;
const char fileName_c[] = "Colorado_844x480.dat";
ALLEGRO_DISPLAY *display = nullptr;
const int maxcolour_c = 255;

//function that reads in data from a file
// the function draws the map depending on the elevation of each variable
bool MapDataDrawer(apmatrix<int> &map){
    ifstream file;
    //opens file
	file.open(fileName_c);
    //checks if the file is open
	if ( ! file.is_open()) {
        cerr << "ERROR FILE NOT OPEN" << endl;
        return false;
    }
	// draws every every pixel using its relative position in the matrix to the display
	for (int y = 0; y < matrixRows_c; y++){
        for (int x = 0; x < matrixCols_c; x++){
            file >>  map[y][x];
            //cout << map[y][x] << " ";
        }
        //cout << endl;
    }
    //closes file
	file.close();
	//returns to prove the function works
	return true;
}//END OF MapDataDrawer


//finds the smallest peak of the set of heights
int findMin(apmatrix<int> &map){
    int lowest = map[0][0];
    //
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


//not using this yet
int drawMap(apmatrix<int> &map, int small, int large){

     float ratios = float(large - small) / maxcolour_c;
    //initialize display
    al_init();
	display = al_create_display(matrixCols_c, matrixRows_c);

	// Always check if your allegro routines worked successfully.
	if (!display) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return 1;
	}
	al_set_window_title(display, "Allegro Example 1 - Create Display");



	for (int y = 0; y < matrixRows_c; y++){
        for (int x = 0; x < matrixCols_c; x++){
            int temp = (map[y][x] - small) / ratios;
            al_draw_pixel(x , y , al_map_rgb(temp, temp, temp));
        }
    }

    return 0;
}


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Sep 30, 2017
   @mname   DrawPixel
   @details
	  \n
  --------------------------------------------------------------------------
 */
bool
drawPixel(int x, int y, MapPixelColour c) {
	 switch (c) {
		case redPixel_c:
			al_draw_pixel(x , y , al_map_rgb(255, 0, 0));
			break;
		case greeenPixel_c:
			al_draw_pixel(x , y , al_map_rgb(0, 255, 0));
			break;
		case bluePixel_c:
			al_draw_pixel(x , y , al_map_rgb(0, 0, 255));
			break;
		default:
			return false;
	 } //end-of-switch
	 return true;

} // end-of-function DrawPixel

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Sep 30, 2017
   @mname   findPath
   @details
	  \n
  --------------------------------------------------------------------------
 */
int
findPath(apmatrix<int>& map, int startRow, int maxvalue, MapPixelColour colour, apvector<int> &path) {
	int total = 0;
	int row = startRow;
	path[0] = startRow;
	for (int j = 1; j < map.numcols(); j++ ) {
		/*
		 * @author   dwlambiri
		 * @date     Oct 1, 2017
		 *  I initialized the deltas with very large values.
		 *  because I know the maximum delta a value of one hundred delta will never be selected
		 *  I used this for the matrix boundaries
		 */

		int n1 = 100*maxvalue;
		int n3 = 100*maxvalue;


		if ((row - 1) >= 0) {
			n1 = abs(map[row-1][j] - map[row][j-1]);

		} //end-of-if

		int n2 = abs(map[row][j] - map[row][j-1]);

		if ((row + 1) < matrixRows_c) {
			n3 = abs(map[row+1][j] - map[row][j - 1]);
		} //end-of-if

		//checks value
		if ((n1 < n2) && (n1 < n3)) {
			row--;
			total += n1;
		}
		else if ((n2 < n1) && (n2 < n3)) {
			total += n2;
		}
		else if ((n3 < n2) && (n3 < n1)) {
			row++;
			total += n3;
		}
		else if ((n1 == n2) && (n1 < n3)) {
			row -= rand()%2;
			total += n1;
//			if(colour == greeenPixel_c)
//				std::cout << row << std::endl;
		}
		else if ((n3 == n2) && (n3 < n1)) {
			row += rand()%2;
			total += n3;
//			if(colour == greeenPixel_c)
//				std::cout << row << std::endl;
		}
		else if ((n1 == n3) && (n1 < n2)) {
			row += 2*rand()%2 - 1;
			total += n1;
//			if(colour == greeenPixel_c)
//				std::cout << row << std::endl;
		}
		else if ((n1 == n2) && (n1 == n3)) {
			row += rand()%3 -1;
			total += n1;
//			if(colour == greeenPixel_c)
//				std::cout << row << std::endl;
		}
		path[j] = row;
		drawPixel(j, row, colour);

	} //end-of-for
	return total;
} // end-of-function findpath


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Sep 30, 2017
   @mname   markAllPaths
   @details
	  \n
  --------------------------------------------------------------------------
 */
void
markAllPaths(apmatrix<int> map, int maxValue) {
	int total1 = -1;
	int rowvalue = 0;
	/*
	 * @author   dwlambiri
	 * @date     Oct 1, 2017
	 *  I store the row numbers for the best path of the run.
	 *
	 *  This is to ensure that the green path that is displayed
	 *  is the path with the smallest delta sum.
	 *
	 *  Because of the use of random number generation
	 *  there are many possible paths from a starting point.
	 *
	 *  Therefore even if a given starting point has the smallest path
	 *  of the run when we run the function again the new path might not
	 *  be the smallest
	 */

	apvector<int> bestRun(map.numcols());
	for (int i = 0; i < map.numrows(); i++){
		/*
		 * @author   dwlambiri
		 * @date     Oct 1, 2017
		 *  For each starting point (row) we return the actual path
		 *  as row positions in a vector who's indeces represent the columns.
		 */

		apvector<int> tempRun(map.numcols());
		int temp = findPath(map, i, maxValue, redPixel_c, tempRun);
		if(i == 11) {
			std::cout << "Min Path Index = " << i << " Value = " << temp << std::endl;
		}

		/*
		 * @author   dwlambiri
		 * @date     Oct 1, 2017
		 *  If the current path has a smaller sum than the current best
		 *  I store the starting row value and the path vector.
		 */

		if (total1 < 0 || total1 > temp){
			total1 = temp;
			rowvalue = i;
			bestRun = tempRun;
		}
	}

	std::cout << "Min Path Index = " << rowvalue << " Value = " << total1 << std::endl;
	/*
	 * @author   dwlambiri
	 * @date     Oct 1, 2017
	 *  I am drawing the best path of the run in green.
	 */

	for (int i = 0; i < map.numcols(); i++ ) {
		drawPixel(i, bestRun[i], greeenPixel_c);
	} //end-of-for
	al_flip_display();
} // end-of-function markAllPaths



//MAIN FUNCTION
int main(int argc, char **argv) {
	//we need full main declaration in osx

	srand (time(NULL));

    apmatrix<int> mountainMat(matrixRows_c, matrixCols_c, 0);

    MapDataDrawer(mountainMat);

    int largestSize = findMax(mountainMat);
    int smallestSize = findMin(mountainMat);

    std::cout << "The largest size is: " << largestSize << endl << "And the smallest size is: " << smallestSize << std::endl;
    drawMap(mountainMat, smallestSize, largestSize);

    markAllPaths(mountainMat, largestSize);
    al_rest(10);
    al_destroy_display(display);
	return 0;
}//RETURN OF MAIN IF EVERTHING GOES WELL
