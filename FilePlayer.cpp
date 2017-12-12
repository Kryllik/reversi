#include "FilePlayer.h"



/*!
 *  \brief FilePlayer's constructor
 *
 *  Construct a FilePlayer of the given color and open the required files.
 *  Wait until the player's file exists on disk
 *
 *  \param color : the player's color
 *  \return none
 */
FilePlayer::FilePlayer(cellContent color/*, string pathToFiles*/) : Player(color){
	string playerFileName, opponentFileName;

	/* Need to check if path exists */
	/*this->pathToFiles = pathToFiles;*/

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
	    //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		playerFile.open(playerFileName);
	}
	
	cout << "fichier existe, la partie peut commencer" << endl;
}

/*!
 *  \brief get the player's next move from its input file
 *
 *  Loop until the next move can be read in the file.
 *
 *  \param game : a reference to the game that can be used to validate the player's move
 *  \return the player's next position
 */
Position FilePlayer::getMove(Board gameBoard, int turn){
	string ligne;
	while (!(getline(playerFile, ligne, '\x0a'))) //caractère de fin de chaine sous linux (?)
	{
				// Echec de la lecture - Effacement des flags d'erreur
				playerFile.clear();
				// Ajout d'une temporisation avant de réessayer
				//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				cout << "waiting" << endl;
			}
	cout << "read : " << ligne << endl;
	return Position::positionFromString(ligne);
}

/*!
 *  \brief write the opponent's last move to its file
 *
 *  \param pos : The position of the opponent's last move
 *  \return none
 */
void FilePlayer::giveMove(Position pos){
	cout << "give move" << pos.toString() << endl;
	opponentFile << pos.toString() << endl;
}


/*!
 *  \brief write the opponent's failure to move to its file
 *
 *  \param none
 *  \return none
 */
void FilePlayer::giveVoidMove(){
	cout << "give void move" << endl;
	opponentFile << "00" << endl;
}
