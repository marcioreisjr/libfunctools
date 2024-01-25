/**
 * String set functions.
 *
 * @date 2024-01-25
 * @author Marcio Reis Jr.
 *
 * This code is released under the GPLv2.1 license. Refer to the LICENSE file
 * for more information.
 */

#ifdef TEST
#include <assert.h>
#include <stdio.h>
#endif
#include <string.h>
#include <stdlib.h>
#include "str_set.h"


 // Documentation in header file.
int str_contains(const char* haystack, char needle) {
    if (!haystack || needle == 0) return 0;
    for (; *haystack; haystack++)
        if (*haystack == needle) return 1;
    return 0;
}


// Documentation in header file.
char* str_set(const char* letters) {
    if (!letters) return NULL;
    char* ret = calloc(strlen(letters) + 1, sizeof(char)); // calloc inits mem with 0
    int retPtr = 0;
    for (int ix = 0; ix < strlen(letters); ix++) {
        if (!str_contains(ret, letters[ix])) ret[retPtr++] = letters[ix];
    }
    return ret;
}

#ifdef TEST

void test_str_contains() {
    assert(str_contains("abc", 'a'));
    assert(str_contains("abc", 'b'));
    assert(str_contains("abc", 'c'));
    assert(!str_contains("", 'a'));
    assert(!str_contains(NULL, 'a'));
    assert(!str_contains("abc", '\0'));
    assert(!str_contains("abc", 'd'));
    assert(!str_contains("abc", 'e'));
    assert(!str_contains("abc", '0'));
    assert(!str_contains("abc", '1'));
    assert(!str_contains("abc", '2'));
}

void test_str_set() {
    // Test NULL and empty string
    char* ret = str_set(NULL);
    assert(!ret);
    ret = str_set("");
    assert(ret);
    assert(strlen(ret) == 0);
    free(ret);
    // Test a few strings
    ret = str_set("abcabc");
    assert(ret);
    assert(strlen(ret) == 3);
    assert(str_contains(ret, 'a'));
    assert(str_contains(ret, 'b'));
    assert(str_contains(ret, 'c'));
    assert(!str_contains(ret, 'd'));
    assert(!str_contains(ret, 'e'));
    assert(!str_contains(ret, '0'));
    assert(!str_contains(ret, '1'));
    assert(!str_contains(ret, '2'));
    free(ret);
}

int main() {
    test_str_contains();
    printf("%s - \033[0;32m%s\033[0m\n", "test_str_contains", "Passed");
    test_str_set();
    printf("%s - \033[0;32m%s\033[0m\n", "test_str_set", "Passed");
    return 0;
}

#endif // TEST
