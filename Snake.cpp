	#include "Snake.h"

	namespace GameBoxes
	{
		Snake::Snake(Box square, int* cArgs)
		{
			for (int x_index = 0; x_index < 2 * cArgs[0] / cArgs[2]; x_index++) // Number of blocks in row
			{
				GridPieceVector rowOfGridPiece;
					// I CAN NOT PREALLOCATE SIZE. SEG FAULT
				twoDGridVector.emplace_back(rowOfGridPiece);
					// Emplace back prevents issues with SharedPointers
				for (int y_index = 0; y_index < 2 * cArgs[1] / cArgs[3]; y_index++) // number of blocks in column
				{
					twoDGridVector[x_index].emplace_back(GridSharedPointer(new GameBoxes::GridPiece(x_index,
					y_index, 0, square)));
						// Again emplace_back is safer
					
					//Originaly, every gridpiece is a safe spot
					addSafe(x_index, y_index);
				}
			}
			//Generates a random coordinate in the grid and spawns the snake head
			std::unique_ptr<Random::RandomGenerator> coordinate (new Random::RandomGenerator(square));
			coordinates = (*coordinate).Return_Rand(arr);
			twoDGridVector[coordinates[0]][coordinates[1]] = GridSharedPointer(new GameBoxes::GridPiece(coordinates[0], coordinates[1], 1, square));
			
			//adds the snake head to a position vector
			std::vector < int > head;
			head.push_back(coordinates[0]);
			head.push_back(coordinates[1]);
			snakePosition.push_back(head);
			
			//Removes head location from the safespot vector
			safe(head[0], head[1]);
			
			//Randomly spawns the snake tail
			addTail(coordinates, arr, square, cArgs);
		}
		
		void Snake::addSafe(int x_coordinate, int y_coordinate)
		{
			std::vector <int> safeSpot;
			safeSpot.push_back(x_coordinate);
			safeSpot.push_back(y_coordinate);
			appleSafeSpot.push_back(safeSpot);
		}
		//This adds a safe spot coordinate is the safe position vector. Used to spawn the apple.
		
		void Snake::safe(int x_coordinate, int y_coordinate)
		{
			for (int iterator = 0; iterator < appleSafeSpot.size(); iterator++)
			{
				if (appleSafeSpot[iterator][0] == x_coordinate && appleSafeSpot[iterator][1] == y_coordinate)
				{
					appleSafeSpot.erase(appleSafeSpot.begin()+iterator);
				}
			}
		}
		//This removes a safespot coordinate from the safe position vector whenever the snake moves, grows, or is spawned
		
		bool Snake::move(int xHeadC, int yHeadC, int xTailC, int yTailC, int cArgsOne, int cArgsTwo, int xHeadCAdd, int yHeadCAdd, Box &square, int headCoordinate, int headCoordinateAdd, int* cArgs)
		{
			//Checks if the snake move is valid (Not onto an edge of the screen or onto itself)
			if (headCoordinateAdd + headCoordinate < 2 * cArgsOne / cArgsTwo && headCoordinateAdd + headCoordinate >= 0 && (*twoDGridVector[xHeadC + xHeadCAdd][yHeadC + yHeadCAdd]).getColorDesignation() != -1)
			{
				//Updates the head of the snake in snake position vector
				std::vector <int> head;
				head.push_back(xHeadC + xHeadCAdd);
				head.push_back(yHeadC + yHeadCAdd);
				snakePosition.insert(snakePosition.begin(), head);
				
				//Checks if the Snake is moving into an apple
				bool eatApple = false;
				if ((*twoDGridVector[xHeadC + xHeadCAdd][yHeadC + yHeadCAdd]).getColorDesignation() == 1)
				{
					eatApple = true;	
				}
				
				//removes the new head position from the lift of safe Grid Pieces
				safe(xHeadC + xHeadCAdd, yHeadC + yHeadCAdd);
				
				//Spawns the head of the snake
				twoDGridVector[xHeadC + xHeadCAdd][yHeadC + yHeadCAdd] = GridSharedPointer(new GameBoxes::GridPiece(xHeadC + xHeadCAdd, yHeadC + yHeadCAdd, 1, square));
				//Changes the previous head of the snake to Red
				twoDGridVector[xHeadC][yHeadC] = GridSharedPointer(new GameBoxes::GridPiece(xHeadC, yHeadC, -1, square));
				//Changes the last piece of tail to White
				twoDGridVector[xTailC][yTailC] = GridSharedPointer(new GameBoxes::GridPiece(xTailC, yTailC, 0, square));
				
				//Adds the last piece of the tail to the safe space vector for Apple Spawning
				addSafe(xTailC, yTailC);
						
				snakePosition.pop_back();
				
				//Spawns an additional tail at the rear of the snake
				if (eatApple == true)
				{
					addTail(coordinates, arr, square, cArgs);
				}
				
				//Return that the snake is alive
				return true;
			}
			else
			{
				//Return that the snake died
				return false;	
			}
		}
		
		bool Snake::moveSnake(Box square, char direction, int* cArgs)
		{
			
			int xHeadCoordinate = snakePosition[0][0];
			int yHeadCoordinate = snakePosition[0][1];
					
			int xTailCoordinate = snakePosition.back()[0];
			int yTailCoordinate = snakePosition.back()[1];
			
			bool alive;
			
			switch(direction)
			{
				case 's' :
							//   current X and Y head Coordinates |current X and Y tail Coordinates |Width and Grid Size | X and Y directions of snake movement | Box | Y Head Coordinate |
							//	 Direction of Y Head Coordinate |cArgs
					alive = move(xHeadCoordinate, yHeadCoordinate, xTailCoordinate, yTailCoordinate, cArgs[1], cArgs[3], 0, 1, square, yHeadCoordinate, 1, cArgs);
					break;
				case 'a' :					
					alive = move(xHeadCoordinate, yHeadCoordinate, xTailCoordinate, yTailCoordinate, cArgs[0], cArgs[2], 1, 0, square, xHeadCoordinate, 1, cArgs);
					break;
				case 'w' :					
					alive = move(xHeadCoordinate, yHeadCoordinate, xTailCoordinate, yTailCoordinate, cArgs[1], cArgs[3], 0, -1, square, yHeadCoordinate, -1, cArgs);
					break;
				case 'd' :					
					alive = move(xHeadCoordinate, yHeadCoordinate, xTailCoordinate, yTailCoordinate, cArgs[0], cArgs[2], -1, 0, square, xHeadCoordinate, -1, cArgs);
					break;
				default :
					//Stop the snake's motion
					alive = true;
					break;
			}
			
			return alive;
		}
		
		void Snake::addTail(int* coordinates, int* arr, Box square, int* cArgs)
		{
			for (int x = 0; x < 10; x++)
			{
				//Creates a random coordinate
				std::unique_ptr<Random::RandomGenerator> coordinate (new Random::RandomGenerator(square));
				coordinates = (*coordinate).Return_Rand(arr);
				
				//Remaps (1,0), (1,1), (0,1), (0,0) to (1,0), (0,-1), (0,1), (-1,0)
				coordinates[0] = coordinates[0] % 2;
				coordinates[1] = coordinates[1] % 2;
				
				if (coordinates[0] + coordinates[1] == 2)
				{
					coordinates[0] = 0;
					coordinates[1] = -1;
				}
				else if (coordinates[0] + coordinates[1] == 0)
				{
					coordinates[0] = -1;
					coordinates[1] = 0;
				}
				
				//Copies the tail end position of the snake
				std::vector <int> temp = snakePosition.back();
				//If the direction of the new snake tail does now overlap itself or go over a screen edge, append a new tail segment to the end of the snake
				if (temp[0] + coordinates[0] < 2 * cArgs[0] / cArgs[2] && temp[1] + coordinates[1] < 2 * cArgs[1] / cArgs[3] && temp[1] + coordinates[1] >= 0 && temp[0] + coordinates[0] >= 0 &&
					(*twoDGridVector[temp[0] + coordinates[0]][temp[1] + coordinates[1]]).getColorDesignation() == 0)
				{
					//Append the tail
					twoDGridVector[temp[0] + coordinates[0]][temp[1] + coordinates[1]] = GridSharedPointer(new GameBoxes::GridPiece(temp[0] + coordinates[0], temp[1] + coordinates[1], -1, square));
					
					//Add the new tail segment to the Snake Position Vector
					std::vector < int > body;
					body.push_back(temp[0] + coordinates[0]);
					body.push_back(temp[1] + coordinates[1]);
					snakePosition.push_back(body);
					
					//Remove the new tail position from the list of safe spaces for apple spawning
					safe(body[0], body[1]);
				}
			}
			
			//Find a safe spot to spawn the apple
			int safe_Spot = rand() % appleSafeSpot.size();
			
			//Spawn the apple
			twoDGridVector[appleSafeSpot[safe_Spot][0]][appleSafeSpot[safe_Spot][1]] = GridSharedPointer(new GameBoxes::GridPiece(appleSafeSpot[safe_Spot][0], appleSafeSpot[safe_Spot][1], 1, square));
			
		}
	} // Gameboxes