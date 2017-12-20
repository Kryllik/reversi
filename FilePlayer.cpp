#include "FilePlayer.h"
#include "IO.h"
#include "Position.h"
#include "Board.h"


/*!
 *  @brief FilePlayer's constructor
 *
 *  Construct a FilePlayer of the given color and open the required files.
 *  Wait until the player's file exists on disk
 *
 *  @param color : the player's color
 *  @return none
 */
FilePlayer::FilePlayer(cellContent color) : Player(color){

	string pathToFiles = IO::askForFilePath(color);
	if (pathToFiles == "") pathToFiles="."; /* Make sure we won't end up with an absolute path to / */

	/* build up paths to file */
	if(this->getColor()==Black) {
		playerFileName = pathToFiles+"/noir.txt";
		opponentFileName = pathToFiles+"/blanc.txt";
	}
	else{
		playerFileName = pathToFiles+"/blanc.txt";
		opponentFileName = pathToFiles+"/noir.txt";
	}

	cout << "player "<< toString() << " will read its moves from " << playerFileName;
	cout << " and write its opponent moves to " << opponentFileName << endl;

	playerFile.open(playerFileName);
	opponentFile.open(opponentFileName, std::ofstream::trunc);
	
	while (!playerFile.is_open())
	{
		cout << "Attente du joueur (fichier "<< playerFileName <<" indisponible)" << endl;
		/* sleep for a while before retrying */
	    std::this_thread::sleep_for(std::chrono::milliseconds(500));
		playerFile.open(playerFileName);
	}
	
	cout << "fichier existe, la partie peut commencer" << endl;
}

/*!
 *  @brief get the player's next move from its input file
 *
 *  Loop until the next move can be read in the file and until that it is a valid moves.
 *
 *  @param game : a reference to the game that can be used to validate the player's move
 *  @return the player's next position
 */
Position FilePlayer::getMove(Board gameBoard){
	string ligne;
	Position pos;
	while (true) {
		cout << "waiting to receive next move in file " << playerFileName << endl;
		while (!(getline(playerFile, ligne))) //, '\x0a'))) /* (??end of line char under windows/linux is different??) */
		{
			playerFile.clear(); /* getline failed, clear errors */
			/* sleep for a while before retrying */
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		bool positionOk;
		pos = Position::positionFromString(ligne,positionOk);
		if (positionOk) {
			if (pos.isValid()) { /* means the position physically exists on the board */
				if (gameBoard.isValidMove(this->playerColor,pos)) {
					return pos;
				} else {
					cout << "Not a valid move, try again" << endl;
				}
			} else {  /* means the position is actually 'user passes its turn because he can't play' */
				if (gameBoard.validMovesExist(this->playerColor)) {
					cout << "user cannot pass its turn, possible moves exists, try again" << endl;
				} else {
					return pos;
				}

			}
		} else {
			cout << "Not a correct syntax, try again" << endl;
		}
	}
}

/*!
 *  @brief write the opponent's last move to its file
 *
 *  @param pos : The position of the opponent's last move
 *  @return none
 */
void FilePlayer::giveMove(Position pos){
	opponentFile << pos.toString() << endl;
}
