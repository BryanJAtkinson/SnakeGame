	#include "RandomGenerator.h"

	// See Version 1 - 4 for info on using templates

	namespace Random
	{
		RandomGenerator::RandomGenerator(Box square) : Box(square)
		{
			int gridDimensions[4];
			getSizeArray(gridDimensions);
			
			x_Coordinate = rand() % (2 * gridDimensions[0] / gridDimensions[2]);
			
			y_Coordinate = rand() % (2 * gridDimensions[1] / gridDimensions[3]);
		}
		//Generates two random numbers, one less than the width of the window in gridpieces and ones less than the hieght of the window in gridpieces
		
		int* RandomGenerator::Return_Rand(int *arr)
		{
			arr[0] = x_Coordinate;
			arr[1] = y_Coordinate;
			
			return arr;
		}
		//returns the random numbers by passing an array by reference
		
	} // Random