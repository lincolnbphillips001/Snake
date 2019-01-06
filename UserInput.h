#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <SDL2/SDL.h>

enum UserInputOptions 
{
	NO_USER_INPUT = 0,
	DIRECTION_UP = 1,
	DIRECTION_DOWN = 2,
	DIRECTION_LEFT = 3,
	DIRECTION_RIGHT = 4,
	SPACE_BAR = 5,
	USER_INPUT_OPTIONS_TOTAL = 6
};

typedef struct EventResult {
	unsigned int userInput;
	bool wasKeyPressed;
} EventResult;

//The mouse button
class UserInput
{
	public:
		//Initializes internal variable
		UserInput (void);

		//Handles mouse event
		EventResult handle_event (SDL_Event* e);

	private:
		unsigned int mUserInput;
		unsigned int mUserInputPrevious;
};

#endif //USER_INPUT_H
