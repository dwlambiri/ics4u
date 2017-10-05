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
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <apmatrix.h>
#include <apvector.h>

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
//Constant variables
const int matrixCols_c = 844;
const int matrixRows_c = 480;
const char* fileName_c  = "Colorado_844x480.dat";
ALLEGRO_DISPLAY *display = nullptr;
//const int maxIntensity_c = 0xff;
const int invalidValue_c = -1;

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



int drawMap(apmatrix<int> &map, int small, int large){

//     float range  = large - small;

    //initialize display
    al_init();
	display = al_create_display(matrixCols_c, matrixRows_c);

	// Always check if your allegro routines worked successfully.
	if (!display) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return 1;
	}
	al_set_window_title(display, "Mountain region map");

	/*
	 * @author   dwlambiri
	 * @date     Oct 5, 2017
	 *  I picked two altitudes at which I change colours.
	 *   Below heights[0] there is green vegetation.
	 *   The lower the altitude the more vegetation and therefore I use a darker colour.
	 *   Between height[0] and height[1] we use a different colour range and use darker colours
	 *   	to denote altitudes closer to height[1]
	 *   Above height[1] is the permanent snow area and I am using a monochromatic scheme with
	 *   	grayer shades at lower altitudes where there is lower snow.
	 *   I an doing linear interpolation obtain the colour shade for a given height
	 */

	int heights[] = { 1800, 2700};

	for (int y = 0; y < matrixRows_c; y++){
        for (int x = 0; x < matrixCols_c; x++){
            if (map[y][x] <= heights[0] ){
            	int shade = (map[y][x] - small) *255 / (heights[0]-small);
            	al_draw_pixel(x , y , al_map_rgb(0, shade, 0));
            }
            else if ((map[y][x] > heights[0]) && (map[y][x] <= heights[1]) ){
            	int shade1 = -(map[y][x] - heights[0]) * (0xf0 -0xd0)/ (heights[1] - heights[0]) + 0xd0;
               	int shade2 = -(map[y][x] - heights[0]) * (0x66 -0x22)/ (heights[1] - heights[0]) + 0x66;
               	int shade3 = -(map[y][x] - heights[0]) * (0xf0 -0xa0)/ (heights[1] - heights[0]) + 0xf0;

                al_draw_pixel(x , y , al_map_rgb(shade3, shade1, shade2));
            } else {
            	int shade = (map[y][x] - heights[1]) * (0xff -0xa0) / (large - heights[1]) + 0xa0;
                al_draw_pixel(x , y , al_map_rgb(shade, shade, shade));
            }
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
bool drawPixel(int x, int y, MapPixelColour c) {
	 switch (c) {
		case redPixel_c:
			al_draw_pixel(x , y , al_map_rgb(0xff, 0, 0));
			break;
		case greeenPixel_c:
			al_draw_pixel(x , y , al_map_rgb(0, 0xff, 0));
			break;
		case bluePixel_c:
			al_draw_pixel(x , y , al_map_rgb(0, 0, 0xff));
			break;
		default:
			return false;
	 } //end-of-switch
	 return true;

} // end-of-function DrawPixel
void printFont(int lowestElev){
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon

    ALLEGRO_FONT *font = al_load_ttf_font("font.ttf",30,0 );

    if (!font){
        cout << "Could not load 'font.ttf'";
    }

    al_draw_textf(font, al_map_rgb(255,255,255), 200, 50,ALLEGRO_ALIGN_CENTRE, "Lowest Elevation: %d", lowestElev);

}
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
	int totalPathLength = 0;
	int currentRow = startRow;
	//The vector path is a vector that stores the row values of each column in a route
	path[0] = startRow;
	for (int columnIndex = 1; columnIndex < map.numcols(); columnIndex++ ) {
		/*
		 * @author   dwlambiri
		 * @date     Oct 1, 2017
		 *  I initialized the deltas with very large values.
		 *  because I know the maximum delta a value of one hundred delta will never be selected
		 *  I used this for the matrix boundaries
		 *
		 */

        //The n variables contain the elevation difference values of each possible edge
		int edge1weight = 1001*maxvalue;
		int edge3weight = 1001*maxvalue;

        //If the row that I am currently in is greater than row zero
		if ((currentRow - 1) >= 0) {
			edge1weight = abs(map[currentRow-1][columnIndex] - map[currentRow][columnIndex-1]);
		} //end-of-if
        //Initiallized the second 'edge'
		int edge2weight = abs(map[currentRow][columnIndex] - map[currentRow][columnIndex-1]);
        // if the third row is equal to the total value of the row then do not assign it a proper value
		if ((currentRow + 1) < matrixRows_c) {
			edge3weight = abs(map[currentRow+1][columnIndex] - map[currentRow][columnIndex - 1]);
		} //end-of-if

        //The following if statements compare the differences in elevation and return the lowest one
		//checks value
		if ((edge1weight < edge2weight) && (edge1weight < edge3weight)) {
			currentRow--;
			totalPathLength += edge1weight;
		}
		else if ((edge2weight < edge1weight) && (edge2weight < edge3weight)) {
			totalPathLength += edge2weight;
		}
		else if ((edge3weight < edge2weight) && (edge3weight < edge1weight)) {
			currentRow++;
			totalPathLength += edge3weight;
		}
		else if ((edge1weight == edge2weight) && (edge1weight < edge3weight)) {
			currentRow -= rand()%2;
			totalPathLength += edge1weight;
//			if(colour == greeenPixel_c)
//				std::cout << row << std::endl;
		}
		else if ((edge3weight == edge2weight) && (edge3weight < edge1weight)) {
			currentRow += rand()%2;
			totalPathLength += edge3weight;
//			if(colour == greeenPixel_c)
//				std::cout << row << std::endl;
		}
		else if ((edge1weight == edge3weight) && (edge1weight < edge2weight)) {
			currentRow += 2*rand()%2 - 1;
			totalPathLength += edge1weight;
//			if(colour == greeenPixel_c)
//				std::cout << row << std::endl;
		}
		else if ((edge1weight == edge2weight) && (edge1weight == edge3weight)) {
			currentRow += rand()%3 -1;
			totalPathLength += edge1weight;
//			if(colour == greeenPixel_c)
//				std::cout << row << std::endl;
		}
		path[columnIndex] = currentRow;
		drawPixel(columnIndex, currentRow, colour);

	} //end-of-for
	return totalPathLength;
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
int
markAllPaths(apmatrix<int>& map, int maxValue) {
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
		drawPixel(i, bestRun[i], bluePixel_c);
	} //end-of-for

	return total1;
} // end-of-function markAllPaths



/*
 * @author   dwlambiri
 * @date     Oct 4, 2017
 *  THIS MARKS THE BEGINING OF THE ALGORITHM TWO FUNCTIONS
 *  THE FOLLOWING ARE FOR ALGORITHM 2
 */


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 4, 2017
   @mname   InitMatrices
   @details
	  \n
  --------------------------------------------------------------------------
 */
void
initMatrices(apmatrix<int>& map) {

	for (int  i = 0; i < matrixRows_c; i++ ) {
		for (int j = 0; j < matrixCols_c; j++ ) {
			map[i][j] = invalidValue_c;
		} //end-of-for
	} //end-of-for
} // end-of-function InitMatrices



/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 4, 2017
   @mname   relax
   @details
	  \n
  --------------------------------------------------------------------------
 */
bool
relaxVertex(int currentX, int y, int nextX, int wheight, apmatrix<int>& d, apmatrix<int>& pi) {

	if (currentX < 0 || (nextX >= matrixRows_c))
		return false;
	if (y >= matrixCols_c-1)
		return false;
	if ((d[nextX][y+1] == invalidValue_c) || (d[nextX][y+1] > d[currentX][y]+ wheight )){
		d[nextX][y+1] = d[currentX][y] + wheight;
		pi[nextX][y+1] = currentX;
	}
	return true;
} // end-of-function relax

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 4, 2017
   @mname   shortestPathsFromSingleStart
   @details
	  \n
  --------------------------------------------------------------------------
 */
int
shortestPathsFromSingleStart(int start, apmatrix<int>& map, apvector<int>& bestPath) {

	static apmatrix<int> d(map.numrows(), map.numcols());
	static apmatrix<int> pi(map.numrows(), map.numcols());

	int row = 0;

	initMatrices(d);
	initMatrices(pi);

	d[start][0] = 0;

	for (int y = 0; y < matrixCols_c-1; y++ ) {
		for (int x = 0; x < matrixRows_c; x++ ) {
			//cout << " x = " << x << "  y = " << y << endl;

			if(d[x][y] == invalidValue_c) continue;

			if (x == 0){
				//top row
				int edge1weight = abs(map[x][y] - map[x][y+1]);
				int edge2weight = abs(map[x][y] - map[x+1][y+1]);
				relaxVertex(x, y, x, edge1weight, d, pi);
				relaxVertex(x, y, (x+1), edge2weight, d, pi);
			}
			else if(x == matrixRows_c-1){
				int edge1weight = abs(map[x][y] - map[x][y+1]);
				int edge3weight = abs(map[x][y] - map[x-1][y+1]);
				relaxVertex(x, y, x, edge1weight, d, pi);
				relaxVertex(x, y, (x-1), edge3weight, d, pi);
			}
			else{
				int edge1weight = abs(map[x][y] - map[x][y+1]);
				int edge2weight = abs(map[x][y] - map[x+1][y+1]);
				int edge3weight = abs(map[x][y] - map[x-1][y+1]);
				relaxVertex(x, y, x, edge1weight, d, pi);
				relaxVertex(x, y, (x+1), edge2weight, d, pi);
				relaxVertex(x, y, (x-1), edge3weight, d, pi);
			}
		} //end-of-for
	} //end-of-for

	for (int i = 0; i < matrixRows_c; i++ ) {
		if (d[i][matrixCols_c-1] == invalidValue_c) continue;
		if ((d[row][matrixCols_c-1] == invalidValue_c) || (d[row][matrixCols_c-1] > d[i][matrixCols_c-1])) {
			row = i;
		} //end-of-if
	} //end-of-for

	int temp2 = pi[row][matrixCols_c-1];
	bestPath[matrixCols_c-1] = row;

	for (int i = matrixCols_c - 1; i >=1 ; i-- ) {
		bestPath[i-1] = pi[temp2][i];
		temp2 = pi[temp2][i];
	} //end-of-for

	cout << " SHORT SHORT " << d[row][matrixCols_c-1] << endl;


	return d[row][matrixCols_c-1];
} // end-of-function shortestPathsFromSingleStart


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Sep 30, 2017
   @mname   markAllPaths
   @details
	  \n
  --------------------------------------------------------------------------
 */
int
markAllPaths2(apmatrix<int>& map, int maxValue) {
	int runsize = -1;
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
		int temp = shortestPathsFromSingleStart(i, map, tempRun);

		/*
		 * @author   dwlambiri
		 * @date     Oct 1, 2017
		 *  If the current path has a smaller sum than the current best
		 *  I store the starting row value and the path vector.
		 */

		if (runsize < 0 || runsize > temp){
			runsize = temp;
			rowvalue = i;
			bestRun = tempRun;
		}
	}

	std::cout << "Min Path Index = " << rowvalue << " Value = " << runsize << std::endl;
	/*
	 * @author   dwlambiri
	 * @date     Oct 1, 2017
	 *  I am drawing the best path of the run in green.
	 */

	for (int i = 0; i < map.numcols(); i++ ) {
		drawPixel(i, bestRun[i], bluePixel_c);
	} //end-of-for

	return runsize;
} // end-of-function markAllPaths


//MAIN FUNCTION
int main(int argc, char **argv) {

	//we need full main declaration in osx
    //Initializes pseudo randomization
	srand (time(NULL));

    //Initializes an apmatrix to store all the map's data
    apmatrix<int> mountainMat(matrixRows_c, matrixCols_c, 0);
    MapDataDrawer(mountainMat);

    //saves the smallest and largest peaks on the mountains into two variables
    int largestSize = findMax(mountainMat);
    int smallestSize = findMin(mountainMat);

    //Prints the value of the largest and smallest peaks on the mountain
    std::cout << "The largest size is: " << largestSize << endl << "And the smallest size is: " << smallestSize << std::endl;
    drawMap(mountainMat, smallestSize, largestSize);

     //Draws the initial map using a grey scale into an allegro buffer
    markAllPaths(mountainMat, largestSize);

    int pathLength = markAllPaths2(mountainMat, matrixRows_c);
    printFont(pathLength);

    al_flip_display();
    al_rest(15);
    al_destroy_display(display);
	return 0;
}//RETURN OF MAIN IF EVERTHING GOES WELL
