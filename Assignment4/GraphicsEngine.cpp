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
 @mname   GraphicsEngine::CalculatorButton::CalculatorButton
 @details
 \n
 --------------------------------------------------------------------------
 */

GraphicsEngine::CalculatorButton::CalculatorButton(int x, int y, int xw, int yw,
		const char* name, ALLEGRO_FONT* fc, PixelColour pc) :
		xpos(x), ypos(y), text(name), xlen(xw), ylen(yw) , pressed(false), f(fc) {

	c = al_map_rgb(0xff, 0xff, 0xff);

	switch (pc) {
	case redPixel_c:
		c = al_map_rgb(0xff, 0, 0);
		break;
	case greenPixel_c:
		c = al_map_rgb(0, 0xff, 0);
		break;
	case bluePixel_c:
		c = al_map_rgb(0, 0, 0xff);
		break;
	case blackPixel_c:
		c = al_map_rgb(0, 0, 0);
		break;
	case whitePixel_c:
		c = al_map_rgb(0xff, 0xff, 0xff);
		break;
	default:
		;
	} //end-of-switch


} // end-of-method CalculatorButton::CalculatorButton

/**
 ---------------------------------------------------------------------------
 @author  dwlambiri
 @date    Oct 29, 2017
 @mname   GraphicsEngine::CalculatorButton::draw
 @details
 \n
 --------------------------------------------------------------------------
 */
void
GraphicsEngine::CalculatorButton::draw() {

	if(pressed == false) {
		al_draw_rounded_rectangle(xpos, ypos, xpos + xlen, ypos + ylen, 10, 10, c,
				2);

		al_draw_textf(f, c, xpos + xlen / 2, ypos + (ylen - fontSize_c) / 2,
				ALLEGRO_ALIGN_CENTER, "%s", text.c_str());
	}
	else {
		al_draw_filled_rounded_rectangle(xpos, ypos, xpos + xlen, ypos + ylen, 10, 10, c);

		al_draw_textf(f, al_map_rgb(0, 0, 0), xpos + xlen / 2, ypos + (ylen - fontSize_c) / 2,
				ALLEGRO_ALIGN_CENTER, "%s", text.c_str());
	}
} // end-of-method CalculatorButton::draw


/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 30, 2017
   @mname   GraphicsEngine::CalculatorButton::checkMouseLocation
   @details
	  \n
  --------------------------------------------------------------------------
 */
bool
GraphicsEngine::CalculatorButton::checkMouseLocation(int x, int y) {

	if(((x > xpos) && x < (xpos+xlen) )
			&& ((y > ypos) && y < (ypos+ylen) )) {
		return true;
	}
	else
		return false;

} // end-of-method GraphicsEngine::CalculatorButton::checkMouseLocation


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
GraphicsEngine::GraphicsEngine() :
		buttons(numButtonColumns_c*numButtonRows_c) {
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

	calcPixelColour = bluePixel_c;
}

/**
  --------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 31, 2017
   @name    GraphicsEngine::cleanup
   @param
   @return  void
   @details
	\n
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

	/*
	 * @author   dwlambiri
	 * @date     Oct 31, 2017
	 *  buttons start in the lower half of the window
	 */

	yButtonStart = windowHeight_c / 2;

	/*
	 * @author   dwlambiri
	 * @date     Oct 31, 2017
	 *  each button length depends on the number of button columns
	 */

	xblen = ((windowWidth_c - xButtonSpace_c) / numButtonColumns_c) - xButtonSpace_c;

	/*
	 * @author   dwlambiri
	 * @date     Oct 31, 2017
	 *  each button height depends on the number of button rows
	 */

	yblen = (yButtonStart / numButtonRows_c) - yButtonSpace_c;
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
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);

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

	initCalculator();
	drawCalculator();

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
bool GraphicsEngine::allegroEventLoop(FloatCalculator& calc, std::string* otherCmdLine, bool* ready, bool* quit) {

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

			if(quit && (*quit == true)) {
				return true;
			}
			if((ready == nullptr) || (*ready == false)) continue;
			if (calc.parse(*otherCmdLine) == false) {
				setErrorString(std::string("error: bad expression"));
			}
			else {
				setErrorString(inputNumber);
			}
			const int topNum_c = 11;
			std::vector<float> topofstack(topNum_c);
			calc.getTopOfStack(topofstack, topNum_c);
			setVector(topofstack);
			*ready = false;
		} else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			//need to exit from main
			//std::cerr << "Don't touch that dude!!" << std::endl;
			//continue;
			return false;
		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES
				|| ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

//			char msg[200];
//			sprintf(msg,"x=%d  y=%d", ev.mouse.x, ev.mouse.y);
//			al_draw_textf(font, al_map_rgb(0xff, 0xff, 0xff), 2 * xButtonSpace_c, yButtonSpace_c + fontSize_c,
//							ALLEGRO_ALIGN_LEFT, "%s", msg);
//			std::cerr << msg << std::endl;

		} else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			/*
			 * @author   dwlambiri
			 * @date     Oct 31, 2017
			 *  the mouse button up event is when things happen
			 */

			for (int i = 0; i < buttons.size(); i++ ) {
				if(buttons[i] && (buttons[i]->isButtonPressed() == true )) {
					buttons[i]->buttonReleased();
					std::string& cmdLine = buttons[i]->getText();
					if(((cmdLine[0] >= '0') && (cmdLine[0]<='9')) || (cmdLine[0]=='.')) {
						inputNumber += cmdLine;
						setErrorString(inputNumber);
					}
					else if(cmdLine.compare("del") == 0) {
						inputNumber = inputNumber.substr(0, inputNumber.size()-1);
						setErrorString(inputNumber);
					}
					else{
						std::string cmd;
						if(cmdLine.compare("enter") == 0) {
							cmd = inputNumber;
						}
						else {
							cmd = inputNumber + " " + cmdLine;
						}
						if (calc.parse(cmd) == false) {
							setErrorString(std::string("error: bad expression"));
						}
						else {
							setErrorString(std::string(""));
						}
						inputNumber = "";
					}
					const int topNum_c = 11;
					std::vector<float> topofstack(topNum_c);
					calc.getTopOfStack(topofstack, topNum_c);
					setVector(topofstack);
				}
			} //end-of-for
			//std::cerr << "Mouse up event" << std::endl;
			//break;
		} else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			/*
			 * @author   dwlambiri
			 * @date     Oct 31, 2017
			 *  check which button we pressed, if any
			 *  each button can check if the mouse if over
			 *  it using the method
			 *  GraphicsEngine::CalculatorButtton::checkMouseLocation
			 */

			for (int i = 0; i < buttons.size(); i++ ) {
				if(buttons[i] && (buttons[i]->checkMouseLocation(ev.mouse.x, ev.mouse.y) == true )) {
					buttons[i]->buttonPressed();
					break;
				}
			} //end-of-for
			//std::cerr << "Mouse down event" << std::endl;
		}

		/*
		 * @author   dwlambiri
		 * @date     Oct 31, 2017
		 *  after events are processed re-draw the calculator
		 */

		drawCalculator();

	}
	return true;
} // end-of-function allegroEventLoop


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
	case greenPixel_c:
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
				if((int)(1000000*(stack[i] - (long)stack[i])))
					sprintf(msg, "%.20f    [Top of Stack]", stack[i]);
				else
					sprintf(msg, "%ld    [Top of Stack]", (long) stack[i]);
			} else {
				if((int)(1000000*(stack[i] - (long)stack[i])))
					sprintf(msg, "%.20f", stack[i]);
				else
					sprintf(msg, "%ld", (long) stack[i]);
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
	case greenPixel_c:
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
			cb->draw();
		}
	} //end-of-for
	displayStack(calcPixelColour);
	displayError(calcPixelColour);
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
	 */

	std::vector<std::string> btext{"1", "2", "3", "4",
								   "5", "6", "7", "8",
								   "9", "0", ".", "enter",
								   "+","-","^","del",
								   "*","/","exp","log",
								   "cos", "sin", "rand", "pop",
								   "swap","series","sum","prod",
								   "sqrt", "e", "pi", "clear"
	};

	/*
	 * @author   dwlambiri
	 * @date     Oct 31, 2017
	 *  buttons are drawn in a 2 for statements, one for columns
	 *  and one for each row in a column
	 */

	for (int i = 0; i < numButtonColumns_c; i++ ) {
		for (int j = 0; j < numButtonRows_c; j++ ) {
			buttons.push_back(
						new CalculatorButton(xButtonStart_c + i * (xblen + xButtonSpace_c),
								yButtonStart + j * (yblen + yButtonSpace_c), xblen, yblen,
								btext[i*numButtonRows_c+j].c_str(),font, calcPixelColour));
		} //end-of-for
	} //end-of-for

} // end-of-method GraphicsEngine::initCalculator

