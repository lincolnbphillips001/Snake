#include "Board.h"


Board::Board (
	int screenWidth, int screenHeight, unsigned int boardWidth, 
	unsigned int boardHeight, unsigned int boardUnitInPixels) {

	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	mBoardWidth = boardWidth;
	mBoardHeight = boardHeight;

	mBoardUnitInPixels = boardUnitInPixels;
}

Board::~Board (void) {

}

unsigned int Board::get_board_width (void) {

	return mBoardWidth;
}

unsigned int Board::get_board_height (void) {

	return mBoardHeight;
}

unsigned int Board::get_board_unit_in_pixels (void) {

	return mBoardUnitInPixels;
}

