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
 * <header file with declaration of string helper functions>
 */

char** splitStringBySpace(const char* str, int& wordsCount);
bool areEqualStrings(const char* str1,const char* str2);
void copyString(char* dest, const char* src);
size_t strLen(const char* str);
char* toLower(const char* str);
char toLowerChar(const char ch);
char* integersToChar(int num1, int num2);
char digitToChar(int digit);
void concatenateString(char* dest, const char* src);

int charToDigit(const char * ch);
char* intToString(int num);
