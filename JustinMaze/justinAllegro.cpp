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
const int scale = 100;

bool initializeEvents(int w, int h){
    //initializes allegro
    al_init();
    al_init_primitives_addon();
    //initializes display

    SCREEN_WIDTH = w*scale;
    SCREEN_HEIGHT = h*scale;

    display = al_create_display (SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display){
        cerr << "failed to create display! " << endl;
        return false;
    }
    return true;
}
//function that creates calculator display. Passes operation string by reference to change it
void drawMaze(apmatrix<mazePart> &maze){



    //al_set_target_bitmap(al_get_backbuffer (display));

	al_clear_to_color(al_map_rgb(0,0,0));

    for (int y = 0; y < maze.numrows(); y++){
        for (int x = 0; x < maze.numcols(); x++){
            if (maze[y][x].character == '#')
                al_draw_filled_rounded_rectangle(x*scale,y*scale, x*scale+scale, y*scale+scale,25,25,WHITE);
            else if (maze[y][x].character == '+')
            	al_draw_filled_circle((x+0.5)*scale,(y+0.5)*scale, scale/2, RED);
                //al_draw_filled_rectangle(x*scale,y*scale, x*scale+scale, y*scale+scale,RED);
            else if (maze[y][x].character == 'S')
                al_draw_filled_rectangle(x*scale,y*scale, x*scale+scale, y*scale+scale,BLUE);
            else if (maze[y][x].character == 'G')
                al_draw_filled_rectangle(x*scale,y*scale, x*scale+scale, y*scale+scale,GREEN);
//            else
//                al_draw_filled_circle((x+0.5)*scale,(y+0.5)*scale, scale/2,WHITE);
        }
    }

    al_flip_display ();
    al_rest(1.0/60.0);
}
