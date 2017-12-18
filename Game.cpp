
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
		playerBlack = new AIPlayer(blackColor,3);
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
		playerWhite = new AIPlayer(whiteColor,3);
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
		//		if (turn==30) {
//			cout << "d1" << endl;
//		}
//		cout << pos.toString() << endl;
		if (pos.isValid()) {
			/* update board by switching cells affected by player's move */
			board->setContentAt(pos, currentPlayer->getColor());
			board->switchCells(currentPlayer->getColor(), pos);
		}
		/* display board info */
		IO::display(*board, *currentPlayer, pos);
//		if (turn==30) {
//			cout << "d2" << endl;
//		}

		opponentPlayer->giveMove(pos);

		if (currentPlayer == playerWhite){
			currentPlayer = playerBlack;
			opponentPlayer = playerWhite;
		} else { 
			currentPlayer = playerWhite;
			opponentPlayer = playerBlack;
		}
		/* TODO : press enter to continue */
//		cout << "Press Enter to Continue";
//		cin.ignore();
	}


	pair <int,int> score = board->getScore();
	int blackScore = score.first;
	int whiteScore = score.second;
	
	IO::displayScore(blackScore,whiteScore);
	delete playerWhite;
	delete playerBlack;
}

/*!
 * MVE : What is it for ? couldn't be replaced by player->getOponentColor() ??
 * @param color
 * @return
 */
cellContent Game::oppositeColor(cellContent color) {
	if (color == Black)
		return cellContent::White;
	else
		return cellContent::Black;
}








