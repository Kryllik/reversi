//Header de HumanPlayer

#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class HumanPlayer: public Player{
		public:
			HumanPlayer(cellContent color);
			~HumanPlayer();
			Position getMove(Game &game);
			void giveMove(Position pos);
			void giveVoidMove();
		private:
};

#endif
