/**
 * Joins a list of strings with a separator. (Header file)
 *
 * @date 2024-01-20
 * @author Marcio Reis Jr.
 *
 * This code is released under the GPLv2.1 license. Refer to the LICENSE file
 * for more information.
 */

#ifndef _STR_JOIN_H_
#define _STR_JOIN_H_

/**
 * Joins a list of strings with a separator.
 *
 * @param list The list of strings to join.
 * @param sep The separator to use.
 *
 * @return The joined string. The caller is responsible for freeing it.
 */
char* str_join(const char** list, const char* sep);


#endif // _STR_JOIN_H_
