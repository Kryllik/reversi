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
	//IO::displayScore(blackScore,whiteScore);
	if(color == White) return whiteScore;
	else return blackScore;
}
	

