#include <string.h>
#include "static_queue.h"

#define QUEUE_SIZE_BY(head, tail, capacity)      \
  ((tail-head) % capacity)

typedef struct _QueueTemplate {
  QUEUE_MEMBERS(uint8_t);
} QueueTemplate;

static que_st Enqueue(void *self, const void *item);
static que_st Dequeue(void *self, void *item);
static inline que_st Clear(void *self);
static inline bool IsEmpty(void *self);
static inline bool IsFull(void *self);

que_st InitQueue(void *self, uint16_t capacity,
                 void *item_vector, uint16_t item_size)
{
  QueueTemplate *cast = (QueueTemplate *)self;
  
  cast->capacity = capacity;
  cast->item_size = item_size;
  cast->head = 0;
  cast->tail = 0;
  cast->items = item_vector;
  cast->Enqueue = Enqueue;
  cast->Dequeue = Dequeue;
  cast->Clear = Clear;
  cast->IsEmpty = IsEmpty;
  cast->IsFull = IsFull;

  return kQueueSuccess;
}

static que_st Enqueue(void *self, const void *new_item)
{
  QueueTemplate *cast = (QueueTemplate *)self;
  uint8_t *base = (uint8_t *)cast->items;
  uint16_t tail = cast->tail;

  if (IsFull(self))
    return kQueueOverrun;

  memcpy(base + (tail * cast->item_size), new_item, cast->item_size);
  cast->tail = (tail + 1) % cast->capacity;

  return kQueueSuccess;
}

static que_st Dequeue(void *self, void *old_item)
{
  QueueTemplate *cast = (QueueTemplate *)self;
  uint8_t *base = (uint8_t *)cast->items;
  uint16_t head = cast->head;

  if (IsEmpty(self))
    return kQueueEmpty;

  if (NULL != old_item)
    memcpy(old_item, base + (head * cast->item_size), cast->item_size);
  cast->head = (head + 1) % cast->capacity;

  return kQueueSuccess;
}

static inline que_st Clear(void *self)
{
  QueueTemplate *cast = (QueueTemplate *)self;

  cast->head = 0;
  cast->tail = 0;

  return kQueueSuccess;
}

static inline bool IsEmpty(void *self)
{
  QueueTemplate *cast = (QueueTemplate *)self;
  uint16_t head = cast->head;
  uint16_t tail = cast->tail;

  return head == tail;
}

static inline bool IsFull(void *self)
{
  QueueTemplate *cast = (QueueTemplate *)self;
  uint16_t head = cast->head;
  uint16_t tail = cast->tail;
  uint16_t capacity = cast->capacity;

  return (cast->capacity - 1) == QUEUE_SIZE_BY(head, tail, capacity);
}
