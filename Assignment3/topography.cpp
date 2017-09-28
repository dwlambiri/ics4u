//includes
#include <iostream>
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <apmatrix.h>

using namespace std;
//Constant vaiables
const int matrixCols_c = 480;
const int matrixRows_c = 480;
const char fileName_c[] = "Colorado_480x480.dat";
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

     float ratios = (large - small) / maxcolour_c;
    //initialize display
    al_init();
	display = al_create_display(matrixCols_c, matrixRows_c);

	// Always check if your allegro routines worked successfully.
	if (!display) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}
	al_set_window_title(display, "Allegro Example 1 - Create Display");



	for (int y = 0; y < matrixRows_c; y++){
        for (int x = 0; x < matrixCols_c; x++){
            int temp = (map[y][x] - small) / ratios;
            al_draw_pixel(x , y , al_map_rgb(temp, temp, temp));
        }
    }
    al_flip_display();
    al_rest(10);
    al_destroy_display(display);
    return 0;
}

//MAIN FUNCTION
int main(int argc, char **argv) {
	//we need full main declaration in osx

    apmatrix<int> mountainMat(matrixCols_c, matrixRows_c, 0);

    MapDataDrawer(mountainMat);

    int largestSize = findMax(mountainMat);
    int smallestSize = findMin(mountainMat);

    cout << "The largest size is: " << largestSize << endl << "And the smallest size is: " << smallestSize << endl;
    drawMap(mountainMat, smallestSize, largestSize);

	return 0;
}//RETURN OF MAIN IF EVERTHING GOES WELL
