
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
	playerBlack = new HumanPlayer(blackColor);
	//playerBlack = new FilePlayer(blackColor);
	playerWhite = new AIPlayer(whiteColor);
	//playerWhite = new FilePlayer(whiteColor);
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


void Game::switchCells(cellContent playerContent, Position pos){
	//cellContent opponentContent=otherPlayerColor(playerContent);
	//si i=-1,j=-1:diagonale en bas a gauche
	//si i=-1,j=0: a gauche
	//si i=-1,j=1:diagonale en haut a gauche
	//si i=0,j=-1: en bas
	//si i=0,j=0:rien
	//si i=0,j=1: en haut
	//si i=1,j=-1: diagonale en bas a droite
	//si i=1, j=0: a droite
	//si i=1, j=1: diagonale en haut a droite
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			//cellContent opponentContent=otherPlayerColor(playerContent);
			Position newPos= pos.incrementedBy(i,j);
			while(newPos.isValid() && board->getContentAt(newPos)!=playerContent && board->getContentAt(newPos)!=Empty){
				newPos=newPos.incrementedBy(i,j);
				//cout<<"content while"<< board->getContentAt(newPos)<<endl;
			}
			if (newPos.isValid() && board->getContentAt(newPos)==playerContent){
				if (j==0 && i==0){}
				else{
					int diffx=newPos.getX()-pos.getX();
					int diffy=newPos.getY()-pos.getY();
					Position switchPos=pos;
					if(diffy==0){//changement que en x
						for(int k=1;k<abs(diffx);k=k+1){
							switchPos.increment(i,0);
							board->switchContentAt(switchPos);
						}
					}
					else if (diffx==0){//changement que en y
						for(int l=1;l<abs(diffy);l=l+1){
							switchPos.increment(0,j);
							board->switchContentAt(switchPos);
							//switchCells(playerContent, switchPos);
						}
					}
					else if(diffx!=0 && diffy!=0){//changement des diagonales, diffy=diffx
						for(int m=1;m<abs(diffx);m=m+1){
							switchPos.increment(i,j);
							board->switchContentAt(switchPos);
							//switchCells(playerContent, switchPos);
						}
					}
				}
			}
		}
	}
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
			switchCells(currentPlayer->getColor(), pos);
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
	getScore();	
}

void Game::getScore() {
	int whiteScore = 0;
	int blackScore = 0;
	Position pos;
	for(unsigned int x = 1; x <= Board::BOARD_SIZE; x++){
		for(unsigned int y = 1; y<= Board::BOARD_SIZE; y++){
			pos = Position(x,y);
			cellContent content = board->getContentAt(pos);
			if (content == Black) {
				blackScore++;
			}
			if (content == White) {
				whiteScore++;
			}
		}
	}
	IO::displayScore(blackScore,whiteScore);
}
	









