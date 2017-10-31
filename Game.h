/* header of Game.cpp
*/ 
#include "Board.h"
#include <vector>

class Game {
	public:
		Game();
		~Game();
		bool isValidMove(cellContent playerContent, Position pos); // renvoie si la position donnée est possible. Plus efficace niveau mémoire // FONCTION DE BOARD ????
		std::vector<Position> validMoves(cellContent playerContent);
		bool validMovesExist(cellContent playerContent);
	private:
		bool Playable(); //Vérifie s'il y a AU MOINS une position valide. Dès qu'elle en trouve une, sortie de la fonction -> efficace niveau ressources.
		Board ValidMoves(); //crée un nouveau Board avec l'ensemble des moves autorisés (marqué avec une croix...). 
							//Utile pour des "indices" pour un joueur humain + utile pour l'Ia (trier les coups valables avant de les évaluer)
		void getScore(); //Imprime les scores
		void getWinner();// Imprime le gagnant (compare getScore()
		bool winnerMoveAtDirection(Position pos, int x, int y, cellContent playerContent);
		
		Board* board;
};
