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

	playerFile.open(playerFileName);
	opponentFile.open(opponentFileName, std::ofstream::trunc);
	
	while (!playerFile.is_open())
	{
		cout << "Attente du joueur (fichier "<< playerFileName <<" indisponible)" << endl;
		// Ajout d'une temporisation avant de réessayer
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		playerFile.open(playerFileName);
	}
	
	cout << "fichier existe, la partie peut commencer" << endl;
	

}

Position FilePlayer::getMove(Game & game){
	string ligne;
	while (!(getline(playerFile, ligne, '\x0a'))) //caractère de fin de chaine sous linux (?)
	{
				// Echec de la lecture - Effacement des flags d'erreur
				playerFile.clear();
				// Ajout d'une temporisation avant de réessayer
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				cout << "waiting" << endl;
			}
	cout << "read : " << ligne << endl;
	return Position::positionFromString(ligne);
}


void FilePlayer::giveMove(Position pos){
	cout << "give move" << pos.toString() << endl;
	opponentFile << pos.toString() << endl;

}



void FilePlayer::giveVoidMove(){
	cout << "give void move" << endl;
	opponentFile << "00" << endl;
}

