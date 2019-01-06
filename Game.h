#ifndef GAME_H
#define GAME_H

const unsigned int GAME_SPEED_LEVEL_ONE = 15;

class Game
{
	public:

		//Initializes the variables
		Game (void);

		unsigned int get_game_speed (void);


	private:
		//The X and Y offsets of the dot
		unsigned int game_speed;

};

#endif //GAME_H
