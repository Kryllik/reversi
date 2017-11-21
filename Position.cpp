#include "Position.h"
#include <iostream>

using std::string;



/*!
 *  \brief default Position's consructor
 *
 *  Construct a position with x=0 and y=0
 *
 *  \param none
 *  \return none
 */
Position::Position(){
	x = 0;
	y = 0;
}

/*!
 *  \brief Position's consructor with non-default values
 *
 *  Construct a position with given x and y
 *
 *  \param x : position's x value
 *  \param y : position's y value
 *  \return none
 */
Position::Position(const int x, const int y){
	this->x = x;
	this->y = y;
}

/*!
 *  \brief move current position by xAdd, yAdd
 *
 *  \param xAdd : position's x increment value (can be < 0)
 *  \param yAdd : position's y increment value (can be < 0)
 *  \return none
 */
void Position::increment(const int xAdd, const int yAdd) {
	x+=xAdd;
	y+=yAdd;
}

/*!
 *  \brief create a new position instance translated from this by (xAdd, yAdd)
 *
 *  \param xAdd : position's x increment value (can be < 0)
 *  \param yAdd : position's y increment value (can be < 0)
 *  \return a new Position instance
 */
Position Position::incrementedBy(const int xAdd, const int yAdd) const {
	return Position(x+xAdd,y+yAdd);
}

/*!
 *  \brief check if our position is valid
 *
 *  \param none
 *  \return true if our position is valid
 */
bool Position::isValid() const {
	//Check if the position is in the Board
	bool validBool = false;
	if (x>=1 && x<=8 && y>=1 && y<=8) {
		validBool = true;
	}
	return validBool;
}

/*!
 *  \brief return a string representation of our position
 *
 *  \param none
 *  \return a 2-char string [a-h][1-8]
 */
string Position::toString() const {
	int xInt = this->getX()+'a'-1;
	string xString;
	xString = (char) xInt;
	string yString = std::to_string(this->getY());
	return xString+yString;
}

/*!
 *  \brief static function to create a Position instance from a string
 *
 *  \param a string that should be a 2-char wide [a-h][1-8]
 *  \return a new Position instance
 */
Position Position::positionFromString(string s) {
	Position pos;
	if (s.size() != 2) {
		pos = Position(0,0);
	} else {
		int posX = s[0]-'a'+1;
		char posYChar = s[1];
		int posY = posYChar-'0';
		pos = Position(posX,posY);
	}
	return pos;
}


/*!
 *  \brief get the X of the Position
 *
 *  \param none
 *  \return this.x
 */
int Position::getX() const {
	return x;
}

/*!
 *  \brief get the Y of the Position
 *
 *  \param none
 *  \return this.y
 */
int Position::getY() const {
	return y;
}
