/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   GraphicsEngine.cpp
 *	Course: ICS4U
 *	Date:   Nov 24, 2017
 *
 *	Purpose:
 *
 *	Usage: This contains a graphics class' methods which are used to draw
 *			the maze.
 *
 *	Revision History:
 *
 *	Known Issues: NONE
 *
 *****************************************************************************/



//includes
#include <iostream>
#include <fstream>
#include <time.h>
#include "GraphicsEngine.hpp"


/**
  --------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 31, 2017
   @name    GraphicsEngine::GraphicsEngine
   @param
   @return
   @details
	constructor\n
  -------------------------------------------------------------------------
 */
GraphicsEngine::GraphicsEngine(){
	display = nullptr;
	event_queue = nullptr;
	timer = nullptr;
	screenBitmap = nullptr;
	font = nullptr;
	windowWidth = 0;
	windowHeight = 0;
	fps = 60;

}

/**
  --------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 31, 2017
   @name    GraphicsEngine::cleanup
   @param
   @return  void
   @details
	This method is called from the GraphicsEngine destructor and it
	destroys all of the allegro aspects. \n
  -------------------------------------------------------------------------
 */
void GraphicsEngine::cleanUp() {
	al_destroy_bitmap(screenBitmap);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_font(font);
}

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @mname   GraphicsEngine::initAllegro
 @details
 I placed all allegro  initializations in this function
 The function returns true if all initializations are 'ok' and returns
 false if any initialization fails
 --------------------------------------------------------------------------
 */
bool
GraphicsEngine::initAllegro(const char* title, const int windowWidth_c,
							const int windowHeight_c) {

	//initialize display
	al_init();
	display = al_create_display(windowWidth_c, windowHeight_c);
	this->windowWidth = windowWidth_c;
	this->windowHeight = windowHeight_c;

	// Always check if your allegro routines worked successfully.
	if (!display) {
		std::cerr << "allegro error: failed to initialize display!"
				<< std::endl;
		return false;
	}

	timer = al_create_timer(1.0 / fps);

	if (!timer) {
		std::cerr << "allegro error: failed to create timer!" << std::endl;
		al_destroy_display(display);
		return false;
	}

	screenBitmap = al_create_bitmap(windowWidth_c, windowHeight_c);

	if (!screenBitmap) {
		std::cerr << "allegro error: failed to create bitmap!" << std::endl;
		al_destroy_display(display);
		al_destroy_timer(timer);
		return false;
	}

	event_queue = al_create_event_queue();
	if (!event_queue) {
		std::cerr << "allegro error: failed to create allegro event queue!"
				<< std::endl;
		al_destroy_bitmap(screenBitmap);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return false;
	}

	//This program does not need / use fonts

	//al_init_font_addon(); // initialize the font addon
	//al_init_ttf_addon(); // initialize the ttf (True Type Font) addon

//	const char* fontfile = "font.ttf";
//	font = al_load_font(fontfile, fontSize_c, 0);
//
//	if (!font) {
//		std::cerr << "allegro error:  could not load 'font.ttf'" << std::endl;
//		al_destroy_event_queue(event_queue);
//		al_destroy_bitmap(screenBitmap);
//		al_destroy_display(display);
//		al_destroy_timer(timer);
//		return false;
//	}

	if(!al_install_mouse()) {
		std::cerr << "allegro error:  could not init mouse'" << std::endl;
		cleanUp();
		return false;
	}

    if (!al_init_primitives_addon()) {
    	std::cerr << "allegro error: could not init primitives" << std::endl;
        al_destroy_event_queue(event_queue);
		al_destroy_bitmap(screenBitmap);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return false;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);

	/*
	 * @author   dwlambiri
	 * @date     Oct 6, 2017
	 *  The next function call will set the bitmap as the target
	 *  	for all the allegro writes
	 */

	//al_set_target_bitmap(screenBitmap);
	//set background to black
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_set_window_title(display, title);
	al_flip_display();

	return true;
} // end-of-function initAllegro



/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @mname   GraphicsEngine::allegroEventLoop
 @details
 This event loop waits for a termination event (pressing the red X on the
 window)\n
 --------------------------------------------------------------------------
 */
bool GraphicsEngine::allegroEventLoop() {

	while (true) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			/*
			 * @author   dwlambiri
			 * @date     Oct 31, 2017
			 *  the timer event is used to check for user input
			 *  provided from the command line as well as quit
			 *  commands
			 *
			 */



		} else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {

			return false;
		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES
				|| ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {


		} else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

		}

	}
	return true;
} // end-of-function allegroEventLoop



/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 29, 2017
 @mname   GraphicsEngine::drawMaze
 @details
 Redraw the maze every time this method is called.
 The walls are drawn in green.
 The starting point is denoted by a yellow circle.
 The end point is denoted by a red circle.
 The path is denoted with a stream of triangles which point in the direction
 that the previous node moved in order to reach it. \n
 --------------------------------------------------------------------------
 */
void GraphicsEngine::drawMaze(apmatrix<char>& maze) {
	static float xratio = ((float)windowWidth)/ maze.numcols();
	static float yratio = ((float)windowHeight) / maze.numrows();

	static ALLEGRO_COLOR wallC = al_map_rgb(0, 0xff, 0);
	static ALLEGRO_COLOR pathC = al_map_rgb(0xff, 0xff, 0xff);
	static ALLEGRO_COLOR startC = al_map_rgb(0xff, 0xff, 0);
	static ALLEGRO_COLOR stopC = al_map_rgb(0xff, 0, 0);
	clearBitmap();
	for (int r = 0; r < maze.numrows(); r++ ) {
		for (int c = 0; c < maze.numcols(); c++ ) {
			switch (maze[r][c]) {
				case '#':
					al_draw_filled_rounded_rectangle(c * xratio, r*yratio, (c+1)* xratio, (r+1)* yratio, 20, 20, wallC);
					break;
				case '.':
					al_draw_filled_circle((c +0.5) * xratio, (r+0.5)*yratio, 5, startC);
					break;
				case 'v':
					//al_draw_filled_circle((c +0.5) * xratio, (r+0.5)*yratio, (xratio < yratio)?xratio/2:yratio/2, pathC);
					al_draw_filled_triangle((c+0.25) * xratio, r*yratio, (c+0.75)* xratio, (r)* yratio, (c+0.5)* xratio, (r+1)* yratio, pathC);
					break;
				case '^':
					//al_draw_filled_circle((c +0.5) * xratio, (r+0.5)*yratio, (xratio < yratio)?xratio/2:yratio/2, pathC);
					al_draw_filled_triangle((c+0.5) * xratio, r*yratio, (c+0.25)* xratio, (r+1)* yratio, (c+0.75)* xratio, (r+1)* yratio, pathC);
					break;
				case '<':
					//al_draw_filled_circle((c +0.5) * xratio, (r+0.5)*yratio, (xratio < yratio)?xratio/2:yratio/2, pathC);
					al_draw_filled_triangle(c * xratio, (r+0.5)*yratio, (c+1)* xratio, (r+0.25)* yratio, (c+1)* xratio, (r+0.75)* yratio, pathC);
					break;
				case '>':
					//al_draw_filled_circle((c +0.5) * xratio, (r+0.5)*yratio, (xratio < yratio)?xratio/2:yratio/2, pathC);
					al_draw_filled_triangle(c * xratio, (r+0.25)*yratio, (c)* xratio, (r+0.75)* yratio, (c+1)* xratio, (r+0.5)* yratio, pathC);
					break;
				case 'S':
					al_draw_filled_circle((c +0.5) * xratio, (r+0.5)*yratio, (xratio < yratio)?xratio/2:yratio/2, startC);
					break;
				case 'G':
					al_draw_filled_circle((c +0.5) * xratio, (r+0.5)*yratio, (xratio < yratio)?xratio/2:yratio/2, stopC);
					break;
				default:
					break;
			} //end-of-switch
		} //end-of-for
	} //end-of-for



	al_flip_display();
} // end-of-method GraphicsEngine::drawMaze



