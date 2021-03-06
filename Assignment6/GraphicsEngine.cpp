/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   GraphicsEngine.cpp
 *	Course: ICS4U
 *	Date:   Jan 15 2018
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
	fps = 100000;

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
 @mname   GraphicsEngine::drawVector
 @details
 This method will redraw the sorting in allegro per frame. There are several
   colour constants declared in the method. We will be using light green
   dark green. Light blue and dark blue.
 Each value in the vector is represented by one of these rectangles drawn
   by this method. Each rectangle is composed of an inner filled rectangle
   and is surrounded by an empty rectangle which acts as a border and
   gives a nice aesthetic look. \n
 --------------------------------------------------------------------------
 */
void GraphicsEngine::drawVector(apvector<int>& data, int pos) {
	static float xratio = ((float)windowWidth) / data.length();
	static float yratio = ((float)windowHeight) / data.length();

	static ALLEGRO_COLOR wallC = al_map_rgb(0, 0xa0, 0);
	static ALLEGRO_COLOR wallB = al_map_rgb(0, 0xff, 0);
	static ALLEGRO_COLOR wallD = al_map_rgb(0, 0, 0xa0);
	static ALLEGRO_COLOR wallE = al_map_rgb(0, 0, 0xff);
//	static ALLEGRO_COLOR pathC = al_map_rgb(0xff, 0xff, 0xff);
//	static ALLEGRO_COLOR startC = al_map_rgb(0xff, 0xff, 0);
//	static ALLEGRO_COLOR stopC = al_map_rgb(0xff, 0, 0);
	clearBitmap();
	for (int r = 0; r < data.length(); r++ ) {
		if (r == pos) {
			al_draw_filled_rounded_rectangle(r * xratio, windowHeight - data[r]* yratio , (r+1)* xratio, windowHeight, 0.25*xratio, 0.25*xratio, wallD);
			if(xratio > 2) al_draw_rounded_rectangle(r * xratio, windowHeight - data[r]* yratio, (r+1)* xratio, windowHeight , 0.25*xratio, 0.25*xratio, wallE,(4<xratio/2)?4:(int)xratio/2);
		} else {
			al_draw_filled_rounded_rectangle(r * xratio, windowHeight - data[r]* yratio , (r+1)* xratio, windowHeight, 0.25*xratio, 0.25*xratio, wallC);
			if(xratio > 2) al_draw_rounded_rectangle(r * xratio, windowHeight - data[r]* yratio, (r+1)* xratio, windowHeight , 0.25*xratio, 0.25*xratio, wallB,(4<xratio/2)?4:(int)xratio/2);
		}//end-of-if
	} //end-of-for

	al_flip_display();
} // end-of-method GraphicsEngine::drawMaze



