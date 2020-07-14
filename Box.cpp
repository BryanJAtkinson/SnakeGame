	#include "Box.h"

	// See Version 1 - 4 for info on using templates

	namespace GameBoxes
	{
		Box::Box() : windowWidth(600), windowHeight(400), blockXSize(20), blockYSize(20)
		{
		}
			//Initializes black screen of size 600 by 400 with 20 x 20 block size.
		
		Box::Box(int width, int height, int xSize, int ySize) : windowWidth(width), windowHeight(height),
				blockXSize(xSize), blockYSize(ySize)
		{
		}
			//Initialized custom black screen size based on command line arguments.
		
		Box::Box(const Box &square)
		{
			int getDimensions[4];
			square.getSizeArray(getDimensions);
			windowWidth  = getDimensions[0];
			windowHeight = getDimensions[1];
			blockXSize   = getDimensions[2];
			blockYSize   = getDimensions[3];
		}
			// Copy Constructor

		void Box::getSizeArray(int (&array)[4]) const
		{
			array[0] = windowWidth;
			array[1] = windowHeight;
			array[2] = blockXSize;
			array[3] = blockYSize;
			
		}
			//Returns Screen Size Parameters
		
		void Box::createBackGroundTexture()
		{
			glutInitDisplayMode(GLUT_SINGLE);
    		glutInitWindowSize(windowWidth, windowHeight);
    		glutInitWindowPosition(100, 100);
    		glutCreateWindow("Hello world!");
		}
			//Creates the black screen for drawing
		
	} // GameBoxes