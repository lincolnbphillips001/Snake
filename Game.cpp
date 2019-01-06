#include "Game.h"

//Initializes internal variable
Game::Game (void) {

	game_speed = GAME_SPEED_LEVEL_ONE;
}

unsigned int Game::get_game_speed (void) {
	return game_speed;
}

