/*
 * GraphicsEngine.cpp
 *
 *  Created on: Oct 29, 2017
 *      Author: dwlambiri
 */

//includes
#include <iostream>
#include <fstream>
#include <time.h>
#include "GraphicsEngine.hpp"

/**
 ---------------------------------------------------------------------------
 @author     dwlambiri
 @date       Sep 30, 2017
 @name       MapPixelColour
 @brief

 ---------------------------------------------------------------------------
 */


//constants that determine the initial values of the variables
// initialize the allegro display

GraphicsEngine::GraphicsEngine() {
	display = nullptr;
	event_queue = nullptr;
	timer = nullptr;
	screenBitmap = nullptr;
	font = nullptr;
	windowWidth = 0;
	windowHeight = 0;
	fps = 60;
}

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
bool GraphicsEngine::initAllegro(const char* title, const int windowWidth_c, const int windowHeight_c) {

	//initialize display
	al_init();
	display = al_create_display(windowWidth_c, windowHeight_c);
	this->windowWidth = windowWidth_c;
	this->windowHeight = windowHeight_c;

	timer = al_create_timer(1.0 / fps);

	if (!al_install_keyboard()) {
		std::cerr << "failed to initialize the keyboard!" << std::endl;
		return false;
	}

	if (!timer) {
		std::cerr << "failed to create timer!" << std::endl;
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

	screenBitmap = al_create_bitmap(windowWidth_c, windowHeight_c);

	if (!screenBitmap) {
		std::cerr << "failed to create bouncer bitmap!" << std::endl;
		al_destroy_display(display);
		al_destroy_timer(timer);
		return false;
	}
	event_queue = al_create_event_queue();
	if (!event_queue) {
		std::cerr << "failed to create event_queue!" << std::endl;
		al_destroy_bitmap(screenBitmap);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return false;
	}

	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon(); // initialize the ttf (True Type Font) addon

	font = al_load_ttf_font("font.ttf", 30, 0);

	if (!font) {
		std::cerr << "Could not load 'font.ttf'" << std::endl;
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
	al_set_window_title(display, title);
	return true;
} // end-of-function initAllegro

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @mname   GraphicsEngine::moveBitmapToDisplay
 @details
   Allegro has a feature that allows all commands to be directed to a bitmap
   I utilized this property by creating a bitmap the same size as the screen
   	   and filling this bitmap.
   Every time I want to move the contents of the bitmap to the display I change
   	   the target of the write to the display itself, copy the bitmap to the display
   	   buffer, flip the display and then set the write target back to the bitmap.
 --------------------------------------------------------------------------
 */
void GraphicsEngine::moveBitmapToDisplay() {

	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(screenBitmap, 0, 0, 0);
	al_flip_display();
	al_set_target_bitmap(screenBitmap);

} // end-of-function moveBitmapToDisplay


/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @mname   GraphicsEngine::allegroEventLoop
 @details
 \n
 --------------------------------------------------------------------------
 */
bool GraphicsEngine::allegroEventLoop() {

	while (true) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			continue;
		} else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			cleanUp();
			return false;
		} else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
							return true;
		}

	}
	return true;
} // end-of-function allegroEventLoop

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 6, 2017
 @mname   GraphicsEngine::allegroExitLoop
 @details
 \n
 --------------------------------------------------------------------------
 */
void GraphicsEngine::allegroExitLoop() {

	while (true) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			cleanUp();
			return;
		}
	}
} // end-of-function allegroExitLoop



/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Sep 30, 2017
 @mname   GraphicsEngine::DrawPixel
 @details
 \n
 --------------------------------------------------------------------------
 */
bool GraphicsEngine::drawPixel(int x, int y, MapPixelColour c) {
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
 @name    GraphicsEngine::displayMessage
 @param   enclosing_method_arguments
 @return  return_type
 @details
 \n
 -------------------------------------------------------------------------
 */
void GraphicsEngine::displayMessage(const char* msg) {

	al_draw_textf(font, al_map_rgb(255, 255, 255), 275, 100,
			ALLEGRO_ALIGN_CENTRE, "%s", msg);
}



