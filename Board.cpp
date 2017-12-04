#include <iostream>     // std::cout

#include "Board.h"
#include "IO.h"

using namespace std;


Board::Board(){
	initBoard();
}

Board::~Board(){
	
}


void Board::initBoard(){
	for(unsigned int x = 1; x <= BOARD_SIZE; x++){
		for(unsigned int y = 1; y<= BOARD_SIZE; y++){
			setContentAt(Position(x,y), Empty); //Remplis l'ensemble du tableau avec des cases vides
		}
	}
	
	//Initialise les positions initiales.
	setContentAt(Position(4,4),White);
	setContentAt(Position(5,5),White);	
	setContentAt(Position(4,5),Black);
	setContentAt(Position(5,4),Black);
	
}


cellContent Board::getContentAt(const Position pos) const{
	return (this->array[pos.getX()-1][pos.getY()-1]).getContent();
}

void Board::setContentAt(const Position pos, const cellContent content){
	(this->array[pos.getX()-1][pos.getY()-1]).setContent(content); 
}

void Board::switchContentAt(const Position pos){
	(this->array[pos.getX()-1][pos.getY()-1]).switchContent(); 
}

int Board::getScore(cellContent color) const {
	int whiteScore = 0;
	int blackScore = 0;
	Position pos;
	for(unsigned int x = 1; x <= Board::BOARD_SIZE; x++){
		for(unsigned int y = 1; y<= Board::BOARD_SIZE; y++){
			pos = Position(x,y);
			cellContent content = this->getContentAt(pos);
			if (content == Black) {
				blackScore++;
			}
			if (content == White) {
				whiteScore++;
			}
		}
	}
	if (color == White) 
		return whiteScore;
	else 
		return blackScore;
}

int Board::cornerNumber(cellContent color) const {
	int corners=0;
	if (this->getContentAt(Position(1,1))==color) {
		corners++;
	}
	if (this->getContentAt(Position(1,Board::BOARD_SIZE))==color) {
		corners++;
	}
	if (this->getContentAt(Position(Board::BOARD_SIZE,1))==color) {
		corners++;
	}
	if (this->getContentAt(Position(Board::BOARD_SIZE,Board::BOARD_SIZE))==color) {
		corners++;
	}
}

bool Board::validMovesExist(cellContent playerContent) {
	bool res = true;
	vector<Position> v = validMoves(playerContent);
	if (v.size() == 0) {
		res = false;
	}
	return res;
}

vector<Position> Board::validMoves(cellContent playerContent) const {
	vector<Position> v;
	Position pos;
	for (int i = 1; i<=Board::BOARD_SIZE; i++) {
		for (int j = 1; j<=Board::BOARD_SIZE; j++) {
			pos = Position(i,j);
			if (isValidMove(playerContent,pos)) {
				v.push_back(pos);
			}
		}
	}
	return v;
}

bool Board::isValidMove(cellContent playerContent, Position pos) const {
	if (this->getContentAt(pos) == Empty) {
		for (int x=-1;x<=1;x++) {
			for (int y=-1;y<=1;y++) {
				if (!(x==0 && y==0)) {
					if (isSwitchInDirection(pos,x,y,playerContent)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Board::isSwitchInDirection(Position pos,int x, int y, cellContent playerContent) const {
	Position newPos = pos.incrementedBy(x,y);
	if (newPos.isValid()) {
		cellContent newContent = this->getContentAt(newPos);
		if (newContent!=playerContent && newContent != Empty) {
			while (true) {
				newPos.increment(x,y);
				if (newPos.isValid()) {
					newContent = this->getContentAt(newPos);
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

void Board::switchCells(cellContent playerContent, Position pos){
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
			while(newPos.isValid() && getContentAt(newPos)!=playerContent && getContentAt(newPos)!=Empty){
				newPos=newPos.incrementedBy(i,j);
				//cout<<"content while"<< board->getContentAt(newPos)<<endl;
			}
			if (newPos.isValid() && getContentAt(newPos)==playerContent){
				if (j==0 && i==0){}
				else{
					int diffx=newPos.getX()-pos.getX();
					int diffy=newPos.getY()-pos.getY();
					Position switchPos=pos;
					if(diffy==0){//changement que en x
						for(int k=1;k<abs(diffx);k=k+1){
							switchPos.increment(i,0);
							switchContentAt(switchPos);
						}
					}
					else if (diffx==0){//changement que en y
						for(int l=1;l<abs(diffy);l=l+1){
							switchPos.increment(0,j);
							switchContentAt(switchPos);
							//switchCells(playerContent, switchPos);
						}
					}
					else if(diffx!=0 && diffy!=0){//changement des diagonales, diffy=diffx
						for(int m=1;m<abs(diffx);m=m+1){
							switchPos.increment(i,j);
							switchContentAt(switchPos);
							//switchCells(playerContent, switchPos);
						}
					}
				}
			}
		}
	}
}
	

