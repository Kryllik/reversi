
#include <stdio.h>
#include "Game.h"
#include "IO.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "FilePlayer.h"
#include "AIPlayer.h"

using namespace std;

/*!
 * The constructor of our game. The two player's type are given as parameter
 * Will construct the board and the players
 * @param player1
 * @param player2
 */
Game::Game(char player1, char player2)  {
	cout << "Bienvenue dans ce super jeu !" << endl<< endl;
	cout << "plateau initial : " << endl << endl;
	Board *board = new Board(); //Create a new board and init it.
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

/*!
 * destructor of the game
 */
Game::~Game() {
	delete board;
}

/*!
 * game playing loop. Loops until game is finished
 */
void Game::gameStart(){
	Position pos;			 	/* The position selected by the current player */

	/* Display first turn info */
	IO::displayFirstTurn(*board);

	/* Initialize current player and opponentPlayer. We always start with blackPlayer active */
	Player *currentPlayer = playerBlack;
	Player *opponentPlayer= playerWhite;

	/* Loop while at least one player can player */
	while (not board->isGameOver()) {
		IO::displayWhoPlays(*currentPlayer, *board);

		pos = currentPlayer->getMove(*board); /* *this needed to validate the move (need to check if the given position is valid for the current board) */

		if (pos.isValid()) {
			/* update board by switching cells affected by player's move */
			board->setContentAt(pos, currentPlayer->getColor());
			board->switchCells(currentPlayer->getColor(), pos);
		}
		/* display board info */
		IO::display(*board, *currentPlayer, pos);

		opponentPlayer->giveMove(pos);

		if (currentPlayer == playerWhite){
			currentPlayer = playerBlack;
			opponentPlayer = playerWhite;
		} else { 
			currentPlayer = playerWhite;
			opponentPlayer = playerBlack;
		}
		/* uncomment next two lines if you want the user to press enter to continue */
//		cout << "\r\n >>> Press Enter to Continue";
//		cin.ignore();
	}


	pair <int,int> score = board->getScore();
	int blackScore = score.first;
	int whiteScore = score.second;
	
	IO::displayScore(blackScore,whiteScore);
	delete playerWhite;
	delete playerBlack;
}
