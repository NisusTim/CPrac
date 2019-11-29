/**
* @file    list.c
* @author  Samuel Chen
* @version V1.0.0
* @date    2018/10/31
* @brief   --
*/

#include "list.h"
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

static LIST_STATUS clear_list(void *list);
static LIST_STATUS add_item(void *list, void *item);
static LIST_STATUS add_range(void *self, void *c);
static LIST_STATUS remove_specified_item(void *list, uint16_t idx);
static LIST_STATUS remove_specified_item2(void* list, uint16_t idx);
static LIST_STATUS union_list(void *self, void *list);
static LIST_STATUS filter_list(void* self, condition func);

typedef struct ListTemplate
{
  LIST_MEMBERS(uint8_t)
}ListTemplate;

void new_list(void *self, void* item_vector, uint16_t list_cap, uint16_t item_size, char *item_type)
{
  ListTemplate *cast = (ListTemplate*)self;
  
  cast->num = 0;
  cast->capacity = list_cap;
  cast->item_size = item_size;
  cast->clear = clear_list;
  cast->add = add_item;
  cast->add_range = add_range;
  cast->remove_at = remove_specified_item2;
  cast->union_list = union_list;
  cast->filter = filter_list;
  cast->items = item_vector;
  memset((ListTemplate*)cast->items, 0, list_cap * item_size);
  strncpy(cast->item_name, item_type, ITEM_TYPE_LEN_LIMIT);
}

/**
* @brief   Removes all of the elements from this list.
*          The list will be empty after this call returns.
* 
* @param[in/out] self: Point to the current instance of the method on which it is used.
* @return        Function returns LIST_SUCCESS if this list changed as a result of the call.
*/
static LIST_STATUS clear_list(void *list)
{
  ListTemplate *cast = (ListTemplate*)list;
  cast->num = 0;

  return LIST_SUCCESS;
}

/**
* @brief   Appends the specified element to the end of this list.
* 
* @param[in/out] self: Point to the current instance of the method on which it is used.
* @param[in]     item: Element to be appended to this list.
* @return        Function returns LIST_SUCCESS if this list changed as a result of the call,
*                otherwise return the others status code.
*/
static LIST_STATUS add_item(void *self, void *item)
{
  ListTemplate *cast = (ListTemplate*)self;
  uint8_t *item_head = (uint8_t*)cast->items;
  
  if(cast->num < cast->capacity)
  {
    memcpy(item_head + cast->num * cast->item_size, item, cast->item_size);
    cast->num++;
    
    return LIST_SUCCESS;
  }
  else
  {
    return LIST_OVERRUN;
  }
}

/**
* @brief   Appends all of the elements in the specified collection to the end of this list.
* 
* @param[in/out] self: Point to the current instance of the method on which it is used.
* @param[in]     c: Collection containing elements to be added to this list
* @return        Function returns LIST_SUCCESS if this list changed as a result of the call,
*                otherwise return the others status code.
*/
static LIST_STATUS add_range(void *self, void *c)
{
  ListTemplate *cast_self = (ListTemplate*)self;
  ListTemplate *cast_c = (ListTemplate*)c;
  uint8_t *self_head = (uint8_t*)cast_self->items;
  uint8_t *c_head = (uint8_t*)cast_c->items;
  
  if(0 != strncmp(cast_self->item_name, cast_c->item_name, ITEM_TYPE_LEN_LIMIT))
  {
    return LIST_ARGUMENT_ERROR;
  }
  
  if(cast_self->capacity - cast_self->num >= cast_c->num)
  {
    memcpy(self_head + cast_self->num * cast_self->item_size, c_head, cast_c->num * cast_c->item_size);
    cast_self->num += cast_c->num;

    return LIST_SUCCESS;
  }
  else
  {
    return LIST_OVERRUN;
  }
}

/**
* @brief   Removes the element at the specified position in this list. 
*          Shifts any subsequent elements to the left(subtracts one from their indices). 
* 
* @param[in/out] self: Point to the current instance of the method on which it is used.
* @param[in]     idx: The index of the element to be removed.
* @return        Function returns LIST_SUCCESS if this list changed as a result of the call,
*                otherwise return the others status code.
*/
static LIST_STATUS remove_specified_item(void *self, uint16_t idx)
{
  ListTemplate *cast = (ListTemplate*)self;
  uint8_t *item_head = (uint8_t*)cast->items;
  
  if(idx < cast->num)
  {
    memcpy(item_head + idx * cast->item_size, item_head + (idx + 1) * cast->item_size, (cast->num - idx - 1) * cast->item_size);
    cast->num--;
    
    return LIST_SUCCESS;
  }
  else
  {
    if(0 == cast->num)
    {
      return LIST_EMPTY;
    }
    else
    {
      return LIST_OUT_OF_RANGE;
    }
  }
}

static LIST_STATUS remove_specified_item2(void* self, uint16_t idx)
{
	ListTemplate* cast = (ListTemplate*)self;
	uint8_t* item_head = (uint8_t*)cast->items;

	if (idx < cast->num)
	{
		if (idx == cast->num - 1u)
		{
			cast->num--;
		}
		else
		{
			memcpy(item_head + idx * cast->item_size, item_head + (cast->num - 1) * cast->item_size, cast->item_size);
			cast->num--;
		}

		return LIST_SUCCESS;
	}
	else
	{
		if (0 == cast->num)
		{
			return LIST_EMPTY;
		}
		else
		{
			return LIST_OUT_OF_RANGE;
		}
	}
}

/**
* @brief   Append the items from the current list and the input list with no repetitions 
*          to the currnet list.
* 
* @param[in/out] self: Point to the current instance of the method on which it is used.
* @param[in]     c: Collection containing elements to do union with this list.
* @return        Function returns LIST_SUCCESS if this list changed as a result of the call,
*                otherwise return the others status code.
*/
static LIST_STATUS union_list(void *self, void *c)
{
  ListTemplate *cast_self = (ListTemplate*)self;
  ListTemplate *cast_c = (ListTemplate*)c;
  uint16_t origin_num = cast_self->num;
  
  if(0 != strncmp(cast_self->item_name, cast_c->item_name, ITEM_TYPE_LEN_LIMIT))
  {
    return LIST_ARGUMENT_ERROR;
  }
  
  for(uint16_t i = 0; i < cast_c->num; i++)
  {
    bool find = false;
    
    for(uint16_t j = 0; j < origin_num; j++)
    {
      if(0 == memcmp(cast_c->items + (i * cast_c->item_size), 
                     cast_self->items + (j * cast_self->item_size), 
                     cast_self->item_size))
      {
        find = true;
        break;
      }
    }
    
    if(false == find)
    {
      if(cast_self->num < cast_self->capacity)
      {
        cast_self->add(cast_self, cast_c->items + i * cast_c->item_size);
      }
      else
      {
        return LIST_OVERRUN;
      }
    }
  }
  
  return LIST_SUCCESS;
}

/**
* @brief   Filter the items that satisfy the condition and shifts any subsequent elements to the left.
*
* @param[in/out] self: Point to the current instance of the method on which it is used.
* @param[in]     func: Pointer to a function to test an element for a condition.
* @return        Function returns LIST_SUCCESS if this list changed as a result of the call,
*                otherwise return the others status code.
*/
static LIST_STATUS filter_list(void* self, condition func)
{
	ListTemplate* cast_self = (ListTemplate*)self;
	uint8_t* item_head = (uint8_t*)cast_self->items;
	uint16_t idx = 0;
	
	while (idx < cast_self->num)
	{
		if (func(item_head + idx * cast_self->item_size))
		{
			cast_self->remove_at(cast_self, idx);
		}
		else
		{
			idx++;
		}
	}

	return LIST_SUCCESS;
}
