//includes
#include <iostream>
#include <fstream>
#include <apmatrix.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include "allegro5/allegro_image.h"

using namespace std;

//keeps a list of colours used to draw lines
enum pixelColour {
	red, green, blue, orange
};

//struct for coordinates objects
struct Coordinates {
	int x;
	int y;
};

//struct for object containing position and size
struct Object {
	Coordinates position;
	int size;
};

//Constant variables
const int MATRIX_COLS = 844;
const int MATRIX_ROWS = 480;
const char FILENAME[] = "Colorado_844x480.dat";
const int MAX_INTENSITY = 255;
const int SCREEN_WIDTH = 844;
const int SCREEN_HEIGHT = 480;
const int FPS = 10;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_TIMER *timer = NULL; //to keep checking for events
ALLEGRO_EVENT_QUEUE *event_queue = NULL; //to store events such as clicks, etc
ALLEGRO_FONT *trebuchet = NULL;
ALLEGRO_FONT *trebuchetSmall = NULL;
ALLEGRO_EVENT ev;
ALLEGRO_TIMEOUT timeout; //how long the computer waits before refreshing its search for an event

//puts up the menu on the Screen
int menuScreen() {
	//variable declaration
	//declaring the buttons as bitmaps
	ALLEGRO_BITMAP *exitButton_bitmap = NULL;
	ALLEGRO_BITMAP *algorithmTwoButton_bitmap = NULL;
	ALLEGRO_BITMAP *algorithmOneButton_bitmap = NULL;
	//this struct holds all aspects of a button needed for it to work
	Object exitButton;
	Object algorithmTwoButton;
	Object algorithmOneButton;

	//initialization of some button variables for formatting
	exitButton.size = 50;
	exitButton.position.x = SCREEN_WIDTH / 2.0 - exitButton.size * 3 / 2.0;
	exitButton.position.y = 360;

	algorithmTwoButton.size = 50;
	algorithmTwoButton.position.x = SCREEN_WIDTH / 2.0
			- algorithmTwoButton.size * 3 / 2.0;
	algorithmTwoButton.position.y = 290;

	algorithmOneButton.size = 50;
	algorithmOneButton.position.x = SCREEN_WIDTH / 2.0
			- algorithmOneButton.size * 3 / 2.0;
	algorithmOneButton.position.y = 220;

	//creating the many different aspects of the main menu
	display = al_create_display(640, 480);
	if (!display) {
		cerr << "failed to create display! " << endl;
	}

	event_queue = al_create_event_queue();
	if (!event_queue) {
		cerr << "failed to create event_queue!" << endl;
		al_destroy_display(display);
	}

	al_install_mouse();
	if (!al_install_mouse()) {
		cerr << "failed to initialize the mouse!" << endl;
	}

	trebuchet = al_load_font("font.ttf", 30, 0);
	if (!trebuchet) {
		fprintf(stderr, "failed to create font!\n");
	}

	trebuchetSmall = al_load_font("font.ttf", 20, 0);
	if (!trebuchet) {
		fprintf(stderr, "failed to create font!\n");
	}

	exitButton_bitmap = al_create_bitmap(exitButton.size * 3, exitButton.size);
	if (!exitButton_bitmap) {
		fprintf(stderr, "failed to create exitButton bitmap!\n");
		al_destroy_display(display);
	}

	algorithmTwoButton_bitmap = al_create_bitmap(algorithmTwoButton.size * 3,
			algorithmTwoButton.size);
	if (!algorithmTwoButton_bitmap) {
		fprintf(stderr, "failed to create mainMenuButton bitmap!\n");
		al_destroy_display(display);
	}

	algorithmOneButton_bitmap = al_create_bitmap(algorithmOneButton.size * 3,
			algorithmOneButton.size);
	if (!algorithmOneButton_bitmap) {
		fprintf(stderr, "failed to create mainMenuButton bitmap!\n");
		al_destroy_display(display);
	}

	timer = al_create_timer(1.0 / FPS); //timer operates 10 per second
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
	}

	//sets the colours for all the buttons
	al_set_target_bitmap(exitButton_bitmap);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(algorithmTwoButton_bitmap);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(algorithmOneButton_bitmap);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	//capture the things I want to display on the screen
	al_set_target_bitmap(al_get_backbuffer(display));

	//allow the event queue to draw events from the follwing sources
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//timer starts
	al_start_timer(timer);

	//the loop that contains the code for any events and their subsequent results
	while (1) {
		al_init_timeout(&timeout, 0.06);

		bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout); // tells computer to look for event

		//exits program if display is closed
		if (get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		//exits program if exit button is pressed
		else if (ev.mouse.y > exitButton.position.y
				&& ev.mouse.y < exitButton.position.y + exitButton.size
				&& ev.mouse.x > exitButton.position.x
				&& ev.mouse.x < exitButton.position.x + exitButton.size * 3) {
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				return 0;
				break;
			}
		}

		//does the second algorithm
		else if (ev.mouse.y > algorithmTwoButton.position.y
				&& ev.mouse.y
						< algorithmTwoButton.position.y
								+ algorithmTwoButton.size
				&& ev.mouse.x > algorithmTwoButton.position.x
				&& ev.mouse.x
						< algorithmTwoButton.position.x
								+ algorithmTwoButton.size * 3) {
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				//algorithmTwoScreen();
				return 2;
				break;
			}
		}

		//does the first algorithm
		else if (ev.mouse.y > algorithmOneButton.position.y
				&& ev.mouse.y
						< algorithmOneButton.position.y
								+ algorithmOneButton.size
				&& ev.mouse.x > algorithmOneButton.position.x
				&& ev.mouse.x
						< algorithmOneButton.position.x
								+ algorithmOneButton.size * 3) {
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				return 1;
				break;
			}
		}

//		//sets the background colour
		al_clear_to_color(al_map_rgb(100, 10, 10));
		al_draw_text(trebuchet, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 50,
				ALLEGRO_ALIGN_CENTRE, "Greedy Walking Mountains!");

		//forms the buttons on the screen
		al_draw_bitmap(algorithmTwoButton_bitmap, algorithmTwoButton.position.x,
				algorithmTwoButton.position.y, 100);
		al_draw_bitmap(exitButton_bitmap, exitButton.position.x,
				exitButton.position.y, 100);
		al_draw_bitmap(algorithmOneButton_bitmap, algorithmOneButton.position.x,
				algorithmOneButton.position.y, 100);

		//puts the labels on the buttons so the user clearly know which one to select
		al_draw_text(trebuchetSmall, al_map_rgb(100, 10, 10), SCREEN_WIDTH / 2,
				235, ALLEGRO_ALIGN_CENTRE, "Lowest Elevation Change");
		al_draw_text(trebuchetSmall, al_map_rgb(100, 10, 10), SCREEN_WIDTH / 2,
				305, ALLEGRO_ALIGN_CENTRE, "Low as Possible");
		al_draw_text(trebuchetSmall, al_map_rgb(100, 10, 10), SCREEN_WIDTH / 2,
				375, ALLEGRO_ALIGN_CENTRE, "Exit");

		al_flip_display();
	}

	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}

//draws the topographical map of the mountain
int drawMap(apmatrix<int> &map, int large, int small) {
	float range = large - small;
	float ratios = range / MAX_INTENSITY;
	//initialize display

	display = al_create_display(MATRIX_COLS, MATRIX_ROWS);

	// Always check if your allegro routines worked successfully.
	if (!display) {
		al_show_native_message_box(display, "Error", "Error",
				"Failed to initialize display!",
				nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		return 1;
	}

	al_set_window_title(display, "Mountain region map");

	for (int y = 0; y < MATRIX_ROWS; y++) {
		for (int x = 0; x < MATRIX_COLS; x++) {
			int shiftValue = map[y][x] - small;
			int temp = shiftValue / ratios;

			if (shiftValue <= (range / 3))
				al_draw_pixel(x, y, al_map_rgb(0, 0, temp));

			else if (shiftValue <= (range * 0.67)
					&& shiftValue > (range * (1 / 3)))
				al_draw_pixel(x, y, al_map_rgb(temp, 0, temp));

			else if (shiftValue > (range * 0.67))
				al_draw_pixel(x, y, al_map_rgb(temp, temp, temp));
		}
	}

	return 0;
}

//function that reads in data from a file
bool MapDataDrawer(apmatrix<int> &map) {
	ifstream file;

	file.open(FILENAME);

	//gives warning if the file didn’t open
	if (!file.is_open()) {
		cerr << "ERROR FILE NOT OPEN" << endl;
		return false;
	}

//takes in the map data
	for (int y = 0; y < map.numrows(); y++) {
		for (int x = 0; x < map.numcols(); x++) {
			file >> map[y][x];
		}
	}

	file.close();
//if successfully drawn data, returns true
	return true;
}

//return the minimum value in a matrix
int findMin(apmatrix<int> &matrix) {

	int lowest = matrix[0][0];

	for (int i = 0; i < matrix.numrows(); i++) {
		for (int j = 1; j < matrix.numcols(); j++) {
			if (lowest > matrix[i][j]) {
				lowest = matrix[i][j];
			}
		}
	}
	return lowest;
}

//return the max value in a matrix
int findMax(apmatrix<int> &matrix) {

	int highest = matrix[0][0];

	for (int i = 0; i < matrix.numrows(); i++) {
		for (int j = 1; j < matrix.numcols(); j++) {
			if (highest < matrix[i][j]) {
				highest = matrix[i][j];
			}
		}
	}
	return highest;
}

//draws one pixel with a choice of three colours
int drawPixel(int x, int y, pixelColour colour) {
	switch (colour) {
	case red:
		al_draw_pixel(x, y, al_map_rgb(255, 0, 0));
		break;
	case green:
		al_draw_pixel(x, y, al_map_rgb(0, 255, 0));
		break;
	case blue:
		al_draw_pixel(x, y, al_map_rgb(0, 0, 255));
		break;
	case orange:
		al_draw_pixel(x, y, al_map_rgb(255, 160, 34));
		break;
	default:
		return 1;
	}
	return 0;
}

int drawPath(apmatrix<int> &map, int startRow, pixelColour colour) {
	int maxvalue = 10000;
	int total = 0;
	int row = startRow;

	for (int j = 1; j < map.numcols(); j++) {

		int n1 = 100 * maxvalue;
		int n3 = 100 * maxvalue;

		if ((row - 1) >= 0) {
			n1 = abs(map[row - 1][j] - map[row][j - 1]);

		} //end-of-if

		int n2 = abs(map[row][j] - map[row][j - 1]);

		if ((row + 1) < map.numrows()) {
			n3 = abs(map[row + 1][j] - map[row][j - 1]);
		} //end-of-if

		//checks value
		if ((n1 < n2) && (n1 < n3)) {
			row--;
			total += n1;
		} else if ((n2 < n1) && (n2 < n3)) {
			total += n2;
		} else if ((n3 < n2) && (n3 < n1)) {
			row++;
			total += n3;
		} else if ((n1 == n2) && (n1 < n3)) {
			row -= rand() % 2;
			total += n1;
		} else if ((n3 == n2) && (n3 < n1)) {
			row += rand() % 2;
			total += n3;
		} else if ((n1 == n3) && (n1 < n2)) {
			row += 2 * rand() % 2 - 1;
			total += n1;
		} else if ((n1 == n2) && (n1 == n3)) {
			row += rand() % 3 - 1;
			total += n1;
		}
		drawPixel(j, row, colour);

	}
	return total;
}

int drawLowPath(apmatrix<int> &map, int startRow, pixelColour colour) {
	int maxvalue = 10000;
	float total = 0;
	int row = startRow;

	for (int i = 1; i < map.numcols(); i++) {

		int n1 = 100 * maxvalue;
		int n3 = 100 * maxvalue;

		if ((row - 1) >= 0) {
			n1 = abs(map[row - 1][i] - map[row][i - 1]);

		} //end-of-if

		int n2 = abs(map[row][i] - map[row][i - 1]);

		if ((row + 1) < map.numrows()) {
			n3 = abs(map[row + 1][i] - map[row][i - 1]);
		} //end-of-if

		int v1 = 100 * maxvalue;
		int v3 = 100 * maxvalue;

		if ((row - 1) >= 0) {
			v1 = map[row - 1][i];

		} //end-of-if

		int v2 = map[row][i];

		if ((row + 1) < map.numrows()) {
			v3 = map[row + 1][i];
		} //end-of-if

		//checks value
		if ((v1 < v2) && (v1 < v3)) {
			row--;
			total += n1;
		} else if ((v2 < v1) && (v2 < v3)) {
			total += n2;
		} else if ((v3 < v2) && (v3 < v1)) {
			row++;
			total += n3;
		} else if ((v1 == v2) && (v1 < v3)) {
			row -= rand() % 2;
			total += n1;
		} else if ((v3 == v2) && (v3 < v1)) {
			row += rand() % 2;
			total += n3;
		} else if ((v1 == v3) && (v1 < v2)) {
			row += 2 * rand() % 2 - 1;
			total += n1;
		} else if ((v1 == v2) && (v1 == v3)) {
			row += rand() % 3 - 1;
			total += n1;
		}
		drawPixel(i, row, colour);

	}
	return total;
}
//finds index of the lowest data point in a vector, returns it
int indexOfLowest(apvector<int> &data) {
	int low = data[0];
	int indexOfLow = 0;

	for (int i = 1; i < data.length(); i++) {
		if (low > data[i]) {
			low = data[i];
			indexOfLow = i;
		}
	}

	return indexOfLow;
}

void printFont(int lowestElev) {

	ALLEGRO_FONT *font = al_load_ttf_font("font.ttf", 30, 0);

	if (!font) {
		cout << "Could not load 'font.ttf'";
	}
	al_draw_textf(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2,
			SCREEN_HEIGHT / 2 - 30, ALLEGRO_ALIGN_CENTRE,
			"Lowest Elevation: %d", lowestElev);
}


int main(int argc, char **argv) {
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon(); // initialize the ttf addon
	al_init(); //initialize allegro

	//variable declaration
	apmatrix<int> mountainMat(MATRIX_ROWS, MATRIX_COLS, 0); //data from mountain textfile
	apvector<int> totalElevChange(mountainMat.numrows(), 0);
	apvector<int> lowestElevChange(mountainMat.numrows(), 0);
	int indexOfLowElevPath;
	int indexOfLowElevChangePath;
	int highestElevation;
	int lowestElevation;
	int userInput;

	userInput = menuScreen();

	//takes data from text file
	MapDataDrawer(mountainMat);

	//finds the lowest and highest points of elevation on the map
	highestElevation = findMax(mountainMat);
	lowestElevation = findMin(mountainMat);

	drawMap(mountainMat, highestElevation, lowestElevation);

	if (userInput == 1) {
		//printing the lines on the map and returning their elevation changes, least elevation change algorithm
		for (int i = 0; i < mountainMat.numrows(); i++) {
			totalElevChange[i] = drawPath(mountainMat, i, red);
		}

		indexOfLowElevPath = indexOfLowest(totalElevChange);

		//cout << "i = " << indexOfLowElevPath << " tec = " << totalElevChange[indexOfLowElevPath] << endl;

		//drawing the path with least elevation change
		drawPath(mountainMat, indexOfLowElevPath, green);

		printFont(totalElevChange[indexOfLowElevPath]);
	}
//
	if (userInput == 2) {
		//printing the lines on the map and returning their average elevation, lowest average elevation algorithm
		for (int i = 0; i < mountainMat.numrows(); i++) {
			lowestElevChange[i] = drawLowPath(mountainMat, i, red);
		}

		indexOfLowElevChangePath = indexOfLowest(lowestElevChange);

		//cout << "i = " << indexOfLowElevPath << " tec = " << lowestElevChange[indexOfLowElevPath] << endl;


		//drawing the path with lowest average elevation
		drawLowPath(mountainMat, indexOfLowElevChangePath, orange);
//
		printFont(lowestElevChange[indexOfLowElevChangePath]);
	}

	if(userInput == 3) {
		return 0;
	}

	//prints to the screen
	al_flip_display();
	al_rest(15);

	return 0;
}
