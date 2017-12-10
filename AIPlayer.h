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
		int const TURN_LIMIT_OFFSET = 4; //Constant of how deep the AI has to search for plays. (replaced by TURN_LIMIT_VECTOR for backtracking)
		vector<int> const TURN_LIMIT_VECTOR {2,3,4}; //Should go in increasing order. 
													 //Each elem corresponds to the depth of the research
		vector<int> const MAX_ELEM_VECTOR {6,2,1}; //Should go in decreasing order. Should have the same size as TURN_LIMIT_VECTOR. Last elem should be 1.
												   //Each elem corresponds to the max number of paths remaining after the corresponding iteration.
		int getBoardScore(Board board, int turn, int limitTurn, cellContent currentPlayerColor);
		vector<int> maxScoreIndexes(vector<int> scores, int maxElem);
		int calcBoardScore(Board& board, int turn, bool endOfGame, cellContent currentPlayerColor);
		int mean(std::vector<int> v);
		bool parite(int turn, cellContent currentPlayerColor);
};

#endif
