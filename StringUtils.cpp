#include "StringUtils.h"
#include "Constants.h"

void copyString(char* dest, const char* src, size_t n) {
    size_t i = 0;
    while(i < n && src[i] != TERMINATE_SYMBOL) {
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

char** splitStringBySpace(const char* str, int& count) {
    // First, we need to count the number of words
    count = 0;
    const char* ptr = str;

    while (*ptr) {
        // Skip leading spaces
        while (*ptr == ' ') {
            ptr++;
        }

        // If we are not at the end, we found a word
        if (*ptr != TERMINATE_SYMBOL) {
            count++;
            // Move to the end of the word
            while (*ptr && *ptr != ' ') {
                ptr++;
            }
        }
    }

    // Allocate memory for the array of strings
    char** result = new char* [count];
    ptr = str;
    int index = 0;

    while (*ptr) {
        // Skip leading spaces
        while (*ptr == ' ') {
            ptr++;
        }

        // If we are n at the end, we found a word
        if (*ptr != TERMINATE_SYMBOL) {
            const char* start = ptr;

            // Move to the end of the word
            while (*ptr && *ptr != ' ') {
                ptr++;
            }

            // Calculate the length of the word
            int length = ptr - start;

            // Allocate memory for the word and copy it
            result[index] = new char[length + 1];
            for (int i = 0; i < length; i++) {
                result[index][i] = start[i];
            }
            result[index][length] = TERMINATE_SYMBOL;  // Null-terminate the string
            index++;
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

int charToDigit(const char * ch) {
    char chCpy = (char)ch;
    if (chCpy >= '0' && chCpy <= '9') {
        return chCpy - '0';
    }
    else if (chCpy >= 'a' && chCpy <= 'm') {
        return chCpy - 'a';
    }
    else if (chCpy >= 'A' && chCpy <= 'M') {
        return chCpy - 'A';
    }


    return -1;
}


