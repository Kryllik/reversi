/* header of Game.cpp
*/ 

#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include <vector>

class Player;

class Game {
	public:
		Game();
		~Game();
		
		/*!
		*  \brief Checks if the position "pos" is valid for the color "playerContent"
		*
		*  The position is valid if it is empty and causes a switch in at least one of the 8 directions. 
		*  This method calls the method "winnerMoveAtDirection" for each direction.
		*
		*  \param playerContent : the player's color
		*  \param pos : the position to check
		*  \return boolean (true if the position is valid)
		*/
		bool isValidMove(cellContent playerContent, Position pos, Board* board = NULL) const; 
		
		/*!
		*  \brief Returns a vector of valid positions to play for the given player color
		*
		*  This method calls the method "isValidMove" for each of the 64 positions.
		*
		*  \param playerContent : the player's color
		*  \return vector of valid positions
		*/
		std::vector<Position> validMoves(cellContent playerContent, Board* board = NULL) const;
		
		/*!
		*  \brief Checks if at least one valid position exists for the given player color
		*
		*  This method calls the method "validMoves" and check if the returned vector is empty.
		*
		*  \param playerContent : the player's color
		*  \return boolean (true if at least one valid move exists)
		*/
		bool validMovesExist(cellContent playerContent);
		
		void gameStart();
		
		void switchCells(cellContent playerContent, Position pos);
		
	private:
		/*!
		*  \brief Calculates and prints the scores
		*
		*  Calculates the score by checking the content of each cell, 
		*  then calls "displayScore" of the class "IO" to print the scores and the winner.
		*
		*  \return void
		*/
		bool isSwitchInDirection(Position pos, int x, int y, cellContent playerContent, Board* board = NULL) const;
		
		Board *board;			/* The Board instance */
		
		Player *playerBlack; 	/* The black player instance */
		
		Player *playerWhite; 	/* The white player instance */
};


#endif /* GAME_H */
