# Libfunctools
Functional Programming C Library

## Introduction
This library has a few functions useful for functional programming in C. All of the functions in this library are pure functions, and they do not mutate their inputs. All data in the outputs of these functions are allocated on the heap and copied from the inputs. The user must free the output objects of these functions.

The library groups the functions into three categories: Functions that
operate on arrays, functions that operate on lists of objects, and functions
that operate on strings.

## Building
This module uses a simple Makefile to build the library. The Makefile has the
following targets:
- `help`: Prints the help message.
- `all`: Builds the library and runs the tests.
- `build/libfunctools.so`: Builds the library.
- `test`: Runs the tests.
- `clean`: Removes the build directory.

To build the library, run `make all` in the project’s root directory. It
will build the object files, run the tests, and build the library. The software library
will be at `build/libfunctools.so`.


## Functions that Operate on Arrays
These functions operate on arrays of data elements of fixed size, such as an
array of structs or an array of integers. They produce a list of objects
(map and filter) or a single object (reduce).
### `map_data`
```c
ObjList map_data(MapDataFn fn, const void* input, size_t el_len, size_t el_count);
```
This function maps a function over an array of elements.

#### Parameters
- `fn`: The function to map over the array.
- `input`: The array to map over.
- `el_len`: The length of each element in the array.
- `el_count`: The number of elements in the array.

#### Return Value
A pointer to the mapped array.

#### Example
```c
void* cube(const void* ii, size_t _) {
    const int* i = ii;
    int* out = malloc(sizeof(int));
    *out = *i * *i * *i;
    return out;
}

int main() {
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
```

### `filter`
```c
ObjList filter_data(FilterDataFn fn, const void* input, size_t el_len, size_t el_count);
```
Filters an array of elements.

#### Parameters
- `fn`: The function to filter the array.
- `input`: The array to filter.
- `el_len`: The length of each element in the array.
- `el_count`: The number of elements in the array.

#### Return Value
A pointer to the filtered array.

#### Example
```c
int is_even(const void* ii, size_t _) {
    const int* i = ii;
    return *i % 2 == 0;
}

int main() {
    int input[] = { 1, 2, 3, 4, 5 };
    int** output = (int**)filter_data(&is_even, input, sizeof(int), 5);
    assert(*output[0] == 2);
    assert(*output[1] == 4);
    assert(output[2] == NULL);
    free_list((ObjList)output, 0);
}
```

### `reduce`
```c
void* reduce(ReduceFn fn, const void* input, size_t el_len, size_t el_count, const void* init);
```
This function reduces an array of elements.

#### Parameters
- `fn`: The function to reduce the array.
- `input`: The array to reduce.
- `el_len`: The length of each element in the array.
- `el_count`: The number of elements in the array.
- `init`: The initial value to reduce with.

#### Return Value
A pointer to the reduced value.

#### Example
```c
void* sum(const void* prev, const void* elem, size_t _) {
    const int zero = 0;
    const int* p = prev ? prev : &zero;
    const int* e = elem;
    int* out = malloc(sizeof(int));
    *out = *p + *e;
    return out;
}

int main() {
    int input[] = { 1, 2, 3, 4, 5 };
    int* output = (int*)reduce_data(&sum, input, sizeof(int), 5, 0);
    assert(*output == 15);
    free(output);
}
```

### `free_list`
```c
void free_list(void** list);
```
This function frees a list of objects. It frees all objects in the list as well.

#### Parameters
- `list`: The list to free.

#### Return Value
None.

#### Example
```c
int main() {
    int* a = malloc(sizeof(int));
    int* b = malloc(sizeof(int));
    int* c = malloc(sizeof(int));
    int** list = malloc(sizeof(int*) * 4);
    list[0] = a;
    list[1] = b;
    list[2] = c;
    list[3] = NULL;
    free_list((void**)list);
    return 0;
}
```

## Functions that Operate on Lists of Objects
These functions operate on lists of objects. They produce a list of objects (map and filter) or a single object (reduce).

### `map`
```c
ObjList map(MapDataFn fn, ObjList input);
```
This function maps a function over a list of objects.

#### Parameters
- `fn`: The function to map over the list.
- `input`: The list to map over.

#### Return Value
A pointer to the mapped list.

#### Example
```c
void* cube(const void* ii, size_t _) {
    const int* i = ii;
    int* out = malloc(sizeof(int));
    *out = *i * *i * *i;
    return out;
}

int main() {
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
    free(output); // let next free_list() free the rest
    free_list((ObjList)input, 5);
}
```

### `filter`
```c
ObjList filter(FilterDataFn fn, ObjList input);
```
This function filters a list of objects.

#### Parameters
- `fn`: The function to filter the list.
- `input`: The list to filter.

#### Return Value
A pointer to the filtered list.

#### Example
```c
int is_even(const void* ii, size_t _) {
    const int* i = ii;
    return *i % 2 == 0;
}

int main() {
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
```

### `reduce`
```c
void* reduce(ReduceFn fn, ObjList input, void* init);
```
This function reduces a list of objects.

#### Parameters
- `fn`: The function to reduce the list.
- `input`: The list to reduce.
- `init`: The initial value to reduce with.

#### Return Value
A pointer to the reduced value.

#### Example
```c
void* sum(const void* prev, const void* elem, size_t _) {
    const int zero = 0;
    const int* p = prev ? prev : &zero;
    const int* e = elem;
    int* out = malloc(sizeof(int));
    *out = *p + *e;
    return out;
}

int main() {
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
    free_list((ObjList)input, 5);
}
```


## Functions that Operate on Strings
These functions operate on strings, represented as a pointer to a null-terminated array of characters. They produce a string (join) or a list of strings (split).


### `str_join`
```c
char* str_join(const char** list, const char* sep);
```
This function joins a list of strings with a separator.

#### Parameters
- `list`: The list of strings to join.
- `sep`: The separator to join the strings with.

#### Return Value
A pointer to the joined string.

#### Example
```c
int main() {
    const char* list[] = { "Hello", "World", "!" };
    char* output = str_join(list, " ");
    assert(strcmp(output, "Hello World !") == 0);
    free(output);
    return 0;
}
```

### `str_split`
```c
char** str_split(const char* str, const char* sep);
```
This function splits a string into a list of strings with a separator.

#### Parameters
- `str`: The string to split.
- `sep`: The separator to split the string with.

#### Return Value
A pointer to the list of strings.

#### Example
```c
int main() {
    const char* input = "Hello World !";
    char** output = str_split(input, " ");
    assert(strcmp(output[0], "Hello") == 0);
    assert(strcmp(output[1], "World") == 0);
    assert(strcmp(output[2], "!") == 0);
    assert(output[3] == NULL);
    free_list((void**)output, 0);
    return 0;
}
```
