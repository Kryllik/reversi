//implémente une matrice du tableau de jeu et les fonctions nécessaires pour l'afficher. Fonctions permettant de vérifier la validité d'un coup ??? (dispose de tout le tableau donc pratique..)
#include <string>
#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>     // std::cout

#include "Board.h"
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
	for(unsigned int line = 0; line < BOARD_SIZE; line++){
		for(unsigned int col =0; col< BOARD_SIZE; col++){
			setContentAt(Position(line,col), Empty); //Remplis l'ensemble du tableau avec des cases vides
		}
	}
		//Initialise les positions initiales.
	setContentAt(Position(3,3),Black);
	setContentAt(Position(4,4),Black);	
	setContentAt(Position(3,4),White);
	setContentAt(Position(4,3),White);
	
	cout << "FIN initialisation du Board" << endl;
}

void Board::Display(){
	cout<<"       a b c d e f g h  " << endl; //Impression des numéros de ligne
	for(unsigned int line =0; line < 8; line++){
		cout<< "     "<<(line+1)<< " "; // Impression des numéros de colonne
		for(unsigned int col = 0; col <8; col++){
			switch(getContentAt(Position(line,col))){
				case Empty: cout << ". "; break;
				case Black: cout << "X "; break;
				case White: cout << "O "; break;
			}
		}
		cout << (line+1) << endl;
	}
	cout<<"       a b c d e f g h  "<< endl;
}



cellContent Board::getContentAt(Position pos){
	return (this->array[pos.line][pos.col]).getContent();
}

void Board::setContentAt(Position pos, cellContent content){
	(this->array[pos.line][pos.col]).setContent(content);
}



