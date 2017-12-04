/* header of Game.cpp
*/ 

#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Player;

class Game {
	public:
		Game();
		~Game();
		
		void gameStart();
		
	private:
		Board *board;			/* The Board instance */
		
		Player *playerBlack; 	/* The black player instance */
		
		Player *playerWhite; 	/* The white player instance */
};


#endif /* GAME_H */
