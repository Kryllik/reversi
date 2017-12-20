#include <iostream>     // std::cout

#include "Board.h"
#include "IO.h"
#include <array>

using namespace std;


/*!
 * Construct a new board and initialize it
 */
Board::Board(){
	initBoard();
}


/*!
 * destruct a board
 */
Board::~Board(){
	
}

/*!
 * initialize a board : set all cell to empty and 4 center one to black/white as specified by game rules
 */
void Board::initBoard(){
	for(unsigned int x = 1; x <= BOARD_SIZE; x++){
		for(unsigned int y = 1; y<= BOARD_SIZE; y++){
			setContentAt(Position(x,y), Empty); //Remplis l'ensemble du tableau avec des cases vides
		}
	}
	
	//Initialise les positions initiales.
	setContentAt(Position(4,4),White);
	setContentAt(Position(5,5),White);	
	setContentAt(Position(4,5),Black);
	setContentAt(Position(5,4),Black);
}


/*!
 * Return the content of the cell at position pos
 * @param pos : the position of the cell of which to return content
 * @return the content of the cell at position pos
 */


/*!
 * set to content of the cell at position pos to content
 * @param pos : the position of the cell to update
 * @param content : the new content of the cell
 */
void Board::setContentAt(const Position pos, const cellContent content){
	(this->array[pos.getX()-1][pos.getY()-1]).setContent(content); 
}

/*!
 * switch (flip) the content of the cell at position pos. White cell become black and vice-versa
 * No check is done to ensure the cell is not empty
 * @param pos : the position of the cell to flip
 */
void Board::flipContentAt(const Position pos){
	(this->array[pos.getX()-1][pos.getY()-1]).switchContent(); 
}

/*!
 * calculate the score of both players and return them as a pair of int
 * @return a pair of int with the score of black player and the score of white player
 */
pair<int,int> Board::getScore() const {
	int whiteScore = 0;
	int blackScore = 0;
	Position pos;
	for(unsigned int x = 1; x <= Board::BOARD_SIZE; x++){
		for(unsigned int y = 1; y<= Board::BOARD_SIZE; y++){
			pos = Position(x,y);
			cellContent content = this->getContentAt(pos);
			if (content == Black) {
				blackScore++;
			}
			if (content == White) {
				whiteScore++;
			}
		}
	}
	return make_pair(blackScore, whiteScore);
}



/*!
 * check if there exist valid move for the given color
 * find all the valid moves and check if there is at least one
 * @param playerContent : the color of the player we are checking if valid move exists
 * @return true if there is at least one valid move for given player
 */
bool Board::validMovesExist(cellContent playerContent) const {
	bool res = true;
	vector<Position> v = validMoves(playerContent);
	if (v.size() == 0) {
		res = false;
	}
	return res;
}

/*!
 * find all valid move for the given color
 * for each cell in the board check if the given color can play there
 * @param playerContent : the color for which we find the valid moves
 * @return a vector of position holding all the valid position for the given color
 */
vector<Position> Board::validMoves(cellContent playerContent) const {
	vector<Position> v;
	Position pos;
	v.reserve(2 * Board::BOARD_SIZE);
	for (int i = 1; i<=Board::BOARD_SIZE; i++) {
		for (int j = 1; j<=Board::BOARD_SIZE; j++) {
			pos = Position(i,j);
			if (isValidMove(playerContent,pos)) {
				v.push_back(pos);
			}
		}
	}
	return v;
}

/*!
 * check if a given position is a valid move for a given color
 * @param playerContent : the color for which we check if cell at position pos is a valid move
 * @param pos : the position of the cell we check
 * @return true is the cell at position pos is a valid move for color
 */
bool Board::isValidMove(cellContent playerContent, Position pos) const {
	if (this->getContentAt(pos) == Empty) {
		for (int x=-1;x<=1;x++) {
			for (int y=-1;y<=1;y++) {
				if (!(x==0 && y==0)) {
					if (isSwitchInDirection(pos,x,y,playerContent)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

/*!
 * check if there is a switch (flip) possible from a given position to a given direction for a given color
 * @param pos : the position we start for
 * @param x : the x direction for the move
 * @param y : the y direction for the move
 * @param playerContent : the color we check
 * @return true if there is a switch (flip) possible in the given direction
 */
bool Board::isSwitchInDirection(Position pos,int x, int y, cellContent playerContent) const {
	Position newPos = pos.incrementedBy(x,y);
	if (newPos.isValid()) {
		cellContent newContent = this->getContentAt(newPos);
		if (newContent!=playerContent && newContent != Empty) {
			while (true) {
				newPos.increment(x,y);
				if (newPos.isValid()) {
					newContent = this->getContentAt(newPos);
					if (newContent==Empty) {
						break;
					}
					if (newContent == playerContent) {
						return true;
					}
				} else {
					break;
				}
			}
		}
	}
	return false;
}

/*!
 * effectively switch cells for a given player playing a given position
 * @param playerContent : the player's color
 * @param pos : the position where player is placing tile
 */
void Board::switchCells(cellContent playerContent, Position pos){
	/*
	 * si i=-1,j=-1:diagonale en bas a gauche
	 * si i=-1,j=0: a gauche
	 * si i=-1,j=1:diagonale en haut a gauche
	 * si i=0,j=-1: en bas
	 * si i=0,j=0:rien
	 * si i=0,j=1: en haut
	 * si i=1,j=-1: diagonale en bas a droite
	 * si i=1, j=0: a droite
	 * si i=1, j=1: diagonale en haut a droite
	 */

	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			/* (0,0) will fail immediately, so no need to test it separately */
			std::array<Position,6> flips; /* The possible flips for this direction, max 6 flips for a given direction (8-2) */
			int flipCount=0;			  /* The number of flips for this direction */
			Position newPos= pos.incrementedBy(i,j);
			while(newPos.isValid() && getContentAt(newPos)!=playerContent && getContentAt(newPos)!=Empty){
				flips[flipCount++] = newPos;		/* add the position to the list of possible flips */
				newPos=newPos.incrementedBy(i,j);
			}
			if (newPos.isValid() && getContentAt(newPos)==playerContent){ /* is this a valid move ? */
				while (flipCount > 0) {		/* yes, flip all the possible positions */
					flipContentAt(flips[--flipCount]);
				}
			}
		}
	}
}
	
/*!
 * check if the game is over. Return false if at least one player can play to at least one position
 * Optimised : return false as soon as the condition is met (doesn't goes through the complete board)
 * @param
 * @return true if the game is over
 */
bool Board::isGameOver() const {
	vector<Position> v;
	Position pos;
	for (int i = 1; i<=Board::BOARD_SIZE; i++) {
		for (int j = 1; j<=Board::BOARD_SIZE; j++) {
			pos = Position(i,j);
			if (isValidMove(Black,pos) or isValidMove(White,pos)) {
				return false;
			}
		}
	}
	return true;
}
