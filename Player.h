//Header de Player

#ifndef PLAYER_H
#define PLAYER_H

//class Game;
#include <iostream>
#include "Position.h"	
#include "IO.h"
#include "Cell.h"
#include "Game.h"

using std::cout;
using std::endl;
using std::string;

/*!
 * @class Player
 * @brief abstract Class for a reversi player.
 *
 *  base class for reversi players (human, file, AI, ...)
 *  allow to set/get/toString player's color
 *  allow to get opponent color
 *  allow to get player's move
 *  allow to inform player of its opponent's move (or void move)
 *
 */
class Player{
	public:
		Player(cellContent color);
		virtual ~Player();
		cellContent getColor() const;
		string toString()const ;
		cellContent getOpponentColor() const;
		virtual Position getMove(Board gameBoard, int turn);
		virtual void giveMove(Position pos);
		virtual void giveVoidMove();
	protected:
		cellContent playerColor;	/*!< the player's color */
};

#endif
