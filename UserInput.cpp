#include <iostream>
#include "UserInput.h"

//Initializes internal variable
UserInput::UserInput (void) {

	mUserInput = DIRECTION_RIGHT;
}

//Handles mouse event
EventResult UserInput::handle_event (SDL_Event* e) {

	EventResult eventResult;

	//If a key was pressed
	if ((e->type == SDL_KEYDOWN) && (e->key.repeat == 0)) {

		//Adjust the velocity
		switch (e->key.keysym.sym)	{
			case SDLK_UP:
				eventResult.userInput = DIRECTION_UP;
				break;
			case SDLK_DOWN:
				eventResult.userInput = DIRECTION_DOWN;
				break;
			case SDLK_LEFT:
				eventResult.userInput = DIRECTION_LEFT;
				break;
			case SDLK_RIGHT:
				eventResult.userInput = DIRECTION_RIGHT;
				break;
			case SDLK_SPACE:
				eventResult.userInput = SPACE_BAR;
				break;
			default:
				eventResult.userInput = NO_USER_INPUT;
				break;
		}
		eventResult.wasKeyPressed = true;
	} else {
		eventResult.userInput = NO_USER_INPUT;
		eventResult.wasKeyPressed = false;
	}

	return eventResult;
}

