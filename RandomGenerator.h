	#ifndef RNG_H
	#define RNG_H

	#include <time.h>
	#include "Box.h"

	namespace Random
	{
		class RandomGenerator : public GameBoxes::Box
		{
			public:
				RandomGenerator(Box square);
				
				int* Return_Rand(int *arr);
			
			private:
				int x_Coordinate, y_Coordinate;
		};	
	} //Random

	#endif //RNG_H