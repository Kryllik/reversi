


//classe fille de Player, contient les fonctions et attributs propre à une intelligence artificielle.

#include "AIPlayer.h"
using namespace std;


AIPlayer::AIPlayer(cellContent color) : Player(color){
}

Position AIPlayer::getMove(Board gameBoard, int turn){
	
	///TODO : gerer le cas ou un joueur ne sait pas jouer dans un board généré >> passer son tour
	
	cout << toString() << " AI processing..." << endl;
	vector<Position> validMoves = gameBoard.validMoves(playerColor);
	int numberOfPaths = validMoves.size();
	int progression = 0;
    
    int maxScore = -100000000;
    Position posToPlay;
    Position candidatePos;
    Board boardCopy;
    for (unsigned int i = 0; i<validMoves.size(); i++) {
		boardCopy = gameBoard;
		candidatePos = validMoves[i];
        boardCopy.setContentAt(candidatePos, playerColor);
        boardCopy.switchCells(playerColor, candidatePos);
        int limitTurn = turn+TURN_LIMIT_OFFSET;
        int score = getBoardScore(boardCopy,turn,limitTurn);
        if (score>maxScore) {
            maxScore = score;
            posToPlay = candidatePos;
        }
        progression = (100*(i+1))/numberOfPaths;
		cout << progression << " % (" << (i+1) << "/" << numberOfPaths << ") Score = "<< score << " (" << candidatePos.toString() << ")" << endl;
    }
    cout << "AI done. Turn " << turn << endl;
    
    return posToPlay;
}

int AIPlayer::getBoardScore(Board board, int turn, int limitTurn) {
    //retourne le score de la branche, en moyennant les branches suivantes. Si 
    int score = 0;
    if (turn >= limitTurn) {
        score = calcBoardScore(board,turn);
        //cout << "\nscore = " << score << endl;
		//IO::boardDisplay(board);
    } else {
        vector<Position> validOpponentMoves = board.validMoves(this->getOpponentColor()); //valid moves for opponent
        //cout << "Valid opponent moves (1)  : ";
        //IO::displayValidMoves(validOpponentMoves);
        vector<int> scoreList1; //list containing scores for opponant moves branches
        Board boardCopy;
        Position opponentPos;
        for (int i = 0; i<validOpponentMoves.size(); i++) {
			opponentPos = validOpponentMoves[i];
            boardCopy = board;
            boardCopy.setContentAt(opponentPos, this->getOpponentColor()); //opponent player plays
            boardCopy.switchCells(this->getOpponentColor(), opponentPos);
            vector<Position> validAIMoves = boardCopy.validMoves(playerColor); //valid moves for AI
            //cout << "Valid IA moves (2) : ";
            //IO::displayValidMoves(validAIMoves);
            Board boardCopy2;
            vector<int> scoreList2; //list containing scores for AI moves branches
            Position AIPos;
            for (int j = 0; j<validAIMoves.size(); j++) {
				AIPos = validAIMoves[j];
                boardCopy2 = boardCopy;
                boardCopy2.setContentAt(AIPos, playerColor); //AI plays
                boardCopy2.switchCells(playerColor, AIPos);
                score = getBoardScore(boardCopy2, turn+2, limitTurn);
                scoreList2.push_back(score);
            }
            int meanList2 = mean(scoreList2);
            scoreList1.push_back(meanList2);
        }
        int meanList1 = mean(scoreList1);
        score = meanList1;
    }
    return score;
}

int AIPlayer::mean(vector<int> v) {
	int res = 0;
	int cardinal = v.size();
	if (cardinal != 0) {
		int sum = 0;
		for (int elem:v) {
			sum+=elem;
		}
		res = (sum/cardinal);
	}
	return res;
}


int AIPlayer::calcBoardScore(Board& board, int turn) {
	///TODO : coin(), parite(), grouper au centre() (début), peu de possiblilités adverses (surtout fin), 
	
	int score = 0;
	//pour la parité :
	//si on joue le dernier tour
	if (turn==60) {
		score+=1500;
	}
	//si on joue dans un tour pair (donc bien parti pour jouer en dernier quand tour=60)
	else if ((turn%2)==0) {
		score+=100;
	}
	
	
	
	int AICorners=board.cornerNumber(playerColor);
	int opponentCorners=board.cornerNumber(this->getOpponentColor());
	score+=AICorners*800;
	score-=opponentCorners*800;
	
    /**if turn<20 {
     * 
    } else if turn<30 {
    * 
    } else if turn>50 {
    * 
    }
    /*
    if board.coin() {
        score++;
    }
    
    if board.parite() {
        score++;
    }
    
    //...*/
    
    
    /*
    if (playerColor==White) {
		score=0;
	}
	if (playerColor==Black) {
		score=0;
	}
    */
	//score = 10000*(board.getScore(playerColor)); //Factor 10000 to handle the mean of an int
	
    
    //cout << "\nscore = " << score << endl;
    //IO::boardDisplay(board);
    return score;
}






