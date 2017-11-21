//classe fille de Player, contient les fonctions et attributs propre à un joueur Humain.

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(cellContent color) : Player(color){
}

Position HumanPlayer::getMove(Game & game){
	//cout << "MAKEMOVE for" << playerColor << endl;
	Position pos = IO::moveInput(game, playerColor);
	return pos;
}


void HumanPlayer::giveMove(Position pos){
}



void HumanPlayer::giveVoidMove(){
}
