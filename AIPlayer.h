//Header de AIPlayer

#ifndef AIPLAYER_MM_H
#define AIPLAYER_MM_H

#include "Player.h"
#include <vector>

class AIPlayer : public Player{
	public:
		AIPlayer(cellContent color);
		~AIPlayer() {}
		int evalBoard(Board board, cellContent playerColor);
		int MiniMax(Board gameBoard, cellContent playerColor, int depth, bool maximizeForPlayer);
		Position getMove(Board gameBoard, int turn);
		
	private:
		cellContent opponentColor; /* our opponent color */

};

#endif
