	#include <chrono>
	#include <thread>
	#include <unistd.h>
	#include <ncurses.h>

	#include "Snake.h"
	#include <GL/glut.h>

	int khbit(void)
	{
		int ch = getch();
		
		if (ch != ERR)
		{
			ungetch(ch);
			return 1;
		}
		else
		{
			return 0;	
		}
	}
	//Checks to see if a key is pressed. If a key is pressed, it's returned to the buffer for later processing

	int main(int argc, char **argv)
	{
		std::unique_ptr<GameBoxes::Box> squareBackground(new GameBoxes::Box(std::stoi(argv[1]), std::stoi(argv[2]),
								   std::stoi(argv[3]), std::stoi(argv[4])));
		//Create a window class

		int cArgs[4];
		(*squareBackground).getSizeArray(cArgs);
		
		
		glutInit(&argc, argv);
		(*squareBackground).createBackGroundTexture();
		//Render the window
		
		glClear(GL_COLOR_BUFFER_BIT); //new
		
		// initialize random seed:
		srand (time(NULL));
		
		// start ncurses
		initscr();
		// Line buffering disabled
		cbreak();
		// Don't echo while we do getch
		noecho();
		// Allows checking for Keypress
		nodelay(stdscr, TRUE);
		scrollok(stdscr, TRUE);
		
		bool play = true;
		while (play == true)
		{
			bool alive = true;
			//Create the snake
			std::unique_ptr<GameBoxes::Snake> snake(new GameBoxes::Snake(*squareBackground, cArgs));
			
			int direction; //direction when a key is pressed
			char directionTwo = 't'; //default direction when no key is pressed. Snake starts out motionless.
			
			flushinp();
			
			while (alive == true)
			{
				//Enters if when a key is pressed
				if (khbit())
				{
					direction = getch();
					directionTwo = direction;
					alive = (*snake).moveSnake(*squareBackground, direction, cArgs);
					flushinp();
				}
				//Move snake in default direction
				else
				{
					alive = (*snake).moveSnake(*squareBackground, directionTwo, cArgs);
				}
				
				//End the game
				if (direction == 'k')
				{
					endwin();
					return 0;
				}
				
				std::chrono::milliseconds dura( 80);
				std::this_thread::sleep_for( dura );

			}
			
		}
		
		glutMainLoop();
		
		return 0;
	}
