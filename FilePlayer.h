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
		~FilePlayer();
		Position getMove(Game & game);
	private:
		ofstream playerFile;
		ifstream opponentFile;

};

#endif
