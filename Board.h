//Header de Board.h

#include "Cell.h"

typedef struct Position{ //Permet de définir une structure de position "cartésienne" en ligne et colonne.
	int line;
	int col;
	Position(int l, int c) : line(l), col (c) {} //constructeur
	Position() : line(-1), col(-1) {} //Constructeur par défaut dans le cas d'une variable non déclarée.
}Position;

class Board{
	public:
		Board(); 
		~Board();
		void Display();
		cellContent getContentAt(Position pos);
		void setContentAt(Position pos, cellContent content);
		static constexpr int BOARD_SIZE = 8; //Taille standard d'un plateau de jeu
	private:
		Cell array[BOARD_SIZE][BOARD_SIZE];
		void initBoard();
};
