/* ??? implémente une matrice du tableau de jeu et les fonctions nécessaires pour l'afficher.
 * ??? Fonctions permettant de vérifier la validité d'un coup ??? (dispose de tout le tableau donc pratique..)
 *
 */

#include <iostream>     // std::cout

#include "Board.h"
using namespace std;


Board::Board(){
	initBoard();
}

Board::~Board(){
	
}


void Board::initBoard(){
	cout << "DEBUT initialisation du Board" << endl;
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
	
	cout << "FIN initialisation du Board" << endl;
}


cellContent Board::getContentAt(Position pos){
	return (this->array[pos.getX()-1][pos.getY()-1]).getContent(); /* -1 ...*/
}

void Board::setContentAt(Position pos, cellContent content){
	(this->array[pos.getX()-1][pos.getY()-1]).setContent(content); /* -1 ...*/
}

void Board::switchContentAt(Position pos){
	(this->array[pos.getX()-1][pos.getY()-1]).switchContent(); /* -1 ...*/
}



