//classe fille de Player, contient les fonctions et attributs propre à un joueur de type Fichier

#include "FilePlayer.h"


FilePlayer::FilePlayer(cellContent color) : Player(color){
	string playerFileName, opponentFileName;
	if(this->getColor()==Black){ 
		playerFileName = "./noir.txt";
		opponentFileName = "./blanc.txt";
	}
	else{
		playerFileName = "./blanc.txt";
		opponentFileName = "./noir.txt";
	
	}

	playerFile.open(playerFileName, std::ofstream::out);
	opponentFile.open(opponentFileName);
	
	while (!opponentFile.is_open())
	{
		cout << "Attente du joueur adverse (fichier "<< opponentFileName <<" indisponible)" << endl;
		// Ajout d'une temporisation avant de réessayer
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		opponentFile.open(opponentFileName);
	}
	
	cout << "fichier existe, la partie peut commencer" << endl;
	

}

Position FilePlayer::getMove(Game & game){
	Position pos(2,2);
	return pos;
}
