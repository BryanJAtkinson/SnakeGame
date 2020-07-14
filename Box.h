	#ifndef BOX
	#define BOX

	#include <stdio.h>
	#include <stdlib.h>
	#include <GL/glut.h>
	#include <iostream>
	
	namespace GameBoxes
	{
		class Box
		{
			public:
				Box(); //Initializes black screen of size 600 by 400 with 20 x 20 block size.

				Box(int width, int height, int xSize, int ySize);
					//Initialized custom black screen size based on command line arguments.

				Box(const Box &square);

				void getSizeArray(int (&array)[4]) const;
					//Returns Screen Size Parameters

				void createBackGroundTexture();
					//Creates the black screen for drawing

			private:
				int windowWidth;
				int windowHeight;
				int blockXSize;
				int blockYSize;

		};
	} //GameBoxes



	#endif //BOX