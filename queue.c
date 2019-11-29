/**
 * @file    queue.h
 * @author  Samuel Chen
 * @version V1.0.0
 * @date    2019/10/08
 * @brief   --
 */

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "queue.h"

typedef struct QueueTemplate
{
	QUEUE_MEMBERS(uint8_t)
} QueueTemplate;

static bool is_full(void* self);

static void* dequeue(void* self);
static void enqueue(void* self, void* item);
static void clear(void* self);
static bool is_empty(void* self);
static bool is_full(void* self);

void new_queue(void *self, void* item_vector, uint16_t list_cap, uint16_t item_size, char *item_type)
{
	QueueTemplate *cast = (QueueTemplate*) self;

	cast->num = 0;
	cast->tail = 0;
	cast->head = list_cap - 1;
	cast->capacity = list_cap;
	cast->item_size = item_size;
	cast->items = item_vector;
	cast->enqueue = enqueue;
	cast->dequeue = dequeue;
	cast->clear = clear;
	cast->is_full = is_full;
	cast->is_empty = is_empty;

	strncpy(cast->item_name, item_type, QUEUE_MAX_ITEM_NAME);
}

static bool is_full(void* self)
{
	QueueTemplate *cast = (QueueTemplate*) self;

	return cast->num == cast->capacity;
}

static bool is_empty(void* self)
{
	QueueTemplate *cast = (QueueTemplate*) self;

	return cast->num == cast->capacity;
}

static void enqueue(void* self, void* item)
{
	QueueTemplate *cast = (QueueTemplate*) self;
	uint8_t* item_head = (uint8_t*) cast->items;

	if (!is_full(self))
	{
		return;
	}
	else
	{
		cast->tail = (cast->tail + 1) % cast->capacity;
		memcpy(item_head + cast->tail * cast->item_size, item, cast->item_size);
		cast->num++;
	}
}

static void* dequeue(void* self)
{
	QueueTemplate *cast = (QueueTemplate*) self;
	uint8_t* item_head = (uint8_t*) cast->items;
	uint8_t* item_pop = NULL;

	if (is_empty(self))
	{
		return NULL;
	}
	else
	{
		item_pop = item_head + cast->head * cast->item_size;
		cast->head = (cast->head + 1) % cast->capacity;
		cast->num--;

		return item_pop;
	}
}

static void clear(void* self)
{
	QueueTemplate *cast = (QueueTemplate*) self;

	cast->num = 0;
	cast->tail = 0;
	cast->head = cast->capacity - 1;
}

