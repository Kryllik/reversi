//Header de FilePlayer

#ifndef FILEPLAYER_H
#define FILEPLAYER_H

#include "Player.h"

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::string;
using std::getline;


class FilePlayer : public Player{
	public:
		FilePlayer(cellContent color);
		virtual ~FilePlayer() {}
		Position getMove(Game & game);
		void giveMove(Position pos);
		void giveVoidMove();
	private:
		ifstream playerFile;
		ofstream opponentFile;

};

#endif
