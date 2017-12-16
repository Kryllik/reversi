//Header de HumanPlayer

#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"


/*!
 * @class HumanPlayer
 * @brief child class based on Player.cpp that handles human players acting through keyboards
 *
 */
class HumanPlayer: public Player{
public:
	HumanPlayer(cellContent color);
	~HumanPlayer() {}
	Position getMove(Board gameBoard);
private:
};

#endif /* HUMANPLAYER_H */
