/*****************************************************************************
 *	Name:
 *	File:
 *	Course: ICS4U
 *	Date:
 *
 *	Usage:
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
#include <fstream>
#include <cstdlib>
#include <apstring.h>
#include <apmatrix.h>
#include <apstring.cpp>


#define WHITE al_map_rgb(255,255,255)
#define BLACK al_map_rgb(0,0,0)
#define BLUE al_map_rgb(50,50,255)
#define YELLOW al_map_rgb(255,255,0)
#define GREEN al_map_rgb(50,255,50)

using namespace std;

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
const int ratioValue = 100;
ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_FONT *trebuchetSmall = nullptr;

void initAllegro(int w, int h){
  //initializes allegro
  al_init();
  al_init_primitives_addon();
  al_init_font_addon();
  al_init_ttf_addon();

  if(!al_init()) {
    fprintf(stderr, "failed to initialize allegro!\n");
    return;
  }

  SCREEN_WIDTH = ratioValue* w;
  SCREEN_HEIGHT = ratioValue* h;

  display = al_create_display (SCREEN_WIDTH, SCREEN_HEIGHT);
  if (!display){
    cerr << "failed to create display! " << endl;
  }

  trebuchetSmall = al_load_font("font.ttf", 15, 0);
  if(!trebuchetSmall) {
    fprintf(stderr, "failed to create font!\n");
    return;
  }

  event_queue = al_create_event_queue();
  if(!event_queue) {
    fprintf(stderr, "failed to create event_queue!\n");
    al_destroy_display(display);
    return;
  }

  al_register_event_source(event_queue, al_get_display_event_source(display));
}

void printMaze(const apmatrix <char> maze, int counter) {

  //al_set_target_bitmap(al_get_backbuffer (display));
  al_clear_to_color(al_map_rgb(0,0,0));
  for (int i = 0; i < maze.numrows(); i++){
    for (int j = 0; j < maze.numcols(); j++){
      if (maze[i][j] == '#')
        al_draw_filled_rounded_rectangle(j*ratioValue,i*ratioValue, j*ratioValue+ratioValue, i*ratioValue+ratioValue, 20,20,WHITE);
      else if (maze[i][j] == '+')
        al_draw_filled_rectangle(j*ratioValue,i*ratioValue, j*ratioValue+ratioValue, i*ratioValue+ratioValue, BLUE);
      else if (maze[i][j] == 'S')
        al_draw_filled_rectangle(j*ratioValue,i*ratioValue, j*ratioValue+ratioValue, i*ratioValue+ratioValue,YELLOW);
      else if (maze[i][j] == 'G')
        al_draw_filled_rectangle(j*ratioValue,i*ratioValue, j*ratioValue+ratioValue, i*ratioValue+ratioValue,GREEN);
//      else
//        al_draw_filled_rectangle(j*ratioValue,i*ratioValue, j*ratioValue+ratioValue, i*ratioValue+ratioValue, WHITE);
    }
  }

//  if (counter == 0)
//    al_draw_text(trebuchetSmall, al_map_rgb(255,255,255), SCREEN_WIDTH / 2, SCREEN_HEIGHT* (6/8), ALLEGRO_ALIGN_CENTRE, "Hit Space for solution");
//  al_draw_text(trebuchetSmall, al_map_rgb(255,255,255), SCREEN_WIDTH / 2, SCREEN_HEIGHT* (7/8), ALLEGRO_ALIGN_CENTRE, "Hit X to exit");

  al_flip_display ();
  al_rest(1.0/60.0);

//  while(1) {
//    ALLEGRO_EVENT ev;
//    ALLEGRO_TIMEOUT timeout;
//    al_init_timeout(&timeout, 0.06);
//
//    bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
//
//    if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
//      al_destroy_display(display);
//      al_destroy_event_queue(event_queue);
//      return;
//    }
//  }
}

bool spacekeyPressed() {
  //variable
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	//form the required objects
  if(!al_install_keyboard()) {
    fprintf(stderr, "failed to initialize the keyboard!\n");
 	}

 	event_queue = al_create_event_queue();
 	if(!event_queue) {
    fprintf(stderr, "failed to create event_queue!\n");
    al_destroy_display(display);
 	}

	//registers the follwing things as sources of events
  al_register_event_source(event_queue, al_get_keyboard_event_source());

	//declaring the variable that stores events
  ALLEGRO_EVENT ev;
  al_wait_for_event(event_queue, &ev);

  //checks if keys are pressed
	if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
		  return true;
  }

  al_destroy_event_queue(event_queue);

  return false;
}

