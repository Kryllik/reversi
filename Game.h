/* header of Game.cpp
*/ 

#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include <vector>
#include <iostream>

using namespace std;
class Player;

class Game {
	public:
		Game(char player1, char player2);
		~Game();
		
		void gameStart();
		
	private:
		Board *board;			/* The Board instance */
		
		Player *playerBlack; 	/* The black player instance */
		
		Player *playerWhite; 	/* The white player instance */
};


#endif /* GAME_H */
