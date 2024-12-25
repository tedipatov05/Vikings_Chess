
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
void captureFigure(char** board, int lastRow, int lastCol, int& caughtAttackers, int& caughtDefenders, int boardSize, char*& history);

bool isGameOver(char** board, int boardSize);
bool isSurrounded(char** board, int boardSize, int x, int y, char target);
bool isKingCaptured(char** board, int boardSize, int x, int y);
int backMove(char** board, char** lastMove, char** history, int movesCount);
void executeLastMove(char** board, char** splitLastMove, char curr);



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
	int moveCount = 0;

	int caughtAttackers = 0;
	int caughtDefenders = 0;

	cin.ignore();

	char* playerOneLastMove = new char[INPUT_MAX_SIZE] {TERMINATE_SYMBOL};
	char* playerTwoLastMove = new char[INPUT_MAX_SIZE] {TERMINATE_SYMBOL};
	char** history = new char* [CAPTURED_FIGURES_MAX_SIZE];

	while (true) {

		if (moveCount % 2 == 0) {
			cout << "First player move! (Attackers)" << endl;
		}
		else {
			cout << "Second player move! (Defenders)" << endl;

		}

		cin.clear();
		cin.sync();

		input = new char[INPUT_MAX_SIZE];

		cin.getline(input, INPUT_MAX_SIZE);

		int wordsCount = 0;

		char** splitWords = splitStringBySpace(input, wordsCount);

		history[moveCount] = new char[CAPTURED_FIGURES_MAX_SIZE] {'\0'};

		if (areEqualStrings(toLower(splitWords[0]), MOVE_COMMAND)) {

			int sourceRow = charToDigit(splitWords[1]);
			int sourceCol = charToDigit(splitWords[2]);
			int destinationRow = charToDigit(splitWords[3]);
			int destinationCol = charToDigit(splitWords[4]);


			int result = makeMove(sourceRow, sourceCol, destinationRow, destinationCol, board, boardSize, moveCount);
			if (!result) {
				cout << "Invalid move!" << endl;
				continue;
			}

			moveCount % 2 == 0 ? copyString(playerOneLastMove, input) : copyString(playerTwoLastMove, input);

			char currentCh = board[destinationRow - 1][destinationCol];
			int directions[DIRECTIONS_ROWS][DIRECTIONS_COLS] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
			for (int i = 0; i < DIRECTIONS_ROWS; i++) {
				int row = directions[i][0];
				int col = directions[i][1];

				captureFigure(board, destinationRow + row, destinationCol + col, caughtAttackers, caughtDefenders, boardSize, history[moveCount]);
			}



			int center = boardSize / 2;
			if (board[center][center] != KING) {
				board[center][center] = THRONE;
			}

			displayBoard(board, boardSize);

			bool isOver = isGameOver(board, boardSize);
			if (isOver) {
				cout << endl;
				cout << "Second PLayer wins the game!" << endl;
				return;
			}
		}
		else if (areEqualStrings(toLower(splitWords[0]), INFO_COMMAND)) {

			cout << "Information" << endl;
			cout << "Captured attackers: " << caughtAttackers << endl;
			cout << "Captured defenders: " << caughtDefenders << endl;
			continue;

		}
		else if (areEqualStrings(toLower(splitWords[0]), QUIT_COMMAND)) {

			const char* output = (moveCount % 2) != 0 ? "First" : "Second";

			cout << output << " player wins the game" << endl;
			break;
		}
		else if (areEqualStrings(toLower(splitWords[0]), HELP_COMMAND)) {

			cout << endl;
			cout << "Possible moves: move, info, quit, help" << endl;
			continue;
		}
		else if (areEqualStrings(toLower(splitWords[0]), BACK_COMMAND)) {

			char** lastMove = new char* [2];
			lastMove[0] = new char[INPUT_MAX_SIZE];
			lastMove[1] = new char[INPUT_MAX_SIZE];


			copyString(lastMove[0], playerOneLastMove);
			*playerOneLastMove = TERMINATE_SYMBOL;

			copyString(lastMove[1], playerTwoLastMove);
			*playerTwoLastMove = TERMINATE_SYMBOL;

			
			int result = backMove(board, lastMove, history, moveCount);
			if (result == 0) {
				cout << "Invalid command" << endl;
				continue;
			}

			displayBoard(board, boardSize);

		}
		else {
			cout << "Invalid command!" << endl;
			continue;
		}

		delete[] input;

		moveCount++;


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
			if (board[sourceRow][sourceCol] == KING && board[sourceRow][col] == THRONE) {
				continue;
			}
			else if (board[sourceRow][col] != EMPTY) {
				return 0;
			}

		}
	}
	else if (sourceCol == destinationCol) {
		int end = sourceRow < destinationRow ? destinationRow : sourceRow;
		int start = sourceRow < destinationRow ? sourceRow + 1 : destinationRow + 1;
		for (int row = start; row < end; row++) {
			if (board[sourceRow][sourceCol] == KING && board[row][sourceCol] == THRONE) {
				continue;
			}
			else if (board[row][sourceCol] != EMPTY) {
				return 0;
			}

		}
	}


	if (board[sourceRow][sourceCol] == KING && board[destinationRow][destinationCol] == THRONE) {
		return 1;
	}
	else if (board[destinationRow][destinationCol] != EMPTY) {
		return 0;
	}

	board[destinationRow][destinationCol] = board[sourceRow][sourceCol];
	board[sourceRow][sourceCol] = EMPTY;




	return 1;
}

int backMove(char** board, char** lastMove, char** history, int movesCount) {

	int words = 0;

	char** splitLastMove = splitStringBySpace(lastMove[movesCount % 2], words);

	int w2 = 0;
	char** history2Split = splitStringBySpace(history[movesCount - 1], w2);

	if (!splitLastMove || !areEqualStrings(splitLastMove[0], MOVE_COMMAND)) {
		cout << "Make a move first!" << endl;
		return 0;
	}
	char current = movesCount % 2 == 0 ? ATTACKER : DEFENDER;
	char opposite = (current == DEFENDER || current == KING) ? ATTACKER : DEFENDER;


	if (!history2Split) {
		
		executeLastMove(board, splitLastMove, current);

	}

	
	int w = 0;
	char** historySplit = splitStringBySpace(history[movesCount - 2], w);

	

	if (history2Split) {
		for (int j = 0; j < w2; j += 2) {
			int row = charToDigit(history2Split[j]);
			int col = charToDigit(history2Split[j + 1]);

			
			board[row][col] = current;

		}

		int res = (movesCount - 1) % 2;

		int wordsLastMove = 0;
		char** lastMovePreviousSplit = splitStringBySpace(lastMove[res], wordsLastMove);

		executeLastMove(board, lastMovePreviousSplit, opposite);
		
	}



	if (historySplit) {
		for (int i = 0; i < w; i += 2) {
			int row = charToDigit(historySplit[i]);
			int col = charToDigit(historySplit[i + 1]);

			board[row][col] = opposite;
		}
	}

	return 1;
}

void executeLastMove(char** board, char** splitLastMove, char curr) {

	int destinationRow = charToDigit(splitLastMove[1]);
	int destinationCol = charToDigit(splitLastMove[2]);
	int sourceRow = charToDigit(splitLastMove[3]);
	int sourceCol = charToDigit(splitLastMove[4]);

	destinationRow--;
	sourceRow--;

	board[destinationRow][destinationCol] = curr;
	board[sourceRow][sourceCol] = EMPTY;
}

void captureFigure(char** board, int row, int col, int& caughtAttackers, int& caughtDefenders, int boardSize, char*& history) {

	row--;
	if (row <= 0 || row >= boardSize) {
		return;
	}

	if (col <= 0 || col >= boardSize) {
		return;
	}

	char figure = board[row][col];
	if (figure == EMPTY) {
		return;
	}
	char opposite = (figure == DEFENDER || figure == KING) ? ATTACKER : DEFENDER;

	int center = boardSize / 2;


	bool captured = isSurrounded(board, boardSize, row, col, opposite);



	if (figure == KING && isKingCaptured(board, boardSize, row, col)) {
		cout << "Game ended! First player wins the game" << endl;
		return;
	}
	else if (captured) {
		board[row][col] = EMPTY;
		concatenateString(history, integersToChar(row, col));
		figure == DEFENDER ? caughtDefenders++ : caughtAttackers++;
		cout << endl;
		cout << "captured figure!" << " (" << figure << ")" << endl;
	}

}

bool isSurrounded(char** board, int boardSize, int x, int y, char target) {
	int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	int center = boardSize / 2;


	for (int i = 0; i < 4; i += 2) {
		int nx1 = x + directions[i][0], ny1 = y + directions[i][1];
		int nx2 = x + directions[i + 1][0], ny2 = y + directions[i + 1][1];

		bool side1 = (nx1 >= 0 && nx1 < boardSize && ny1 >= 0 && ny1 < boardSize) &&
			(board[nx1][ny1] == target || board[nx1][ny1] == THRONE || board[nx1][ny1] == EDGE || (center == nx1 && center == ny1 && board[nx1][ny1] == KING));
		bool side2 = (nx2 >= 0 && nx2 < boardSize && ny2 >= 0 && ny2 < boardSize) &&
			(board[nx2][ny2] == target || board[nx2][ny2] == THRONE || board[nx2][ny2] == EDGE || (center == nx2 && center == ny2 && board[nx2][ny2] == KING));

		if (side1 && side2) {
			return true;
		}
	}

	return false;
}

bool isKingCaptured(char** board, int boardSize, int x, int y) {
	int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	int captureCount = 0;

	for (int i = 0; i < 4; ++i) {
		int nx = x + directions[i][0], ny = y + directions[i][1];

		if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardSize) {
			if (board[nx][ny] == ATTACKER || board[nx][ny] == THRONE) {
				++captureCount;
			}
		}
		else {
			++captureCount;
		}
	}

	return captureCount == 4;
}

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


