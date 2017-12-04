//Header de AIPlayer

#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
#include <vector>

class AIPlayer : public Player{
	public:
		AIPlayer(cellContent color);
		~AIPlayer() {}
		
		Position getMove(Board gameBoard, int turn);
		
	private:
		int getBoardScore(Board board, int turn, int limitTurn);
		int calcBoardScore(Board& board, int turn);
		int mean(std::vector<int> v);
};

#endif
