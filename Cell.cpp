//Classe contenant les attributs et fonctions pour les pions

#include "Cell.h"
using namespace std;

Cell::Cell(){
//	cout<< "constructeur de Cell" << endl;
}

Cell::~Cell(){
//	cout << "destructeur de Cell" << endl;
}

void Cell::setContent(cellContent content){
	this->content = content;
}
cellContent Cell::getContent(){
	return this->content;
}
