


//classe fille de Player, contient les fonctions et attributs propre à une intelligence artificielle.

#include "limits.h"
#include "AIPlayer.h"
#include <climits>

using namespace std;

/**
 * AIPlayer constructor
 */
AIPlayer::AIPlayer(cellContent color) : Player(color){
	if (playerColor==White) opponentColor=Black;
	else opponentColor=White;
	//minimaxCall=0;
	alphabetaCall=0;
	turnNumber = 0;
	evalType=0;
	depthStart=0;
}

/**
 * AI player destructor
 */
AIPlayer::~AIPlayer() {
	cout << "minimax call for player ";
	if (playerColor==Black) cout << "black "; else cout << "white " << endl;
//	cout << this->minimaxCall << endl;

	cout << "alphabeta call for player ";
	if (playerColor==Black) cout << "black "; else cout << "white " << endl;
//	cout << this->alphabetaCall << endl;
}

/**
 * first eval board function : basic score of player - basic score of opponent
 * cornes = 4, external lines = 2, lines/row 2/7 = 0, other = 1
 */
int AIPlayer::evalBoard1(Board board,cellContent playerColor) {
	int tot = 0;
	Position pos;
	for(unsigned int x = 1; x <= Board::BOARD_SIZE; x++){
		for(unsigned int y = 1; y<= Board::BOARD_SIZE; y++){
			pos = Position(x,y);
			cellContent content = board.getContentAt(pos);
			if (content == playerColor) {
				if ((x == 1 or x == 8 ) and (y == 1 or y == 8 )) {
					tot += 4; // corner
				}
				else if ((x == 1 or x == 8) or (y == 1 or y == 8)) {
					tot += 2; // side
				} else if (x==2 or x==7 or y==2 or y==7) {
					//tot -= 1;
				}else {
					tot+=1;
				}
			} else if (content != Empty) {
				if ((x == 1 or x == 8 ) and (y == 1 or y == 8 )) {
					tot -= 4; // corner
				}
				else if ((x == 1 or x == 8) or (y == 1 or y == 8)) {
					tot -= 2; // side
				} else if (x==2 or x==7 or y==2 or y==7) {
					//tot -= 1;
				}else {
					tot-=1;
				}
			}
		}
	}
	return tot;
}

int weightedPos[8][8] = {
		{20,-4,5,5,5,5,-4,20},
		{-4,-6,2,2,2,2,-6,-4},
		{5,2,2,2,2,2,2,5},
		{5,2,2,2,2,2,2,5},
		{5,2,2,2,2,2,2,5},
		{5,2,2,2,2,2,2,5},
		{-4,-6,2,2,2,2,-6,-4},
		{20,-4,5,5,5,5,-4,20}
};
/**
 * second eval board function : weighted score of player - weighted score of opponent
 * score weight is taken in above array
 *
 */
int AIPlayer::evalBoard2(Board board,cellContent playerColor) {
	int tot = 0;
	Position pos;
	for(unsigned int x = 1; x <= Board::BOARD_SIZE; x++){
		for(unsigned int y = 1; y<= Board::BOARD_SIZE; y++){
			pos = Position(x,y);
			cellContent content = board.getContentAt(pos);
			int weight = weightedPos[x-1][y-1];
			if (content == playerColor) {
				tot+=weight;
			} else if (content != Empty) {
				tot-=weight;
			}
		}
	}
	return tot;
}


/**
 * third eval board function :
 * - weighted score of player - weighted score of opponent
 * - if round player is our player, remove 50 points if we won't end the game (parity)
 * - if round player is our player, add 10 points per possible moves (mobility)
 */
int AIPlayer::evalBoard3(Board board,cellContent roundColor) {
	int tot = 0;
	int freeCell=0;
	Position pos;
	for(unsigned int x = 1; x <= Board::BOARD_SIZE; x++){
		for(unsigned int y = 1; y<= Board::BOARD_SIZE; y++){
			pos = Position(x,y);
			cellContent content = board.getContentAt(pos);
			int weight = weightedPos[x-1][y-1];
			if (content == playerColor) {
				tot+=weight;
			} else if (content == opponentColor) {
				tot-=weight;
			} else {
				freeCell++; /* count free cell for parity check */
			}
		}
	}
	if ((freeCell%2) == 0) { /* odd cell number remaining, player won't be the last player in the game */
		if (roundColor==this->playerColor) tot-=50; /* try to avoid this path by giving it a bad score */
	}
	if (roundColor==this->playerColor) { /* check mobility for our player */
		vector<Position> pos = board.validMoves(this->playerColor);
		tot+=pos.size()*10;
	}
	return tot;
}


/**
 * main evalboard function. Depending on evalType values, will call one of the 3 available evaluation function
 * defined above.
 */
int AIPlayer::evalBoard(Board board,cellContent playerColor) {
	switch (this->evalType) {
	case 1: return evalBoard1(board,playerColor);
	case 2: return evalBoard2(board,playerColor);
	case 3:
	default: return evalBoard3(board, playerColor);
	}
}

/**
 * AlphaBeta algo implementation. shall be called recursively with a gameBoard state for a player's color and
 * for a remaining depth to dig into.  Alpha and Beta are passed along
 *
 * Returns the best score (given by an evaluation function)
 */
int AIPlayer::AlphaBeta(Board& gameBoard, cellContent playerColor, int depth, int alpha, int beta) {
	alphabetaCall++;

	/* check if max depth is reacher or if the game is over because no player can play */
	if ((depth==0) or (gameBoard.isGameOver())) {
		return evalBoard(gameBoard,playerColor); /* return the board's evaluation for this leaf */
	}

	/* calc how much time has elapsed for this position evaluation */
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - turnStartTime).count();
	if (elapsed>20000) return evalBoard(gameBoard,playerColor);

	/* note: left with 2 big if/then clause for readibility. Could be further improved as there is much
		 * in common in the two parts of the if/them */

	if (playerColor==this->playerColor) { /* player is us, so we are maximimzing for player on this round */
		vector<Position> moves = gameBoard.validMoves(this->playerColor);
		if (moves.size() == 0) return evalBoard(gameBoard,this->playerColor);

		for (unsigned int i = 0; i<moves.size(); i++) {
			Board tempBoard = gameBoard;
			Position p = moves[i];
			tempBoard.setContentAt(p, playerColor);
			tempBoard.switchCells(playerColor, p);
		
			int v = AlphaBeta(tempBoard, this->opponentColor, depth-1, alpha, beta);

			if (v> alpha) {
				alpha = v;
				if (alpha >= beta) {
					break;
				}
			}
		}
		return alpha;
	} else {  /* player is opponent, so we are minimizing for player this round */
		vector<Position> moves = gameBoard.validMoves(this->opponentColor);
		if (moves.size() == 0) return evalBoard(gameBoard,this->opponentColor);
		for (unsigned int i = 0; i<moves.size(); i++) {
			Board tempBoard = gameBoard;
			Position p = moves[i];
			tempBoard.setContentAt(p, playerColor);
			tempBoard.switchCells(playerColor, p);

			int v = AlphaBeta(tempBoard, this->playerColor, depth-1, alpha, beta);

			if ( v < beta) {
				beta=v;
				if (alpha>=beta) {
					break;
				}
			}
		}
		return beta;
	}
}


///**
// * Minimax algo implementation. shall be called recursively with a gameBoard state for a player's color and
// * for a remaining depth to dig into.
// *
// * Returns the best score (given by an evaluation function)
// */
//int AIPlayer::MiniMax(Board& gameBoard, cellContent playerColor, int depth) {
//	this->minimaxCall++;
//
//	/* check if max depth is reacher or if the game is over because no player can play */
//	if ((depth==0) or (gameBoard.isGameOver())) {
//		return evalBoard(gameBoard,playerColor); /* return the board's evaluation for this leaf */
//	}
//
//	int bestValue;
//
//	/* note: left with 2 big if/then clause for readibility. Could be further improved as there is much
//	 * in common in the two parts of the if/them */
//
//	if (playerColor==this->playerColor) { /* player is us, so we are maximimzing for player on this round */
//		bestValue = INT_MIN;
//		vector<Position> moves = gameBoard.validMoves(this->playerColor);
//		if (moves.size() == 0) return evalBoard(gameBoard,this->playerColor);
//
//		for (unsigned int i = 0; i<moves.size(); i++) {
//			Board tempBoard = gameBoard;
//			Position p = moves[i];
//			tempBoard.setContentAt(p, playerColor);
//			tempBoard.switchCells(playerColor, p);
//			int v = MiniMax(tempBoard, this->opponentColor,depth-1); /* next level will be for opponent */
//			bestValue = std::max(bestValue, v);
//		}
//	} else {				/* player is opponent, so we are minimizing for player this round */
//		bestValue=INT_MAX;
//		vector<Position> moves = gameBoard.validMoves(this->opponentColor);
//		if (moves.size() == 0) return evalBoard(gameBoard,this->opponentColor);
//		for (unsigned int i = 0; i<moves.size(); i++) {
//			Board tempBoard = gameBoard;
//			Position p = moves[i];
//			tempBoard.setContentAt(p, playerColor);
//			tempBoard.switchCells(playerColor, p);
//			int v = MiniMax(tempBoard, this->playerColor,depth-1); /* next level will be for us */
//			bestValue = std::min(bestValue, v);
//
//		}
//	}
//	return bestValue;
//}

/**
 * return the AI computed move for the player, given the gameBoard state
 * for each possible move for player, an alphabeta will be started in order to score the move and the best move is then selected
 *
 */
Position AIPlayer::getMove(Board gameBoard){

	vector<Position> moves = gameBoard.validMoves(playerColor);

/* Uncomment below to have an AI with trivial algo (return first possible move) for white or black) */
//	if (playerColor == White) {
//		if (moves.size()>0) return moves[0];
//		else return Position(0,0);
//	}

//if (playerColor==White) { /* AI mode for white player */
//	evalType=1;
//	depthStart=8;
//} else {				  /* AI mode for black player */
	if (this->turnNumber< 6) {
		evalType=3;
		depthStart=7;
	}
	else if (this->turnNumber<20) {
		evalType=3;
		depthStart=5;
	}
	else {
		this->evalType=3;
		depthStart=8;
	}
//}

	int maxPoints = INT_MIN;	/* start with worse points possible */

	Position bestMove;

	/* save the current time stamp */
	turnStartTime = std::chrono::steady_clock::now();


	/* for each possible moves at this level proceed with a minimax or alphabeta evaluation to choose the best move */
	for (unsigned int i = 0; i<moves.size(); i++) {
		/* build a temp board with the current move */
		Board tempBoard = gameBoard;
		Position p = moves[i];
		tempBoard.setContentAt(p, playerColor);
		tempBoard.switchCells(playerColor, p);


		/* current move is this player's move. So we enter minimax / alphabeta recursion at opponent's level */
		//int points = MiniMax(tempBoard, this->opponentColor, this->depthStart);
		int points = AlphaBeta(tempBoard, this->opponentColor, this->depthStart,INT_MIN, INT_MAX);

		if (points > maxPoints) {	/* if current move leads to better score, remember it as best move */
			maxPoints = points;
			bestMove=p;
		}

		/* some progress indication on screen */
		int progression = (100*(i+1))/moves.size();


		/* calc how much time has elapsed for this position evaluation */
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - turnStartTime).count();

		/* display some info about this position's evaluation */
		cout << progression << " % (" << (i+1) << "/" << moves.size() << ")"<<" Score = "<< points <<"; Best Score = "
					 << maxPoints << " (" << bestMove.toString() << ")" << " elapsed : "
					 << elapsed/1000.0
					 << "(turn: "<< this->turnNumber << "; evaltype: "<<this->evalType << "; depth: "<<this->depthStart<< ") " << std::endl;

	}

	/* TODO: check bestMove is valid, if not, maybe fall back on first move of list of move */

	this->turnNumber++; /* increment turn counter each time we play */
	return bestMove;
}



