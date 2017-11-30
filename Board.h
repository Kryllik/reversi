//Header de Board.h

#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"
#include "Position.h"


class Board{
	public:
		static constexpr int BOARD_SIZE = 8; //Taille standard d'un plateau de jeu
		Board(); 
		~Board();
		cellContent getContentAt(Position pos) const;
		void setContentAt(Position pos, cellContent content);
		void switchContentAt(Position pos);

		int getScore(cellContent color = Black); //Imprime les scores
		
		/*!
		*  \brief Checks if playing at the given position with the given color causes a switch in the given direction
		*
		*  A switch is caused if the following conditions are met : 
		*  1) The color of the first cell in the direction is opposite to the player's color
		*  2) All of the cells in the direction are of opposite color until a cell of the player's color is reached
		*
		*  \param pos : the position that would cause the switch
		*  \param x : the x-coordinate of the direction
		*  \param y : the y-coordinate of the direction
		*  \param playerContent : the player's color
		*  \return boolean (true if there is a switch in the direction)
		*/
	private:
		Cell array[BOARD_SIZE][BOARD_SIZE];
		void initBoard();
};

#endif
