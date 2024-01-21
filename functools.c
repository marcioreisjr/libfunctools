/**
 * @brief Implementation of the functions defined in functools.h
 * @date 2024-01-20
 * @author Marcio Reis Jr.
 *
 * This code is released under the GPLv2.1 license. Refer to the LICENSE file
 * for more information.
 */

#include "functools.h"
#include <string.h>

#ifdef TEST
#include <assert.h>
#include <stdio.h>
#endif // TEST


// Documentation in functools.h
ObjList filter_data(FilterDataFn fn, const void* input, size_t el_len, size_t el_count) {
    if (input == NULL || fn == NULL || el_len == 0 || el_count == 0) {
        return NULL;
    }
    ObjList out = NULL;
    size_t j = 0; // index of the current element
    size_t k = 0; // index of the current element in the output array
    unsigned char* ix = (unsigned char*)input;
    while (j < el_count) {
        if (fn((void*)&ix[j * el_len], j)) {
            out = realloc(out, sizeof(void*) * (k + 1));
            out[k] = malloc(el_len);
            memcpy(out[k], (char*)&ix[j * el_len], el_len);
            k++;
        }
        j++;
    }
    out = realloc(out, sizeof(void*) * (k + 1));
    out[k] = NULL;
    return out;
}


// Documentation in functools.h
ObjList map_data(MapDataFn fn, const void* input, size_t el_len, size_t el_count) {
    if (input == NULL || fn == NULL || el_len == 0 || el_count == 0) {
        return NULL;
    }
    ObjList out = malloc(sizeof(void*) * (el_count + 1));
    size_t j = 0; // index of the current element
    unsigned char* ix = (unsigned char*)input;
    while (j < el_count) {
        out[j] = fn((void*)&ix[j * el_len], j);
        j++;
    }
    out[j] = NULL;
    return out;
}


// Documentation in functools.h
void* reduce_data(ReduceDataFn fn, const void* input,
    size_t el_len, size_t el_count, void* init) {

    if (input == NULL || fn == NULL || el_len == 0 || el_count == 0) {
        return NULL;
    }
    size_t j = 0; // index of the current element
    unsigned char* ix = (unsigned char*)input;
    void* tmp;
    while (j < el_count) {
        tmp = fn(init, (void*)&ix[j * el_len], j);
        free(init);
        init = tmp;
        j++;
    }
    return init;
}


// Documentation in functools.h
ObjList filter(FilterDataFn fn, ObjList input) {
    if (input == NULL || input[0] == NULL || fn == NULL) {
        return NULL;
    }
    ObjList out = NULL;
    size_t i = 0;
    size_t j = 0;
    for (i = 0; input[i] != NULL; i++) {
        if (fn(input[i], i)) {
            out = realloc(out, sizeof(void*) * (j + 1));
            out[j] = input[i];
            j++;
        }
    }
    out = realloc(out, sizeof(void*) * (j + 1));
    out[j] = NULL;
    return out;
}


// Documentation in functools.h
ObjList map(MapDataFn fn, ObjList input) {
    if (input == NULL || input[0] == NULL || fn == NULL) {
        return NULL;
    }
    size_t i = 0;
    for (i = 0; input[i] != NULL; i++);
    ObjList out = malloc(sizeof(void*) * (i + 1));
    for (i = 0; input[i] != NULL; i++) {
        out[i] = fn(input[i], i);
    }
    out[i] = NULL;
    return out;
}


// Documentation in functools.h
void* reduce(ReduceDataFn fn, ObjList input, void* init) {
    if (input == NULL || input[0] == NULL || fn == NULL) {
        return NULL;
    }
    size_t i = 0;
    void* tmp;
    for (i = 0; input[i] != NULL; i++) {
        tmp = fn(init, input[i], i);
        free(init);
        init = tmp;
    }
    return init;
}


// Documentation in functools.h
void free_list(void** list, size_t list_len) {
    if (list == NULL) return;
    size_t i = 0;
    if (list_len == 0) {
        while (list[i] != NULL) {
            free(list[i]);
            list[i] = NULL;
            i++;
        }
    }
    else {
        for (i = 0; i < list_len; i++) {
            if (list[i] != NULL) {
                free(list[i]);
                list[i] = NULL;
            }
        }
    }
    free(list);
}


#ifdef TEST
int is_even(const void* ii, size_t _) {
    const int* i = ii;
    return *i % 2 == 0;
}


void* cube(const void* ii, size_t _) {
    const int* i = ii;
    int* out = malloc(sizeof(int));
    *out = *i * *i * *i;
    return out;
}


void* sum(const void* prev, const void* elem, size_t _) {
    const int zero = 0;
    const int* p = prev ? prev : &zero;
    const int* e = elem;
    int* out = malloc(sizeof(int));
    *out = *p + *e;
    return out;
}


void test_filter_data() {
    int input[] = { 1, 2, 3, 4, 5 };
    int** output = (int**)filter_data(&is_even, input, sizeof(int), 5);
    assert(*output[0] == 2);
    assert(*output[1] == 4);
    assert(output[2] == NULL);
    free_list((ObjList)output, 0);
}


void test_map_data() {
    int input[] = { 1, 2, 3, 4, 5 };
    int** output = (int**)map_data(&cube, input, sizeof(int), 5);
    assert(*output[0] == 1);
    assert(*output[1] == 8);
    assert(*output[2] == 27);
    assert(*output[3] == 64);
    assert(*output[4] == 125);
    assert(output[5] == NULL);
    free_list((ObjList)output, 0);
}


void test_reduce_data() {
    int input[] = { 1, 2, 3, 4, 5 };
    int* output = (int*)reduce_data(&sum, input, sizeof(int), 5, 0);
    assert(*output == 15);
    free(output);
}


void test_filter() {
    int** input = malloc(sizeof(int*) * 6);
    input[0] = malloc(sizeof(int));
    input[1] = malloc(sizeof(int));
    input[2] = malloc(sizeof(int));
    input[3] = malloc(sizeof(int));
    input[4] = malloc(sizeof(int));
    input[5] = NULL;
    *input[0] = 1;
    *input[1] = 2;
    *input[2] = 3;
    *input[3] = 4;
    *input[4] = 5;
    int** output = (int**)filter(&is_even, (ObjList)input);
    assert(*output[0] == 2);
    assert(*output[1] == 4);
    assert(output[2] == NULL);
    free(output); // let next free_list() free the rest
    free_list((ObjList)input, 5);
}


void test_map() {
    int** input = malloc(sizeof(int*) * 6);
    input[0] = malloc(sizeof(int));
    input[1] = malloc(sizeof(int));
    input[2] = malloc(sizeof(int));
    input[3] = malloc(sizeof(int));
    input[4] = malloc(sizeof(int));
    input[5] = NULL;
    *input[0] = 1;
    *input[1] = 2;
    *input[2] = 3;
    *input[3] = 4;
    *input[4] = 5;
    int** output = (int**)map(&cube, (ObjList)input);
    assert(*output[0] == 1);
    assert(*output[1] == 8);
    assert(*output[2] == 27);
    assert(*output[3] == 64);
    assert(*output[4] == 125);
    assert(output[5] == NULL);
    free_list((ObjList)output, 0);
    free_list((ObjList)input, 0);
}


void test_reduce() {
    int** input = malloc(sizeof(int*) * 6);
    input[0] = malloc(sizeof(int));
    input[1] = malloc(sizeof(int));
    input[2] = malloc(sizeof(int));
    input[3] = malloc(sizeof(int));
    input[4] = malloc(sizeof(int));
    input[5] = NULL;
    *input[0] = 1;
    *input[1] = 2;
    *input[2] = 3;
    *input[3] = 4;
    *input[4] = 5;
    int* output = (int*)reduce(&sum, (ObjList)input, NULL);
    assert(*output == 15);
    free(output);
    free_list((ObjList)input, 0);
}


int main() {
    test_filter_data();
    printf("%s - \033[0;32m%s\033[0m\n", "test_filter_data", "Passed");
    test_map_data();
    printf("%s - \033[0;32m%s\033[0m\n", "test_map_data", "Passed");
    test_reduce_data();
    printf("%s - \033[0;32m%s\033[0m\n", "test_reduce_data", "Passed");
    test_filter();
    printf("%s - \033[0;32m%s\033[0m\n", "test_filter", "Passed");
    test_map();
    printf("%s - \033[0;32m%s\033[0m\n", "test_map", "Passed");
    test_reduce();
    printf("%s - \033[0;32m%s\033[0m\n", "test_reduce", "Passed");
    return 0;
}

#endif // TEST
