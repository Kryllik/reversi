/**
 * Base class of all *Player classes (HumanPlayer, FilePlayer, AIPlayer)
 *
 */
#include "Player.h"
/**
 * Construct a new Player instance of given color
 */
Player::Player(cellContent color){
	playerColor = color;
}

/**
 * return the color of the Player
 */
cellContent Player::getColor(){
	return this->playerColor;
}

/**
 * return the color of the oponent color
 */
cellContent Player::getOpponentColor(){
	if(this->playerColor == Black)
		return cellContent::White;
	else
		return cellContent::Black;
}

/**
 * virtual function that tells to the player which move the opponent did
 * can be overriden by child classes
 */
void Player::giveMove(Position pos){
}

/**
 * virtual function that tells to the player that the opponent could make a valid move
 * can be overriden by child classes
 */
void Player::giveVoidMove(){
}

