/*
 * GraphicsEngine.hpp
 *
 *  Created on: Oct 29, 2017
 *      Author: dwlambiri
 */

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
#include "Maze.hpp"



enum PixelColour {
	redPixel_c, greenPixel_c, bluePixel_c, whitePixel_c, blackPixel_c
};
//end-of-enum PixelColour

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
	GraphicsEngine(Maze& m) ;

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


	bool initAllegro(const char* title, const int w, const int h);

	void cleanUp();

	bool allegroEventLoop();


private:
	//--------------------------------------------------
	// Data Members
	//--------------------------------------------------
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_BITMAP *screenBitmap;
	ALLEGRO_FONT *font;
	PixelColour  calcPixelColour;

	int windowWidth;
	int windowHeight;
	int fps;
	std::string errorString;
	std::vector<float> stack;
	std::string inputNumber;

	static const int xButtonStart_c = 20;
	int yButtonStart;
	static const int yButtonSpace_c = 20;
	static const int xButtonSpace_c = 20;
	int xblen;
	int yblen;
	static const int fontSize_c = 30;
	static const int numButtonColumns_c = 8;
	static const int numButtonRows_c = 4;
	Maze& maze;


private:
	//--------------------------------------------------
	// Private Methods
	//--------------------------------------------------
	void moveBitmapToDisplay();

	void displayError(PixelColour c);
	void clearBitmap()  {
	    //this should clear the bitmap
	    al_clear_to_color(al_map_rgb(0,0,0));
	}
	void initMaze();
	void drawMaze();


	/**
	  -------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Oct 29, 2017
	   @name    GraphicsEngine::setErrorString
	   @param   std::string& str
	   @return  void
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	void setErrorString(std::string str) {
		errorString =  str;
	}

	/**
	  -------------------------------------------------------------------------
	   @author  dwlambiri
	   @date    Oct 29, 2017
	   @name    GraphicsEngine::setVector
	   @param   std::vector<float>& v
	   @return  void
	   @details
		  \n
	  -------------------------------------------------------------------------
	 */
	void setVector(std::vector<float>& v) {
		stack.clear();
		stack = v;
	}


}; //end-of-class GraphicsEngine






#endif /* ASSIGNMENT4_GRAPHICSENGINE_HPP_ */
