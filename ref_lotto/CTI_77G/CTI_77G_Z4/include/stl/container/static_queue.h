#ifndef STATIC_QUEUE_H_
#define STATIC_QUEUE_H_

#include <stdint.h>
#include <stdbool.h>

// #define QUEUE_MAX_ITEM_NAME 16

typedef enum {
  kQueueSuccess,    // No error.
  kQueueArgErr,     // One or more arguments are incorrect.
  kQueueOverrun,    // Queue is full.
  kQueueEmpty,      // Queue is empty.
  kQueueOutOfRange  // The index is g/equal to the capacity of queue.
} que_st;

/*
 * Static memory, circular queue for element/item of generic data type.
 *
 * Member variables and functions:
 * capacity: Maximum number of items container can hold.
 * item_size: Memory size of a single item in container.
 * queue_size: The number of items currently in container queue. (removed)
 * head: The index where item is oldest and ready to be dequeued.
 * tail: The index of the one after last one.
 *       i.e. The index of the latest item would be [tail-1].
 * Enqueue: 
 * Dequeue:
 * Clear:
 * IsEmpty:
 * IsFull:
 */
#define QUEUE_MEMBERS(item_type)                        \
  uint16_t   capacity;                                  \
  uint16_t   item_size;                                 \
  uint16_t   head;                                      \
  uint16_t   tail;                                      \
  item_type *items;                                     \
  que_st     (*Enqueue)(void *self, const void *item);  \
  que_st     (*Dequeue)(void *self, void *item);        \
  que_st     (*Clear)(void *self);                      \
  bool       (*IsEmpty)(void *self);                    \
  bool       (*IsFull)(void *self);                     \

que_st InitQueue(void *self, uint16_t capacity,
                 void *item_vector, uint16_t item_size);

#endif  // STATIC_QUEUE_H_
