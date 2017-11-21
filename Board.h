//Header de Board.h

#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"
#include "Position.h"

/*typedef struct Position{ //Permet de définir une structure de position "cartésienne" en ligne et colonne.
	int line;
	int col;
	Position(int l, int c) : line(l), col (c) {} //constructeur
	Position() : line(-1), col(-1) {} //Constructeur par défaut dans le cas d'une variable non déclarée.
}Position;*/

class Board{
	public:
		static constexpr int BOARD_SIZE = 8; //Taille standard d'un plateau de jeu
		Board(); 
		~Board();
		cellContent getContentAt(Position pos);
		void setContentAt(Position pos, cellContent content);
		void switchContentAt(Position pos);
	private:
		Cell array[BOARD_SIZE][BOARD_SIZE];
		void initBoard();
};

#endif
