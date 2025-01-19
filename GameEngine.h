#pragma once

/**
 *
 * Solution to course project #7
 * Introduction to programing course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2024/2025
 *
 * @author Teodor Patov
 * @idnumber 2MI0600491
 * @compiler VC
 *
 * <header file with declaration of functions for main functionality>
 */

struct Tafl;
void runGame();
void startGame();
void quitGame();
char** initializeBoard(int boardSize);
void displayBoard(char** board, int boardSize);
void placeAttackers(char** board, int boardSize);
void placeDefenders(char** board, int boardSize);
int makeMove(int sourceRow, int sourceCol, int destinationRow, int destinationCol, char** board, int boardSize, int player, bool& isEnded);
bool isInBoard(int row, int col, int boardSize);
void captureFigure(char** board, int lastRow, int lastCol, int boardSize, bool& isEnded);

void copyBoard(char** board, char** destination, int size);
void insertAtEnd(Tafl*& head, char** board, int moveCount);
bool isGameOver(char** board, int boardSize);
bool isSurrounded(char** board, int boardSize, int x, int y, char target);
bool isKingCaptured(char** board, int boardSize, int x, int y, bool& isEnded);
void deleteAtEnd(Tafl*& head, int boardSize);
void freeHistory(Tafl*& head, int boardSize);
void freeMemoryBoard(char** board, int boardSize);
void findCapturedFigures(char** board, int boardSize, int& currentAttackers, int& currentDefenders);
