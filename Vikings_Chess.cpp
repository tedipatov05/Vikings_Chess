

#include <iostream>
#include <iomanip>
using namespace std;


const int BOARD_SIZE = 11; // Standard size of a Viking Chess board
const char EMPTY = '.';    // Empty cell
const char KING = 'K';     // King piece
const char ATTACKER = 'A'; // Attacker piece
const char DEFENDER = 'D'; // Defender piece
const char EDGE = 'X';


void runGame();
void startGame();
void quitGame();
char** initializeBoard();
void displayBoard(char** board);
void placeAttackers(char** board);
void placeDefenders(char** board);




int main()
{
	runGame();

    char** board = initializeBoard();
    displayBoard(board);
}

void startGame() {
	cout << "Enter rows and cols of your board: ";
	int rows;
	cin >> rows;

}

void placeAttackers(char** board) {

    int center = BOARD_SIZE / 2;

    for (int i = 3; i <= 7; ++i) {
        board[0][i] = ATTACKER;
        board[BOARD_SIZE - 1][i] = ATTACKER;
        board[i][0] = ATTACKER;
        board[i][BOARD_SIZE - 1] = ATTACKER;
    }

    board[1][center] = ATTACKER;
    board[BOARD_SIZE - 2][center] = ATTACKER;
    board[center][BOARD_SIZE - 2] = ATTACKER;
    board[center][1] = ATTACKER;



}

void placeDefenders(char** board) {
    int center = BOARD_SIZE / 2;
    board[center - 1][center] = DEFENDER;
    board[center + 1][center] = DEFENDER;
    board[center][center - 1] = DEFENDER;
    board[center][center + 1] = DEFENDER;

    board[center - 2][center] = DEFENDER;
    board[center + 2][center] = DEFENDER;
    board[center][center - 2] = DEFENDER;
    board[center][center + 2] = DEFENDER;

    board[center - 1][center - 1] = DEFENDER;
    board[center - 1][center + 1] = DEFENDER;
    board[center + 1][center - 1] = DEFENDER;
    board[center + 1][center + 1] = DEFENDER;
}

char** initializeBoard() {
    char** board = new char* [BOARD_SIZE];
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        board[i] = new char[BOARD_SIZE];
        for (size_t j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }

    int center = BOARD_SIZE / 2;
    board[center][center] = KING;

    placeDefenders(board);

    placeAttackers(board);

    board[0][0] = EDGE;
    board[0][BOARD_SIZE - 1] = EDGE;
    board[BOARD_SIZE - 1][0] = EDGE;
    board[BOARD_SIZE - 1][BOARD_SIZE - 1] = EDGE;

    return board;
}


void displayBoard(char** board) {
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        for (size_t j = 0; j < BOARD_SIZE; j++) {
            std::cout << setw(2) << board[i][j];
        }
        std::cout << endl;
    }
}


void quitGame() {
	return; 
}

void runGame() {
	cout << "Choose your options: " << endl;
	cout << "1. Start game" << endl;
	cout << "2. Quit" << endl;

	int option;

	cout << "Enter your choice: ";
	cin >> option;

	//cout << option;

	if (option == 1) {
		startGame();
	}
	else {
		quitGame();
	}


}


