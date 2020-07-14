	#include "GridPiece.h"

	// See Version 1 - 4 for info on using templates

	namespace GameBoxes
	{
		GridPiece::GridPiece() : colorDesignation(-2), xIndexNumb(-1), yIndexNumb(-2)
		{
		}
		
		// Inherits from Box, creates a quadrilateral
		GridPiece::GridPiece(int xPositionNumb, int yPositionNumb, int color, Box square) : Box(square),
			colorDesignation(color), xIndexNumb(xPositionNumb), yIndexNumb(yPositionNumb)
		{			
			int gridDimensions[4];
			getSizeArray(gridDimensions);
				//called from parent Box
			
			glBegin(GL_QUADS);
				//Used to create a rectangle
				
			setSquareType(colorDesignation);

			glVertex2f((gridDimensions[0] - (xIndexNumb + 1) * gridDimensions[2]) / (float)gridDimensions[0],
				(gridDimensions[1] - (yIndexNumb + 1) * gridDimensions[3]) / (float)gridDimensions[1]);
			glVertex2f((gridDimensions[0] - xIndexNumb * gridDimensions[2]) / (float)gridDimensions[0],
				(gridDimensions[1] - (yIndexNumb + 1) * gridDimensions[3]) / (float)gridDimensions[1]);
			glVertex2f((gridDimensions[0] - xIndexNumb * gridDimensions[2]) / (float)gridDimensions[0],
				(gridDimensions[1] - yIndexNumb * gridDimensions[3]) / (float)gridDimensions[1]);
			glVertex2f((gridDimensions[0] - (xIndexNumb + 1) * gridDimensions[2]) / (float)gridDimensions[0],
				(gridDimensions[1] - yIndexNumb * gridDimensions[3]) / (float)gridDimensions[1]);
			// Vertices start at the upper left hand corner and go clockwise
				
			glEnd();
    		glFlush();
		}
				 
		int GridPiece::getColorDesignation()
		{
			return colorDesignation;
		}
		// Returns the color as an integer
				 
		void GridPiece::setSquareType(int designation)
		{
			colorDesignation = designation;
			if (colorDesignation == 0)
			{
				glColor3f(1.0,1.0,1.0);
				//white
			}
			else if (colorDesignation == 1)
			{
				glColor3f(0.0,0.0,0.0);
				//Black
			}
			else if (colorDesignation == -1)
			{
				glColor3f(1.0,0.0,0.0);
				//Red
			}
			// uses an integer to set colorDesignation above
				// -1 is red, 1 is black, and 0 is white
		}

	} // GameBoxes