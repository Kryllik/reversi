


//classe fille de Player, contient les fonctions et attributs propre à une intelligence artificielle.

#include "limits.h"
#include "AIPlayer.h"
#include <climits>
#include <chrono>

using namespace std;


AIPlayer::AIPlayer(cellContent color) : Player(color){
	if (playerColor==White) opponentColor=Black;
	else opponentColor=White;
	minimaxCall=0;
	alphabetaCall=0;
	depthStart=8; /* default start depth */
}

AIPlayer::~AIPlayer() {
	cout << "minimax call for player ";
	if (playerColor==Black) cout << "black "; else cout << "white ";
	cout << this->minimaxCall << endl;

	cout << "alphabeta call for player ";
	if (playerColor==Black) cout << "black "; else cout << "white ";
	cout << this->alphabetaCall << endl;
}
/* Basic AI : return one possible move */
//Position AIPlayer::getMove(Board gameBoard, int turn){
//	vector<Position> moves = gameBoard.validMoves(playerColor);
//	if (moves.size()>0) return moves[0];
//	else return Position(0,0);
//}

/*TODO: take into account opponents tiles to evaluate board */
int AIPlayer::evalBoard(Board board, cellContent playerColor) {
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
			}
		}
	}
	return tot;
}



int AIPlayer::AlphaBeta(Board gameBoard, cellContent playerColor, int depth, int alpha, int beta) {
	alphabetaCall++;

	/* check if max depth is reacher or if the game is over because no player can play */
	if ((depth==0) or (gameBoard.isGameOver())) {
		return evalBoard(gameBoard, this->playerColor); /* return the board's evaluation for this leaf */
	}

	/* note: left with 2 big if/then clause for readibility. Could be further improved as there is much
		 * in common in the two parts of the if/them */

	if (playerColor==this->playerColor) { /* player is us, so we are maximimzing for player on this round */
		vector<Position> moves = gameBoard.validMoves(playerColor);
		if (moves.size() == 0) return evalBoard(gameBoard, this->playerColor);

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
		vector<Position> moves = gameBoard.validMoves(playerColor);
		if (moves.size() == 0) return evalBoard(gameBoard,this->playerColor);
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



int AIPlayer::MiniMax(Board gameBoard, cellContent playerColor, int depth) {
	this->minimaxCall++;

	/* check if max depth is reacher or if the game is over because no player can play */
	if ((depth==0) or (gameBoard.isGameOver())) {
		return evalBoard(gameBoard, this->playerColor); /* return the board's evaluation for this leaf */
	}

	int bestValue;

	/* note: left with 2 big if/then clause for readibility. Could be further improved as there is much
	 * in common in the two parts of the if/them */

	if (playerColor==this->playerColor) { /* player is us, so we are maximimzing for player on this round */
		bestValue = INT_MIN;
		vector<Position> moves = gameBoard.validMoves(this->playerColor);
		if (moves.size() == 0) return evalBoard(gameBoard, this->playerColor);

		for (unsigned int i = 0; i<moves.size(); i++) {
			Board tempBoard = gameBoard;
			Position p = moves[i];
			tempBoard.setContentAt(p, playerColor);
			tempBoard.switchCells(playerColor, p);
			int v = MiniMax(tempBoard, this->opponentColor,depth-1); /* next level will be for opponent */
			bestValue = std::max(bestValue, v);
		}
	} else {				/* player is opponent, so we are minimizing for player this round */
		bestValue=INT_MAX;
		vector<Position> moves = gameBoard.validMoves(this->opponentColor);
		if (moves.size() == 0) return evalBoard(gameBoard,this->playerColor);
		for (unsigned int i = 0; i<moves.size(); i++) {
			Board tempBoard = gameBoard;
			Position p = moves[i];
			tempBoard.setContentAt(p, playerColor);
			tempBoard.switchCells(playerColor, p);
			int v = MiniMax(tempBoard, this->playerColor,depth-1); /* next level will be for us */
			bestValue = std::min(bestValue, v);

		}
	}
	return bestValue;
}

Position AIPlayer::getMove(Board gameBoard){

	vector<Position> moves = gameBoard.validMoves(playerColor);

/* Uncomment below to have an AI with trivial algo (return first possible move) for white or black) */
//	if (playerColor == White) {
//		if (moves.size()>0) return moves[0];
//		else return Position(0,0);
//	}



	int maxPoints = INT_MIN;	/* start with worse points possible */

	Position bestMove;

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();


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


		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

		double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin).count();


		cout << progression << " % (" << (i+1) << "/" << moves.size() << ") Points = "
					 << maxPoints << " (" << bestMove.toString() << ")" << " elapsed : "
					 << elapsed/1000.0 << std::endl;

	}

	/* TODO: check bestMove is valid, if not, maybe fall back on first move of list of move */
	return bestMove;
}



