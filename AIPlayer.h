//Header de AIPlayer

#ifndef AIPLAYER_MM_H
#define AIPLAYER_MM_H

#include "Player.h"
#include <vector>

class AIPlayer : public Player{
	public:
		AIPlayer(cellContent color);
		~AIPlayer();
		int evalBoard(Board board, cellContent playerColor);
		int AlphaBeta(Board gameBoard, cellContent playerColor, int depth, int alpha, int beta);
		int MiniMax(Board gameBoard, cellContent playerColor, int depth);
		Position getMove(Board gameBoard);

		

	private:
		cellContent opponentColor; /* our opponent color */
		int minimaxCall;
		int alphabetaCall;


};

#endif
