
#include "Position.h"


Position::Position(){
	line = -1;
	col = -1;
}

Position::Position(int l, int c){
	line = l;
	col = c;
}

void Position::increment(int lAdd, int cAdd) {
	line+=lAdd;
	col+=cAdd;
}


bool Position::isValid() {
	//Check if the position is in the Board
	bool validBool = false;
	if (col>=0 && col<=7 && line>=0 && line<=7) {
		validBool = true;
	}
	return validBool;
}

int Position::getLine() {
	return line;
}

int Position::getCol() {
	return col;
}
