/* header of Game.cpp
*/ 

#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include <vector>

class Game {
	public:
		Game();
		~Game();
		bool isValidMove(cellContent playerContent, Position pos) const; // renvoie si la position donnée est possible. Plus efficace niveau mémoire // FONCTION DE BOARD ????
		std::vector<Position> validMoves(cellContent playerContent); // renvoie un vecteur de positions de jeu valides pour la couleur donnée
		bool validMovesExist(cellContent playerContent); //Vérifie s'il y a AU MOINS une position valide.
		void gameStartPvP();
	private:
		void getScore(); //Imprime les scores
		void getWinner();// Imprime le gagnant (compare getScore()
		cellContent PlayerContentSwitch(cellContent playerContent);
		bool winnerMoveAtDirection(Position pos, int x, int y, cellContent playerContent) const;
		
		Board* board;
};


#endif
