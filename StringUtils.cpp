#include "StringUtils.h"
#include "Constants.h"

void copyString(char* dest, const char* src, size_t n) {
	size_t i = 0;
	while (i < n && src[i] != TERMINATE_SYMBOL) {
		dest[i] = src[i];
		i++;
	}

	dest[i] = TERMINATE_SYMBOL;
}


/// <summary>
/// This function takes a string (char*) and return its split by space
/// </summary>
/// <param name="str"></param>
/// <param name="wordCount"></param>
/// <returns> string split by space</returns>

char** splitStringBySpace(const char* str, int& wordCount) {
	wordCount = 0;

	// Calculate the number of words
	const char* ptr = str;
	while (*ptr) {
		// Skip leading spaces
		while (*ptr == ' ') {
			++ptr;
		}

		// Count a word if there are non-space characters
		if (*ptr) {
			++wordCount;
			while (*ptr && *ptr != ' ') {
				++ptr;
			}
		}
	}

	if (wordCount == 0) {
		return nullptr; // No words found
	}

	// Allocate memory for the result array (char**)
	char** result = new char* [wordCount + 1];

	// Extract words
	ptr = str; // Reset pointer to the start of the string
	int index = 0;

	while (*ptr) {
		// Skip leading spaces
		while (*ptr == ' ') {
			++ptr;
		}

		// Find the end of the current word
		const char* wordStart = ptr;
		while (*ptr && *ptr != ' ') {
			++ptr;
		}

		// Calculate word length
		size_t wordLength = ptr - wordStart;

		// Allocate memory for the word and copy it
		if (wordLength > 0 && index < wordCount) {
			result[index] = new char[wordLength + 1]; // +1 for null terminator
			for (size_t i = 0; i < wordLength; ++i) {
				result[index][i] = wordStart[i];
			}
			result[index][wordLength] = '\0'; // Null-terminate the word
			++index;
		}
	}

	return result;
}

bool areEqualStrings(const char* str1, const char* str2)
{
	if (!str1 || !str2) {
		return false;
	}

	const char* str1Copy = str1;
	const char* str2Copy = str2;

	size_t str1Len = strLen(str1Copy);
	size_t str2Len = strLen(str2Copy);



	if (str1Len != str2Len) {
		return false;
	}

	while (*str1Copy) {

		if (*str1Copy != *str2Copy) {
			return false;
		}

		str1Copy++;
		str2Copy++;
	}

	return true;
}

size_t strLen(const char* str)
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

char toLowerChar(const char ch) {
	if (ch >= 'A' && ch <= 'Z') {
		return ch + ('a' - 'A');
	}

	return ch;
}

char* toLower(const char* str) {
	// Calculate the length of the input string
	size_t length = 0;
	const char* temp = str;
	while (*temp) {
		length++;
		temp++;
	}

	// Allocate memory for the result string
	char* lowerStr = new char[length + 1];

	// Convert each character to lowercase
	const char* src = str;
	char* dest = lowerStr;
	while (*src) {
		*dest = toLowerChar(*src);
		++src;
		++dest;
	}

	*dest = TERMINATE_SYMBOL;

	return lowerStr;
}

int charToDigit(const char* ch) {

	if (!ch) {
		return -1;
	}


	int result = 0;

	while (*ch) {
		result *= 10;
		if (*ch >= '0' && *ch <= '9') {
			result += *ch - '0';
		}
		else if (*ch >= 'a' && *ch <= 'm') {
			result += *ch - 'a';
		}
		else if (*ch >= 'A' && *ch <= 'M') {
			result += *ch - 'A';
		}
		ch++;
	}




	return result;
}


