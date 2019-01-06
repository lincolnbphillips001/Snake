#include <iostream>
#include "Snake.h"
#include "Board.h"


//Initializes internal variable
Snake::Snake (void) {

	mLengthOfSnake = 1;
	mDirection = DIRECTION_RIGHT;
	mDirectionPrevious = mDirection;

	// make room for 2 elements
	mSnakePositionVector.resize(mLengthOfSnake);

	//Initialize the snakes starting position
	mSnakePositionVector[0].mPosX = 2;
	mSnakePositionVector[0].mPosInPixelsX = 2*20;
	mSnakePositionVector[0].mPosY = 0;
	mSnakePositionVector[0].mPosInPixelsY = 0*20;
}

//Initializes internal variable
Snake::~Snake (void) {

	//Deallocate
	free();
}

bool Snake::initialize(SDL_Renderer* mRenderer) {

	//Loading success flag
	bool success = true;

	mTexture = new Texture();

	//Load snake sprite
	if( !mTexture->load_from_file(mRenderer, "../images/dot.bmp"))
	{
		std::cout << "Failed to load snake sprite gfx!\n" << std::endl;
		success = false;
	}

	return success;
}

//Deallocates textures
void Snake::free (void) {

	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture->get_m_texture());
		mTexture = NULL;
	}
}

void Snake::increase_snake_length (unsigned int userInput) {

	if (userInput == SPACE_BAR) {
		mLengthOfSnake++;
		mSnakePositionVector.resize(mLengthOfSnake);
	}
}

void Snake::move (Board mBoard, unsigned int userInput) {

	SnakePosition snakePositionTmp;
	mDirection = userInput;

	if (userInput == NO_USER_INPUT || userInput == SPACE_BAR) {
		mDirection = mDirectionPrevious;
	}

	//Store old position
	snakePositionTmp = mSnakePositionVector[0];

	switch (mDirection) {
		case DIRECTION_UP:
			if (mDirectionPrevious == DIRECTION_DOWN) {
				mDirection = DIRECTION_DOWN;
			}
			break;
		case DIRECTION_DOWN:
			if (mDirectionPrevious == DIRECTION_UP) {
				mDirection = DIRECTION_UP;
			}
			break;
		case DIRECTION_LEFT:
			if (mDirectionPrevious == DIRECTION_RIGHT) {
				mDirection = DIRECTION_RIGHT;
			}
			break;
		case DIRECTION_RIGHT:
			if (mDirectionPrevious == DIRECTION_LEFT) {
				mDirection = DIRECTION_LEFT;
			}
			break;
	}

	switch (mDirection) {
		case DIRECTION_UP:
			mSnakePositionVector[0].mPosY = mSnakePositionVector[0].mPosY - 1;
			mSnakePositionVector[0].mPosInPixelsY = 
				convert_board_position_to_pixel_position(mBoard, mSnakePositionVector[0].mPosY);
			break;
		case DIRECTION_DOWN:
			mSnakePositionVector[0].mPosY = mSnakePositionVector[0].mPosY + 1;
			mSnakePositionVector[0].mPosInPixelsY = 
				convert_board_position_to_pixel_position(mBoard, mSnakePositionVector[0].mPosY);
			break;
		case DIRECTION_LEFT:
			mSnakePositionVector[0].mPosX = mSnakePositionVector[0].mPosX - 1;
			mSnakePositionVector[0].mPosInPixelsX = 
				convert_board_position_to_pixel_position(mBoard, mSnakePositionVector[0].mPosX);
			break;
		case DIRECTION_RIGHT:
			mSnakePositionVector[0].mPosX = mSnakePositionVector[0].mPosX + 1;
			mSnakePositionVector[0].mPosInPixelsX = 
				convert_board_position_to_pixel_position(mBoard, mSnakePositionVector[0].mPosX);
			break;
	}

	mDirectionPrevious = mDirection;

	//Shift whole snake
	if (mLengthOfSnake == 1) {

		//do nothing

	} else if (mLengthOfSnake == 2) {

		mSnakePositionVector[1] =	snakePositionTmp;

	} else if (mLengthOfSnake >= 3) {

		for (int i = mLengthOfSnake-1; i > 1; i--) {
			mSnakePositionVector[i] =	mSnakePositionVector[i-1];	
		}
		mSnakePositionVector[1] =	snakePositionTmp;
	}
}

//Renders texture at given point
void Snake::render (SDL_Renderer* renderer) {

	for (unsigned int i = 0; i < mLengthOfSnake; i++) {
		//Set rendering space and render to screen
		SDL_Rect renderQuad = {
			mSnakePositionVector[i].mPosInPixelsX, 
			mSnakePositionVector[i].mPosInPixelsY, 
			mTexture->get_width(), mTexture->get_height()};

		//Render to screen
		SDL_RenderCopyEx(renderer, mTexture->get_m_texture(), NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
	}
}

int Snake::convert_board_position_to_pixel_position(Board mBoard, int boardPosition) {

	int pixelPosition = 0;

	pixelPosition = mBoard.get_board_unit_in_pixels() * boardPosition;

  return pixelPosition;
}

