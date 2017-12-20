#include "Position.h"
#include <iostream>

using std::string;



/*!
 *  @brief default Position's constructor
 *
 *  Construct a position with x=0 and y=0 which is invalid as
 *  position for first row:first column is 1:1
 *  position 0:0 is reserved as 'user cannot play during this turn'
 *
 *  @param none
 *  @return none
 */
Position::Position(){
	x = 0;
	y = 0;
}

/*!
 *  @brief Position's constructor with non-default values
 *
 *  Construct a position with given x and y
 *
 *  @param x : position's x value
 *  @param y : position's y value
 *  @return none
 */
Position::Position(const int x, const int y){
	this->x = x;
	this->y = y;
}

/*!
 *  @brief move current position by xAdd, yAdd
 *
 *  @param xAdd : position's x increment value (can be < 0)
 *  @param yAdd : position's y increment value (can be < 0)
 *  @return none
 */
void Position::increment(const int xAdd, const int yAdd) {
	x+=xAdd;
	y+=yAdd;
}

/*!
 *  @brief create a new position instance translated from this by (xAdd, yAdd)
 *
 *  @param xAdd : position's x increment value (can be < 0)
 *  @param yAdd : position's y increment value (can be < 0)
 *  @return a new Position instance
 */
Position Position::incrementedBy(const int xAdd, const int yAdd) const {
	return Position(x+xAdd,y+yAdd);
}

/*!
 *  @brief check if our position is valid
 *  0:0 (user cannot play during this turn) is considered as an invalid position
 *
 *  @param none
 *  @return true if our position is valid
 */
bool Position::isValid() const {
	return  (x>=1 && x<=8 && y>=1 && y<=8) ; /* first row:first column is 1:1 */
}

/*!
 *  @brief return a string representation of our position
 *
 *  @param none
 *  @return a 2-char string [a-h][1-8]
 */
string Position::toString() const {
	if (this->getX()==0 && this->getY()==0) return "OO";
	int xInt = this->getX()+'a'-1;
	string xString;
	xString = (char) xInt;
	string yString = std::to_string(this->getY());
	return xString+yString;
}

/*!
 *  @brief static function to create a Position instance from a string
 *
 *  @param a string that should be a 2-char wide [a-h][1-8]
 *  @return a new Position instance
 */
Position Position::positionFromString(string s, bool &ok) {
	Position pos;
	ok=true;
	if (s.size() != 2) {
		pos = Position(9,9); /* position is incorrect */
		ok = false;
	} else {

		if (s[0]=='O' && s[1] == 'O') {
			pos = Position(0,0);
		} else {
			if ( (s[0]<'a' || s[0]>'h') ||
					(s[1]<'1' || s[1]>'8') ) {
				pos =  Position(9,9); /* position is incorrect */
				ok = false;
			} else {
				int posX = s[0]-'a'+1; /* first row:first column is 1:1 */
				char posYChar = s[1];
				int posY = posYChar-'0';
				pos = Position(posX,posY);
			}
		}

	}
	return pos;
}



