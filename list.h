/**
* @file    list.h
* @author  Samuel Chen
* @version V1.1.0
* @date    2019/05/15
* @brief   --
*/

#ifndef __LIST_H
#define __LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define ITEM_TYPE_LEN_LIMIT	16

typedef enum
{
  LIST_SUCCESS,         /**< No error. */
  LIST_ARGUMENT_ERROR,  /**< One or more arguments are incorrect. */
  LIST_OVERRUN,         /**< List is full. */
  LIST_EMPTY,           /**< List is empty. */
  LIST_OUT_OF_RANGE     /**< The index is greater than or equal to the number of items. */
}LIST_STATUS;

typedef bool (*condition)(void* item);	/**< Pointer to a function to test an element for a condition. */

/**
* @brief Property and method in list object.
*
*  capacity: The total number of elements the list can hold.
*  item_name: The name of elements contained in the list.
*  item_size: The size of elements contained in the list.
*  num: The number of elements contained in the list.
*  add: Appends the specified element to the end of this list.
*  add_range: Appends all of the elements in the specified collection to the end of this list.
*  remove_at: Removes the element at the specified position in this list.
*  union_list: Append the items from the current list and the input list with no repetitions to the currnet list.
*  filter: Filter the items that satisfy the condition and shifts any subsequent elements to the left.
*  clear: Removes all of the elements from this list.
*  items: The elements container for this list.
*/
#define LIST_MEMBERS(item_type)							\
  uint16_t capacity;                                    \
  char item_name[ITEM_TYPE_LEN_LIMIT];                  \
  uint16_t item_size;                                   \
  uint16_t num;                                         \
  LIST_STATUS (*add)(void *self, void *item);           \
  LIST_STATUS (*add_range)(void *self, void *list);     \
  LIST_STATUS (*remove_at)(void *self, uint16_t idx);   \
  LIST_STATUS (*union_list)(void *self, void *list);    \
  LIST_STATUS (*filter)(void *self, condition func);	\
  LIST_STATUS (*clear)(void *self);                     \
  item_type* items;                              
    
void new_list(void* self, void* item_vector, uint16_t list_cap, uint16_t item_size, char* item_type);
  
#ifdef __cplusplus
}
#endif

#endif /* __LIST_H */
