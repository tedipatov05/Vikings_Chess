#pragma once

char** splitStringBySpace(const char* str, int& wordsCount);
bool areEqualStrings(const char* str1,const char* str2);
void copyString(char* dest, const char* src);
size_t strLen(const char* str);
char* toLower(const char* str);
char toLowerChar(const char ch);

int charToDigit(const char * ch);
