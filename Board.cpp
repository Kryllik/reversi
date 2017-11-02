//implémente une matrice du tableau de jeu et les fonctions nécessaires pour l'afficher. Fonctions permettant de vérifier la validité d'un coup ??? (dispose de tout le tableau donc pratique..)
#include <string>
#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>     // std::cout

#include "Board.h"
//#include "Position.h"
//#include "Cell.h"
using namespace std;


Board::Board(){
	cout<< "constructeur de Board" << endl;
	initBoard();
}
Board::~Board(){
	cout<<"destruction d'un Board"<< endl;
}


void Board::initBoard(){
	cout << "DEBUT initialisation du Board" << endl;
	for(unsigned int line = 1; line <= BOARD_SIZE; line++){
		for(unsigned int col =1; col<= BOARD_SIZE; col++){
			setContentAt(Position(line,col), Empty); //Remplis l'ensemble du tableau avec des cases vides
		}
	}
		//Initialise les positions initiales.
	setContentAt(Position(4,4),White);
	setContentAt(Position(5,5),White);	
	setContentAt(Position(4,5),Black);
	setContentAt(Position(5,4),Black);
	
	cout << "FIN initialisation du Board" << endl;
}


cellContent Board::getContentAt(Position pos){
	return (this->array[pos.getX()-1][pos.getY()-1]).getContent();
}

void Board::setContentAt(Position pos, cellContent content){
	(this->array[pos.getX()-1][pos.getY()-1]).setContent(content);
}

void Board::switchContentAt(Position pos, cellContent content){
	(this->array[pos.getX()-1][pos.getY()-1]).switchContent(content);
}



