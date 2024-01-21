/**
 * Joins a list of strings with a separator.
 *
 * @date 2024-01-20
 * @author Marcio Reis Jr.
 *
 * This code is released under the GPLv2.1 license. Refer to the LICENSE file
 * for more information.
 */

#include <stdlib.h>
#include <string.h>
#include "str_join.h"
#ifdef TEST
#include <assert.h>
#include <stdio.h>
#endif

 // Documentation in header file.
char* str_join(const char** list, const char* sep) {
    int i, len = 0, seplen = strlen(sep);
    for (i = 0; list[i]; i++) {
        len += strlen(list[i]);
        if (list[i + 1]) len += seplen;
    }
    char* ret = malloc(len + 1);
    char* p = ret;
    for (i = 0; list[i]; i++) {
        strcpy(p, list[i]);
        p += strlen(list[i]);
        if (list[i + 1]) {
            strcpy(p, sep);
            p += seplen;
        }
    }
    *p = '\0';
    return ret;
}

#ifdef TEST
void test_join() {
    const char* list[] = { "a", "b", "c", NULL };
    char* result = str_join(list, ",");
    assert(strcmp(result, "a,b,c") == 0);
    free(result);

    const char* list2[] = { "a", "b", "c", NULL };
    result = str_join(list2, "");
    assert(strcmp(result, "abc") == 0);
    free(result);

    const char* list3[] = { "a", "b", "c", NULL };
    result = str_join(list3, " ");
    assert(strcmp(result, "a b c") == 0);
    free(result);

    const char* list4[] = { "a", "b", "c", NULL };
    result = str_join(list4, "123");
    assert(strcmp(result, "a123b123c") == 0);
    free(result);

    const char* list5[] = { "a", "b", "c", NULL };
    result = str_join(list5, "123");
    assert(strcmp(result, "a123b123c") == 0);
    free(result);

    const char* list6[] = { "a", "", "c", NULL };
    result = str_join(list6, "123");
    assert(strcmp(result, "a123123c") == 0);
    free(result);

    const char* list7[] = { "a", "b", "", NULL };
    result = str_join(list7, "123");
    assert(strcmp(result, "a123b123") == 0);

    const char* list8[] = { "", "b", "c", NULL };
    result = str_join(list8, "123");
    assert(strcmp(result, "123b123c") == 0);
    free(result);

    printf("%s - \033[0;32m%s\033[0m\n", "test_join", "Passed");
}

int main() {
    test_join();
    return 0;
}

#endif // TEST
