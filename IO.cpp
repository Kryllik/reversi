#include "IO.h"
#include <vector>
#include <sys/stat.h>


/* returns true if "path" is a directory that exists */
bool dirExists(string path) {
struct stat sb;
return  (stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode));
}


/*!
 * ask the player for its next move and make sure it is a valid move
 * @param gameBoard
 * @param playerContent
 * @return
 */
Position IO::moveInput(Board const & gameBoard, cellContent playerContent){
	Position pos;
	string move;
	while (true) {
		cout<<"Enter your move (column row)"<<endl;
		cin>>move;
		bool positionOk;
		pos = Position::positionFromString(move,positionOk);
		if (positionOk) {
			if (pos.isValid()) { /* means the position physically exists on the board */
				if (gameBoard.isValidMove(playerContent,pos)) {
					return pos;
				} else {
					cout << "Not a valid move, try again" << endl;
				}
			} else {			/* means the position is actually 'user passes its turn because he can't play */
				if (gameBoard.validMovesExist(playerContent)) {
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
 * Ask the user for the types of the players. Possible players type are A (AI), H (Human), F (File)
 * @return a pair chars for first and second player's type
 */
pair<char,char> IO::playerCreation(){
	bool validBlack = false;
	bool validWhite = false;
	pair<char, char> players;
	string stringplayers;
	while(!(validBlack&&validWhite)){
		cout << "choisir le type de joueur noir, puis le type de joueur blanc (H,F,A) " << endl;
		cin >> stringplayers;
		if (stringplayers.size() == 2){
			if(stringplayers[0] == 'H' || stringplayers[0] == 'F'|| stringplayers[0] == 'A'){
				players.first = stringplayers[0];
				validBlack = true;
			}
			else{
				cout << "mauvaise entrée du joueur noir, veuillez recommencer" <<endl;
				validBlack=false;
				}
			if(stringplayers[1] == 'H' || stringplayers[1] == 'F'||stringplayers[1] == 'A'){
				players.second = stringplayers[1];
				validWhite = true;
			}
			else{
				cout << "mauvaise entrée du joueur blanc, veuillez recommencer" <<endl;
				validWhite = false;
			}
		}
		else{
			cout << "mauvais nombre d'arguments, veuillez recommencer" << endl;
		}
	}	 
	return players;
}				

/*!
 * Ask the user for a file path (used by filePlayers) and make sure the path exists
 * @param playerColor : the color for which we ask a file path
 * @return a valid path
 */
string IO::askForFilePath(cellContent playerColor) {
	string path;
	while (true) {
		if (playerColor == Black) {
			cout << "entrer le r�pertoire des fichiers pour le joueur Noir ( '.' pour le r�pertoire courant) : ";
		} else {
			cout << "entrer le r�pertoire des fichiers pour le joueur Blanc  ( '.' pour le r�pertoire courant) : ";
		}
		cin >> path;
		if (path.back() == '/') path.pop_back(); /* remove trailing / if any */

		if (dirExists(path)) {
			break; /* path is valid, exit the while loop */
		} else {
			cout << "le chemin introduit n'est pas valide, veuillez r�essayer" << endl;
		}
	}
	return path;
}

/*!
 * display the last move followed by the update board
 * @param board
 * @param player
 * @param pos
 */
void IO::display(Board & board, const Player &player, Position pos){
	cout << endl << endl;
	cout << "Le joueur " << player.toString() << " vient de jouer en : " << pos.toString() << endl;
	//cout << "mise à jour du board " << endl;
	cout << endl << endl;
	boardDisplay(board);
}

/*!
 * display who is playing now followed by its valid moves
 * @param player
 * @param gameBoard
 */
void IO::displayWhoPlays(const Player &player, Board const& gameBoard){
	cout << endl << endl << endl;
	cout << "Au joueur " << player.toString() << " de jouer" << endl;
	displayValidMoves(player,gameBoard);
}


/*!
 * display the board
 * @param board
 */
void IO::displayFirstTurn(Board & board) {
	boardDisplay(board);
}

/*!
 * display the valid moves for a player
 * @param player
 * @param gameBoard
 */
void IO::displayValidMoves(const Player &player, Board const& gameBoard) {
	std::vector<Position> v = gameBoard.validMoves(player.getColor());
	cout << "Valid moves : ";
	if (v.size() == 0) {
		cout << "none !" << endl;
	} else {
		for (unsigned int i = 0; i<v.size(); i++) {
			if (i != v.size()-1) {
				cout << v[i].toString() << " - ";
			} else {
				cout << v[i].toString() << endl;
			}
		}
	}
}

/*!
 * display a given list of valid moves
 * @param v
 */
void IO::displayValidMoves(std::vector<Position> v) {
	if (v.size() == 0) {
		cout << "empty" << endl;
	} else {
		for (unsigned int i = 0; i<v.size(); i++) {
			if (i != v.size()-1) {
				cout << v[i].toString() << " - ";
			} else {
				cout << v[i].toString() << endl;
			}
		}
	}
}

/*!
 * display the  board
 * @param board
 */
void IO::boardDisplay(Board & board){
	cout<<"       a b c d e f g h  " << endl; //Impression des numéros de ligne
	for(unsigned int line =1; line <= 8; line++){
		cout<< "     "<<(line)<< " "; // Impression des numéros de colonne
		for(unsigned int col = 1; col <=8; col++){
			switch(board.getContentAt(Position(col,line))){
				case Empty: cout << ". "; break;
				case Black: cout << "B "; break;
				case White: cout << "W "; break;
			}
		}
		cout << (line) << endl;
	}
	cout<<"       a b c d e f g h  "<< endl;
}

/*!
 * display the scores for each player
 * @param blackScore
 * @param whiteScore
 */
void IO::displayScore(int blackScore, int whiteScore) {
	cout << "Black score : " << blackScore << " - " << "White score : " << whiteScore << endl;
	if (blackScore>whiteScore) {
		cout << "Victoire du joueur Noir" << endl;
	}
	if (whiteScore>blackScore) {
		cout << "Victoire du joueur Blanc" << endl;
	}
	if (blackScore==whiteScore) {
		cout << "Match nul" << endl;
	}
}




