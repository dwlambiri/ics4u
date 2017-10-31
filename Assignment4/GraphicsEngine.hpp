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
#include "FloatCalculator.hpp"



enum PixelColour {
	redPixel_c, greeenPixel_c, bluePixel_c, whitePixel_c, blackPixel_c
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


	bool initAllegro(const char* title, const int w, const int h);
	void moveBitmapToDisplay();

	bool allegroEventLoop(FloatCalculator& calc, std::string* otherCmdLine, bool* ready, bool* quit);


	bool drawPixel(int x, int y, PixelColour c);
	void displayStack(PixelColour c);
	void displayError(PixelColour c);
	void clearBitmap()  {
	    //this should clear the bitmap
	    al_clear_to_color(al_map_rgb(0,0,0));
	}

	void initCalculator();
	void drawCalculator();
	void cleanUp();

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

	/**
	  ---------------------------------------------------------------------------
	   @author     dwlambiri
	   @date       Oct 29, 2017
	   @classname  CalculatorButton
	   @brief
		 \n
	   @details
		\n
	  ---------------------------------------------------------------------------
	 */
	class CalculatorButton {

	public:
		//--------------------------------------------------
		// Public Methods (External Type Interface)
		//--------------------------------------------------
		/**
		  --------------------------------------------------------------------------
		   @author  dwlambiri
		   @date    Oct 29, 2017
		   @name    CalculatorButton::CalculatorButton
		   @param   -
		   @return  -
		   @details
			Default constructor of Class CalculatorButton \n
		  --------------------------------------------------------------------------
		 */
		CalculatorButton(int x, int y, int xw, int yw, const char* name, ALLEGRO_FONT* fc, PixelColour c);

		/**
		  --------------------------------------------------------------------------
		   @author  dwlambiri
		   @date    Oct 29, 2017
		   @name    CalculatorButton::~CalculatorButton
		   @param   -
		   @return  -
		   @details
			Default destructor of class CalculatorButton \n
		  --------------------------------------------------------------------------
		 */
		~CalculatorButton() {}

		/**
		  -------------------------------------------------------------------------
		   @author  dwlambiri
		   @date    Oct 29, 2017
		   @name    CalculatorButton::draw
		   @param
		   @return  void
		   @details
			  \n
		  -------------------------------------------------------------------------
		 */
		void draw();


		/**
		  -------------------------------------------------------------------------
		   @author  dwlambiri
		   @date    Oct 30, 2017
		   @name    CalculatorButton::getText
		   @param
		   @return  std::string&
		   @details
			  \n
		  -------------------------------------------------------------------------
		 */
		std::string& getText() {
			return text;
		}

		/**
		  -------------------------------------------------------------------------
		   @author  dwlambiri
		   @date    Oct 30, 2017
		   @name    CalculatorButton::checkMouseLocation
		   @param
		   @return  bool
		   @details
			  \n
		  -------------------------------------------------------------------------
		 */
		bool checkMouseLocation(int x, int y);

		/**
		  -------------------------------------------------------------------------
		   @author  dwlambiri
		   @date    Oct 30, 2017
		   @name    CalculatorButton::setFont
		   @param   ALLEGRO_FONT* f
		   @return  void
		   @details
			  \n
		  -------------------------------------------------------------------------
		 */
		void setFont(ALLEGRO_FONT* f);

		/**
		  -------------------------------------------------------------------------
		   @author  dwlambiri
		   @date    Oct 30, 2017
		   @name    CalculatorButton::buttonPressed()
		   @param
		   @return  void
		   @details
			  \n
		  -------------------------------------------------------------------------
		 */
		void buttonPressed() {
			pressed = true;
		}


		/**
		  -------------------------------------------------------------------------
		   @author  dwlambiri
		   @date    Oct 30, 2017
		   @name    CalculatorButton::buttonReleased()
		   @param
		   @return  void
		   @details
			  \n
		  -------------------------------------------------------------------------
		 */
		void buttonReleased() {
			pressed = false;
		}

		/**
		  -------------------------------------------------------------------------
		   @author  dwlambiri
		   @date    Oct 30, 2017
		   @name    CalculatorButton::isButtonPressed
		   @param
		   @return  bool
		   @details
			  \n
		  -------------------------------------------------------------------------
		 */
		bool isButtonPressed() const {
			return pressed;
		}

	private:
		//--------------------------------------------------
		// Data Members
		//--------------------------------------------------
		int xpos;
		int ypos;
		std::string text;
		int xlen;
		int ylen;
		bool pressed;
		ALLEGRO_FONT* f;
		ALLEGRO_COLOR c;


	private:
		//--------------------------------------------------
		// Private Methods
		//--------------------------------------------------

	}; //end-of-class CalculatorButton


private:
	//--------------------------------------------------
	// Data Members
	//--------------------------------------------------
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_BITMAP *screenBitmap;
	ALLEGRO_FONT *font;

	std::vector<CalculatorButton*> buttons;

	int windowWidth;
	int windowHeight;
	int fps;
	std::string errorString;
	std::vector<float> stack;

	static const int xButtonStart_c = 20;
	int yButtonStart;
	static const int yButtonSpace_c = 20;
	static const int xButtonSpace_c = 20;
	int xblen;
	int yblen;
	static const int fontSize_c = 30;


private:
	//--------------------------------------------------
	// Private Methods
	//--------------------------------------------------


}; //end-of-class GraphicsEngine






#endif /* ASSIGNMENT4_GRAPHICSENGINE_HPP_ */
