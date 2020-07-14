	#ifndef GRIDPIECE_H
	#define GRIDPIECE_H
		//The preprocessor lines above needed to be changed from Gridpiece to work

	#include "Box.h"
	namespace GameBoxes
	{
	
		class GridPiece : public GameBoxes::Box
		{
		public:
			GridPiece();
				// Dummy Constructor. If colorDesignation = -2, then setPosition gives that pointer
				// a null pointer
			
			GridPiece(int xPositionNumb, int yPositionNumb, int color, Box square);
				// Class Constructor. Sets Square Sizes Based Off Position and BlockSize

			void setSquareType(int designation);
				// uses an integer to set colorDesignation below
				// -1 is red, 1 is black, and 0 is white
			
			int getColorDesignation();
				// Returns the color as an integer

		private:
				
			int colorDesignation;
			
			int xIndexNumb;
			int yIndexNumb;
				// These two are going to be used to find boundaries of the grid.
		
		};
		
	} // GameBoxes


	#endif //GridPiece_H