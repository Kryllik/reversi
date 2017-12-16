


//classe fille de Player, contient les fonctions et attributs propre à une intelligence artificielle.

#include "limits.h"
#include "AIPlayer.h"
#include <climits>

using namespace std;


AIPlayer::AIPlayer(cellContent color) : Player(color){
	if (playerColor==White) opponentColor=Black;
	else opponentColor=White;
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
int minimaxCall=0;
int AIPlayer::MiniMax(Board gameBoard, cellContent playerColor, int depth, bool maximizeForPlayer) {


	/* check if max depth is reacher or if the game is over because no player can play */
	if ((depth==0) or (gameBoard.isGameOver())) {
		return evalBoard(gameBoard, this->playerColor); /* return the board's evaluation for this leaf */
	}

	int bestValue;

	cellContent opponentColor;
	if (playerColor==White) opponentColor=Black;
	else opponentColor=White;

	if (maximizeForPlayer) {
		bestValue = INT_MIN;
		vector<Position> moves = gameBoard.validMoves(playerColor);
		if (moves.size() == 0) return evalBoard(gameBoard, this->playerColor);

		for (unsigned int i = 0; i<moves.size(); i++) {
			Board tempBoard = gameBoard;
			Position p = moves[i];
			tempBoard.setContentAt(p, playerColor);
			tempBoard.switchCells(playerColor, p);
			int v = MiniMax(tempBoard, opponentColor,depth-1, false);
			bestValue = std::max(bestValue, v);
		}
	} else {
		bestValue=INT_MAX;
		vector<Position> moves = gameBoard.validMoves(playerColor);
		if (moves.size() == 0) return evalBoard(gameBoard,this->playerColor);
		for (unsigned int i = 0; i<moves.size(); i++) {
			Board tempBoard = gameBoard;
			Position p = moves[i];
			tempBoard.setContentAt(p, playerColor);
			tempBoard.switchCells(playerColor, p);
			int v = MiniMax(tempBoard, opponentColor,depth-1, true);
			bestValue = std::min(bestValue, v);

		}
	}
	minimaxCall++;
	return bestValue;
}

Position AIPlayer::getMove(Board gameBoard, int turn){

	vector<Position> moves = gameBoard.validMoves(playerColor);

	if (playerColor == White) {
		if (moves.size()>0) return moves[0];
		else return Position(0,0);
	}


	minimaxCall=0;

	int maxPoints = INT_MIN;	/* start with worse points possible */

	Position bestMove;

	/* for each possible moves at this level proceed with a minimax evaluation to choose the best move */
	for (unsigned int i = 0; i<moves.size(); i++) {

		/* build a temp board with the current move */
		Board tempBoard = gameBoard;
		Position p = moves[i];
		tempBoard.setContentAt(p, playerColor);
		tempBoard.switchCells(playerColor, p);

		/* start minimax recursion to evaluate current move */
		unsigned int depth = 3;
		int points = MiniMax(tempBoard, this->opponentColor, depth, false);

		if (points > maxPoints) {	/* if current move leads to better score, remember it as best move */
			maxPoints = points;
			bestMove=p;

		}

		int progression = (100*(i+1))/moves.size();
		cout << progression << " % (" << (i+1) << "/" << moves.size() << ") Points = "
			 << maxPoints << " (" << bestMove.toString() << ")" << endl;


	}
	cout << "minimax Call : "<<minimaxCall<<endl;
	/* TODO: check bestMove is valid */
	return bestMove;
}



