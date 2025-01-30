#include "StringUtils.h"
#include "Constants.h"

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
 * <file with implementation of string helper functions >
 */

/// <summary>
/// Copies the string from src to dest
/// </summary>
/// <param name="dest"></param>
/// <param name="src"></param>

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
/// Split the string by space
/// </summary>
/// <param name="str"></param>
/// <param name="wordsCount"></param>
/// <returns>return the words in a new array</returns>

char** splitStringBySpace(const char* str, int& wordsCount) {
	wordsCount = 0;

	if (!str) {
		return nullptr;
	}
	
	const char* ptr = str;
	while (*ptr) {
		
		while (*ptr == ' ') {
			++ptr;
		}

		
		if (*ptr) {
			++wordsCount;
			while (*ptr && *ptr != ' ') {
				++ptr;
			}
		}
	}

	if (wordsCount == 0) {
		return nullptr; 
	}


	char** result = new char* [wordsCount + 1];

	
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

		
		if (wordLength > 0 && index < wordsCount) {
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

/// <summary>
/// Checks if two strings are equal
/// </summary>
/// <param name="str1"></param>
/// <param name="str2"></param>
/// <returns>bool</returns>
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


/// <summary>
/// Gets the length of the string
/// </summary>
/// <param name="str"></param>
/// <returns>return length of the string size_t</returns>
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

/// <summary>
/// Returns char to lower case
/// </summary>
/// <param name="ch"></param>
/// <returns>char</returns>
char toLowerChar(const char ch) {
	if (ch >= 'A' && ch <= 'Z') {
		return ch + ('a' - 'A');
	}

	return ch;
}

/// <summary>
/// Return the whole string to lower case
/// </summary>
/// <param name="str"></param>
/// <returns>char*</returns>
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

/// <summary>
/// Converts char to its ascii value
/// </summary>
/// <param name="ch"></param>
/// <returns>int</returns>
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

/// <summary>
/// Convert number to string
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
char* intToString(int num) {
	int temp = num, length = 0;

	
	if (num == 0) {
		char* str = new char[2];
		str[0] = '0';
		str[1] = TERMINATE_SYMBOL;
		return str;
	}

	while (temp > 0) {
		length++;
		temp /= 10;
	}

	char* str = new char[length + 1];
	str[length] = TERMINATE_SYMBOL;  

	while (num > 0) {
		str[--length] = (num % 10) + '0';
		num /= 10;
	}

	return str;
}



/// <summary>
/// Converts all integers to char
/// </summary>
/// <param name="num1"></param>
/// <param name="num2"></param>
/// <returns>char*</returns>
char* integersToChar(int num1, int num2) {
	char* str1 = intToString(num1);
	char* str2 = intToString(num2);

	int length1 = 0;
	while (str1[length1] != TERMINATE_SYMBOL) {
		length1++;
	}

	int length2 = 0;
	while (str2[length2] != TERMINATE_SYMBOL) {
		length2++;
	}

	char* result = new char[length1 + length2 + 2]; 

	for (int i = 0; i < length1; i++) {
		result[i] = str1[i];
	}

	result[length1] = ' ';

	for (int i = 0; i < length2; i++) {
		result[length1 + 1 + i] = str2[i];
	}

	result[length1 + length2 + 1] = TERMINATE_SYMBOL;

	delete[] str1;
	delete[] str2;

	return result;
}

/// <summary>
/// Converts digit to char
/// </summary>
/// <param name="digit"></param>
/// <returns>char</returns>

char digitToChar(int digit) {
	if (digit >= 0 && digit <= 9) {
		return '0' + digit;
	}
	return TERMINATE_SYMBOL;
}

/// <summary>
/// Concatenates two strings
/// </summary>
/// <param name="dest"></param>
/// <param name="src"></param>
void concatenateString(char* dest, const char* src) {
	size_t len = strLen(dest);
	dest += len;
	*dest = SPACE;
	dest++;

	copyString(dest, src);
}


