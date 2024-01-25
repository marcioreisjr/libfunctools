/**
 * String set functions. (Header)
 *
 * @date 2024-01-25
 * @author Marcio Reis Jr.
 *
 * This code is released under the GPLv2.1 license. Refer to the LICENSE file
 * for more information.
 */
#ifndef _STR_SET_H_
#define _STR_SET_H_


/**
 * Checks if the given string contains the given character.
 *
 * @param haystack The string to check.
 * @param needle The character to check for.
 * @return 1 if the string contains the character, 0 otherwise.
 */
int str_contains(const char* haystack, char needle);

/**
 * Returns a set of characters from the given string.
 *
 * @param letters The string to get the set from.
 * @return A set of characters from the given string.
 * @note The caller is responsible for freeing the returned string.
 */
char* str_set(const char* letters);


#endif /* _STR_SET_H_ */
