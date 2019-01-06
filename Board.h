#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>

class Board
{
	public:

		Board (int screenWidth, int screenHeight, 
			unsigned int boardWidth, unsigned int boardHeight, unsigned int boardUnitInPixels);

		~Board (void);

		unsigned int get_board_width (void);
		unsigned int get_board_height (void);

		unsigned int get_board_unit_in_pixels (void);

	private:
		//The dimensions of the screen
		int mScreenWidth;
		int mScreenHeight;

		//The dimensions of the board
		unsigned int mBoardWidth;
		unsigned int mBoardHeight;

		unsigned int mBoardUnitInPixels;
};

#endif //BOARD_H
