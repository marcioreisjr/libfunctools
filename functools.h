/**
 * @brief A collection of functional programming tools.
 * @details This file contains a collection of functional programming tools
 * that can be used to filter, map and reduce arrays of objects.
 * @date 2024-01-20
 * @author Marcio Reis Jr.
 *
 * This code is released under the GPLv2.1 license. Refer to the LICENSE file
 * for more information.
 */
#include <stdlib.h>

/**
 * A list of objects.
 */
typedef void** ObjList;

/**
 * Function type for filtering.
 *
 * @param index The index of the current element.
 * @param elem The current element.
 * @return 1 if the element should be included, 0 otherwise.
 */
typedef int (*FilterDataFn)(const void*, size_t index);

/**
 * Function type for mapping.
 *
 * @param elem The current element.
 * @param index The index of the current element.
 * @return A pointer to the mapped element.
 */
typedef void* (*MapDataFn)(const void*, size_t index);

/**
 * Function type for reducing.
 *
 * @param prev The previous value of the accumulator.
 * @param elem The current element.
 * @param index The index of the current element.
 * @return A pointer to the reduced value.
 */
typedef void* (*ReduceDataFn)(const void* prev, const void* elem, size_t index);

/**
 * Filter an array of elements.
 *
 * @param fn The filter function. Must return 1 for true, 0 for false.
 * @param input The input array.
 * @param el_len The length of each element.
 * @param el_count The number of elements.
 * @return A pointer to the filtered array of objects. The last element is NULL.
 *
 * @note The returned array must be freed by the caller with free_list().
 */
ObjList filter_data(
    FilterDataFn fn, const void* input, size_t el_len, size_t el_count);


/**
 * Map an array of elements.
 *
 * @param fn The map function. Must return a pointer to the mapped element,
 *  which will be copied into the output array.
 * @param input The input array.
 * @param el_len The length of each element.
 * @param el_count The number of elements.
 * @return A pointer to the mapped array of objects. The last element is NULL.
 *
 * @note The returned array must be freed by the caller with free_list().
 */
ObjList map_data(
    MapDataFn fn, const void* input, size_t el_len, size_t el_count);


/**
 * Reduce an array of elements.
 *
 * @param fn The reduce function. Must return a pointer to the reduced value.
 * @param input The input array.
 * @param el_len The length of each element.
 * @param el_count The number of elements.
 * @param init The initial value of the accumulator.
 * @return A pointer to the reduced value.
 *
 * @note The returned value must be freed by the caller.
 */
void* reduce_data(ReduceDataFn fn, const void* input, size_t el_len,
    size_t el_count, void* init);


/**
 * Filter an array of elements.
 *
 * @param fn The filter function. Must return 1 for true, 0 for false.
 * @param input The input array.
 * @return A pointer to the filtered array of objects. The last element is NULL.
 *
 * @note The returned array must be freed by the caller with free_list().
*/
ObjList filter(FilterDataFn fn, ObjList input);


/**
 * Map an array of elements.
 *
 * @param fn The map function. Must return a pointer to the mapped element,
 * which will be copied into the output array.
 * @param input The input array.
 * @return A pointer to the mapped array of objects. The last element is NULL.
 *
 * @note The returned array must be freed by the caller with free_list().
 */
ObjList map(MapDataFn fn, ObjList input);


/**
 * Reduce an array of elements.
 *
 * @param fn The reduce function. Must return a pointer to the reduced value.
 * @param input The input array.
 * @param init The initial value of the accumulator.
 * @return A pointer to the reduced value.
 *
 * @note The returned value must be freed by the caller.
 */
void* reduce(ReduceDataFn fn, ObjList input, void* init);


/**
 * Free a list of objects and the inner objects.
 *
 * @param list The list of objects.
 * @param list_len Optional length of the list. Set to zero to free a NULL
 * terminated list. If list_len is set to a non-zero value, the list will be
 * freed up to the specified length, skipping the NULL objects.
 */
void free_list(void** list, size_t list_len);
