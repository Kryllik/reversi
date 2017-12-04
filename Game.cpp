
#include <stdio.h>
#include "Game.h"
#include "IO.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "FilePlayer.h"
#include "AIPlayer.h"



Game::Game(char player1, char player2)  {
	cout << "Bienvenue dans ce super jeu !" << endl<< endl;
	cout << "plateau initial : " << endl << endl;
	Board *board = new Board(); //Cree un nouveau Board et l'initialise. Renvoie un pointeur.
	this->board = board;
	cellContent blackColor = Black;
	cellContent whiteColor = White;
	if(player1 == 'H'){
		playerBlack = new HumanPlayer(blackColor);
	}
	else if(player1 == 'F'){
		playerBlack = new FilePlayer(blackColor);
	}
	else if(player1 == 'A'){
		playerBlack = new AIPlayer(blackColor);
	}
	else{
		cout << "ERREUR DE CONFIGURATION DES JOUEURS " << endl; //sécurité, mais ne devrait jamais être déclenché, après la vérif dans IO
	}
	if(player2 == 'H'){
		playerWhite = new HumanPlayer(whiteColor);
	}
	else if(player2 == 'F'){
		playerWhite = new FilePlayer(whiteColor);
	}
	else if(player2 == 'A'){
		playerWhite = new AIPlayer(whiteColor);
	}
	else{
		cout << "ERREUR DE CONFIGURATION DES JOUEURS " << endl;
	}
}

Game::~Game() {
	delete board;
}


bool Game::validMovesExist(cellContent playerContent) {
	bool res = true;
	vector<Position> v = validMoves(playerContent);
	if (v.size() == 0) {
		res = false;
	}
	return res;
}

vector<Position> Game::validMoves(cellContent playerContent, Board* board) const {
	vector<Position> v;
	Position pos;
	if (board == NULL) {
		board = this->board;
	}
	for (int i = 1; i<=Board::BOARD_SIZE; i++) {
		for (int j = 1; j<=Board::BOARD_SIZE; j++) {
			pos = Position(i,j);
			if (isValidMove(playerContent,pos,board)) {
				v.push_back(pos);
			}
		}
	}
	return v;
}

bool Game::isValidMove(cellContent playerContent, Position pos, Board* board) const {
	if (board == NULL) {
		board = this->board;
	}
	if (board->getContentAt(pos) == Empty) {
		for (int x=-1;x<=1;x++) {
			for (int y=-1;y<=1;y++) {
				if (!(x==0 && y==0)) {
					if (isSwitchInDirection(pos,x,y,playerContent,board)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Game::isSwitchInDirection(Position pos,int x, int y, cellContent playerContent, Board* board) const {
	Position newPos = pos.incrementedBy(x,y);
	if (newPos.isValid()) {
		cellContent newContent = board->getContentAt(newPos);
		if (newContent!=playerContent && newContent != Empty) {
			while (true) {
				newPos.increment(x,y);
				if (newPos.isValid()) {
					newContent = board->getContentAt(newPos);
					if (newContent==Empty) {
						break;
					}
					if (newContent == playerContent) {
						return true;
					}
				} else {
					break;
				}
			}
		}
	}
	return false;
}

void Game::gameStart(){
	bool currentPlayerCanPlay; 	/* Can the current player play ? */
	Position pos;			 	/* The position selected by the current player */
	int turn = 1;

	/* Display first turn info */
	IO::displayFirstTurn(*board,*this);

	/* Initialize current player and opponentPlayer. We always start with blackPlayer active */
	Player *currentPlayer = playerBlack;
	Player *opponentPlayer= playerWhite;

	/* Loop while at least one player can player */
	while ((currentPlayerCanPlay = validMovesExist(currentPlayer->getColor())) || validMovesExist(currentPlayer->getOpponentColor())) {
		/* We should always ask user his choice, even if he can't play (in this case he will enter '00'
		 * Otherwise FilePlayer will loose sync. filePlayer will give '00' in its file if he can't play,
		 * so we must read this !
		 * More over project specs §4.1 specifically says user must enter '00' if he must pass
		 */
		if (currentPlayerCanPlay){
			IO::displayWhoPlays(*currentPlayer, *this);
			
			pos = currentPlayer->getMove(*this, *board, turn); /* *this needed to validate the move (need to check if the given position is valid for the current board) */
			cout << pos.toString() << endl;
			/* update board by switching cells affected by player's move */
			board->setContentAt(pos, currentPlayer->getColor());
			board->switchCells(currentPlayer->getColor(), pos);
			/* display board info */
			IO::display(*board, *currentPlayer,*this, pos);
			turn++;
		} else {
			//TODO :: afficher 00
		}
		/* inform opponentplayer of the move player just made */
		if(currentPlayerCanPlay) 
			opponentPlayer->giveMove(pos);
		else 
			opponentPlayer->giveVoidMove();
		
		/* proceed with next player */
		if (currentPlayer == playerWhite){
			 currentPlayer = playerBlack;
			 opponentPlayer=playerWhite;
		} else { 
			currentPlayer = playerWhite;
			opponentPlayer=playerBlack;
		}
	}
	int blackScore = board->getScore(Black);
	int whiteScore = board->getScore(White);
	IO::displayScore(blackScore,whiteScore);
}











