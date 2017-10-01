//includes
#include <iostream>
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
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
enum MapPixelColour {
	redPixel_c,
	greeenPixel_c,
	bluePixel_c
}; //end-of-enum MapPixelColour

//Constant vaiables
const int matrixCols_c = 844;
const int matrixRows_c = 480;
const char fileName_c[] = "Colorado_844x480.dat";
ALLEGRO_DISPLAY *display = nullptr;
const int maxcolour_c = 255;

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
findPath(apmatrix<int> map, int startRow, int maxvalue, MapPixelColour colour) {
	int total = 0;
	int row = startRow;
	for (int j = 1; j < matrixCols_c; j++ ) {
		int n1 = 10*maxvalue;
		int n3 = 10*maxvalue;
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
		if ((n2 < n1) && (n2 < n3)) {
			total += n2;
		}
		if ((n3 < n2) && (n3 < n1)) {
			row++;
			total += n3;
		}
		if ((n1 == n2) && (n1 < n3)) {
			row -= rand()%2;
			total += n1;
		}
		if ((n3 == n2) && (n3 < n1)) {
			row += rand()%2;
			total += n3;
		}
		if ((n1 == n3) && (n1 < n2)) {
			row = row -1 + 2*rand()%2;
			total += n1;
		}
		if ((n1 == n2) && (n1 == n3)) {
			row += rand()%3 -1;
			total += n1;
		}
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
	for (int i = 0; i < matrixRows_c; i++){
		int temp = findPath(map, i, maxValue, redPixel_c);
		//std::cout << temp << endl;
		if (total1 < 0 || total1 > temp){
			total1 = temp;
			rowvalue = i;
		}
	}
	findPath(map, rowvalue, maxValue, greeenPixel_c);
	al_flip_display();
} // end-of-function markAllPaths



//MAIN FUNCTION
int main(int argc, char **argv) {
	//we need full main declaration in osx

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

