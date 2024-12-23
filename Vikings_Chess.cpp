

#include <iostream>
#include "Constants.h"
#include "StringUtils.h"


using namespace std;

void runGame();
void startGame();
void quitGame();
char** initializeBoard(int boardSize);
void displayBoard(char** board, int boardSize);
void placeAttackers(char** board, int boardSize);
void placeDefenders(char** board, int boardSize);
int makeMove(int sourceRow, int sourceCol, int destinationRow, int destinationCol, char** board, int boardSize, int player);
bool isInBoard(int row, int col, int boardSize);
void captureFigure(char** board, int lastRow, int lastCol, int& caughtAttackers, int& caughtDefenders, int boardSize);

//bool isGameOver(char** board, int boardSize);



int main()
{
	runGame();

}

void runGame() {
	cout << "Welcome to Vikings Chess" << endl;
	cout << "1. Start game" << endl;
	cout << "2. Quit" << endl;
	int option;


	do {
		cout << "Enter your choice: ";
		cin >> option;
	} while (option != 1 && option != 2);



	//cout << option;

	if (option == 1) {
		startGame();
	}
	else {
		quitGame();
	}

}

void startGame() {

	int boardSize;
	do {
		cout << "Enter valid board size (9, 11 or 13): ";
		cin >> boardSize;
	} while (boardSize != 9 && boardSize != 11 && boardSize != 13);

	char** board = initializeBoard(boardSize);
	displayBoard(board, boardSize);

	char* input = nullptr;
	int playerMove = 0;

	int caughtAttackers = 0;
	int caughtDefenders = 0;

	cin.ignore();


	while (true) {

		if (playerMove % 2 == 0) {
			cout << "First player move! (Attackers)" << endl;
		}
		else {
			cout << "Second player move! (Defenders)" << endl;

		}

		cin.clear();
		cin.sync();

		input = new char[INPUT_MAX_SIZE];

		cin.getline(input, INPUT_MAX_SIZE);



		//if (areEqualStrings(input, EXIT_NUMBER)) {


		//}
		//else if (isGameEnded(board, boardSize)) {
		//	cout << "Game ended" << endl;
		//	break;
		//}



		int wordsCount = 0;

		char** splitWords = splitStringBySpace(input, wordsCount);

		//char* cmd1 = result[0];

		delete[] input;


		if (areEqualStrings(toLower(splitWords[0]), MOVE_COMAND)) {

			int sourceRow = charToDigit(splitWords[1]);
			int sourceCol = charToDigit(splitWords[2]);
			int destinationRow = charToDigit(splitWords[3]);
			int destinationCol = charToDigit(splitWords[4]);


			int result = makeMove(sourceRow, sourceCol, destinationRow, destinationCol, board, boardSize, playerMove);
			if (!result) {
				cout << "Invalid move!" << endl;
				continue;
			}
			int directions[DIRECTIONS_ROWS][DIRECTIONS_COLS] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
			for (int i = 0; i < DIRECTIONS_ROWS; i++) {
				int row = directions[i][0];
				int col = directions[i][1];
				captureFigure(board, destinationRow + row, destinationCol + col, caughtAttackers, caughtDefenders, boardSize);

			}

			/*captureFigure(board, destinationRow, destinationCol - 1, caughtAttackers, caughtDefenders, boardSize);
			captureFigure(board, destinationRow + 1, destinationCol, caughtAttackers, caughtDefenders, boardSize);
			captureFigure(board, destinationRow - 1, destinationCol, caughtAttackers, caughtDefenders, boardSize);
			captureFigure(board, destinationRow, destinationCol + 1, caughtAttackers, caughtDefenders, boardSize);*/

			displayBoard(board, boardSize);
			bool isOver = isGameOver(board, boardSize);
			if (isOver) {
				cout << endl;
				cout << "Second PLayer wins the game!" << endl;
				return;
			}
		}
		else if (areEqualStrings(toLower(splitWords[0]), INFO_COMAND)) {
			cout << "Information" << endl;

		}
		else if (areEqualStrings(toLower(splitWords[0]), QUIT_COMAND)) {
			const char* output = (playerMove % 2) != 0 ? "First" : "Second";

			cout << output << " player wins the game" << endl;
			break;
		}
		else if (areEqualStrings(toLower(splitWords[0]), HELP_COMMAND)) {
			cout << endl;
			cout << "Possible moves: move, info, quit, help" << endl;
			continue;
		}
		else {
			cout << "Invalid command!" << endl;
			continue;
		}


		playerMove++;


	}

}

void placeAttackers(char** board, int boardSize) {

	int center = boardSize / 2;

	for (size_t i = 3; i < boardSize - 3; i++) {
		board[0][i] = ATTACKER;
		board[boardSize - 1][i] = ATTACKER;
		board[i][0] = ATTACKER;
		board[i][boardSize - 1] = ATTACKER;
	}

	board[1][center] = ATTACKER;
	board[boardSize - 2][center] = ATTACKER;
	board[center][boardSize - 2] = ATTACKER;
	board[center][1] = ATTACKER;

}

void placeDefenders(char** board, int boardSize) {
	int center = boardSize / 2;
	board[center - 1][center] = DEFENDER;
	board[center + 1][center] = DEFENDER;
	board[center][center - 1] = DEFENDER;
	board[center][center + 1] = DEFENDER;

	if (boardSize > 9) {
		board[center - 2][center] = DEFENDER;
		board[center + 2][center] = DEFENDER;
		board[center][center - 2] = DEFENDER;
		board[center][center + 2] = DEFENDER;
	}


	board[center - 1][center - 1] = DEFENDER;
	board[center - 1][center + 1] = DEFENDER;
	board[center + 1][center - 1] = DEFENDER;
	board[center + 1][center + 1] = DEFENDER;
}

char** initializeBoard(int boardSize) {
	char** board = new char* [boardSize];
	for (size_t i = 0; i < boardSize; i++) {
		board[i] = new char[boardSize];
		for (size_t j = 0; j < boardSize; j++) {
			board[i][j] = EMPTY;
		}
	}

	int center = boardSize / 2;
	board[center][center] = KING;

	placeDefenders(board, boardSize);

	placeAttackers(board, boardSize);

	board[0][0] = EDGE;
	board[0][boardSize - 1] = EDGE;
	board[boardSize - 1][0] = EDGE;
	board[boardSize - 1][boardSize - 1] = EDGE;

	return board;
}



void displayBoard(char** board, int boardSize) {
	for (size_t i = 0; i < boardSize; i++) {
		for (size_t j = 0; j < boardSize; j++) {
			std::cout << "  " << board[i][j];
		}

		std::cout << " |" << i + 1 << endl;
	}

	for (size_t i = 0; i < boardSize; i++) {
		cout << "___";
	}
	cout << endl;
	for (size_t i = 0; i < boardSize; i++) {
		cout << "  " << (char)(i + 'a');
	}
	cout << endl;
}


void quitGame() {
	return;
}

int makeMove(int sourceRow, int sourceCol, int destinationRow, int destinationCol, char** board, int boardSize, int player) {

	if (!isInBoard(sourceRow, sourceCol, boardSize)) {
		return 0;
	}
	if (!isInBoard(destinationRow, destinationCol, boardSize)) {
		return 0;
	}
	if (sourceRow != destinationRow && sourceCol != destinationCol) {
		return 0;
	}

	sourceRow--;
	destinationRow--;

	if (player % 2 == 0 && board[sourceRow][sourceCol] != ATTACKER) {
		return 0;
	}

	if (player % 2 == 1 && board[sourceRow][sourceCol] != DEFENDER && board[sourceRow][sourceCol] != KING) {
		return 0;
	}

	if (sourceRow == destinationRow) {
		int end = sourceCol < destinationCol ? destinationCol : sourceCol;
		int start = sourceCol < destinationCol ? sourceCol + 1 : destinationCol + 1;
		for (int col = start; col < end; col++) {
			if (board[sourceRow][col] != EMPTY && board[sourceRow][sourceCol] != KING) {
				return 0;
			}
			else if (board[sourceRow][col] != EMPTY && board[sourceRow][col] != THRONE && board[sourceRow][sourceCol] == KING) {
				return 0;
			}
		}
	}
	else if (sourceCol == destinationCol) {
		int end = sourceRow < destinationRow ? destinationRow : sourceRow;
		int start = sourceRow < destinationRow ? sourceRow + 1 : destinationRow + 1;
		for (int row = start; row < end; row++) {
			if (board[row][sourceCol] != EMPTY && board[sourceRow][sourceCol] != KING) {
				return 0;
			}
			else if (board[row][sourceCol] != THRONE && board[row][sourceCol] != EMPTY && board[sourceRow][sourceCol] == KING) {
				return 0;
			}
		}
	}

	board[destinationRow][destinationCol] = board[sourceRow][sourceCol];
	board[sourceRow][sourceCol] = EMPTY;

	int center = boardSize / 2;
	if (board[center][center] != KING) {
		board[center][center] = THRONE;
	}


	return 1;
}

void captureFigure(char** board, int row, int col, int& caughtAttackers, int& caughtDefenders, int boardSize) {

	row--;
	if (row <= 0 || row >= boardSize - 1) {
		return;
	}

	if (col <= 0 || col >= boardSize - 1) {
		return;
	}

	char ch = board[row][col];
	char opposite = (ch == DEFENDER || ch == KING) ? ATTACKER : DEFENDER;

	int center = boardSize / 2;

	int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // Up, Down, Left, Right
	int captures = 0;
	int capturesKing = 0;

	for (int i = 0; i < 4; i+=2) {
		int nx1 = row + directions[i][0];
		int ny1 = col + directions[i][1];
		int nx2 = row + directions[i+1][0];
		int ny2 = col + directions[i+1][1];

		//char oppositesAttacker[3] = { DEFENDER, KING, THRONE };

		if (board[nx1][ny1] != ch && board[nx1][ny1] != EMPTY && board[nx2][ny2] != ch && board[nx2][ny2] != EMPTY && ch != KING && ch != EMPTY) {
			captures++;
		}
		else if (ch == KING && board[nx1][ny1] == ATTACKER && board[nx2][ny2] == ATTACKER) {
			capturesKing++;
		}

	}

	if (capturesKing == 2 && ch == KING) {
		cout << "Game ended! First player wins the game" << endl;
		return;
	}
	else if (captures == 1) {
		board[row][col] = EMPTY;
		ch == DEFENDER ? caughtDefenders++ : caughtAttackers++;
		cout << endl;
		cout << "captured figure!" << " (" << ch << ")" << endl;
	}

}
//
//bool isCaptured(char** board, int row, int col, int boardSize) {
//	return true;
//}


bool isInBoard(int row, int col, int boardSize) {
	row--;
	if (row < 0 || row >= boardSize || col < 0 || col >= boardSize) {
		return false;
	}
	return true;
}


bool isGameOver(char** board, int boardSize) {

	return board[0][0] == KING || board[0][boardSize - 1] == KING
		|| board[boardSize - 1][0] == KING || board[boardSize - 1][boardSize - 1] == KING;
}


