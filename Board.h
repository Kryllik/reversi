//Header de Board.h

#include "Cell.h"

class Board{
	public:
		Board(); 
		~Board();
		static constexpr int BOARD_SIZE = 8; //Taille standard d'un plateau de jeu
	private:
		Cell array[BOARD_SIZE][BOARD_SIZE];
		void initBoard();
};
