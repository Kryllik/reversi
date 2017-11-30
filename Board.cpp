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
	for(unsigned int line = 1; line <= BOARD_SIZE; line++){
		for(unsigned int col = 1; col<= BOARD_SIZE; col++){
			setContentAt(Position(line,col), Empty); //Remplis l'ensemble du tableau avec des cases vides
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

int Board::getScore(cellContent color) {
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
	

