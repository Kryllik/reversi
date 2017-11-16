
#include <stdio.h>
#include "Game.h"
#include "IO.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "FilePlayer.h"

using namespace std;


Game::Game()  {
	cout << "bienvenue dans ce super jeu" << endl;
	Board *board = new Board(); //Crée un nouveau Board et l'initialise. Renvoie un pointeur.
	this->board = board;
	cellContent blackColor = Black;
	cellContent whiteColor = White;
	playerBlack = new HumanPlayer(blackColor);
	//playerWhite = new HumanPlayer(whiteColor);
	playerWhite = new FilePlayer(whiteColor);
	cout << "impression couleur " << playerBlack->getColor() << endl;
	
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

vector<Position> Game::validMoves(cellContent playerContent) const {
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

void Game::switchCells(cellContent playerContent, Position pos){
	cellContent opponentContent=playerContentSwitch(playerContent);
	cout << "switchcells" << endl;
	//si i=-1,j=-1:diagonale en bas a gauche
	//si i=-1,j=0: a gauche
	//si i=-1,j=1:diagonale en haut a gauche
	//si i=0,j=-1: en bas
	//si i=0,j=0:rien
	//si i=0,j=1: en haut
	//si i=1,j=-1: diagonale en bas a droite
	//si i=1, j=0: a droite
	//si i=1, j=1: diagonale en haut a droite
	for(int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			cellContent opponentContent=playerContentSwitch(playerContent);
			cout << " i " << i << " j " << j << endl;
			cout <<"pos"<<pos.toString()<<endl;
			Position newPos= pos.incrementedBy(i,j);
			cout <<"newpos"<<newPos.toString()<<endl;
			while(board->getContentAt(newPos)!=playerContent && board->getContentAt(newPos)!=Empty && newPos.isValid()){
				newPos=newPos.incrementedBy(i,j);
				cout << " i " << i << " j " << j << endl;
				cout <<"newpos while"<<newPos.toString()<<endl;
				cout<<"content while"<< board->getContentAt(newPos)<<endl;
				
			}
			if (board->getContentAt(newPos)==playerContent){
				if (j==0 && i==0){}
				else{
					cout << "if black next to white" << endl;
					int diffx=newPos.getX()-pos.getX();
					cout << "diffx"<< diffx<< endl;
					int diffy=newPos.getY()-pos.getY();
					cout << "diffy"<< diffy<< endl;
					Position switchPos=pos;
					if(diffy==0){//changement que en x
						for(int k=1;k<abs(diffx);k=k+1){
							cout <<"switchpos"<<switchPos.toString()<<endl;
							cout<<"k "<<k<<endl;
							switchPos.increment(i,0);
							cout <<"switchpos"<<switchPos.toString()<<endl;
							cout <<"switchx"<<endl;
							cout << "switch content at " << switchPos.toString() << endl;
							cout<<"content at "<< board->getContentAt(switchPos)<<endl;
							board->switchContentAt(switchPos,opponentContent);
							cout<<"content at "<< board->getContentAt(switchPos)<<endl;
						}
					}
					else if (diffx==0){//changement que en y
						for(int l=1;l<abs(diffy);l=l+1){
							cout<<"switchyp"<<endl;
							switchPos.increment(0,j);
							board->switchContentAt(switchPos,opponentContent);
							//switchCells(playerContent, switchPos);
						}
					}
					else if(diffx!=0 && diffy!=0){//changement des diagonales, diffy=diffx
						for(int m=1;m<abs(diffx);m=m+1){
							cout<<"switchdiag"<<endl;
							switchPos.increment(i,j);
							board->switchContentAt(switchPos,opponentContent);
							//switchCells(playerContent, switchPos);
							}
						}
					}
				}
			}
		}
	}

void Game::gameStartPvP(){
	IO::displayFirstTurn(*board,*this);
	bool currentPlayerCanPlay;
	Player *currentPlayer = playerBlack;
	Player *opponentPlayer= playerWhite;
	cout << "current player : " << playerBlack << endl;
	Position pos;
	while(currentPlayerCanPlay = validMovesExist(currentPlayer->getColor()) ||
				validMovesExist(currentPlayer->getOpponentColor()))
				{ //sortie du jeu si aucun mouvement n'est possible pour les 2 joueurs
		if(currentPlayerCanPlay){
			//Position pos = IO::moveInput(*this, currentPlayerContent);
			pos = currentPlayer->getMove(*this);
			cout << "playerBLACK " << playerBlack->getColor() << endl;
			board->setContentAt(pos, currentPlayer->getColor());
			cout << "before switch" << endl;
			switchCells(currentPlayer->getColor(), pos);
			cout << "after switch" << endl;
			IO::display(*board, currentPlayer->getColor(),*this, pos);
			
			//currentPlayerContent=playerContentSwitch(currentPlayerContent);
		}
		else{
			//TODO :: afficher 00
		}
		cout << currentPlayer << "zz" << endl;
		if(currentPlayerCanPlay) {cout << "blibli" << endl; opponentPlayer->giveMove(pos); }
		else opponentPlayer->giveVoidMove();
		
		cout << "after else" << endl;
		if(currentPlayer == playerWhite)
		{
			 currentPlayer = playerBlack;
			 opponentPlayer=playerWhite;
		}
		else { 
			currentPlayer = playerWhite;
			opponentPlayer=playerBlack;
		}
	}		

}


	









