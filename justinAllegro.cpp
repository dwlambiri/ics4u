/*****************************************************************************
 *	Name:   Justin Lee
 *	File:   justinAllegro.cpp
 *	Course: ICS4U
 *	Date:   Oct 28, 2017
 *
 *	Usage: Contains functions that use allegro. These include initializing allegro(such as the
            mouse and keyboard) and creating the calculator display.
 *
 *	Revision History:
 *
 *	Known Issues:
 *
 *****************************************************************************/
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#include <iostream>
#include "justinAllegro.h"

#define WHITE al_map_rgb(255,255,255)
#define BLACK al_map_rgb(0,0,0)
#define RED al_map_rgb(255,0,0)
#define BLUE al_map_rgb(0,0,255)
#define YELLOW al_map_rgb(255,255,0)
#define GREEN al_map_rgb(0,255,0)

using namespace std;
//constant for allegro pointer
ALLEGRO_DISPLAY *display = nullptr;
int SCREEN_WIDTH;
float SCREEN_HEIGHT;
const int scale = 30;

void initializeEvents(){
    //initializes allegro
    al_init();
    al_init_primitives_addon();
    //initializes display
    display = al_create_display (SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display){
        cerr << "failed to create display! " << endl;
    }
}
//function that creates calculator display. Passes operation string by reference to change it
void drawMaze(apmatrix<mazePart> &maze){
    al_init();

    SCREEN_WIDTH = maze.numcols()*scale;
    SCREEN_HEIGHT = maze.numrows()*scale;

    initializeEvents();
    al_set_target_bitmap(al_get_backbuffer (display));

    for (int y = 0; y < maze.numrows(); y++){
        for (int x = 0; x < maze.numcols(); x++){
            if (maze[y][x].character == '#')
                al_draw_filled_rectangle(x*scale,y*scale, x*scale+scale, y*scale+scale,BLACK);
            else if (maze[y][x].character == '+')
                al_draw_filled_rectangle(x*scale,y*scale, x*scale+scale, y*scale+scale,RED);
            else if (maze[y][x].character == 'S')
                al_draw_filled_rectangle(x*scale,y*scale, x*scale+scale, y*scale+scale,BLUE);
            else if (maze[y][x].character == 'G')
                al_draw_filled_rectangle(x*scale,y*scale, x*scale+scale, y*scale+scale,GREEN);
            else
                al_draw_filled_rectangle(x*scale,y*scale, x*scale+scale, y*scale+scale,WHITE);
        }
    }

    al_flip_display ();
    al_rest(5);
}
