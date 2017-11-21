

#include "Position.h"
#include <iostream>
using std::string;

/* Should be better to have positions starting at 0 till 7 iso 1 till 8
 * 1. Allow to use unsigned it and compare <=7 to assert validity
 * 2. avoid all the +1 / -1 maths spread all over the code
 */

Position::Position(){
	x = 0;
	y = 0;
}

Position::Position(int x, int y){
	this->x = x;
	this->y = y;
}

void Position::increment(int xAdd, int yAdd) {
	x+=xAdd;
	y+=yAdd;
}

Position Position::incrementedBy(int xAdd, int yAdd) {
	return Position(x+xAdd,y+yAdd);
}


bool Position::isValid() {
	//Check if the position is in the Board
	bool validBool = false;
	if (x>=1 && x<=8 && y>=1 && y<=8) {
		validBool = true;
	}
	return validBool;
}

string Position::toString() {
	int xInt = this->getX()+'a'-1;
	string xString;
	xString = (char) xInt;
	string yString = std::to_string(this->getY());
	return xString+yString;
}


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

int Position::getX() {
	return x;
}

int Position::getY() {
	return y;
}
