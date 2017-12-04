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
		int const TURN_LIMIT_OFFSET = 4; //Constant of how deep the AI has to search for plays. must be an even number
		int getBoardScore(Board board, int turn, int limitTurn);
		int calcBoardScore(Board& board, int turn);
		int mean(std::vector<int> v);
};

#endif
