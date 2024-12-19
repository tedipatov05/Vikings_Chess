#include "StringUtils.h"
#include "Constants.h"

char** splitStringBySpace(const char* str, int& wordCount) {
	wordCount = 0; // Initialize word count
	int length = 0;

	for (const char* ptr = str; *ptr != TERMINATE_SYMBOL; ptr++) {
		length++;
		if (*ptr == ' ' && (ptr != str && *(ptr - 1) != ' ')) {
			wordCount++;
		}
	}

	if (length > 0 && str[length - 1] != ' ') {
		wordCount++;
	}

	char** result = new char* [wordCount];
	const char* wordStart = nullptr;
	int wordIndex = 0;

	for (const char* ptr = str; *ptr != TERMINATE_SYMBOL; ptr++) {
		if (*ptr != ' ' && wordStart == nullptr) {
			wordStart = ptr;
		}
		else if ((*ptr == ' ' || *(ptr + 1) == TERMINATE_SYMBOL) && wordStart != nullptr) {
			int wordLength = ptr - wordStart + (*ptr != ' ');
			result[wordIndex] = new char[wordLength + 1];


			for (int i = 0; i < wordLength; i++) {
				result[wordIndex][i] = wordStart[i];
			}
			result[wordIndex][wordLength] = TERMINATE_SYMBOL;
			wordIndex++;
			wordStart = nullptr;
		}
	}

	return result;
}

bool areEqualStrings(const char** str1, const char** str2)
{
	if (!str1 || !str2) {
		return false;
	}

	size_t str1Len = strLen(str1);
	size_t str2Len = strLen(str2);
	if (str1Len != str2Len) {
		return false;
	}

	while (*str1) {

		if (*str1 != *str2) {
			return false;
		}

		str1++;
		str2++;
	}

	return true;
}

size_t strLen(const char** str)
{
	if (!str) {
		return 0;
	}

	size_t length = 0;

	while (*str) {
		length++;
		str++;
	}

	return length;
}
