/* header of Game.cpp
*/ 

#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include <vector>
#include <iostream>

using namespace std;
class Player;

/*!
 * @class Game
 * @brief class representing a game between two player instance and a board
 */
class Game {
	public:
		Game(char player1, char player2);
		~Game();
		
		void gameStart();
		static cellContent oppositeColor(cellContent color); //used in AIPlayer
		
	private:
		Board  *board;			/*<! The Board instance */
		Player *playerBlack; 	/*<! The black player instance */
		Player *playerWhite; 	/*<! The white player instance */
};


#endif /* GAME_H */
