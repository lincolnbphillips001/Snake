#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <SDL2/SDL.h>
#include "Texture.h"
#include "UserInput.h"
#include "Board.h"

typedef struct SnakePosition {
	int mPosX;
	int mPosY;
	int mPosInPixelsX;
	int mPosInPixelsY;
} SnakePosition;

class Snake
{
	public:
		//Initializes the variables
		Snake (void);

		//Destructor
		~Snake (void);

		bool initialize (SDL_Renderer*);

		//Deallocates textures
		void free (void);

		void increase_snake_length (unsigned int);

		//Moves the snake
		void move (Board mBoard, unsigned int);

		//Show the snake
		void render (SDL_Renderer*);

	private:
		//Snake sprite 
		Texture *mTexture;

		//The X and Y offsets of the dot
		int mPosX;
		int mPosY;

		unsigned int mDirection;
		unsigned int mDirectionPrevious;

		int convert_board_position_to_pixel_position(Board, int);

		std::vector<SnakePosition> mSnakePositionVector;

		unsigned int mLengthOfSnake;
};

#endif //SNAKE_H
