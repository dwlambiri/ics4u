/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   GraphicsEngine.hpp
 *	Course: ICS4U
 *	Date:   Nov 24, 2017
 *
 *	Purpose: Declaration of the GraphicsEnginge class
 *
 *	Usage:
 *
 *	Revision History:
 *
 *	Known Issues: NONE
 *
 *****************************************************************************/



#ifndef ASSIGNMENT4_GRAPHICSENGINE_HPP_
#define ASSIGNMENT4_GRAPHICSENGINE_HPP_
//includes
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include "apmatrix.h"


/**
  ---------------------------------------------------------------------------
   @author     dwlambiri
   @date       Oct 7, 2017
   @classname  GraphicsEngine
   @brief
	 \n
   @details
	\n
  ---------------------------------------------------------------------------
 */
class GraphicsEngine {

public:
	//--------------------------------------------------
	// Public Methods (External Type Interface)
	//--------------------------------------------------
	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Oct 7, 2017
	   @name    GraphicsEngine::GraphicsEngine
	   @param   -
	   @return  -
	   @details
		Default constructor of Class GraphicsEngine \n
	  --------------------------------------------------------------------------
	 */
	GraphicsEngine() ;

	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Oct 7, 2017
	   @name    GraphicsEngine::~GraphicsEngine
	   @param   -
	   @return  -
	   @details
		Default destructor of class GraphicsEngine \n
	  --------------------------------------------------------------------------
	 */
	~GraphicsEngine(){}

	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 25, 2017
	   @name    GraphicsEngine::initAllegro
	   @param   -
	   @return  -
	   @details
		Allogro initialization is placed here because the constructor
		does not return a value. Thus it is difficult to figure out
		if the initialization was done correctly or not \n
	  --------------------------------------------------------------------------
	 */
	bool initAllegro(const char* title, const int w, const int h);

	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 25, 2017
	   @name    GraphicsEngine::cleanUp
	   @param   -
	   @return  -
	   @details
		Allogro clean up \n
	  --------------------------------------------------------------------------
	 */
	void cleanUp();

	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 25, 2017
	   @name    GraphicsEngine::allegroEventLoop
	   @param   -
	   @return  -
	   @details
		Allogro event loop \n
	  --------------------------------------------------------------------------
	 */
	bool allegroEventLoop();


	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 25, 2017
	   @name    GraphicsEngine::pauseOnDisplayFrame
	   @param   -
	   @return  -
	   @details
		Pause the computation for 1/fps. This allows for animation \n
	  --------------------------------------------------------------------------
	 */
	void pauseOnDisplayFrame(){
		al_rest(1.0/fps);
	}

	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 25, 2017
	   @name    GraphicsEngine::errorBox
	   @param   -
	   @return  -
	   @details
		 Display a user error message \n
	  --------------------------------------------------------------------------
	 */
	void errorBox(std::string& usrmsg) {
		al_show_native_message_box(display, "Error", "Error", usrmsg.c_str(),
		               nullptr, ALLEGRO_MESSAGEBOX_ERROR);

	}

	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 25, 2017
	   @name    GraphicsEngine::errorBox
	   @param   -
	   @return  -
	   @details
		 Display a notification for the user \n
	  --------------------------------------------------------------------------
	 */
	void okBox(std::string& usrmsg) {
		al_show_native_message_box(display, "Success", "Success", usrmsg.c_str(),
		               nullptr, ALLEGRO_MESSAGEBOX_WARN);

	}


	/**
	  --------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Nov 25, 2017
	   @name    GraphicsEngine::drawMaze
	   @param   -
	   @return  -
	   @details
		 Draws an allegro version of the maze provided as a parameter\n
	  --------------------------------------------------------------------------
	 */
	void drawMaze(apmatrix<char>& m);
private:
	//--------------------------------------------------
	// Data Members
	//--------------------------------------------------
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_BITMAP *screenBitmap;
	ALLEGRO_FONT *font;

	int windowWidth;
	int windowHeight;
	int fps;
	static const int fontSize_c = 30;



private:
	//--------------------------------------------------
	// Private Methods
	//--------------------------------------------------

	void clearBitmap()  {
		//this should clear the bitmap
		al_clear_to_color(al_map_rgb(0,0,0));
	}


}; //end-of-class GraphicsEngine






#endif /* ASSIGNMENT4_GRAPHICSENGINE_HPP_ */
