#include "StringUtils.h"
#include "Constants.h"

void copyString(char* dest, const char* src) {
	//size_t i = 0;
	while (*src != TERMINATE_SYMBOL) {
		*dest = *src;
		dest++;
		src++;
	}

	*dest = TERMINATE_SYMBOL;
}


/// <summary>
/// This function takes a string (char*) and return its split by space
/// </summary>
/// <param name="str"></param>
/// <param name="wordCount"></param>
/// <returns> string split by space</returns>

char** splitStringBySpace(const char* str, int& wordCount) {
	wordCount = 0;

	
	const char* ptr = str;
	while (*ptr) {
		
		while (*ptr == ' ') {
			++ptr;
		}

		
		if (*ptr) {
			++wordCount;
			while (*ptr && *ptr != ' ') {
				++ptr;
			}
		}
	}

	if (wordCount == 0) {
		return nullptr; 
	}


	char** result = new char* [wordCount + 1];

	
	ptr = str; 
	int index = 0;

	while (*ptr) {
		
		while (*ptr == ' ') {
			++ptr;
		}

		
		const char* wordStart = ptr;
		while (*ptr && *ptr != ' ') {
			++ptr;
		}

	
		size_t wordLength = ptr - wordStart;

		
		if (wordLength > 0 && index < wordCount) {
			result[index] = new char[wordLength + 1]; 
			for (size_t i = 0; i < wordLength; ++i) {
				result[index][i] = wordStart[i];
			}
			result[index][wordLength] = TERMINATE_SYMBOL; 
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
	
	size_t length = 0;
	const char* temp = str;
	while (*temp) {
		length++;
		temp++;
	}

	
	char* lowerStr = new char[length + 1];
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


