//implémente une matrice du tableau de jeu et les fonctions nécessaires pour l'afficher. Fonctions permettant de vérifier la validité d'un coup ??? (dispose de tout le tableau donc pratique..)
#include <string>
#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>     // std::cout

#include "Board.h"
using namespace std;


Board::Board(){
	cout<< "constructeur de Board" << endl;
	initBoard();
}
Board::~Board(){
	cout<<"destruction d'un Board"<< endl;
}

void Board::initBoard(){
	cout << "initialisation du Board" << endl;
}


