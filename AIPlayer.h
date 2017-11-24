//Header de AIPlayer

#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
#include <vector>

class AIPlayer : public Player{
	public:
		AIPlayer(cellContent color);
		~AIPlayer() {}
		
		Position getMove(Game& game, Board boardCopy, int turn);
		
	private:
		int getBoardScore(Game& game, Board board, int turn, int limitTurn);
		int calcBoardScore(Board& board, int turn);
};

#endif
