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
	private:
		Cell array[BOARD_SIZE][BOARD_SIZE];
		void initBoard();
};

#endif
