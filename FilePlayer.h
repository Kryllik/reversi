
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

/*! \class FilePlayer
 * \brief child class based on Player.cpp that handles players acting through files
 *
 * two files shall be used by the player, noir.txt and blanc.txt
 * if player is black, the player movements will be read from noir.txt and the opponent's move written to blanc.txt
 * if player is white, the player movements will be read from blanc.txt and the opponent's move written to noir.txt
 */
class FilePlayer : public Player{
	public:
		FilePlayer(cellContent color /*, string pathToFiles*/);
		~FilePlayer() {}
		Position getMove(Board gameBoard, int turn);
		void giveMove(Position pos);
		//void giveVoidMove();
	private:
		ifstream playerFile; 	/*!< the player's input file */
		ofstream opponentFile;	/*!< the opponent's output file */
		/* string pathToFiles; */

};

#endif /* FILEPLAYER_H */
