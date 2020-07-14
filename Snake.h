	#ifndef SNAKE_H
	#define SNAKE_H

	#include "GridPiece.h"
	#include <string>
	#include <vector>
	#include <memory>
	#include "RandomGenerator.h"

	namespace GameBoxes
	{
		class Snake
		{
			public:
				//Spawns the snake randomly
				Snake(Box square, int* cArgs);
				
				//Moves the snake
				bool moveSnake(Box square, char direction, int* cArgs);
				
				//Random spawns a tail or random adds to the tail
				void addTail(int* coordinates, int* arr, Box square, int* cArgs);
			
			private:
				//used for random coordinates
				int* coordinates;
				
				//used for returning values to coordinates
				int arr[2];
				
				//Used to hold the gridpieces which are colored blocks
				typedef std::shared_ptr<GameBoxes::GridPiece> GridSharedPointer;
				typedef std::vector< GridSharedPointer > GridPieceVector;
				std::vector < GridPieceVector > twoDGridVector;
				
				std::vector < std::vector < int > > snakePosition;
				
				std::vector < std::vector < int > > appleSafeSpot;
				
				//Removes an entry from the appleSafeSpot vector
				void safe(int x_coordinate, int y_coordinate);
				
				//Adds an entry to the appleSafeSpot vector
				void addSafe(int x_coordinate, int y_coordinate);
				
				//Moves the snake in the direction presented
				bool move(int xHeadC, int yHeadC, int xTailC, int yTailC, int cArgsOne, int cArgsTwo, int xHeadCAdd, int yHeadCAdd, Box &square, int headCoordinate, int headCoordinateAdd, int* cArgs);
		};
	}


	#endif //SNAKE_H