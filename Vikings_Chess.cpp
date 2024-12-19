

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
void doMoves(char** board);

bool isGameEnded(char** board);



int main()
{
	runGame();

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

	while (true) {

		if (playerMove % 2 == 0) {
			cout << "First player move!" << endl;
		}
		else {
			cout << "Second player move!" << endl;

		}

		cin.clear();
		cin.sync();
		cin.ignore();

		cin.getline(input, INPUT_MAX_SIZE);

		int wordsCount = 0;


		if (input[0] == '2') {

			const char* output = (playerMove % 2) != 0 ? "First" : "Second";

			cout << output << " player wins the game" << endl;
			break;
		}
		else if (isGameEnded(board)) {
			cout << "Game ended" << endl;
			break;
		}


		char** result = splitStringBySpace(input, wordsCount);

		for (int i = 0; i < wordsCount; i++) {
			cout << result[i] << endl;
		}


		playerMove++;


	}

	

	delete[] input;



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

void doMoves(char** board) {

}


void displayBoard(char** board, int boardSize) {
	for (size_t i = 0; i < boardSize; i++) {
		for (size_t j = 0; j < boardSize; j++) {
			std::cout << "  " << board[i][j] ;
		}

		std::cout << " |" << i + 1 << endl;
	}

	for (size_t i = 0; i < boardSize; i++) {
		cout << "___";
	}
	cout << endl;
	for (size_t i = 0; i < boardSize; i++) {
		cout << "  " << (char)(i + 'a') ;
	}
	cout << endl;
}


void quitGame() {
	return;
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

bool isGameEnded(char** board) {
	return false;
}


