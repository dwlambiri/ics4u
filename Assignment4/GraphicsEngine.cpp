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
 @author  dwlambiri
 @date    Oct 29, 2017
 @mname   CalculatorButton::CalculatorButton
 @details
 \n
 --------------------------------------------------------------------------
 */

GraphicsEngine::CalculatorButton::CalculatorButton(int x, int y, int xw, int yw,
		const char* name) :
		xpos(x), ypos(y), text(name), xlen(xw), ylen(yw) {

} // end-of-method CalculatorButton::CalculatorButton

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 29, 2017
 @mname   CalculatorButton::draw
 @details
 \n
 --------------------------------------------------------------------------
 */
void GraphicsEngine::CalculatorButton::draw(ALLEGRO_COLOR c, ALLEGRO_FONT* f) {

	al_draw_rounded_rectangle(xpos, ypos, xpos + xlen, ypos + ylen, 10, 10, c,
			2);

	al_draw_textf(f, c, xpos + xlen / 2, ypos + (ylen - fontSize_c) / 2,
			ALLEGRO_ALIGN_CENTER, "%s", text.c_str());
} // end-of-method CalculatorButton::draw

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

GraphicsEngine::GraphicsEngine() :
		buttons(50) {
	display = nullptr;
	event_queue = nullptr;
	timer = nullptr;
	screenBitmap = nullptr;
	font = nullptr;
	windowWidth = 0;
	windowHeight = 0;
	fps = 60;
	errorString = "";
	yButtonStart = 0;
	xblen = 0;
	yblen = 0;
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
bool GraphicsEngine::initAllegro(const char* title, const int windowWidth_c,
		const int windowHeight_c) {

	yButtonStart = windowHeight_c / 2;
	xblen = ((windowWidth_c - xButtonSpace_c) / 4) - xButtonSpace_c;
	yblen = (yButtonStart / 4) - yButtonSpace_c;
	//initialize display
	al_init();
	display = al_create_display(windowWidth_c, windowHeight_c);
	this->windowWidth = windowWidth_c;
	this->windowHeight = windowHeight_c;

	// Always check if your allegro routines worked successfully.
	if (!display) {
//		al_show_native_message_box(display, "Error", "Error",
//				"Failed to initialize display!",
//				nullptr, ALLEGRO_MESSAGEBOX_ERROR);

		std::cerr << "allegro error: failed to initialize display!"
				<< std::endl;
		return false;
	}

	timer = al_create_timer(1.0 / fps);

//	if (!al_install_keyboard()) {
//		std::cerr << "allegro error: failed to initialize the keyboard!"
//				<< std::endl;
//		al_destroy_display(display);
//		return false;
//	}

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

	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon(); // initialize the ttf (True Type Font) addon

	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "./");

	al_set_path_filename(path, "font.ttf");

	font = al_load_ttf_font(al_path_cstr(path, '/'), fontSize_c, 0);
	al_destroy_path(path);

	if (!font) {
		std::cerr << "allegro error:  could not load 'font.ttf'" << std::endl;
		al_destroy_event_queue(event_queue);
		al_destroy_bitmap(screenBitmap);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return false;
	}

	if(!al_install_mouse()) {
		std::cerr << "allegro error:  could not init mouse'" << std::endl;
		cleanUp();
		return false;
	}


	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
//	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	/*
	 * @author   dwlambiri
	 * @date     Oct 6, 2017
	 *  The next function call will set the bitmap as the target
	 *  	for all the allegro writes
	 */

	al_set_target_bitmap(screenBitmap);
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
			//need to exit from main
			return false;
			std::cerr << "Don't touch that dude!!" << std::endl;
		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES
				|| ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

			char msg[200];
			sprintf(msg,"x=%d  y=%d", ev.mouse.x, ev.mouse.y);
//			al_draw_textf(font, al_map_rgb(0xff, 0xff, 0xff), 2 * xButtonSpace_c, yButtonSpace_c + fontSize_c,
//							ALLEGRO_ALIGN_LEFT, "%s", msg);
			drawCalculator();
			std::cerr << msg << std::endl;

		} else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			std::cerr << "Mouse up event" << std::endl;
			drawCalculator();
			//break;
		} else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			//break;
			drawCalculator();
			std::cerr << "Mouse down event" << std::endl;
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
bool GraphicsEngine::drawPixel(int x, int y, PixelColour c) {
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
void GraphicsEngine::displayStack(PixelColour c) {

	ALLEGRO_COLOR fc = al_map_rgb(0xff, 0xff, 0xff);

	switch (c) {
	case redPixel_c:
		fc = al_map_rgb(0xff, 0, 0);
		break;
	case greeenPixel_c:
		fc = al_map_rgb(0, 0xff, 0);
		break;
	case bluePixel_c:
		fc = al_map_rgb(0, 0, 0xff);
		break;
	case blackPixel_c:
		fc = al_map_rgb(0, 0, 0);
		break;
	case whitePixel_c:
		fc = al_map_rgb(0xff, 0xff, 0xff);
		break;
	default:
		;
	} //end-of-switch

	al_draw_rounded_rectangle(xButtonSpace_c, yButtonSpace_c,
			windowWidth - xButtonSpace_c,
			windowHeight / 2 - fontSize_c - yButtonSpace_c, 20, 20, fc, 10);
	if (stack.size() == 0) {
		al_draw_textf(font, fc, 2 * xButtonSpace_c, yButtonSpace_c + fontSize_c,
				ALLEGRO_ALIGN_LEFT, "%s", "stack is empty");
	} else {
		char msg[200];
		sprintf(msg, "stack contains %.0f elements", stack[0]);
		al_draw_textf(font, fc, 2 * xButtonSpace_c,
				(yButtonSpace_c + fontSize_c), ALLEGRO_ALIGN_LEFT, "%s", msg);
		int i = 1;
		for (;
				(i < stack.size())
						&& (i
								< (windowHeight / 3
										/ (yButtonSpace_c + fontSize_c)));
				i++) {
			if (i == 1) {
				sprintf(msg, "%.3f    [Top of Stack]", stack[i]);
			} else {
				sprintf(msg, "%.3f", stack[i]);
			}
			al_draw_textf(font, fc, 2 * xButtonSpace_c,
					(i + 1) * (yButtonSpace_c + fontSize_c), ALLEGRO_ALIGN_LEFT,
					"%s", msg);
		} //end-of-for
		if (stack[0] > (windowHeight / 3 / (yButtonSpace_c + fontSize_c))) {
			sprintf(msg, ".......");
		} else {
			sprintf(msg, "<end of stack>");
		}
		al_draw_textf(font, fc, 2 * xButtonSpace_c,
				(i + 1) * (yButtonSpace_c + fontSize_c), ALLEGRO_ALIGN_LEFT,
				"%s", msg);

	}
} //end-of-method

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 29, 2017
 @mname   GraphicsEngine::displayError
 @details
 \n
 --------------------------------------------------------------------------
 */
void GraphicsEngine::displayError(PixelColour c) {

	ALLEGRO_COLOR fc = al_map_rgb(0xff, 0xff, 0xff);

	switch (c) {
	case redPixel_c:
		fc = al_map_rgb(0xff, 0, 0);
		break;
	case greeenPixel_c:
		fc = al_map_rgb(0, 0xff, 0);
		break;
	case bluePixel_c:
		fc = al_map_rgb(0, 0, 0xff);
		break;
	case blackPixel_c:
		fc = al_map_rgb(0, 0, 0);
		break;
	case whitePixel_c:
		fc = al_map_rgb(0xff, 0xff, 0xff);
		break;
	default:
		;
	} //end-of-switch

	al_draw_textf(font, fc, xButtonSpace_c, windowHeight / 2 - 1.5 * fontSize_c,
			ALLEGRO_ALIGN_LEFT, "%s", errorString.c_str());

} // end-of-method GraphicsEngine::displayError

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 29, 2017
 @mname   GraphicsEngine::drawCalculator
 @details
 Draw fresh calculator\n
 --------------------------------------------------------------------------
 */
void GraphicsEngine::drawCalculator() {

	clearBitmap();
	for (int i = 0; i < buttons.size(); i++) {
		CalculatorButton* cb = buttons[i];
		if (cb) {
			cb->draw(al_map_rgb(0xff, 0xff, 0xff), font);
		}
	} //end-of-for
	displayStack(whitePixel_c);
	displayError(whitePixel_c);
	moveBitmapToDisplay();
} // end-of-method GraphicsEngine::drawCalculator

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 29, 2017
 @mname   GraphicsEngine::initCalculator
 @details
 Add buttons to vector\n
 --------------------------------------------------------------------------
 */
void GraphicsEngine::initCalculator() {

	/*
	 * @author   dwlambiri
	 * @date     Oct 29, 2017
	 *  column 1
	 */

	buttons.push_back(
			new CalculatorButton(xButtonStart_c, yButtonStart, xblen, yblen,
					"/"));
	buttons.push_back(
			new CalculatorButton(xButtonStart_c,
					yButtonStart + yblen + yButtonSpace_c, xblen, yblen, "*"));
	buttons.push_back(
			new CalculatorButton(xButtonStart_c,
					yButtonStart + 2 * (yblen + yButtonSpace_c), xblen, yblen,
					"-"));
	buttons.push_back(
			new CalculatorButton(xButtonStart_c,
					yButtonStart + 3 * (yblen + yButtonSpace_c), xblen, yblen,
					"+"));

	/*
	 * @author   dwlambiri
	 * @date     Oct 29, 2017
	 *  column 2
	 */

	buttons.push_back(
			new CalculatorButton(xButtonStart_c + xblen + xButtonSpace_c,
					yButtonStart, xblen, yblen, "^"));
	buttons.push_back(
			new CalculatorButton(xButtonStart_c + xblen + xButtonSpace_c,
					yButtonStart + yblen + yButtonSpace_c, xblen, yblen,
					"sqrt"));
	buttons.push_back(
			new CalculatorButton(xButtonStart_c + xblen + xButtonSpace_c,
					yButtonStart + 2 * (yblen + yButtonSpace_c), xblen, yblen,
					"exp"));
	buttons.push_back(
			new CalculatorButton(xButtonStart_c + xblen + xButtonSpace_c,
					yButtonStart + 3 * (yblen + yButtonSpace_c), xblen, yblen,
					"log"));

	/*
	 * @author   dwlambiri
	 * @date     Oct 29, 2017
	 *  column 3
	 */

	buttons.push_back(
			new CalculatorButton(xButtonStart_c + 2 * (xblen + xButtonSpace_c),
					yButtonStart, xblen, yblen, "cos"));
	buttons.push_back(
			new CalculatorButton(xButtonStart_c + 2 * (xblen + xButtonSpace_c),
					yButtonStart + yblen + yButtonSpace_c, xblen, yblen,
					"sin"));
	buttons.push_back(
			new CalculatorButton(xButtonStart_c + 2 * (xblen + xButtonSpace_c),
					yButtonStart + 2 * (yblen + yButtonSpace_c), xblen, yblen,
					"pop"));
	buttons.push_back(
			new CalculatorButton(xButtonStart_c + 2 * (xblen + xButtonSpace_c),
					yButtonStart + 3 * (yblen + yButtonSpace_c), xblen, yblen,
					"clear"));

	/*
	 * @author   dwlambiri
	 * @date     Oct 29, 2017
	 *  column 4
	 */

	buttons.push_back(
			new CalculatorButton(xButtonStart_c + 3 * (xblen + xButtonSpace_c),
					yButtonStart, xblen, yblen, "series"));
	buttons.push_back(
			new CalculatorButton(xButtonStart_c + 3 * (xblen + xButtonSpace_c),
					yButtonStart + yblen + yButtonSpace_c, xblen, yblen,
					"swap"));
	buttons.push_back(
			new CalculatorButton(xButtonStart_c + 3 * (xblen + xButtonSpace_c),
					yButtonStart + 2 * (yblen + yButtonSpace_c), xblen, yblen,
					"sum"));
	buttons.push_back(
			new CalculatorButton(xButtonStart_c + 3 * (xblen + xButtonSpace_c),
					yButtonStart + 3 * (yblen + yButtonSpace_c), xblen, yblen,
					"prod"));

} // end-of-method GraphicsEngine::initCalculator

