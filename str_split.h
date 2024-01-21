/**
 * Split a string into a list of strings. (Header file)
 *
 * @date 2024-01-20
 * @author Marcio Reis Jr.
 *
 * This code is released under the GPLv2.1 license. Refer to the LICENSE file
 * for more information.
 */

#ifndef __STR_SPLIT_H__
#define __STR_SPLIT_H__

extern void free_list(void** list, size_t list_len);

/**
 * Split a string by a separator.
 *
 * @param str The string to split.
 * @param delim The separator.
 *
 * @return A list of strings.
 */
char** str_split(const char* str, const char* delim);

#endif // __STR_SPLIT_H__
