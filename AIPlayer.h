//Header de AIPlayer

#ifndef AIPLAYER_MM_H
#define AIPLAYER_MM_H

#include "Player.h"
#include <vector>
#include <chrono>

class AIPlayer : public Player{
	public:
		AIPlayer(cellContent color);
		~AIPlayer();
		int evalBoard1(Board board,cellContent playerColor);
		int evalBoard2(Board board,cellContent playerColor);
		int evalBoard3(Board board,cellContent playerColor);
		int evalBoard(Board board,cellContent playerColor);
		int AlphaBeta(Board gameBoard, cellContent playerColor, int depth, int alpha, int beta);
		int MiniMax(Board gameBoard, cellContent playerColor, int depth);
		Position getMove(Board gameBoard);

		

	private:
		cellContent opponentColor; /* our opponent color */
//		int minimaxCall;		/*<! keep track of how many times minimax has been called */
		int alphabetaCall;		/*<! keep track of how many times alphabeta has been called */
		int depthStart;			/*<! define how deep we shall dig */
		int evalType;			/*<! define the evaluation function that will be used to evaluate a board */
		int turnNumber; 		/*<! let's count the turn (+1 each time we play) */
		std::chrono::steady_clock::time_point turnStartTime; /*<! remember the timestamp when we start a turn */


};

#endif
