/**
 * Split a string into a list of strings.
 *
 * @date 2024-01-20
 * @author Marcio Reis Jr.
 *
 * This code is released under the GPLv2.1 license. Refer to the LICENSE file
 * for more information.
 */

#include <stdlib.h>
#include <string.h>
#include "str_split.h"
#ifdef TEST
#include <stdio.h>
#include <assert.h>
#endif


//
// Private classes - not exposed in the header
//
/**
 * The result of a collect operation.
 * @param el The current element.
 * @param nx The next element.
 * @param next 1 if there is a next element, 0 otherwise.
 */
typedef struct { char* el; char* nx; int next; } CollectResponse; // private

/**
 * The result of a split operation.
 * @param list The list of strings.
 * @param length The length of the list.
 */
typedef struct { char** list; size_t length; } SplitResult;


/**
 * Find the next element before the separator. -- private
 *
 * @param curr_el The current element.
 * @param sep The separator.
 * @return A copy of the current element and the next element.
 */
CollectResponse collect_element(char* curr_el, const char* sep) {
    CollectResponse res;
    char* found = strstr(curr_el, sep);
    if (!found) { // No separator found, the whole string is the element
        res.el = strdup(curr_el);
        res.nx = curr_el + strlen(curr_el);
        res.next = 0;
    } else if (sep[0] == 0) { // if separator is empty return a 1-char string
        res.el = malloc(2);
        res.el[0] = curr_el[0];
        res.el[1] = 0;
        if (curr_el[0] == 0) {
            res.nx = curr_el;
            res.next = 0;
        } else {
            res.nx = curr_el + 1;
            res.next = 1;
        }
    } else if (found) { // return the string before next separator
        found[0] = 0;
        res.el = strdup(curr_el);
        res.nx = found + strlen(sep);
        res.next = 1;
    }
    return res;
}

// Documentation in header file.
char** str_split(const char* str, const char* delim) {
    if (!str || !delim) {
        return NULL;
    }
    char* local = strdup(str);
    SplitResult result = { .length = 0 };
    CollectResponse resp = { .nx = local };
    do {
        resp = collect_element(resp.nx, delim);
        result.list = realloc(result.list, (result.length + 1) * sizeof(void*));
        result.list[result.length] = resp.el;
        result.length++;
    } while (resp.next);
    result.list = realloc(result.list, (result.length + 1) * sizeof(void*));
    result.list[result.length] = NULL;
    free(local);
    return result.list;
}

// Documentation in header file.
void str_split_free(char** result) {
    if (!result) return;
    for (int i = 0; result[i]; i++) {
        free(result[i]);
    }
    free(result);
    result = NULL;
}

#ifdef TEST
/**
 * Unit tests for str_split.
 */
void test_str_split() {
    char** result = str_split("a,b,c", ",");
    assert(strcmp(result[0], "a") == 0);
    assert(strcmp(result[1], "b") == 0);
    assert(strcmp(result[2], "c") == 0);
    str_split_free(result);

    result = str_split("a,b,c", "");
    assert(strcmp(result[0], "a") == 0);
    assert(strcmp(result[1], ",") == 0);
    assert(strcmp(result[2], "b") == 0);
    assert(strcmp(result[3], ",") == 0);
    assert(strcmp(result[4], "c") == 0);
    str_split_free(result);

    result = str_split("a,b,c", "b");
    assert(strcmp(result[0], "a,") == 0);
    assert(strcmp(result[1], ",c") == 0);
    str_split_free(result);

    result = str_split("a,b,c", "d");
    assert(strcmp(result[0], "a,b,c") == 0);
    str_split_free(result);

    result = str_split("a,b,c", "c");
    assert(strcmp(result[0], "a,b,") == 0);
    assert(strcmp(result[1], "") == 0);
    str_split_free(result);

    result = str_split("a,b,c", "a");
    assert(strcmp(result[0], "") == 0);
    assert(strcmp(result[1], ",b,c") == 0);
    str_split_free(result);

    result = str_split("a,b,c", "a,b,c");
    assert(strcmp(result[0], "") == 0);
    assert(strcmp(result[1], "") == 0);
    str_split_free(result);

    result = str_split("", "a,b,c,");
    assert(strcmp(result[0], "") == 0);
    str_split_free(result);

    result = str_split("", "");
    assert(strcmp(result[0], "") == 0);
    str_split_free(result);

    printf("%s - \033[0;32m%s\033[0m\n", "test_split", "Passed");
}


int main() {
    test_str_split();
    return 0;
}

#endif // TEST
