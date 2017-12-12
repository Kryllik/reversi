


//classe fille de Player, contient les fonctions et attributs propre à une intelligence artificielle.

#include "AIPlayer.h"

using namespace std;


AIPlayer::AIPlayer(cellContent color) : Player(color){
}

Position AIPlayer::getMove(Board gameBoard, int turn){
	
	///TODO : moyenne géométrique ou similaire pour moyenner les coups adverses, pour que les pires cas aient une plus grande importance
	///TODO : pas de moyenne pour moyenner nos coups, prendre juste le meilleur, car on a le choix. Mais problème : meilleur score pour branche où on joue en dernier
	
	
	cout << toString() << " AI processing..." << endl;
	
	
	/* Without backtracking
	 * 
	 * */
	/*vector<Position> validMoves = gameBoard.validMoves(playerColor);
	int numberOfPaths = validMoves.size();
	int progression = 0;
	int limitTurn = turn+TURN_LIMIT_OFFSET;
    
    int maxScore = -100000000;
    Position posToPlay;
    Position candidatePos;
    Board boardCopy;
    for (unsigned int i = 0; i<validMoves.size(); i++) {
		boardCopy = gameBoard;
		candidatePos = validMoves[i];
		
        boardCopy.setContentAt(candidatePos, playerColor);
        boardCopy.switchCells(playerColor, candidatePos);
        
        int score = getBoardScore(boardCopy,turn,limitTurn,Game::oppositeColor(this->getColor()));
        if (score>maxScore) {
            maxScore = score;
            posToPlay = candidatePos;
        }
        progression = (100*(i+1))/numberOfPaths;
		cout << progression << " % (" << (i+1) << "/" << numberOfPaths << ") Score = "<< score << " (" << candidatePos.toString() << ")" << endl;
    }*/
    
    /* With backtracking
     * 
     * */
    Position posToPlay;
    vector<Position> validMoves = gameBoard.validMoves(playerColor);
    for (unsigned int turnLimitIndex = 0; turnLimitIndex<TURN_LIMIT_VECTOR.size(); turnLimitIndex++) {
		vector<int> scores;
		vector<Position> positions;
		int turnLimitOffset = TURN_LIMIT_VECTOR[turnLimitIndex];
		int limitTurn = turn+turnLimitOffset;
		int numberOfPaths = validMoves.size();
		cout << "Preprocessing " << turnLimitIndex+1 << ". Offset : " << turnLimitOffset << endl;
		Board boardCopy;
		Position candidatePos;
		for (unsigned int i = 0; i<validMoves.size(); i++) {
			boardCopy = gameBoard;
			candidatePos = validMoves[i];
			
			boardCopy.setContentAt(candidatePos, playerColor);
			boardCopy.switchCells(playerColor, candidatePos);
			
			int score = getBoardScore(boardCopy,turn,limitTurn,Game::oppositeColor(this->getColor()));
			
			int progression = (100*(i+1))/numberOfPaths;
			cout << progression << " % (" << (i+1) << "/" << numberOfPaths << ") Score = "<< score << " (" << candidatePos.toString() << ")" << endl;
			
			scores.push_back(score);
			positions.push_back(candidatePos);
		}
		int maxElemCount = MAX_ELEM_VECTOR[turnLimitIndex];
		vector<int> indexes = maxScoreIndexes(scores,maxElemCount);
		if (indexes.size()>1) {
			vector<Position> newValidMoves;
			for (unsigned int i = 0; i<indexes.size(); i++) {
				int indexToPlay = indexes[i];
				newValidMoves.push_back(validMoves[indexToPlay]);
			}
			validMoves=newValidMoves;
			cout << "Moves remaining : ";
			IO::displayValidMoves(validMoves);
		} else {
			int indexToPlay = indexes[0];
			posToPlay = validMoves[indexToPlay];
		}
	}
    
    cout << "AI done. Turn " << turn << endl;
    
    return posToPlay;
}

vector<int> AIPlayer::maxScoreIndexes(vector<int> scores, int maxElem) {
	maxElem = min(maxElem,(int)scores.size());
	vector<int> indexes;
	for (int i=0;i<maxElem;i++) {
		int maxScore=scores[0];
		int maxIndex=0;
		for (int j=1;j<scores.size();j++) {
			if (scores[j]>maxScore) {
				maxScore=scores[j];
				maxIndex=j;
			}
		}
		indexes.push_back(maxIndex);
		scores[maxIndex] = -100000000; //set the highest score to a very low value so that the index is not taken twice
	}
	return indexes;
}


/*
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
}*/

int AIPlayer::getBoardScore(Board board, int turn, int limitTurn, cellContent currentPlayerColor) {
    //retourne le score de la branche, en moyennant les branches suivantes.
    int score = 0;
    vector<Position> validMoves = board.validMoves(currentPlayerColor);
    vector<Position> validOpponentMoves = board.validMoves(Game::oppositeColor(currentPlayerColor));
    bool currentCanPlay = (validMoves.size()!=0);
    bool otherCanPlay = (validOpponentMoves.size()!=0);
    bool endOfGame = (!(currentCanPlay || otherCanPlay));
    if ((turn > limitTurn) || (endOfGame)) {
        score = calcBoardScore(board,turn,endOfGame,currentPlayerColor);
    } else {
        if (!currentCanPlay) {
			score = getBoardScore(board, turn, limitTurn, Game::oppositeColor(currentPlayerColor)); //if can't play, make the opponent player play (don't increment turn)
		}else{
			int newTurn = turn+1;
			vector<int> scoreList;
			Board boardCopy;
			Position pos;
			for (int i = 0; i<validMoves.size(); i++) {
				pos = validMoves[i];
				boardCopy = board;
				boardCopy.setContentAt(pos, currentPlayerColor);
				boardCopy.switchCells(currentPlayerColor, pos);
				score = getBoardScore(boardCopy, newTurn, limitTurn, Game::oppositeColor(currentPlayerColor));
				scoreList.push_back(score);
			}
			//int meanOfList = mean(scoreList);
			if (currentPlayerColor==playerColor) {
				//max
				score = maxElem(scoreList);
			} else {
				//min
				score = minElem(scoreList);
			}
		}
    }
    return score;
}

int AIPlayer::mean(vector<int> v) {
	float sum = 0;
	int cardinal = v.size();
	for (int i = 0; i<cardinal; i++) {
		int elem = v[i];
		sum+=elem;
	}
	return (sum/cardinal);
}

int AIPlayer::minElem(vector<int> v) {
	int minimum = 1000000;
	int cardinal = v.size();
	for (int i = 0; i<cardinal; i++) {
		int elem = v[i];
		if (elem<minimum) {
			minimum = elem;
		}
	}
	return minimum;
}

int AIPlayer::maxElem(vector<int> v) {
	int maximum = -1000000;
	int cardinal = v.size();
	for (int i = 0; i<cardinal; i++) {
		int elem = v[i];
		if (elem>maximum) {
			maximum = elem;
		}
	}
	return maximum;
}

int AIPlayer::calcBoardScore(Board& board, int turn, bool endOfGame, cellContent currentPlayerColor) {
	///TODO : coin(), parite(), grouper au centre() (début), peu de possiblilités adverses (surtout fin), 
	
	
	//résultats: 19-45 (noir algo vs blanc algo) 21-43(noir algo vs blanc sans algo) 53-11 (H vs sans algo) 32-32 (humain vs algo)
	int score = 0;
	
	int playerScore = board.getScore(playerColor);
	int opponentScore = board.getScore(this->getOpponentColor());
	
	if (endOfGame) { //si le jeu est fini, on check seulement si on a gagné, perdu ou fait match nul
		if (playerScore>opponentScore) {
			//On a gagné
			score=10000;
		} else if (playerScore==opponentScore) {
			//Match nul
			score=0;
		} else {
			//On a perdu
			score=-10000;
		}
	} else {
		//pour la parité :
		//si on joue dans un tour pair (donc bien parti pour jouer en dernier quand tour=60)
		if (parite(turn,currentPlayerColor)) {
			score+=100;
		}
		
		int AICorners=board.cornerNumber(playerColor);
		int opponentCorners=board.cornerNumber(this->getOpponentColor());
		score+=AICorners*800;
		score-=opponentCorners*800;
	}
	
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
    /// si tour<20 {
    ///enlever points par pions au bord
	///}
	
	///fonction moves permanents
    
    ///jouer peu en frontière de pions adverses
    
    if (playerColor==White) {
		score=0;
	}/*
	if (playerColor==Black) {
		score=0;
	}*/
    
	//score = 10000*(board.getScore(playerColor)); //Factor 10000 to handle the mean of an int
	
    
    //cout << "\nscore = " << score << endl;
    //IO::boardDisplay(board);
    return score;
}

bool AIPlayer::parite(int turn, cellContent currentPlayerColor) {
	bool parite = false;
	if (((turn%2)==0)==(currentPlayerColor==playerColor)) { // vrai soit si tour pair joué par notre IA, soit si tour impair joué par l'autre IA
		parite = true;
	}
	return parite;
}




