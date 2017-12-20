#include "Player.h"


/*!
 *  @brief Player's constructor
 *
 *  Construct a player of the given color
 *
 *  @param color : the player's color
 */
Player::Player(const cellContent color){
	playerColor = color;
}

/*!
 *  @brief Player's destructor
 *
 *  @param none
 */
Player::~Player() {

}

/*!
 *  @brief get the color of the Player
 *
 *  @param none
 *  @return the color of the player
 */
cellContent Player::getColor() const {
	return this->playerColor;
}

/*!
 *  @brief get a string representing the color of the Player
 *
 *  @param none
 *  @return a string "Noir" or "Blanc"
 */
string Player::toString() const {
	return (this->playerColor==Black?"Noir":"Blanc");
}

/*!
 *  @brief get the color of the opponent
 *
 *  @param none
 *  @return the color of the opponent
 */
cellContent Player::getOpponentColor() const {
	if(this->playerColor == Black)
		return cellContent::White;
	else
		return cellContent::Black;
}

/*!
 *  @brief virtual function that will be called when the player next move is requested
 *
 *  @param the current game that can be used to validate the player's move before returning it
 *  @return the position where the player move
 */
Position Player::getMove(Board gameBoard) {
	return Position(0,0);
}

/*!
 *  @brief virtual function that tells to the player which move the opponent did
 *
 *  @param pos : the position where the opponent just moved
 *  @return none
 */
void Player::giveMove(Position pos){}
