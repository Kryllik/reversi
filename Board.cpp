#include <iostream>     // std::cout

#include "Board.h"

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



