//Header de Board.h

#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"
#include "Position.h"
#include <vector>

using namespace std;

/*!
 * @class Board
 * @brief a class providing access to a reversi board
 *
 * hold a full reversi board (8*8 cells) and provide methods to manipulate it
 */
class Board{
	public:
		static constexpr int BOARD_SIZE = 8; //Taille standard d'un plateau de jeu
		Board(); 
		~Board();
		cellContent getContentAt(const Position pos) const{
			return (this->array[pos.getX()-1][pos.getY()-1]).getContent();
		}

		/*!
		 * Return the content of the cell at position pos
		 * @param pos : the position of the cell of which to return content
		 * @return the content of the cell at position pos
		 */
		void setContentAt(Position pos, cellContent content);

		void flipContentAt(Position pos);
		void switchCells(cellContent playerContent, Position pos);
		
		
		pair<int,int> getScore() const; //retourne les scores
		
		/*!
		*  @brief Checks if the position "pos" is valid for the color "playerContent"
		*
		*  The position is valid if it is empty and causes a switch in at least one of the 8 directions. 
		*  This method calls the method "winnerMoveAtDirection" for each direction.
		*
		*  @param playerContent : the player's color
		*  @param pos : the position to check
		*  @return boolean (true if the position is valid)
		*/
		bool isValidMove(cellContent playerContent, Position pos) const; 
		
		/*!
		*  @brief Returns a vector of valid positions to play for the given player color
		*
		*  This method calls the method "isValidMove" for each of the 64 positions.
		*
		*  @param playerContent : the player's color
		*  @return vector of valid positions
		*/
		std::vector<Position> validMoves(cellContent playerContent) const;
		
		/*!
		*  @brief Checks if at least one valid position exists for the given player color
		*
		*  This method calls the method "validMoves" and check if the returned vector is empty.
		*
		*  @param playerContent : the player's color
		*  @return boolean (true if at least one valid move exists)
		*/
		bool validMovesExist(cellContent playerContent) const;
		
		
		bool isGameOver() const;


	private:
		/*!
		*  @brief Checks if playing at the given position with the given color causes a switch in the given direction
		*
		*  A switch is caused if the following conditions are met : 
		*  1) The color of the first cell in the direction is opposite to the player's color
		*  2) All of the cells in the direction are of opposite color until a cell of the player's color is reached
		*
		*  @param pos : the position that would cause the switch
		*  @param x : the x-coordinate of the direction
		*  @param y : the y-coordinate of the direction
		*  @param playerContent : the player's color
		*  @return boolean (true if there is a switch in the direction)
		*/
		bool isSwitchInDirection(Position pos, int x, int y, cellContent playerContent) const;
		
		Cell array[BOARD_SIZE][BOARD_SIZE];
		
		void initBoard();
};

#endif
