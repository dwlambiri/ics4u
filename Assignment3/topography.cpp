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
	redPixel_c, greeenPixel_c, bluePixel_c
};
//end-of-enum MapPixelColour

//constants that determine the initial values of the variables
// initialize the allegro display
//Constant variables
const int matrixCols_c = 844;
const int matrixRows_c = 480;
const char* fileName_c = "Colorado_844x480.dat";
const int fps_c = 60;

ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_TIMER *timer = nullptr;
ALLEGRO_BITMAP *screenBitmap = nullptr;
ALLEGRO_FONT *font = nullptr;

const int invalidValue_c = -1;

bool mapDataReader(apmatrix<int> &map);
int findMin(apmatrix<int> &map);
int findMax(apmatrix<int> &map);
bool initAllegro();
void moveBitmapToDisplay();
void cleanUpAllegro();
bool allegroEventLoop();
void allegroExitLoop();
int drawMap(apmatrix<int>& map, int small, int large);
bool drawPixel(int x, int y, MapPixelColour c);
void printLowestPathInfo(int lowestElev);
void displayMessage(const char* msg);
int findPath(apmatrix<int>& map, int startRow, int maxvalue,
		MapPixelColour colour, apvector<int> &path);
int markAllPaths(apmatrix<int>& map, int maxValue);
void initMatrices(apmatrix<int>& map);
bool relaxVertex(int currentX, int y, int nextX, int wheight,
		apmatrix<int>& distance, apmatrix<int>& predecesor);
int shortestPathsFromVertex(int start, apmatrix<int>& map,
		apvector<int>& bestPath);
int markAllPaths2(apmatrix<int>& map);

/**
 --------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @name    mapDataReader
 @param   enclosing_method_arguments
 @return  return_type
 @details
 function that reads in data from a file
 the function draws the map depending on the elevation of each variable
 \n
 -------------------------------------------------------------------------
 */
bool mapDataReader(apmatrix<int> &map) {
	ifstream file;
	//opens file
	file.open(fileName_c);
	//checks if the file is open
	if (!file.is_open()) {
		cerr << "ERROR FILE NOT OPEN" << endl;
		return false;
	}
	// draws every every pixel using its relative position in the matrix to the display
	for (int y = 0; y < matrixRows_c; y++) {
		for (int x = 0; x < matrixCols_c; x++) {
			file >> map[y][x];
		}
	}
	//closes file
	file.close();
	//returns to prove the function works
	return true;
} //END OF mapDataReader

/**
 --------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @name    findMin
 @param   enclosing_method_arguments
 @return  return_type
 @details
 finds the smallest peak of the set of heights\n
 -------------------------------------------------------------------------
 */
int findMin(apmatrix<int> &map) {
	int lowest = map[0][0];
	//
	for (int y = 0; y < matrixRows_c; y++) {
		for (int x = 0; x < matrixCols_c; x++) {
			if (lowest > map[y][x]) {
				lowest = map[y][x];
			}
		}
	}
	return lowest;
} // END OF findMin

/**
 --------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @name    findMax
 @param   enclosing_method_arguments
 @return  return_type
 @details
 finds the largest peak of the set of heights\n
 -------------------------------------------------------------------------
 */
int findMax(apmatrix<int> &map) {
	int largest = map[0][0];

	for (int y = 0; y < matrixRows_c; y++) {
		for (int x = 0; x < matrixCols_c; x++) {
			if (largest < map[y][x]) {
				largest = map[y][x];
			}
		}
	}
	return largest;
} // END OF findMin

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @mname   initAllegro
 @details
 I placed all allegro  initializations in this function
 The function returns true if all initializations are 'ok' and returns
 false if any initialization fails
 --------------------------------------------------------------------------
 */
bool initAllegro() {

	//initialize display
	al_init();
	display = al_create_display(matrixCols_c, matrixRows_c);

	timer = al_create_timer(1.0 / fps_c);

	if (!al_install_keyboard()) {
		cerr << "failed to initialize the keyboard!" << endl;
		return false;
	}

	if (!timer) {
		cerr << "failed to create timer!" << endl;
		return false;
	}

	// Always check if your allegro routines worked successfully.
	if (!display) {
		al_show_native_message_box(display, "Error", "Error",
				"Failed to initialize display!",
				nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_timer(timer);
		return false;
	}

	screenBitmap = al_create_bitmap(matrixCols_c, matrixRows_c);

	if (!screenBitmap) {
		cerr << "failed to create bouncer bitmap!" << endl;
		al_destroy_display(display);
		al_destroy_timer(timer);
		return false;
	}
	event_queue = al_create_event_queue();
	if (!event_queue) {
		cerr << "failed to create event_queue!" << endl;
		al_destroy_bitmap(screenBitmap);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return false;
	}

	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon(); // initialize the ttf (True Type Font) addon

	font = al_load_ttf_font("font.ttf", 30, 0);

	if (!font) {
		cerr << "Could not load 'font.ttf'" << endl;
		al_destroy_event_queue(event_queue);
		al_destroy_bitmap(screenBitmap);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return false;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	/*
	 * @author   dwlambiri
	 * @date     Oct 6, 2017
	 *  The next function call will set the bitmap as the target
	 *  	for all the allegro writes
	 */

	al_set_target_bitmap(screenBitmap);
	al_set_window_title(display, "Mountain region map");
	return true;
} // end-of-function initAllegro

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @mname   moveBitmapToDisplay
 @details
   Allegro has a feature that allows all commands to be directed to a bitmap
   I utilized this property by creating a bitmap the same size as the screen
   	   and filling this bitmap.
   Every time I want to move the contents of the bitmap to the display I change
   	   the target of the write to the display itself, copy the bitmap to the display
   	   buffer, flip the display and then set the write target back to the bitmap.
 --------------------------------------------------------------------------
 */
void moveBitmapToDisplay() {

	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(screenBitmap, 0, 0, 0);
	al_flip_display();
	al_set_target_bitmap(screenBitmap);

} // end-of-function moveBitmapToDisplay

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @mname   cleanUp
 @details
 I am collecting all allegro cleanups in this function.
 This function is called before main exits to properly clean up the allegro library
 --------------------------------------------------------------------------
 */
void cleanUpAllegro() {
	al_destroy_bitmap(screenBitmap);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_font(font);
} // end-of-function cleanUp

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @mname   allegroEventLoop
 @details
 \n
 --------------------------------------------------------------------------
 */
bool allegroEventLoop() {

	while (true) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			continue;
		} else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			cleanUpAllegro();
			return false;
		} else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			return true;
		}

	}
	return true;
} // end-of-function allegroEventLoop

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @mname   allegroExitLoop
 @details
 \n
 --------------------------------------------------------------------------
 */
void allegroExitLoop() {

	while (true) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			cleanUpAllegro();
			return;
		}
	}
} // end-of-function allegroExitLoop

/**
 --------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @name    drawMap
 @param   enclosing_method_arguments
 @return  return_type
 @details
 \n
 -------------------------------------------------------------------------
 */
int drawMap(apmatrix<int>& map, int small, int large) {

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

	int heights[] = { 1800, 2700 };

	for (int y = 0; y < matrixRows_c; y++) {
		for (int x = 0; x < matrixCols_c; x++) {
			if (map[y][x] <= heights[0]) {
				int shade = (map[y][x] - small) * 255 / (heights[0] - small);
				al_draw_pixel(x, y, al_map_rgb(0, shade, 0));
			} else if ((map[y][x] > heights[0]) && (map[y][x] <= heights[1])) {
				int shade1 = -(map[y][x] - heights[0]) * (0xf0 - 0xd0)
						/ (heights[1] - heights[0]) + 0xd0;
				int shade2 = -(map[y][x] - heights[0]) * (0x66 - 0x22)
						/ (heights[1] - heights[0]) + 0x66;
				int shade3 = -(map[y][x] - heights[0]) * (0xf0 - 0xa0)
						/ (heights[1] - heights[0]) + 0xf0;

				al_draw_pixel(x, y, al_map_rgb(shade3, shade1, shade2));
			} else {
				int shade = (map[y][x] - heights[1]) * (0xff - 0xa0)
						/ (large - heights[1]) + 0xa0;
				al_draw_pixel(x, y, al_map_rgb(shade, shade, shade));
			}
		}
	}
	moveBitmapToDisplay();
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
		al_draw_pixel(x, y, al_map_rgb(0xff, 0, 0));
		break;
	case greeenPixel_c:
		al_draw_pixel(x, y, al_map_rgb(0, 0xff, 0));
		break;
	case bluePixel_c:
		al_draw_pixel(x, y, al_map_rgb(0, 0, 0xff));
		break;
	default:
		return false;
	} //end-of-switch
	return true;

} // end-of-function DrawPixel

/**
 --------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @name    printLowestPathInfo
 @param   enclosing_method_arguments
 @return  return_type
 @details
 \n
 -------------------------------------------------------------------------
 */
void printLowestPathInfo(int lowestElev) {

	al_draw_textf(font, al_map_rgb(255, 255, 255), 200, 50,
			ALLEGRO_ALIGN_CENTRE, "Lowest Elevation: %d", lowestElev);

}

/**
 --------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @name    displayMessage
 @param   enclosing_method_arguments
 @return  return_type
 @details
 \n
 -------------------------------------------------------------------------
 */
void displayMessage(const char* msg) {

	al_draw_textf(font, al_map_rgb(255, 255, 255), 275, 100,
			ALLEGRO_ALIGN_CENTRE, "%s", msg);
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
int findPath(apmatrix<int>& map, int startRow, int maxvalue,
		MapPixelColour colour, apvector<int> &path) {
	int totalPathLength = 0;
	int currentRow = startRow;
	//The vector path is a vector that stores the row values of each column in a route
	path[0] = startRow;
	for (int columnIndex = 1; columnIndex < map.numcols(); columnIndex++) {
		/*
		 * @author   dwlambiri
		 * @date     Oct 1, 2017
		 *  I initialized the deltas with very large values.
		 *  because I know the maximum delta a value of one hundred delta will never be selected
		 *  I used this for the matrix boundaries
		 *
		 */

		//The n variables contain the elevation difference values of each possible edge
		int edge1weight = 1001 * maxvalue;
		int edge3weight = 1001 * maxvalue;

		//If the row that I am currently in is greater than row zero
		if ((currentRow - 1) >= 0) {
			edge1weight = abs(
					map[currentRow - 1][columnIndex]
							- map[currentRow][columnIndex - 1]);
		} //end-of-if
		  //Initiallized the second 'edge'
		int edge2weight = abs(
				map[currentRow][columnIndex]
						- map[currentRow][columnIndex - 1]);
		// if the third row is equal to the total value of the row then do not assign it a proper value
		if ((currentRow + 1) < matrixRows_c) {
			edge3weight = abs(
					map[currentRow + 1][columnIndex]
							- map[currentRow][columnIndex - 1]);
		} //end-of-if

		//The following if statements compare the differences in elevation and return the lowest one
		//checks value
		if ((edge1weight < edge2weight) && (edge1weight < edge3weight)) {
			currentRow--;
			totalPathLength += edge1weight;
		} else if ((edge2weight < edge1weight) && (edge2weight < edge3weight)) {
			totalPathLength += edge2weight;
		} else if ((edge3weight < edge2weight) && (edge3weight < edge1weight)) {
			currentRow++;
			totalPathLength += edge3weight;
		} else if ((edge1weight == edge2weight)
				&& (edge1weight < edge3weight)) {
			currentRow -= rand() % 2;
			totalPathLength += edge1weight;
		} else if ((edge3weight == edge2weight)
				&& (edge3weight < edge1weight)) {
			currentRow += rand() % 2;
			totalPathLength += edge3weight;
		} else if ((edge1weight == edge3weight)
				&& (edge1weight < edge2weight)) {
			currentRow += 2 * rand() % 2 - 1;
			totalPathLength += edge1weight;
		} else if ((edge1weight == edge2weight)
				&& (edge1weight == edge3weight)) {
			currentRow += rand() % 3 - 1;
			totalPathLength += edge1weight;
		}
		path[columnIndex] = currentRow;
		drawPixel(columnIndex, currentRow, colour);

	} //end-of-for
	moveBitmapToDisplay();
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
int markAllPaths(apmatrix<int>& map, int maxValue) {
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
	for (int i = 0; i < map.numrows(); i++) {
		/*
		 * @author   dwlambiri
		 * @date     Oct 1, 2017
		 *  For each starting point (row) we return the actual path
		 *  as row positions in a vector who's indeces represent the columns.
		 */

		apvector<int> tempRun(map.numcols());
		int temp = findPath(map, i, maxValue, redPixel_c, tempRun);
		if (i == 11) {
			std::cout << "Min Path Index = " << i << " Value = " << temp
					<< std::endl;
		}

		/*
		 * @author   dwlambiri
		 * @date     Oct 1, 2017
		 *  If the current path has a smaller sum than the current best
		 *  I store the starting row value and the path vector.
		 */

		if (total1 < 0 || total1 > temp) {
			total1 = temp;
			rowvalue = i;
			bestRun = tempRun;
		}
	}

	std::cout << "Min Path Index = " << rowvalue << " Value = " << total1
			<< std::endl;
	/*
	 * @author   dwlambiri
	 * @date     Oct 1, 2017
	 *  I am drawing the best path of the run in green.
	 */

	for (int i = 0; i < map.numcols(); i++) {
		drawPixel(i, bestRun[i], bluePixel_c);
	} //end-of-for

	moveBitmapToDisplay();

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
void initMatrices(apmatrix<int>& map) {

	for (int i = 0; i < matrixRows_c; i++) {
		for (int j = 0; j < matrixCols_c; j++) {
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
  This function implements the algorithm found in section 24.1 (page 586)
   of the second edition of the CLR algorithms book.
 --------------------------------------------------------------------------
 */
bool relaxVertex(int currentX, int y, int nextX, int wheight,
		apmatrix<int>& distance, apmatrix<int>& predecesor) {

	if (currentX < 0 || (nextX >= matrixRows_c))
		return false;
	if (y >= matrixCols_c - 1)
		return false;
	if ((distance[nextX][y + 1] == invalidValue_c)
			|| (distance[nextX][y + 1] > distance[currentX][y] + wheight)) {
		distance[nextX][y + 1] = distance[currentX][y] + wheight;
		predecesor[nextX][y + 1] = currentX;
	}
	return true;
} // end-of-function relax

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 4, 2017
 @mname   shortestPathsFromSingleStart
 @details
   This function implements the algorithm found in section 24.2 (page 592)
   	   of the second edition of the CLR algorithms book.
   The algorithm finds shortest paths from a given source to all nodes on
   	   the last column if a path exists.
   Please note there are node pairs that do not have connecting paths using
   	   the three edge connectivity property of this problem.
   After finding all the pats the algorithm will iterate through all the found
   	   paths to find the best possible path among this set.
   This path is then displayed to the screen as a red line.

   I picked this algorithm because the map with the three edges can be modeled
   	   as an acyclical, directed graph with no negative edge values.
   The CLR book states that the performance of Floyd-Warshall is proportional
   	   with n^3 where n is the number of vertices.
   In our problem n = maxCols_c * maxRows_c
   The algorithm I chose has a performance of n + e where e is the number of edges.
   This algorithm is called in markAllPaths2 maxRows_c times.
   The number of edges is at most 3*n for our problem.
   Therefore the running time of finding the shortest path with this method is
   	   (n + 3n) * maxRows_c
   This is better than the FW algorithm by a large factor.
   Considering how long this algorithm takes to finish, FW would have taken
   	   a looooooooooooooooong time to complete.
 --------------------------------------------------------------------------
 */
int shortestPathsFromVertex(int start, apmatrix<int>& map,
		apvector<int>& bestPath) {

	/*
	 * @author   dwlambiri
	 * @date     Oct 6, 2017
	 *  I declared these two variables static to avoid being created every
	 *  	time the function is called.
	 *  This way the variables are created only the first time the function
	 *  	is called.
	 *  In CLR distanceToStartVertex is denoted by d and
	 *  	predecesorVertex is denoted by pi.
	 */

	static apmatrix<int> distanceToStartVertex(map.numrows(), map.numcols());
	static apmatrix<int> predecesorVertex(map.numrows(), map.numcols());

	int row = 0;

	initMatrices(distanceToStartVertex);
	initMatrices(predecesorVertex);

	distanceToStartVertex[start][0] = 0;

	for (int y = 0; y < matrixCols_c - 1; y++) {
		bool done = false;
		/*
		 * @author   dwlambiri
		 * @date     Oct 6, 2017
		 *  Each column we start using this expression.
		 *  	int x = ((start - y) >= 0) ? (start - y) : 0
		 */

		for (int x = ((start - y) >= 0) ? (start - y) : 0; x < matrixRows_c;
				x++) {

			if ((done == false)
					&& (distanceToStartVertex[x][y] == invalidValue_c))
				continue;

			/*
			 * @author   dwlambiri
			 * @date     Oct 6, 2017
			 *  The variable done is used to reduce the number of iterations.
			 *  We need to stop processing nodes in a column when we encounter
			 *  	an invalidValue_c after we have seen nodes with positive path lengths.
			 */

			if ((done == true)
					&& (distanceToStartVertex[x][y] == invalidValue_c))
				break;

			if (x == 0) {
				//top row
				int edge1weight = abs(map[x][y] - map[x][y + 1]);
				int edge2weight = abs(map[x][y] - map[x + 1][y + 1]);
				relaxVertex(x, y, x, edge1weight, distanceToStartVertex,
						predecesorVertex);
				relaxVertex(x, y, (x + 1), edge2weight, distanceToStartVertex,
						predecesorVertex);
				done = true;
			} else if (x == matrixRows_c - 1) {
				int edge1weight = abs(map[x][y] - map[x][y + 1]);
				int edge3weight = abs(map[x][y] - map[x - 1][y + 1]);
				relaxVertex(x, y, x, edge1weight, distanceToStartVertex,
						predecesorVertex);
				relaxVertex(x, y, (x - 1), edge3weight, distanceToStartVertex,
						predecesorVertex);
				done = true;
			} else {
				int edge1weight = abs(map[x][y] - map[x][y + 1]);
				int edge2weight = abs(map[x][y] - map[x + 1][y + 1]);
				int edge3weight = abs(map[x][y] - map[x - 1][y + 1]);
				relaxVertex(x, y, x, edge1weight, distanceToStartVertex,
						predecesorVertex);
				relaxVertex(x, y, (x + 1), edge2weight, distanceToStartVertex,
						predecesorVertex);
				relaxVertex(x, y, (x - 1), edge3weight, distanceToStartVertex,
						predecesorVertex);
				done = true;
			}
		} //end-of-for
	} //end-of-for

	for (int i = 0; i < matrixRows_c; i++) {
		if (distanceToStartVertex[i][matrixCols_c - 1] == invalidValue_c)
			continue;
		if ((distanceToStartVertex[row][matrixCols_c - 1] == invalidValue_c)
				|| (distanceToStartVertex[row][matrixCols_c - 1]
						> distanceToStartVertex[i][matrixCols_c - 1])) {
			row = i;
		} //end-of-if
	} //end-of-for

	int temp2 = predecesorVertex[row][matrixCols_c - 1];
	bestPath[matrixCols_c - 1] = row;

	for (int i = matrixCols_c - 1; i >= 1; i--) {
		bestPath[i - 1] = predecesorVertex[temp2][i];
		temp2 = predecesorVertex[temp2][i];
	} //end-of-for

	for (int i = 0; i < map.numcols(); i++) {
		drawPixel(i, bestPath[i], redPixel_c);
	} //end-of-for

	moveBitmapToDisplay();
	return distanceToStartVertex[row][matrixCols_c - 1];
} // end-of-function shortestPathsFromVertex

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Sep 30, 2017
 @mname   markAllPaths2
 @details
  This function calls shortestPathsFromVertex() for each node in the first
  	  column of the matrix.
  Similar to markAllPaths() it then remembers the best possible path up to that point
      in the run.

 --------------------------------------------------------------------------
 */
int markAllPaths2(apmatrix<int>& map) {
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
	for (int i = 0; i < map.numrows(); i++) {
		/*
		 * @author   dwlambiri
		 * @date     Oct 1, 2017
		 *  For each starting point (row) we return the actual path
		 *  as row positions in a vector who's indeces represent the columns.
		 */

		apvector<int> tempRun(map.numcols());
		int temp = shortestPathsFromVertex(i, map, tempRun);

		/*
		 * @author   dwlambiri
		 * @date     Oct 1, 2017
		 *  If the current path has a smaller sum than the current best
		 *  I store the starting row value and the path vector.
		 */

		if (runsize < 0 || runsize > temp) {
			runsize = temp;
			rowvalue = i;
			bestRun = tempRun;
		}
	}

	std::cout << "Min Path Index = " << rowvalue << " Value = " << runsize
			<< std::endl;
	/*
	 * @author   dwlambiri
	 * @date     Oct 1, 2017
	 *  I am drawing the best path of the run in green.
	 */

	for (int i = 0; i < map.numcols(); i++) {
		drawPixel(i, bestRun[i], bluePixel_c);
	} //end-of-for

	return runsize;
} // end-of-function markAllPaths

//MAIN FUNCTION
int main(int argc, char **argv) {

	//we need full main declaration in osx
	//Initializes pseudo randomization
	srand(time(nullptr));
	if (initAllegro() == false) {
		cerr << "program error: could not initialize allegro" << endl;
		return 1;
	}

	//Initializes an apmatrix to store all the map's data
	apmatrix<int> mountainMat(matrixRows_c, matrixCols_c, 0);
	mapDataReader(mountainMat);

	//saves the smallest and largest peaks on the mountains into two variables
	int largestSize = findMax(mountainMat);
	int smallestSize = findMin(mountainMat);

	//Prints the value of the largest and smallest peaks on the mountain
	std::cout << "The largest size is: " << largestSize << endl <<"And the smallest size is: " << smallestSize << std::endl;

    /*
	 * @author   dwlambiri
	 * @date     Oct 6, 2017
	 *  The method runs in three steps.
	 *  1. It draws the map
	 *  2. It calculates and draws paths
	 *  3. It highlights the optimal path
	 *  4. It waits for user input to either continue with the next method or exit.
	 *
	 *   The method is animated and the paths are drawn as they are calculated.
	 *   Because the computational complexity of the markAllPaths is low,
	 *   	(3 * matrixCols_c * matrixRows_c) the animation is very fast.
	 */

    drawMap(mountainMat, smallestSize, largestSize);
     //Draws the initial map using a grey scale into an allegro buffer
    int pathLength = markAllPaths(mountainMat, largestSize);
    printLowestPathInfo(pathLength);
    displayMessage("Press any key to see next algorithm");
    moveBitmapToDisplay();

    // Wait for key press
    if(allegroEventLoop() == false) return 0;

    //this should clear the bitmap
    al_clear_to_color(al_map_rgb(0,0,0));

    /*
    	 * @author   dwlambiri
    	 * @date     Oct 6, 2017
    	 *  The method runs in three steps.
    	 *  1. It draws the map
    	 *  2. It calculates and draws paths
    	 *  3. It highlights the optimal path
    	 *  4. It waits for user input to either continue with the next method or exit.
    	 *
    	 *   The method is animated and the paths are drawn as they are calculated.
    	 *   The computational complexity is much greater than for the previous algorithm,
    	 *   	((n + 3n) * maxRows_c) this runs maxRows_c slower.
    	 */

    drawMap(mountainMat, smallestSize, largestSize);
    pathLength = markAllPaths2(mountainMat);
    printLowestPathInfo(pathLength);
    displayMessage("Close window to exit program");
    moveBitmapToDisplay();

    allegroExitLoop();
	return 0;
}//RETURN OF MAIN IF EVERTHING GOES WELL
