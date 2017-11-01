/* Reversi Project - INFOH-304
 * membres du groupe : DESLYPERRE Clara, GOOSSENS Victor, MOREAU Lila, VERSTRAETEN Maxime
*/

//Main file of the game, includes main()

#include <stdio.h>
#include "Game.h"
#include "IO.h"

using namespace std;

Game::Game() {
	cout << "bienvenue dans ce super jeu" << endl;
	Board *board = new Board(); //Crée un nouveau Board et l'initialise. Renvoie un pointeur.
	board->display();
	this->board = board;
	
}

Game::~Game() {
	cout << "destruction d'un Game" << endl;
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

vector<Position> Game::validMoves(cellContent playerContent) {
	vector<Position> v;
	Position pos;
	for (int i = 1; i<=8; i++) {
		for (int j = 1; j<=8; j++) {
			pos = Position(i,j);
			if (isValidMove(playerContent,pos)) {
				v.push_back(pos);
			}
		}
	}
	return v;
}

bool Game::isValidMove(cellContent playerContent, Position pos) const {
	//cout << "\nTest if valid move - " << pos.toString() << endl;
	if (board->getContentAt(pos) == Empty) {
		//cout << "Condition 1 ok, it's empty" << endl;
		//test all 8 directions
		for (int x=-1;x<=1;x++) {
			for (int y=-1;y<=1;y++) {
				if (!(x==0 && y==0)) {
					if (winnerMoveAtDirection(pos,x,y,playerContent)) {
						//cout << pos.toString() << " is valid" << endl;
						return true;
					}
				}
			}
		}
		//cout << "No win direction" << endl;
	} else {
		//cout << "Condition 1 not ok, not empty" << endl;
	}
	return false;
}

bool Game::winnerMoveAtDirection(Position pos,int x, int y, cellContent playerContent) const {
	//cout << "Test of direction x:" << x << " y:" << y << endl;
	Position newPos = pos.incrementedBy(x,y);
	if (newPos.isValid()) {
		cellContent newContent = board->getContentAt(newPos);
		if (newContent!=playerContent && newContent != Empty) {
			//cout << "Condition 2 ok, first cell in direction x:" << x << " y:" << y << " is opposite color" << endl;
			while (true) {
				newPos.increment(x,y);
				newContent = board->getContentAt(newPos);
				if (newContent==Empty || !newPos.isValid()) {
					break;
				}
				if (newContent == playerContent) {
					//cout << "Condition 3 ok, cell at position " << newPos.toString() << " is same color" << endl;
					return true;
				}
			}
		}
	}
	return false;
}

cellContent Game::playerContentSwitch(cellContent playerContent){
	if(playerContent == Black){
		playerContent = White;
	}
	else{
		playerContent = Black;
	}
	return playerContent;
}


void Game::gameStartPvP(){
	bool currentPlayerCanPlay;
	cellContent currentPlayerContent = Black;
	while(currentPlayerCanPlay = validMovesExist(currentPlayerContent) || validMovesExist(playerContentSwitch(currentPlayerContent))){ //sortie du jeu si aucun mouvement n'est possible pour les 2 joueurs
		if(currentPlayerCanPlay){
			Position pos = IO::moveInput(*this, currentPlayerContent);
			board->setContentAt(pos, currentPlayerContent);
			IO::display(*board, currentPlayerContent);
			currentPlayerContent=playerContentSwitch(currentPlayerContent);
			}
		else{
			currentPlayerContent=playerContentSwitch(currentPlayerContent);
			Position pos = IO::moveInput(*this, currentPlayerContent);
			IO::display(*board, currentPlayerContent);
			board->setContentAt(pos, currentPlayerContent);
		}
		
	}
	
}


	









