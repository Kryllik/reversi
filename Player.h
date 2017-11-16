//Header de Player

#ifndef PLAYER_H
#define PLAYER_H

//#include "Game.h"
class Game;
#include <iostream>
#include "Position.h"	
#include "IO.h"
#include "Cell.h"

using std::cout;
using std::endl;
using std::string;

class Player{
	public:
		Player(cellContent color);
		cellContent getColor();
		virtual Position getMove(Game &game) =0;
		cellContent getOpponentColor();
	protected:
		cellContent playerColor;
};

#endif
