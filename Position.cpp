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
 *  @brief return a string representation of our position
 *
 *  @param none
 *  @return a 2-char string [a-h][1-8]
 */
string Position::toString() const {
	if (this->getX()==0 && this->getY()==0) return "00";
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

		if (s[0]=='0' && s[1] == '0') {
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
