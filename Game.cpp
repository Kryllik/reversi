
#include <stdio.h>
#include "Game.h"
#include "IO.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "FilePlayer.h"
#include "AIPlayer.h"

using namespace std;


Game::Game()  {
	cout << "Bienvenue dans ce super jeu !" << endl<< endl;
	cout << "plateau initial : " << endl << endl;
	Board *board = new Board(); //CrÃ©e un nouveau Board et l'initialise. Renvoie un pointeur.
	this->board = board;
	cellContent blackColor = Black;
	cellContent whiteColor = White;
	playerBlack = new AIPlayer(blackColor);
	//playerBlack = new FilePlayer(blackColor);
	playerWhite = new AIPlayer(whiteColor);
	//playerWhite = new FilePlayer(whiteColor);
}

Game::~Game() {
	delete board;
}

void Game::gameStart(){
	bool currentPlayerCanPlay; 	/* Can the current player play ? */
	Position pos;			 	/* The position selected by the current player */
	int turn = 1;

	/* Display first turn info */
	IO::displayFirstTurn(*board);

	/* Initialize current player and opponentPlayer. We always start with blackPlayer active */
	Player *currentPlayer = playerBlack;
	Player *opponentPlayer= playerWhite;

	/* Loop while at least one player can player */
	while ((currentPlayerCanPlay = board->validMovesExist(currentPlayer->getColor())) || board->validMovesExist(currentPlayer->getOpponentColor())) {
		/* We should always ask user his choice, even if he can't play (in this case he will enter '00'
		 * Otherwise FilePlayer will loose sync. filePlayer will give '00' in its file if he can't play,
		 * so we must read this !
		 * More over project specs §4.1 specifically says user must enter '00' if he must pass
		 */
		if (currentPlayerCanPlay){
			IO::displayWhoPlays(*currentPlayer, *board);
			
			pos = currentPlayer->getMove(*board, turn); /* *this needed to validate the move (need to check if the given position is valid for the current board) */
			if (turn==30) {
				cout << "d1" << endl;
			}
			cout << pos.toString() << endl;
			/* update board by switching cells affected by player's move */
			board->setContentAt(pos, currentPlayer->getColor());
			board->switchCells(currentPlayer->getColor(), pos);
			/* display board info */
			IO::display(*board, *currentPlayer, pos);
			if (turn==30) {
				cout << "d2" << endl;
			}
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
			 opponentPlayer = playerWhite;
		} else { 
			currentPlayer = playerWhite;
			opponentPlayer = playerBlack;
		}
	}
	int blackScore = board->getScore(Black);
	int whiteScore = board->getScore(White);
	IO::displayScore(blackScore,whiteScore);
}











