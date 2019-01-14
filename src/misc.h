
#ifndef EUGENEJONAS__CPP_STUFF__MISC_H
#define EUGENEJONAS__CPP_STUFF__MISC_H


#include <cassert>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>


namespace eugenejonas::cpp_stuff
{


/**
 * Searches for the first occurrence of the substring in the given string.
 * 
 * @param substr The substring to search for.
 * @param str The string to search in.
 * @return Position of the first occurrence of the substring or
 *		string::npos if the substring was not found.
 */
std::string::size_type findSubstring(std::string substr, std::string str)
{
	std::string::size_type substrLength = substr.length();
	std::string::size_type strLength = str.length();

	long diff = ((long) strLength) - substrLength;
	long i = 0;
	char *position;

	// searching
	for (position = str.c_str(); i <= diff; ++position, ++i)
	{
		if (std::memcmp(substr.c_str(), position, substrLength) == 0)
		{
			return (position - str.c_str());
		}
	}

	return std::string::npos;
}

/**
 * Determines whether brackets structure is correct.
 */
bool areBracketsCorrect(std::string str)
{
	char *s = str.c_str();
	std::vector <char> v;

	for ( ; *s != '\0'; s++)
	{
		if (isOpeningBracket(*s))
		{
			v.push_back(*s);
		}
		else if (isClosingBracket(*s))
		{
			if (v.empty())
			{
				return false;
			}
			char tmp = v.back();
			if (!doBracketsMatch(tmp, *s))
			{
				return false;
			}
			v.pop_back();
		}
	}

	if (!v.empty())
	{
		return false;
	}
	else
	{
		return true;
	}
}
/**
 * Checks if closing bracket matches opening bracket.
 * The allowed brackets are: ( ) [ ] { } < >
 * 
 * @param opening The opening bracket.
 * @param closing The closing bracket.
 * @return true if brackets match. If the character represented by one
 *		of the parameters is not a bracket, returns false.
 */
bool doBracketsMatch(char opening, char closing)
{
	return (
			opening == '{' && closing == '}' ||
			opening == '(' && closing == ')' ||
			opening == '[' && closing == ']' ||
			opening == '<' && closing == '>'
	);
}
bool isOpeningBracket(char c)
{
	return (c == '{' || c == '(' || c == '[' || c == '<');
}
bool isClosingBracket(char c)
{
	return (c == '}' || c == ')' || c == ']' || c == '>');
}

/**
 * Compares two strings. Works like "strcmp", but ignores case of the characters.
 * 
 * @return n, where n > 0 if str1 > str2, 0 > n if str2 > str1, n == 0 if str1 == str2.
 */
int compareIgnoreCase(std::string str1, std::string str2)
{
	char *s1 = str1.c_str(), *s2 = str2.c_str();

	while (std::tolower(*s1) == std::tolower(*s2))
	{
		if (*s1 == '\0')
		{
			return 0;
		}
		++s1;
		++s2;
	}

	return std::tolower(*s1) - std::tolower(*s2);
}


}


#endif
