//Contient les attributs et fonctions des Players. C'est la classe mère des sous-classe HumanPlayer, FilePlayer, AIPlayer

#include "Player.h"

Player::Player(cellContent color){
	playerColor = color;
	cout << "player color " <<  this->getColor() << endl;

}




cellContent Player::getColor(){
	return this->playerColor;
}

cellContent Player::getOpponentColor(){
	if(this->playerColor == Black)
		return cellContent::White;
	else
		return cellContent::Black;
}

void Player::giveMove(Position pos){
	cout << "xx" << endl;

}

void Player::giveVoidMove(){
	cout << "yy" << endl;
}

