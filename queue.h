/**
* @file    queue.h
* @author  Samuel Chen
* @version V1.0.0
* @date    2019/10/08
* @brief   --
*/

#ifndef __QUEUE_H
#define __QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define QUEUE_MAX_ITEM_NAME	16

/**
* @brief Property and method in list object.
*
*  capacity: The total number of elements the list can hold.
*  item_name: The name of elements contained in the list.
*  item_size: The size of elements contained in the list.
*  num: The number of elements contained in the list.
*  clear: Removes all of the elements from this list.
*  items: The elements container for this list.
*/
#define QUEUE_MEMBERS(item_type)						\
  uint16_t capacity;                                    \
  char item_name[QUEUE_MAX_ITEM_NAME];                  \
  uint16_t item_size;                                   \
  uint16_t num;                                         \
  uint16_t tail;										\
  uint16_t head;										\
  void (*enqueue)(void *self, void *item);				\
  void* (*dequeue)(void *self);							\
  void (*clear)(void* self);							\
  bool (*is_full)(void* self);							\
  bool (*is_empty)(void* self);							\
  item_type* items;

void new_queue(void* self, void* item_vector, uint16_t list_cap, uint16_t item_size, char* item_type);

#ifdef __cplusplus
}
#endif

#endif /* __QUEUE_H */
