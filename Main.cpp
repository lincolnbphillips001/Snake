//Using SDL and standard IO 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include "Texture.h"
#include "UserInput.h"
#include "Game.h"
#include "Board.h"
#include "Snake.h"

/* Global variables */
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Screen dimension constants
const unsigned int BOARD_WIDTH_IN_PIXELS = 32;
const unsigned int BOARD_HEIGHT_IN_PIXELS = 24;

//A single board unit in pixels
const unsigned int BOARD_UNIT_IN_PIXELS = 20;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
Texture gBgTexture;

UserInput gUserInput;
Game gGame;
Snake gSnake;
Board gBoard(
	SCREEN_WIDTH, SCREEN_HEIGHT, BOARD_WIDTH_IN_PIXELS, 
	BOARD_HEIGHT_IN_PIXELS, BOARD_UNIT_IN_PIXELS);


/* Forward declarations */
//Starts up SDL and creates window
bool initialize (void);

bool load_media (void);

//Frees media and shuts down SDL
void close (void);

				 
bool initialize (void) {

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool load_media (void) {
	
	//Load bg texture
	if(gBgTexture.load_from_file(gRenderer, "../images/background.png") == false)
	{
		printf( "Failed to load bg texture!\n" );
		return false;
	}

	if (gSnake.initialize(gRenderer) == false) 
	{
		printf("Failed to initialize snake!\n");
		return false;
	}

	return true;
}


void close (void) {

	gSnake.free();

	//Free loaded images
	gBgTexture.free();

	//Destroy window
	SDL_DestroyRenderer (gRenderer);
	SDL_DestroyWindow (gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main (int argc, char* args[]) {

	//This is to suppress warnings at compile time
  (void)argc;
	(void)*args;

	unsigned int gameLoopCounter = 0;
	unsigned int gameLoopTimeStamp = 0;
	unsigned int userInput = NO_USER_INPUT;
	EventResult eventResult;

	//Start up SDL and create window
	if (!initialize() )
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!load_media() )
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent (&e) != 0) 
				{
					//User requests quit
					if (e.type == SDL_QUIT) 
					{
						quit = true;
					}

					//Get user input
					eventResult = gUserInput.handle_event(&e);

					if (eventResult.wasKeyPressed == true) {
						userInput = eventResult.userInput;
					} 
				}

				if (gameLoopCounter >= (gameLoopTimeStamp + gGame.get_game_speed())) {
					//Move the snake
					gSnake.increase_snake_length (userInput);
					gSnake.move(gBoard, userInput);
					userInput = NO_USER_INPUT;
					gameLoopTimeStamp = gameLoopCounter;
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

			 	//Render background
				gBgTexture.render(gRenderer, 0, 0);

				//Render object
				gSnake.render( gRenderer );

				//Update screen
				SDL_RenderPresent( gRenderer );

				gameLoopCounter++;
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
